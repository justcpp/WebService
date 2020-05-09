#pragma once
#include "mongoose.h"
#include <string>
enum SimpleHttpStatusCode
{
	SHSC_Continue = 100,
	SHSC_SwitchingProtocols = 101,
	SHSC_OK = 200,
	SHSC_Created = 201,
	SHSC_Accepted = 202,
	SHSC_NonAuthoritativeInformation = 203,
	SHSC_NoContent = 204,
	SHSC_ResetContent = 205,
	SHSC_PartialContent = 206,
	SHSC_MultipleChoices = 300,
	SHSC_Ambiguous = 300,
	SHSC_MovedPermanently = 301,
	SHSC_Moved = 301,
	SHSC_Found = 302,
	SHSC_Redirect = 302,
	SHSC_SeeOther = 303,
	SHSC_RedirectMethod = 303,
	SHSC_NotModified = 304,
	SHSC_UseProxy = 305,
	SHSC_Unused = 306,
	SHSC_TemporaryRedirect = 307,
	SHSC_RedirectKeepVerb = 307,
	SHSC_BadRequest = 400,
	SHSC_Unauthorized = 401,
	SHSC_PaymentRequired = 402,
	SHSC_Forbidden = 403,
	SHSC_NotFound = 404,
	SHSC_MethodNotAllowed = 405,
	SHSC_NotAcceptable = 406,
	SHSC_ProxyAuthenticationRequired = 407,
	SHSC_RequestTimeout = 408,
	SHSC_Conflict = 409,
	SHSC_Gone = 410,
	SHSC_LengthRequired = 411,
	SHSC_PreconditionFailed = 412,
	SHSC_RequestEntityTooLarge = 413,
	SHSC_RequestUriTooLong = 414,
	SHSC_UnsupportedMediaType = 415,
	SHSC_RequestedRangeNotSatisfiable = 416,
	SHSC_ExpectationFailed = 417,
	SHSC_InternalServerError = 500,
	SHSC_NotImplemented = 501,
	SHSC_BadGateway = 502,
	SHSC_ServiceUnavailable = 503,
	SHSC_GatewayTimeout = 504,
	SHSC_HttpVersionNotSupported = 505,
};

enum SimpleHttpMethod
{
	SHM_UNKNOW,
	SHM_GET,
	SHM_POST,
	SHM_DELETE,
	SHM_PUT,
};
class SimpleHttpUtility
{
public:
	SimpleHttpUtility(void);
	~SimpleHttpUtility(void);
public:
	static void std_string_to_lower(std::string& data);
	static void std_string_to_upper(std::string& data);
	static int  method_check(http_message *http_msg);
	static bool route_check(http_message *http_msg, char *route_prefix);
	static bool get_cookie(http_message * http_msg,const char* name, std::string& str);
	static bool get_postVar(http_message * http_msg,const char* name, std::string & str);
	static bool get_getVar(http_message * http_msg,const char* name, std::string & str);
	static bool get_header(http_message * http_msg,const char* name,std::string& str);
	static bool get_body(http_message *http_msg,std::string& body);
	static void get_remote_ip_address(mg_connection *connection,std::string& address,bool isWithPort);
};
