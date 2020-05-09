#include "StdAfx.h"
#include "SimpleHttpServer.h"
#include <algorithm>
#include "SimpleHttpUtility.h"

CSimpleHttpServer::CSimpleHttpServer(void)
{
}

CSimpleHttpServer::~CSimpleHttpServer(void)
{
}

void CSimpleHttpServer::Init(const std::string &host,int port)
{
	CStringA strAddress;
	strAddress.Format("%s:%d",host.c_str(),port);
	Init(strAddress.GetString());
}

void CSimpleHttpServer::Init(const std::string &address)
{
	m_address = address;
	s_web_dir="./not_exist_dir";
	s_server_option.enable_directory_listing = "no";  
	s_server_option.document_root = s_web_dir.c_str();  
}

bool CSimpleHttpServer::Start()
{
	mg_mgr_init(&m_mgr, NULL);  
	mg_connection *connection = mg_bind(&m_mgr, m_address.c_str(), OnHttpEvent);  
	if (connection == NULL)  
		return false;  
	mg_set_protocol_http_websocket(connection);
	connection->user_data=this;
	//printf("starting http server at port: %s\n", m_address.c_str());  
	// loop  
	while (true)  
		mg_mgr_poll(&m_mgr, 500); // ms  
	return true;  
}

bool CSimpleHttpServer::Close()
{
	mg_mgr_free(&m_mgr);  
	return true;  
}

void CSimpleHttpServer::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	CSimpleHttpServer* pThis=(CSimpleHttpServer*)connection->user_data;
	if(pThis==NULL)
		return;
	http_message *http_req = (http_message *)event_data;  
	switch (event_type)  
	{  
	case MG_EV_HTTP_REQUEST:  
		pThis->HandleEvent(connection, http_req);  
		break;  
	default:  
		break;  
	}  
}

void CSimpleHttpServer::OnUnknowRoute(mg_connection *connection)
{
	mg_printf(  
		connection,  
		"%s",  
		"HTTP/1.1 501 Not Implemented\r\n"  
		"Content-Length: 0\r\n\r\n");  
}

void CSimpleHttpServer::HandleEvent(mg_connection *connection, http_message *http_req)
{
	std::string req_str = std::string(http_req->message.p, http_req->message.len);  
	//printf("got request: %s\n", req_str.c_str());  

	// 先过滤是否已注册的函数回调  
	std::string url = std::string(http_req->uri.p, http_req->uri.len);  
	//std::string body = std::string(http_req->body.p, http_req->body.len);  
	
	SimpleHttpUtility::std_string_to_lower(url);
	HTTP_PROC_MAP::iterator hIt=m_mRequestHandler.find(url);
	if(hIt!=m_mRequestHandler.end())
	{
		PROC_HTTP proc=hIt->second;
		if((this->*proc)(connection,http_req))
			return;
	} 
	OnUnknowRoute(connection);
}

void CSimpleHttpServer::SendJsonRsp(mg_connection* connection,const std::string& json)
{
	char* pFixedHeader="HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s";
	CStringA response;
	response.Format(pFixedHeader,json.size(),json.c_str());
	mg_send(connection, response.GetString(),response.GetLength());
}

void CSimpleHttpServer::SendTextPlainRsp(mg_connection* connection,const std::string& text)
{
	char* pFixedHeader="HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%s";
	CStringA response;
	response.Format(pFixedHeader,text.size(),text.c_str());
	mg_send(connection, response.GetString(),response.GetLength());
}

void CSimpleHttpServer::SendChunkedRsp(mg_connection *connection,const std::string& json)
{
	// 必须先发送header  
	mg_printf(connection, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");  
	// 以json形式返回  
	mg_printf_http_chunk(connection, "%s", json.c_str());  
	// 发送空白字符快，结束当前响应  
	mg_send_http_chunk(connection, "", 0); 
}

bool CSimpleHttpServer::AddHandler(char* pRoute,PROC_HTTP handler)
{
	if(pRoute && handler)
	{
		std::string url=pRoute;
		SimpleHttpUtility::std_string_to_lower(url);
		m_mRequestHandler[url]=handler;
		return true;
	}
	else
		return false;
}

void CSimpleHttpServer::RemoveHandler(char* pRoute)
{
	if(pRoute==NULL)
		return;
	std::string url=pRoute;
	SimpleHttpUtility::std_string_to_lower(url);
	HTTP_PROC_MAP::iterator hIt=m_mRequestHandler.find(url);
	if(hIt!=m_mRequestHandler.end())
		m_mRequestHandler.erase(hIt);
}


