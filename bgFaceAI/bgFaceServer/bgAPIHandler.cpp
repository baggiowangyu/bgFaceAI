#include "bgAPIHandler.h"

bgAPIHandler::bgAPIHandler()
{}

bgAPIHandler::~bgAPIHandler()
{}

std::string bgAPIHandler::RequestDispatch(std::string method, std::string uri, std::string request_body)
{
	// 首先过滤uri
	if (method.compare("POST") == 0)
	{
		// 在这里处理API请求
	}

	return "";
}