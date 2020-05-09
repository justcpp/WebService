using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using WSAgent;

namespace WSQuery
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnQuery_Click(object sender, EventArgs e)
        {
            WSAgent.WebServerAgent wsAgent = new WSAgent.WebServerAgent();
            string strCity = textBoxCity.Text.Trim();
            string strWeather = wsAgent.GetWeather(strCity);
            //MessageBox.Show(strWeather);
            textBoxWeather.Text = strWeather;
        }
    }
}
