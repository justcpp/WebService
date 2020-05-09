using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading;
using System.Configuration.Install;
using System.Runtime.InteropServices;
using System.Reflection;

namespace BeneJudgmentService
{
    static class Program
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool AllocConsole();

        [DllImport("kernel32", SetLastError = true)]
        static extern bool AttachConsole(int dwProcessId);

        static EventWaitHandle waitEvent;
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        static void Main(string[] args)
        {
            if (Environment.UserInteractive)
            {
                bool createNew;
                waitEvent = new EventWaitHandle(false, EventResetMode.AutoReset, "BeneJudgmentServiceEvent", out createNew);
                // 如果该命名事件已经存在(存在有前一个运行实例)，则发事件通知并退出
                if (!createNew)
                    return;
                string param = string.Concat(args);
                switch (param)
                {
                    case "-install":
                        ManagedInstallerClass.InstallHelper(new string[] { Assembly.GetExecutingAssembly().Location }); //安装服务  
                        break;
                    case "-uninstall":
                        ManagedInstallerClass.InstallHelper(new string[] { "/u", Assembly.GetExecutingAssembly().Location });   //卸载服务  
                        break;
                    case "-start":
                        StartService("BeneJudgmentService", 30000);
                        break;
                    case "-stop":
                        StopService("BeneJudgmentService", 30000);
                        break;
                    case "-test":
                        {
                            if (!AttachConsole(-1))
                                AllocConsole();
                            ServiceManager sm = new ServiceManager();
                            sm.RunConsole(args);
                            Console.WriteLine("running...");
                            Thread.Sleep(1000);
                            Console.ReadKey();
                        }
                        break;
                    default:
                        break;
                }
            }
            else
            {
                ServiceBase[] ServicesToRun;
                ServicesToRun = new ServiceBase[] 
			    { 
				    new JudgmentService() 
			    };
                ServiceBase.Run(ServicesToRun);
            }
        }

        /// <summary>
        /// 启动服务
        /// </summary>
        /// <param name="srv_name">服务名称</param>
        /// <param name="time_out">启动超时，默认30秒</param>
        /// <returns>成功：true，失败：false</returns>
        public static bool StartService(string srv_name, int time_out)
        {
            ServiceController service = new ServiceController(srv_name);
            try
            {
                TimeSpan timeout = TimeSpan.FromMilliseconds(time_out);
                service.Start();
                service.WaitForStatus(ServiceControllerStatus.Running, timeout);
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                return false;
            }
        }

        /// <summary>
        /// 停止服务
        /// </summary>
        /// <param name="srv_name">服务名称</param>
        /// <param name="time_out">停止超时，默认30秒</param>
        /// <returns>成功：true，失败：false</returns>
        public static bool StopService(string srv_name, int time_out)
        {
            ServiceController service = new ServiceController(srv_name);
            try
            {
                TimeSpan timeout = TimeSpan.FromMilliseconds(time_out);
                service.Stop();
                service.WaitForStatus(ServiceControllerStatus.Stopped, timeout);
                return true;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                return false;
            }
        }
    }
}
