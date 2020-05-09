using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Newtonsoft.Json;

namespace ClientDemo
{
    public partial class Form1 : Form
    {
        public class PatientListItem
        {
            /// <summary>
            /// 
            /// </summary>
            public string PID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Name { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int Gender { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Birthday { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string IDCard { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string HealthCardID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Age { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int Age_Unit { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Height { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int Height_Unit { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Weight { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int Weight_Unit { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Telephone { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Address { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string ClinicInfo { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string ClinicDoctor { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Ward { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string InPatientID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string OutPatientID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string RegID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string OrderID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Department { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string HosDistrict { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string RoomID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string Sickbed { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string ReqProcID { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string AccessionNumber { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string AccessionTime { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISSMOKE { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISDIABETES { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISHYPERTENSION { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISHIGHBLOODFAT { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISCARDIOPATHY { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISTYPEANGINA { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISNOTYPEANGINA { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ISMEDICINERECORD { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ASYMPTOMATIC { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int ABSENCEANGINA { get; set; }
        }

        public class Root
        {
            /// <summary>
            /// 
            /// </summary>
            public int PatientCount { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public List<PatientListItem> PatientList { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public double ExecutionTime { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public double MemoryUsage { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public int RepCode { get; set; }
            /// <summary>
            /// 
            /// </summary>
            public string RepCodeDesc { get; set; }
        }
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_upload_Click(object sender, EventArgs e)
        {
           // PostResultInfo();
            //UploadFile();
            test();
        }

        private void PostResultInfo()
        {
            string url = "http://192.168.0.28:13996/PostResultInfo";
            //string url = "http://192.168.0.28:8023/welcome/upload";
            HttpClient client = new HttpClient(url);
            client.PostingData.Add("DocAccount", "zhang");
            client.PostingData.Add("DocName", "张三");
            client.PostingData.Add("RoleID", "0");
            client.PostingData.Add("RecordID", "H1109236641");
            client.PostingData.Add("DGSResult", "窦性心律");
            client.PostingData.Add("AlyTimeSpan", "12:12:21");
            //client.AttachFile("D://test.txt", "file");
            string html = client.GetString();
            MessageBox.Show(html, "返回结果");
        }

        private void UploadFile()
        {
            string url = "http://192.168.0.28:8021/test/uploadfile";
            HttpClient client = new HttpClient(url);
            string strAppPath = Directory.GetCurrentDirectory();
            string strDataDir = "D://666666_1311084208_张安乐.pdf";
            client.AttachFile(strDataDir, "BlockFile");
            string html = client.GetString();
            MessageBox.Show(html, "返回结果");
        }

        private void test()
        {
            try
            {
                string id = textBox1.Text;
                string url = string.Format("http://localhost/Queryhis/QueryFromHISByHealthCardID?AppCode=ECG&&HealthCardID={0}", id);
                HttpClient client = new HttpClient(url);
                client.UserAgent = "User Agent-BeneNetCore V0.1";
                string html = client.GetString();
                MessageBox.Show(html, "返回结果");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "返回结果");
            }
            
        }

    }
}
