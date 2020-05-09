using NHttp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.IO;
using Newtonsoft.Json;
using System.Text.RegularExpressions;
using System.Collections.Specialized;
using Newtonsoft.Json.Bson;
using System.Runtime.InteropServices;

namespace BeneJudgmentService
{
    enum RoleType
    {
        Judgment = 0,
        AlyDoc = 1,
    }
    public class NotifyCommon
    {
        public string RemotAddress;
        public NotifyCommon()
        {
            RemotAddress = null;
        }
    }

    public class UploadResultInfo
    {
        public string Account;
        public string Name;
        public int    RoleID;
        public string RecordID;
        public string DGSResult;
        public string AlyTimeSpan;
        public string FileName;
        public byte[] FileData;
        public UploadResultInfo()
        {
            Account = null;
            Name = null;
            RoleID = 0;
            RecordID = null;
            DGSResult = null;
            AlyTimeSpan = null;
            FileName = null;
        }
    }

    public class NotifyResult
    {
        public int RepCode;
        public string Message;
        public NotifyResult()
        {
            RepCode = -1;
            Message = null;
        }
    }

    public class UploadResultPara
    {
         public  string strAccount;
         public  string strName;
         public  int    iRoleID;
         public  string strRecordID;
         public  string strDGSResult;
         public  string strAlyTimeSpan;
         public UploadResultPara()
         {
             strAccount = null;
             strName = null;
             iRoleID = 0;
             strRecordID = null;
             strDGSResult = null;
             strAlyTimeSpan = null;
         }
    }

    class BeneServiceSetting
    {
        public string Host;
        public string Account;
        public string Password;
        public BeneServiceSetting()
        {
            Host = "127.0.0.1";
            Account = "root";
            Password = "123456";
        }
    }

    class ComparePara
    {
        public string test;
        public string std;
        public string appdir;
        public ComparePara()
        {
            test = null;
            std = null;
        }
        public bool CheckFilePath()
        {
            bool bRet = true;
            if (File.Exists(test) == false)
            {
                string strError = string.Format("File: {0}  is not Exist!",test);
                Logger.Error(strError);
                bRet = false;
            }
            if (File.Exists(std) == false)
            {
                string strError = string.Format("File: {0}  is not Exist!",test);
                Logger.Error(strError);
                bRet = false;
            }
            return bRet;
        }
    }

    class CompareThread
    {
        public Thread ts;
        private string strJsonInput = null;
        private ReportInfo reportInfo = null;
        private JudgmentDatabaseManager _dbManager = null;
        private readonly object CompareLock = new object();
        [DllImport(@"compare.dll")]
        public static extern IntPtr Compare(ref byte str);
        public CompareThread(ref string strJson,ref ReportInfo rptInfo, ref JudgmentDatabaseManager db)
        {
            ts = new Thread(new ThreadStart(this.run));
            strJsonInput = strJson;
            reportInfo = rptInfo;
            _dbManager = db;
            ts.Start();
        }
        void run()
        {
            //work
            lock (CompareLock)
            {
                try
                {
                    byte[] byteArray = Encoding.UTF8.GetBytes(strJsonInput);
                    IntPtr pRet = Compare(ref byteArray[0]);
                    string strRet = Marshal.PtrToStringAnsi(pRet);
                    Logger.Info(strRet);
                    CompareInfo _info = new CompareInfo();
                    _info.DocAccount = reportInfo.DocAccount;
                    _info.RecordID = reportInfo.RecordID;
                    _info.Score = 0;
                    _info.Status = 2;
                    _info.CompareResult = strRet;
                    _dbManager.UpdateCompareInfo(_info);
                }
                catch (Exception e)
                {
                    Logger.Error(e.Message);
                }
            }
        }
    }

    class ServiceManager
    {
        private ManualResetEvent manualResetEvent = new ManualResetEvent(false);
        private Mutex mutex = new Mutex();
        Thread httpTs;
        private string strDGSResultDataDir = null;
        private string strJudgmentDataDir = null;
        private string strAppPath = null;
        private JudgmentDatabaseManager _dbManager = null;
        private SettingManager _settingManager = null;
        public void RunService()
        {
            Logger.Info("Service Start!");
            InitService();
            string jsonFileDir = Path.Combine(strAppPath,"SettingConfig.json");
            _settingManager = new SettingManager(ref jsonFileDir);
            BeneServiceSetting _setting = _settingManager.serviceSetting;
            _dbManager = new JudgmentDatabaseManager(_setting.Host, _setting.Account, _setting.Password);
            httpTs = new Thread(new ThreadStart(WebServiceThreadProc));
            httpTs.IsBackground = true;
            httpTs.Start();
        }

        public int RunConsole(string[] args)
        {
            RunService();
            Console.ReadKey();
            StopService();
            return 0;
        }

        public void StopService()
        {
            manualResetEvent.Set();
            httpTs.Join();
            Console.WriteLine("WebService Host Stop!");
            //manualResetEvent.Dispose();
            Console.WriteLine("Service Stop");
            Logger.Info("Service Stop!");
            Thread.Sleep(2000);
            System.Diagnostics.Process.GetCurrentProcess().Kill();
        }

        private static byte[] StreamToBytes(Stream stream)
        {
            byte[] bytes = new byte[stream.Length];
            stream.Read(bytes, 0, bytes.Length);
            // 设置当前流的位置为流的开始
            stream.Seek(0, SeekOrigin.Begin);
            return bytes;
        }

        private void WebServiceThreadProc()
        {
            HostService(manualResetEvent);
        }

