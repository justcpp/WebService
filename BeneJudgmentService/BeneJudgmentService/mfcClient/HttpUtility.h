#pragma once

#include <string>
using std::string;
using std::wstring;

#ifndef tstring
#ifdef _UNICODE
#define tstring	wstring
#else
#define tstring string
#endif
#endif

namespace HttpUtility
{
	bool Utf8ToUnicode(const string& szUTF8, wstring& strUnicode);
	bool Utf8ToTString(const string& szUTF8, tstring& strValue);
	bool UnicodeToUtf8(const wstring& strUnicode, string& szUTF8);
	bool TStringToUtf8(const tstring& strValue, string& szUTF8);
	void ConvertToUTF8(const CString& strValue,std::string& utf8);
	void ConvertToUTF8(const tstring& tsText,std::string& utf8);
	void ConvertUTf8ToCString(const std::string& utf8,CString& result);
	void ConvertUTf8ToTstring(const std::string& utf8,tstring& result);
	time_t ParseTime64( string strDateTime, string strFormat );
	COleDateTime ParseTime(string strDateTime, string strFormat="");
}

