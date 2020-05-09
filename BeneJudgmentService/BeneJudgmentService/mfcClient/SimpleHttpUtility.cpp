#include "StdAfx.h"
#include "SimpleHttpUtility.h"
#include <algorithm>

char easytolower(char in) {
	if(in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

char easytoupper(char in) {
	if(in <= 'z' && in >= 'a')
		return in + ('Z' - 'z');
	return in;
}

SimpleHttpUtility::SimpleHttpUtility(void)
{
}

SimpleHttpUtility::~SimpleHttpUtility(void)
{
}

void SimpleHttpUtility::std_string_to_lower(std::string& data)
{
	std::transform(data.begin(), data.end(), data.begin(), easytolower);
}

void SimpleHttpUtility::std_string_to_upper(std::string& data)
{
	std::transform(data.begin(), data.end(), data.begin(), easytolower);
}

const int CHAR_HTTP_VAR_MAX = 128;
const int CHAR_HTTP_COOKIE_MAX = 400;

bool SimpleHttpUtility::get_getVar(http_message * http_msg,const char* name, std::string & str)
{
	str.clear();
	char var[CHAR_HTTP_VAR_MAX];
	var[0] = '\0';
	if (http_msg == NULL || name == NULL || http_msg->query_string.p == NULL)
		return false;
	mg_get_http_var(&http_msg->query_string, name, var, sizeof(var));        //获取变量
	if (var[0] == '\0')
		return false;
	str = var;    //如果数据正确
	return true;
}

bool SimpleHttpUtility::get_postVar(http_message * http_msg,const char* name, std::string & str)
{
	str.clear();
	char var[CHAR_HTTP_VAR_MAX];
	var[0] = '\0';
	if (http_msg == NULL || name == NULL || http_msg->body.p == NULL)
		return false;
	mg_get_http_var(&http_msg->body, name, var, sizeof(var));        //获取变量
	if (var[0] == '\0')
		return false;
	str = var;    //如果数据正确
	return true;
}

bool SimpleHttpUtility::get_header(http_message * http_msg,const char* name,std::string& str)
{
	str.clear();
	if (http_msg == NULL || name == NULL || http_msg->message.p == NULL)
		return false;
	struct mg_str *header = mg_get_http_header(http_msg, name);
	if (header == NULL)
		return false;
	str.assign(header->p,header->len);    //如果数据正确
	return true;
}

bool SimpleHttpUtility::get_cookie(http_message * http_msg,const char* name, std::string& str)
{
	str.clear();
	char var[CHAR_HTTP_COOKIE_MAX];    //Cookie 最大更长
	var[0] = '\0';
	if (http_msg == NULL || name == NULL || http_msg->message.p == NULL)
		return false;
	struct mg_str *cookie_header = mg_get_http_header(http_msg, "cookie");    //获取Cookie 整条
	if (cookie_header == NULL)
		return false;
	mg_http_parse_header(cookie_header, name, var, sizeof(var));
	if (var[0] == '\0')
		return false;
	str = var;    //如果数据正确
	return true;
}

int SimpleHttpUtility::method_check(http_message *http_msg)
{
	if(mg_vcmp(&http_msg->method, "POST")==0)
		return SHM_POST;
	else if(mg_vcmp(&http_msg->method, "GET")==0)
		return SHM_GET;
	else if(mg_vcmp(&http_msg->method, "PUT")==0)
		return SHM_PUT;
	else if(mg_vcmp(&http_msg->method, "DELETE")==0)
		return SHM_DELETE;
	else
		return SHM_UNKNOW;
}

bool SimpleHttpUtility::route_check(http_message *http_msg, char *route_prefix)  
{  
	if (mg_vcmp(&http_msg->uri, route_prefix) == 0)  
		return true;  
	else  
		return false;  
}  

bool SimpleHttpUtility::get_body(http_message *http_msg,std::string& body)
{
	if(http_msg && http_msg->body.p)
	{
		body.assign(http_msg->body.p, http_msg->body.len);
		return true;
	}
	else
	{
		body.clear();
		return false;
	}
}

void SimpleHttpUtility::get_remote_ip_address(mg_connection *connection,std::string& address,bool isWithPort)
{
	address.clear();
	if(connection)
	{
		char szAddress[128]={0};
		DWORD nLen=ARRAYSIZE(szAddress);
		if(0==WSAAddressToStringA((LPSOCKADDR)&connection->sa,sizeof(connection->sa),NULL,szAddress,&nLen))
		{
			address=szAddress;
			if(!isWithPort)
			{
				std::string::size_type pos=address.find(':');
				if(pos!=std::string::npos)
					address.resize(pos);
			}
		}
	}
}
