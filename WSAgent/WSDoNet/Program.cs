using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WSDoNet.WeaterServer;

namespace WSDoNet
{
    class Program
    {
        static void Main(string[] args)
        {

            WeaterServer.WeatherWebService ws = new WeaterServer.WeatherWebService();
            string[] items = ws.getWeatherbyCityName("杭州");
            string strResult = "";
            for (int i = 0; i < items.Length; i++)
            {
                strResult += items[i];
            }
        }
    }
}
