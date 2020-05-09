// CLRWS.cpp: 主项目文件。

#include "stdafx.h"
#include "WeatherWebService.h"

using namespace System;
using namespace System::Net;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	WeatherWebService ^wsService =gcnew WeatherWebService();
	wsService->SetUrl(L"http://www.webxml.com.cn/WebServices/WeatherWebService.asmx");
	try
	{
		array<System::String ^> ^data = wsService->getWeatherbyCityName(L"杭州");
		System::String ^strWh = L"";
		for (int i=0;i<data->Length;i++)
		{
			strWh += data[i];
		}
		Console::WriteLine(strWh);
	}
	catch (WebException^ e)
	{
		Console::WriteLine(e->Message);
	}
	Console::ReadLine();
    return 0;
}
