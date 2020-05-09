// WSHost.cpp: 主项目文件。

#include "stdafx.h"

using namespace System;
using namespace WSAgent;

int main(array<System::String ^> ^args)
{
    //Console::WriteLine(L"Hello World");
	WebServerAgent ^wsAgent = gcnew WebServerAgent();
	System::String ^strResult = wsAgent->GetWeather(L"杭州");
	Console::WriteLine(strResult);
	Console::ReadLine();
    return 0;
}
