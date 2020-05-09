#pragma once
#include "mongoose\mongoose.h"
#include <string>
#include <hash_map>
using namespace std;
using namespace stdext;

class CSimpleHttpServer;
typedef bool (CSimpleHttpServer::*PROC_HTTP)(mg_connection*,http_message*);
typedef hash_map<std::string,PROC_HTTP> HTTP_PROC_MAP;

class CSimpleHttpServer
{
public:
	CSimpleHttpServer(void);
	~CSimpleHttpServer(void);
	void Init(const std::string &address); // 初始化设置  
	void Init(const std::string &host,int port);
	bool Start(); //启动httpserver  
	bool Close(); //关闭
protected:
	bool AddHandler(char* pRoute,PROC_HTTP handler);
	void RemoveHandler(char* pRoute);
	virtual	void OnUnknowRoute(mg_connection *connection);
	virtual void HandleEvent(mg_connection *connection, http_message *http_req);
protected:
	static void OnHttpEvent(mg_connection *connection, int event_type, void *event_data);
	static void SendChunkedRsp(mg_connection *connection,const std::string& rsp);
	static void SendJsonRsp(mg_connection* connection,const std::string& json);
	static void SendTextPlainRsp(mg_connection* connection,const std::string& text);
protected:
	std::string m_address;				//监听地址  
	mg_mgr m_mgr;						//连接管理器  
	std::string s_web_dir;				//网页根目录   
	mg_serve_http_opts s_server_option; //web服务器选项
	HTTP_PROC_MAP	 m_mRequestHandler;
};