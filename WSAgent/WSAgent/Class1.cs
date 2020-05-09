using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WSAgent.WeatherServer;

namespace WSAgent
{
    public class WebServerAgent
    {
        public string GetWeather(string strCityName)
        {
            WeatherServer.WeatherWebService ws = new WeatherServer.WeatherWebService();
            string[] items = ws.getWeatherbyCityName(strCityName);
            string strResult = "";
            strResult = (strCityName + "气象：" + "\r\n" + "天气：" + items[6] + "\r\n" + "温度：" + items[5]);
            return strResult;
        }
    }
}
