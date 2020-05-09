using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MySql.Data.MySqlClient;
using System.Data;

namespace BeneJudgmentService
{
    public enum NetCoreRetCode		//返回值错误码,成功或可继续执行返回>=0,失败返回<0
    {
        //-1 ~ -20
        Fail = -1,					//操作失败
        InvalidParam = -2,			//无效参数
        UnknownReq = -3,			//未知请求
        UnAuth = -4,				//未授权
        ServerError = -5,			//服务器错误
        InvalidReq = -6,			//无效请求
        NoPrivilege = -7,			//无权限
        // -21 ~ -41: Data Upload Error
        DataLocked = -21,			//数据锁定
        DataExisted = -22,			//数据已存在
        DataUploadFailed = -23,		//数据上传失败
        DiskIsFull = -24,			//数据已满
        DataInconformity = -25,		//数据不一致
        DataNotExisted = -26,		//数据不存在
        NullDataFile = -27,			//无效的数据文件
        TooMuchUpload = -28,		//单个用户过多的上传线程
        DataCompleted = -29,		//数据已经上传完成无需继续
        TooMuchDownload = -30,		//单个用户过多的下载线程
        FileNotExisted = -31,		//文件不存在
        FileOverflow = -32,			//文件上传或位置超过文件大小
        UserOrPasswordError = -33,  //用户名或密码错误
        ClientNotMatch = -34,		//客户端与用户类型不匹配
        UserLocked = -35,			//用户帐户被锁定
        Success = 0,				//操作成功
        False = 1,					//操作非完全成功,但可以继续执行
        DataUploding = 2,			//数据正在上传
    };

	public class ReportInfo
	{
		public string ID { get; set; }
		public string DocName { get; set; }
		public string DocAccount { get; set; }
		public string RoleID { get; set; }
		public string RecordID { get; set; }
		public string DGSResult { get; set; }
        public string AlyTimeSpan { get; set; }
        public DateTime UploadTime { get; set; }
		public int Status { get; set; }
	}

