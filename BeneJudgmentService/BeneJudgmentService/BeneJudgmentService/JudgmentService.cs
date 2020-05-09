using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Runtime.InteropServices;

namespace BeneJudgmentService
{
    [StructLayout(LayoutKind.Sequential)]
    public struct SERVICE_STATUS
    {
        public int serviceType;
        public int currentState;
        public int controlsAccepted;
        public int win32ExitCode;
        public int serviceSpecificExitCode;
        public int checkPoint;
        public int waitHint;
    }

    public enum State
    {
        SERVICE_STOPPED = 0x00000001,
        SERVICE_START_PENDING = 0x00000002,
        SERVICE_STOP_PENDING = 0x00000003,
        SERVICE_RUNNING = 0x00000004,
        SERVICE_CONTINUE_PENDING = 0x00000005,
        SERVICE_PAUSE_PENDING = 0x00000006,
        SERVICE_PAUSED = 0x00000007,
    }
    public partial class JudgmentService : ServiceBase
    {
        private SERVICE_STATUS myServiceStatus;
        [DllImport("ADVAPI32.DLL", EntryPoint = "SetServiceStatus")]
        public static extern bool SetServiceStatus(
                        IntPtr hServiceStatus,
                        ref SERVICE_STATUS lpServiceStatus
                        );
        private ServiceManager svcManager = new ServiceManager();
        public JudgmentService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            svcManager.RunService();
            IntPtr handle = this.ServiceHandle;
            myServiceStatus.currentState = (int)State.SERVICE_RUNNING;
            SetServiceStatus(handle, ref myServiceStatus);
            Logger.Debug("BeneJudgmentService Start!");
            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnhandledExceptionHandler);
        }

        static public void UnhandledExceptionHandler(object sender, UnhandledExceptionEventArgs args)
        {
            Exception ex = (Exception)args.ExceptionObject;
            Logger.Error(string.Format("UnhandledException caught : {0}", ex.Message));
            Logger.Error(ex.StackTrace);
            Logger.Error(string.Format("Runtime terminating: {0}", args.IsTerminating));
        }

        protected override void OnStop()
        {
            svcManager.StopService();
            Logger.Debug("BeneJudgmentService Stop!");
        }
    }
}
