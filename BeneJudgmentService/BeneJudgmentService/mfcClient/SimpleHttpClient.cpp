#include "StdAfx.h"
#include "SimpleHttpClient.h"

void CSimpleHttpClient::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	SimpleHttpResponse* pResponse=(SimpleHttpResponse*)connection->user_data;
	assert(pResponse);
	http_message *hm = (struct http_message *)event_data;  
	int connect_status;  

	switch (event_type)   
	{  
	case MG_EV_CONNECT:  
		connect_status = *(int *)event_data;  
		if (connect_status != 0)   
		{  
			//printf("Error connecting to server, error code: %d\n", connect_status);  
			pResponse->connectionStatus=connect_status;
			pResponse->SetEvent();
		}  
		break;  
	case MG_EV_HTTP_REPLY:  
		{  
			//printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);  
			pResponse->content.assign(hm->body.p,(int)hm->body.len);
			pResponse->contentLength=pResponse->content.size();
			SimpleHttpUtility::get_header(hm,"Content-Type",pResponse->contentType);
			SimpleHttpUtility::get_header(hm,"Content-Encoding",pResponse->contentEncoding);
			pResponse->statusCode=(SimpleHttpStatusCode)hm->resp_code;
			connection->flags |= MG_F_SEND_AND_CLOSE;  
			pResponse->SetEvent(); 
		}  
		break;  
	case MG_EV_CLOSE:  
		pResponse->SetEvent();
		break;  
	default:  
		break;  
	}
}

void CSimpleHttpClient::SendJsonRequset(const std::string& url,const std::string& jsonBody,SimpleHttpResponse& response)
{ 
	response.Reset();
	mg_mgr mgr;  
	mg_mgr_init(&mgr, NULL);
	const char* pFixedFmt="Content-Type: application/json\r\nContent-Length: %d\r\n";
	CStringA extraHeader;
	extraHeader.Format(pFixedFmt,jsonBody.size());
	mg_connection* connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), extraHeader.GetString(), jsonBody.c_str());
	connection->user_data=&response;
	mg_set_protocol_http_websocket(connection);  

	// loop  
	while (true)
	{
		mg_mgr_poll(&mgr, 500);
		if(response.WaitEvent(1)!=WAIT_TIMEOUT)
			break;
	}
	mg_mgr_free(&mgr);  
}

//////////////////////////////////////////////////////////////////////////
SimpleHttpResponse::SimpleHttpResponse()
{
	reqEvent=CreateEvent(NULL,true,false,NULL);
	Reset();
}

SimpleHttpResponse::~SimpleHttpResponse()
{
	if(reqEvent!=NULL)
	{
		CloseHandle(reqEvent);
		reqEvent=NULL;
	}
}

void SimpleHttpResponse::Reset()
{
	content.clear();
	contentEncoding.clear();
	contentType.clear();
	contentLength=-1;
	statusCode=SHSC_Unused;
	if(reqEvent!=NULL)
		ResetEvent(reqEvent);
	connectionStatus=0;
}

void SimpleHttpResponse::SetEvent()
{
	if(reqEvent!=NULL)
		::SetEvent(reqEvent);
}

DWORD SimpleHttpResponse::WaitEvent(int nTimeout)
{
	return WaitForSingleObject(reqEvent,nTimeout);
}
