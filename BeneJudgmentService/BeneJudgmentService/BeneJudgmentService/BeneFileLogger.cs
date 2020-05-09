using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Threading;

namespace BeneJudgmentService
{
	public class Logger
	{
		private static string PATH = System.AppDomain.CurrentDomain.BaseDirectory + "Logs";
		private static string FILE_NAME = "BeneJudgmentService.log";
		public static readonly object Locker = new object();
		public static readonly object writeLocker = new object();
		private static StreamWriter WRITER;

		private static string ContinueWriteCaches;
		private static readonly Stopwatch Continue_WriteSw;
		private static int ContinueTime = 300; // 300毫秒以后，连续写操作，都统一到一块操作
		private static int ContinueCountMax = 100; // 当连续写操作次数上限到指定的数值后，都写一次操作，之后的重新再计算
		private static int ContinueCount = 0;
		private static int MaxLogSize = 1024 * 1024 * 8;		//8MB
		private static int TruncateSaveSize = 1024 * 256;	//256KB
		public static int AllWriteCount = 0;

		static Logger()
		{
			Continue_WriteSw = new Stopwatch();
		}
		public static string LogFileName
		{
			set { FILE_NAME = value; }
			get { return FILE_NAME; }
		}
		public static string FULL_NAME
		{
			get { return (PATH + "\\" + FILE_NAME); }
		}
		public static void SetLogPath(string path)
		{
			PATH = path;
			if(PATH.EndsWith("\\"))
			{
				char[] charsToTrim = {'\\'};
				PATH.TrimEnd(charsToTrim);
			}
		}
		private static void Write(string msg)
		{
			if (string.IsNullOrEmpty(msg)) return;
			if (!msg.EndsWith("\r\n"))
				msg += "\r\n";
			lock (Locker)
			{
				if (Continue_WriteSw.IsRunning && Continue_WriteSw.ElapsedMilliseconds < ContinueTime)
				{
					if (ContinueWriteCaches == null) ContinueWriteCaches = msg;
					else ContinueWriteCaches += msg;
					ContinueCount++;
					if (ContinueCount > ContinueCountMax)
					{
						_Write();
					}
					return;
				}

				if (!Continue_WriteSw.IsRunning) Continue_WriteSw.Start();
				if (ContinueWriteCaches == null) ContinueWriteCaches = msg;
				else ContinueWriteCaches += msg;

				Thread t = new Thread(delegate()
				{
					Thread.Sleep(ContinueTime);
					_Write();
				});
				t.Start();
			}
		}

		private static void _Write()
		{
			lock (writeLocker)
			{
				if (ContinueWriteCaches != null)
				{
					if (!File.Exists(FULL_NAME))
					{
						if (!Directory.Exists(PATH))
							Directory.CreateDirectory(PATH);
						//File.Create(ProjectFullName);
					}

					using (WRITER = new StreamWriter(FULL_NAME, true, Encoding.UTF8))
					{
						WRITER.Write(ContinueWriteCaches);
						WRITER.Flush();
						WRITER.Close();
					}
				}
				Continue_WriteSw.Stop();
				Continue_WriteSw.Reset();
				ContinueWriteCaches = null;
				ContinueCount = 0;

				Interlocked.Increment(ref AllWriteCount);

				if (AllWriteCount > 1000 && (AllWriteCount % 2000 == 0))
				{
					try
					{
						FileInfo fileInfo = new FileInfo(FULL_NAME);
						if (fileInfo.Exists && fileInfo.Length > MaxLogSize)
						{
							byte[] buffer = new byte[TruncateSaveSize];
							using (FileStream fs = fileInfo.Open(FileMode.Open, FileAccess.ReadWrite))
							{
								fs.Seek(TruncateSaveSize, SeekOrigin.End);
								fs.Read(buffer, 0, TruncateSaveSize);
								fs.SetLength(3);//保留原UTF8标志位
								fs.Write(buffer, 0, TruncateSaveSize);
								fs.Flush();
								fs.Close();
							}
						}
					}
					catch (Exception)
					{
					}
				}
			}
		}

		public static void Debug(string msg)
		{
			msg = string.Format("[{0} {1}] : {2}", "Debug", DateTime.Now.ToString(), msg);
			Write(msg);
		}

		public static void Info(string msg)
		{
			msg = string.Format("[{0} {1}] : {2}", "Info", DateTime.Now.ToString(), msg);
			Write(msg);
		}

		public static void Error(string msg)
		{
			msg = string.Format("[{0} {1}] : {2}", "Error", DateTime.Now.ToString(), msg);
			Write(msg);
		}
	}
}
