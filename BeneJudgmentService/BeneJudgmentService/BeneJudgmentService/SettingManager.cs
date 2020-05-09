using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Security.Cryptography;

namespace BeneJudgmentService
{
    public class DES
    {
        static private byte[] keyvi = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x05, 0x07 };
        static public string DesEncrypt(string normalTxt, string EncryptKey)
        {
            var bytes = Encoding.Default.GetBytes(normalTxt);
            var key = Encoding.UTF8.GetBytes(EncryptKey.PadLeft(8, '0').Substring(0, 8));
            using (MemoryStream ms = new MemoryStream())
            {
                var encry = new DESCryptoServiceProvider();
                CryptoStream cs = new CryptoStream(ms, encry.CreateEncryptor(key, keyvi), CryptoStreamMode.Write);
                cs.Write(bytes, 0, bytes.Length);
                cs.FlushFinalBlock();
                return Convert.ToBase64String(ms.ToArray());
            }
        }
        static public string DesDecrypt(string securityTxt, string EncryptKey)//解密
        {
            try
            {
                var bytes = Convert.FromBase64String(securityTxt);
                var key = Encoding.UTF8.GetBytes(EncryptKey.PadLeft(8, '0').Substring(0, 8));
                using (MemoryStream ms = new MemoryStream())
                {
                    var descrypt = new DESCryptoServiceProvider();
                    CryptoStream cs = new CryptoStream(ms, descrypt.CreateDecryptor(key, keyvi), CryptoStreamMode.Write);
                    cs.Write(bytes, 0, bytes.Length);
                    cs.FlushFinalBlock();
                    return Encoding.UTF8.GetString(ms.ToArray());
                }

            }
            catch (Exception)
            {
                return string.Empty;
            }
        }
    }

    class SettingManager
    {
        public BeneServiceSetting serviceSetting = null;
        public SettingManager(ref string dir)
        {
            if (File.Exists(dir))
            {
                StreamReader file = File.OpenText(dir);
                JsonTextReader reader = new JsonTextReader(file);
                JObject o = (JObject)JToken.ReadFrom(reader);
                serviceSetting = o.ToObject<BeneServiceSetting>();
            }else
            {
                serviceSetting = new BeneServiceSetting();
            }
        }
    }
}
