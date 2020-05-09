#pragma once
#include <string>
#include "mongoose.h"
#include "SimpleHttpUtility.h"
using namespace std;

class SimpleHttpResponse
{
public:
	int connectionStatus;		//0:ok,others:connect server error
	std::string content;
	std::string contentEncoding;
	std::string contentType;
	int contentLength;
	SimpleHttpStatusCode statusCode;
protected:
	HANDLE reqEvent;
public:
	SimpleHttpResponse();
	~SimpleHttpResponse();
	void Reset();
	void SetEvent();
	DWORD  WaitEvent(int nTimeout);
};

class CSimpleHttpClient
{
public:
	static void SendJsonRequset(const std::string& url,const std::string& jsonBody,SimpleHttpResponse& response);
protected:
	static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);  
};