        private static T InputStreamToBson<T>(Stream stream)
        {
            using (BsonReader reader = new BsonReader(stream))
            {
                JsonSerializer serializer = new JsonSerializer();
                return serializer.Deserialize<T>(reader);
            }
        }

        private static string BsonToBase64String(Object e)
        {
            MemoryStream ms = new MemoryStream();
            using (BsonWriter writer = new BsonWriter(ms))
            {
                JsonSerializer serializer = new JsonSerializer();
                serializer.Serialize(writer, e);
            }
            string data = Convert.ToBase64String(ms.ToArray());
            return data;
        }

        private void InitService()
        {
            strAppPath = AppDomain.CurrentDomain.BaseDirectory;
            strJudgmentDataDir = Path.Combine(strAppPath, "Judgment");
            strDGSResultDataDir =Path.Combine(strAppPath, "DGSResult");
            CheckDataDir(strJudgmentDataDir);
            CheckDataDir(strDGSResultDataDir);
        }

        //检查文件夹，如果不存在，就创建对应的文件夹
        private void CheckDataDir(string strPath)
        {
            if (Directory.Exists(strPath) == false)
            {
                Directory.CreateDirectory(strPath);
            }
        }

        private string CalcTimeSpan(string last,string now)
        {
            string strCalc = null;
            if (last == null) last = "0.00:00:00";
            if (now == null) now = "0.00:00:00";
            TimeSpan A = TimeSpan.Parse(last);
            TimeSpan B = TimeSpan.Parse(now);
            TimeSpan C = A + B;
            strCalc = string.Format("{0}.{1}:{2}:{3}", C.Days, C.Hours, C.Minutes, C.Seconds);
            return strCalc;
        }

        public void HostService(ManualResetEvent resetEvent)
        {
            using (var server = new HttpServer())
            {
                IPAddress ip = IPAddress.Parse("192.168.0.28");
                server.EndPoint = new IPEndPoint(ip, 13996);
                server.RequestReceived += (s, e) =>
                {
                    try
                    {
                        string path = e.Request.Path;
                        if (String.Compare("/UploadReportInfo", path, true) == 0 &&
                                e.Request.InputStream != null &&
                                e.Request.InputStream.Length > 0)
                        {
                            byte[] inputData = StreamToBytes(e.Request.InputStream);
                            string str = Encoding.UTF8.GetString(inputData);
                            byte[] bytes = Convert.FromBase64String(str);
                            Stream stream = new MemoryStream(bytes);
                            UploadResultInfo Info = InputStreamToBson<UploadResultInfo>(stream);
                            string strDataPath = strJudgmentDataDir;
                            if ((RoleType)Info.RoleID == RoleType.AlyDoc)
                            {
                                strDataPath = strDGSResultDataDir + "\\" + Info.Account;
                                CheckDataDir(strDataPath);
                            }
                            string strDataDir = strDataPath + "\\" + Info.FileName;
                            File.WriteAllBytes(strDataDir, Info.FileData);
                            //更新数据库
                            ReportInfo reportInfo = new ReportInfo();
                            bool bRet = _dbManager.QueryReportInfo(Info.Account, Info.RecordID,out reportInfo);
                            if (reportInfo == null) reportInfo = new ReportInfo();
                            reportInfo.DocAccount = Info.Account;
                            reportInfo.DocName = Info.Name;
                            reportInfo.RoleID = Info.RoleID==0?"0":"1";
                            reportInfo.RecordID = Info.RecordID;
                            reportInfo.DGSResult = Info.DGSResult;
                            string strSpanTime = CalcTimeSpan(reportInfo.AlyTimeSpan, Info.AlyTimeSpan);
                            reportInfo.AlyTimeSpan = strSpanTime;
                            reportInfo.UploadTime = DateTime.Now;
                            reportInfo.Status = 1;
                            string strRespone = JsonConvert.SerializeObject(reportInfo);
                            Console.WriteLine(strRespone);
                            Logger.Info(strRespone);
                            if (bRet == false)
                               bRet = _dbManager.InsertReportInfo(reportInfo);
                            else
                               bRet = _dbManager.UpdateReportInfo(reportInfo);
                            NotifyResult result = new NotifyResult();
                            result.RepCode =bRet?0:1;
                            result.Message = "Report Upload Success!";
                            using (var writer = new StreamWriter(e.Response.OutputStream))
                            {
                                writer.Write(BsonToBase64String(result));
                            }
                            ComparePara _para = new ComparePara();
                            _para.std = strJudgmentDataDir + "\\" + Info.FileName;
                            _para.test = strDGSResultDataDir + "\\" + Info.Account + "\\" + Info.FileName;
                            _para.appdir = AppDomain.CurrentDomain.BaseDirectory;
                            if (((RoleType)Info.RoleID == RoleType.AlyDoc) && _para.CheckFilePath())
                            {
                                string strJson = JsonConvert.SerializeObject(_para);
                                CompareThread compareThread = new CompareThread(ref strJson, ref reportInfo, ref _dbManager);
                            }
                        }
                        if (String.Compare("/Stream", path, true) == 0 &&
                                e.Request.InputStream != null &&
                                e.Request.InputStream.Length > 0)
                        {
                            using (var writer = new StreamWriter(e.Response.OutputStream))
                            {
                                byte[] inputData = StreamToBytes(e.Request.InputStream);
                                string str = Encoding.UTF8.GetString(inputData);
                                writer.Write(str);
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Logger.Error("HostService");
                        Logger.Error(ex.ToString());
                    }
                };
    
                server.Start();
                Console.WriteLine("WebService Host Start!");
                resetEvent.WaitOne();
            }
        }

    }
}