    public class CompareInfo
    {
        public string DocAccount { get; set; }
        public string RecordID { get; set; }
        public string CompareResult { get; set; }
        public Double Score { get; set; }
        public int Status { get; set; }
    }
	public enum BPNP_Hospital_Flag
	{
		HomeHolterAly = 0x01,		//支持HomeHolter的分析
		HomeHolterAgent = 0x02,		//HomeHolter操作员代理医院
	}
	public enum BPNP_DataInfo_SuplStatus
	{
		Null = -1,				//默认的状态
		Downloading = 0,		//正在下载
		Downladed = 1,			//下载完毕
		Uploading = 2,			//正在上传
		Uploaded = 3,			//上传完毕
	}
	public enum ReportStatus
	{
		Uploading = 0,			//上传中
		Uploaded = 1			//已上传
	}
	public class MySqlDbManagerBase : IDisposable
	{
		protected MySqlConnection connection;
		private bool isDisposed = false;
		public MySqlDbManagerBase(string connectionText)
		{
			UpdateConnectionSetting(connectionText);
		}
		public virtual bool UpdateConnectionSetting(string connectionString)
		{
			try
			{
				connection = new MySqlConnection(connectionString);
				return true;
			}
			catch (Exception ex)
			{
				connection = null;
				Logger.Error("UpdateConnectionSetting");
				Logger.Error(ex.Message);
				return false;
			}
		}
		public static string MakeConnectionSetting(string address, string userName, string password, string database)
		{
			string connectionString;
			connectionString = "SERVER=" + address + ";" + "DATABASE=" + database + ";" + "UID=" + userName + ";" + "PASSWORD=" +
				password + ";" + "charset=utf8;AllowZeroDateTime=true;ConvertZeroDateTime=true;Pooling=true;";
			return connectionString;
		}
		public virtual MySqlConnection OpenConnection()
		{
			if (connection == null)
				return null;
			try
			{
				connection.Open();
				return connection;
			}
			catch (Exception ex)
			{
				Logger.Error("OpenConnection");
				Logger.Error(ex.Message);
				return null;
			}
		}
		protected virtual bool CloseConnection()
		{
			if (connection == null)
				return true;
			try
			{
				connection.Close();
				return true;
			}
			catch (Exception ex)
			{
				Logger.Error("CloseConnection");
				Logger.Error(ex.Message);
				return false;
			}
		}
		protected virtual void Dispose(bool disposing)
		{
			if (isDisposed)
				return; //如果已经被回收，就中断执行
			if (disposing)
			{
				CloseConnection();
			}
			//TODO:释放非托管资源，设置对象为null
			isDisposed = true;
		}
		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}
		~MySqlDbManagerBase()
		{
			Dispose(false);
		}
	}
	public class DatabaseHelper
	{
		public delegate bool PrcocessDBFunction(MySqlCommand cmd, ref NetCoreRetCode rc);
		public delegate void PrcocessDBFunctionSimple(MySqlCommand cmd);
		public delegate int PrcocessDBCheckFunc();
		public delegate int PrcocessDBCheckFuncEx(MySqlCommand cmd);
		protected string mySqlConnectionText = null;
		public string lastErrorMsg;
		protected void ProcessException(MySqlCommand cmd, Exception ex, string functionName)
		{
			Logger.Error(functionName);
			lastErrorMsg = ex.Message;
			Logger.Error(lastErrorMsg);
			Logger.Error(cmd.CommandText);
			if (cmd.Transaction != null)
				cmd.Transaction.Rollback();
		}
		protected NetCoreRetCode DBFramewrokImp(string cmdText, string funcName, PrcocessDBFunction func,
												bool bUseTransaction, IsolationLevel isoLevel,
												PrcocessDBFunctionSimple afterFunc)
		{
			lastErrorMsg = string.Empty;
			if (string.IsNullOrEmpty(mySqlConnectionText))
				return NetCoreRetCode.InvalidParam;
			NetCoreRetCode retCode = NetCoreRetCode.Fail;
			using (MySqlDbManagerBase db = new MySqlDbManagerBase(mySqlConnectionText))
			{
				MySqlConnection connection = db.OpenConnection();
				if (connection != null)
				{
					using (MySqlCommand cmd = new MySqlCommand(cmdText, connection))
					{
						if (bUseTransaction)
						{
							using (MySqlTransaction myTransaction = connection.BeginTransaction(isoLevel))
							{
								cmd.Transaction = myTransaction;
								try
								{
									if (func(cmd, ref retCode))
										myTransaction.Commit();
									else
										myTransaction.Rollback();
									if (retCode == NetCoreRetCode.Fail)
										retCode = NetCoreRetCode.Success;
									if (retCode == NetCoreRetCode.Success &&
										afterFunc != null)
										afterFunc(cmd);
								}
								catch (Exception ex)
								{
									ProcessException(cmd, ex, funcName);
									retCode = NetCoreRetCode.ServerError;
								}
							}
						}
						else
						{
							try
							{
								func(cmd, ref retCode);
								if (retCode == NetCoreRetCode.Fail)
									retCode = NetCoreRetCode.Success;
								if (retCode == NetCoreRetCode.Success &&
									afterFunc != null)
									afterFunc(cmd);
							}
							catch (Exception ex)
							{
								ProcessException(cmd, ex, funcName);
								retCode = NetCoreRetCode.ServerError;
							}
						}
					}
				}
				else
					retCode = NetCoreRetCode.ServerError;
			}
			return retCode;
		}
		protected NetCoreRetCode DBCommonFramewrok(string cmdText, string funcName, PrcocessDBFunction func)
		{
			return DBFramewrokImp(cmdText, funcName, func, false, IsolationLevel.ReadCommitted, null);
		}
		protected NetCoreRetCode DBTransactionFramewrok(string cmdText, string funcName, PrcocessDBFunction func, PrcocessDBFunctionSimple afterCommit)
		{
			return DBFramewrokImp(cmdText, funcName, func, true, IsolationLevel.ReadCommitted, afterCommit);
		}
		protected NetCoreRetCode DBTransactionFramewrok(string cmdText, string funcName, PrcocessDBFunction func)
		{
			return DBFramewrokImp(cmdText, funcName, func, true, IsolationLevel.ReadCommitted, null);
		}
		protected NetCoreRetCode DBIsoSerializableTransactionFramewrok(string cmdText, string funcName, PrcocessDBFunction func)
		{
			return DBFramewrokImp(cmdText, funcName, func, true, IsolationLevel.Serializable, null);
		}
	}
	public class JudgmentDatabaseManager : DatabaseHelper
	{
		public JudgmentDatabaseManager(string address,string user,string password)
		{
			UpdateSetting(address, user, password);
		}
		public void UpdateSetting(string address, string user, string password)
		{
			mySqlConnectionText = MySqlDbManagerBase.MakeConnectionSetting(
									address,
									user,
									password,
									"bene_judgment_service");
		}
        public bool QueryReportInfo(string DocAccount, string RecordID, out ReportInfo reportInfo)
		{
            reportInfo = null;
			string sql;
            sql = string.Format("SELECT * FROM bene_report WHERE DocAccount='{0}' AND RecordID='{1}'", DocAccount,RecordID);
            ReportInfo findReportInfo = null;
			PrcocessDBFunction core1 = (MySqlCommand cmd, ref NetCoreRetCode rc) =>
			{
				MySqlDataReader dataReader = cmd.ExecuteReader();
				int uploadTime = dataReader.GetOrdinal("UploadTime");
				//Read the data and store them in the list
				while (dataReader.Read())
				{
                    findReportInfo = new ReportInfo();
                    findReportInfo.ID = dataReader.GetString("ID");
                    findReportInfo.DocName = dataReader.GetString("DocName");
                    findReportInfo.DocAccount = dataReader.GetString("DocAccount");
                    findReportInfo.RoleID = dataReader.GetString("RoleID");
                    findReportInfo.RecordID = dataReader.GetString("RecordID");
                    findReportInfo.DGSResult = dataReader.GetString("DGSResult");
                    findReportInfo.AlyTimeSpan = dataReader.GetString("AlyTimeSpan");
                    findReportInfo.Status = dataReader.GetInt32("Status");
                    if (!dataReader.IsDBNull(uploadTime))
                        findReportInfo.UploadTime = dataReader.GetDateTime(uploadTime);
                    else
                        findReportInfo.UploadTime = DateTime.MinValue;
					break;
				}
				//close Data Reader
				dataReader.Close();
				return true;
			};
            DBCommonFramewrok(sql, "QueryReportInfo", core1);
            reportInfo = findReportInfo;
            return reportInfo != null;
		}
        public bool InsertReportInfo(ReportInfo reportInfo)
		{
			bool success = false;
			string sql;
			sql = "INSERT INTO bene_report (DocName, DocAccount,RoleID,RecordID,DGSResult,AlyTimeSpan,UploadTime,Status) "+
                "VALUES (@name, @da, @roi, @rei, @dgs, @ats, @ut, @st)";
			//Logger.Debug(string.Format("UHHRS SQL={0}", sql));
			PrcocessDBFunction core = (MySqlCommand cmd, ref NetCoreRetCode rc) =>
			{
                cmd.Parameters.AddWithValue("@name", reportInfo.DocName);
                cmd.Parameters.AddWithValue("@da", reportInfo.DocAccount);
                cmd.Parameters.AddWithValue("@roi", reportInfo.RoleID);
                cmd.Parameters.AddWithValue("@rei", reportInfo.RecordID);
                cmd.Parameters.AddWithValue("@dgs", reportInfo.DGSResult);
                cmd.Parameters.AddWithValue("@ats", reportInfo.AlyTimeSpan);
                cmd.Parameters.AddWithValue("@ut", reportInfo.UploadTime);
                cmd.Parameters.AddWithValue("@st", reportInfo.Status);
				if (cmd.ExecuteNonQuery() > 0)
					success = true;
				return true;
			};
            DBTransactionFramewrok(sql, "InsertReportInfo", core);
			return success;
		}
        public bool UpdateReportInfo(ReportInfo reportInfo)
        {
            bool success = false;
            string sql = "UPDATE bene_report SET " +
                        "DGSResult = @dgs, AlyTimeSpan = @ats, Status = @st, " +
                        "UploadTime = @ut " +
                        "WHERE DocAccount = @da AND RecordID = @rei";
            //Logger.Debug(string.Format("UHHRS SQL={0}", sql));
            PrcocessDBFunction core1 = (MySqlCommand cmd, ref NetCoreRetCode rc) =>
            {
                cmd.Parameters.AddWithValue("@dgs", reportInfo.DGSResult);
                cmd.Parameters.AddWithValue("@ats", reportInfo.AlyTimeSpan);
                cmd.Parameters.AddWithValue("@st", reportInfo.Status);
                cmd.Parameters.AddWithValue("@ut", DateTime.Now);
                cmd.Parameters.AddWithValue("@da", reportInfo.DocAccount);
                cmd.Parameters.AddWithValue("@rei", reportInfo.RecordID);
                if (cmd.ExecuteNonQuery() > 0)
                    success = true;
                return true;
            };
            DBTransactionFramewrok(sql, "UpdateReportInfo", core1);
            return success;
        }
        public bool UpdateCompareInfo(CompareInfo compareInfo)
        {
            bool success = false;
            string sql = "UPDATE bene_report SET " +
                        "CompareResult = @cr, Score = @sc, " +
                        "Status = @st " +
                        "WHERE DocAccount = @da AND RecordID = @rei";
            //Logger.Debug(string.Format("UHHRS SQL={0}", sql));
            PrcocessDBFunction core1 = (MySqlCommand cmd, ref NetCoreRetCode rc) =>
            {
                cmd.Parameters.AddWithValue("@cr", compareInfo.CompareResult);
                cmd.Parameters.AddWithValue("@sc", compareInfo.Score);
                cmd.Parameters.AddWithValue("@st", compareInfo.Status);
                cmd.Parameters.AddWithValue("@da", compareInfo.DocAccount);
                cmd.Parameters.AddWithValue("@rei", compareInfo.RecordID);
                if (cmd.ExecuteNonQuery() > 0)
                    success = true;
                return true;
            };
            DBTransactionFramewrok(sql, "UpdateCompareInfo", core1);
            return success;
        }
	}
}
