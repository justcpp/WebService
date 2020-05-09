#include "stdafx.h"
#include "HttpUtility.h"

namespace HttpUtility
{
	bool Utf8ToUnicode(const string& szUTF8, wstring& strUnicode)
	{
		int nUnicodeLen;
		nUnicodeLen= MultiByteToWideChar(CP_UTF8,0,szUTF8.c_str(),szUTF8.size(),NULL,0);
		if(nUnicodeLen<0)
		{
			strUnicode.clear();
			return false;
		}
		strUnicode.resize(nUnicodeLen);
		
		MultiByteToWideChar(CP_UTF8,0,szUTF8.c_str(),szUTF8.size(),(LPWSTR)strUnicode.c_str(),nUnicodeLen);
		return true;
	}

	bool Utf8ToTString(const string& szUTF8, tstring& strValue)
	{
		wstring strUnicode;
		if(Utf8ToUnicode(szUTF8,strUnicode))
		{
			strValue=CW2T(strUnicode.c_str()).m_psz;
			return true;
		}
		else
		{
			strValue.clear();
			return false;
		}
	}

	bool UnicodeToUtf8(const wstring& strUnicode, string& szUTF8)
	{
		int nUnicodeLen;
		nUnicodeLen=WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)strUnicode.c_str(), -1, NULL, 0, NULL, NULL);  
		if(nUnicodeLen<0)
		{
			szUTF8.clear();
			return false;
		}
		szUTF8.resize(nUnicodeLen);
		WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)strUnicode.c_str(), -1,(LPSTR)szUTF8.c_str(), nUnicodeLen, NULL,NULL);
		szUTF8 = szUTF8.substr(0,szUTF8.length()-1);    //È¥³ýÄ©Î²µÄ0
		return true;
	}

	bool TStringToUtf8(const tstring& strValue, string& szUTF8)
	{
		wstring strUnicode=CT2W(strValue.c_str()).m_psz;
		if(UnicodeToUtf8(strUnicode,szUTF8)) return true;
		else
		{
			szUTF8.clear();
			return false;
		}
	}

	void ConvertToUTF8(const CString& strValue,std::string& utf8)
	{
		utf8.clear();
		tstring tsText;
		tsText=strValue.GetString();
		TStringToUtf8(tsText,utf8);
	}

	void ConvertToUTF8(const tstring& tsText,std::string& utf8)
	{
		utf8.clear();
		TStringToUtf8(tsText,utf8);
	}

	void ConvertUTf8ToCString(const std::string& utf8,CString& result)
	{
		tstring tsText;
		Utf8ToTString(utf8,tsText);
		result=tsText.c_str();
	}

	void ConvertUTf8ToTstring(const std::string& utf8,tstring& result)
	{
		Utf8ToTString(utf8,result);
	}

	time_t ParseTime64( string strDateTime, string strFormat )
	{
		if(strFormat=="") strFormat="%d-%d-%d %d:%d:%d";
		int year=0,month=0,day=0,hour=0,minutes=0,seconds=0;
		sscanf_s(strDateTime.c_str(),strFormat.c_str(),&year,&month,&day,&hour,&minutes,&seconds);    
		if(year <1900) year = 1970;
		if(month <0) month = 1;
		if(day <0) day = 1;
		if(hour <0) hour = 0;
		if(minutes <0) minutes = 0;
		if(seconds <0) seconds = 0;
		CTime timeParse(year, month, day, hour, minutes, seconds);
		return timeParse.GetTime();
	}

	COleDateTime ParseTime( string strDateTime, string strFormat )
	{
		if(strFormat=="") strFormat="%d-%d-%d %d:%d:%d";
		int year=0,month=0,day=0,hour=0,minutes=0,seconds=0;
		sscanf_s(strDateTime.c_str(),strFormat.c_str(),&year,&month,&day,&hour,&minutes,&seconds);    
		if(year <1900) year = 1970;
		if(month <0) month = 1;
		if(day <0) day = 1;
		if(hour <0) hour = 0;
		if(minutes <0) minutes = 0;
		if(seconds <0) seconds = 0;

		return COleDateTime(year, month, day, hour, minutes, seconds);
	}
}