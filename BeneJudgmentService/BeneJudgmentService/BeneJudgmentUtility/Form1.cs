using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.ServiceProcess;

namespace BeneDGSResultUtility
{
    public partial class Form1 : Form
    {
        private string serviceName = "BeneJudgmentService";

        public Form1()
        {
            InitializeComponent();
        }

        private void btn_install_Click(object sender, EventArgs e)
        {
            string strCmdText;
            strCmdText = "-install";
            string strBase = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            string strApp = string.Format("{0}{1}.exe", strBase, serviceName);
            try
            {
                System.Diagnostics.Process process = System.Diagnostics.Process.Start(strApp, strCmdText);
                if (process != null)
                {
                    if (process.WaitForExit(20000))
                    {
                        if (process.ExitCode == 0)
                            MessageBox.Show("安装服务成功!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        else
                            MessageBox.Show("安装服务失败!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                        MessageBox.Show("安装服务超时!", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception ex)
            {
                string msg = string.Format("安装服务出错:{0}", ex.Message);
                MessageBox.Show(msg, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btn_uninstall_Click(object sender, EventArgs e)
        {
            string strCmdText;
            strCmdText = "-uninstall";
            string strBase = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            string strApp = string.Format("{0}{1}.exe", strBase, serviceName);
            try
            {
                System.Diagnostics.Process process = System.Diagnostics.Process.Start(strApp, strCmdText);
                if (process != null)
                {
                    if (process.WaitForExit(20000))
                    {
                        if (process.ExitCode == 0)
                            MessageBox.Show("卸载服务成功!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        else
                            MessageBox.Show("卸载服务失败!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                        MessageBox.Show("卸载服务超时!", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception ex)
            {
                string msg = string.Format("卸载服务出错:{0}", ex.Message);
                MessageBox.Show(msg, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            try
            {
                ServiceController controller = new ServiceController(serviceName);
                if (controller.Status == ServiceControllerStatus.Running)
                    controller.Stop();

                if (controller.Status == ServiceControllerStatus.Stopped)
                    controller.Start();

                MessageBox.Show("启动服务成功!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                string msg = string.Format("重启服务出错:{0}", ex.Message);
                MessageBox.Show(msg, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btn_stop_Click(object sender, EventArgs e)
        {
            string errMsg = null;
            if (StopService(ref errMsg))
            {
                MessageBox.Show("停止服务成功!", "信息", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                string msg = string.Format("停止服务出错:{0}", errMsg);
                MessageBox.Show(msg, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private bool StopService(ref string strErrorMsg)
        {
            try
            {
                ServiceController controller = new ServiceController(serviceName);
                if (controller.Status == ServiceControllerStatus.Running)
                    controller.Stop();
                return true;
            }
            catch (Exception ex)
            {
                strErrorMsg = ex.Message;
                return false;
            }
        }
    }
}
