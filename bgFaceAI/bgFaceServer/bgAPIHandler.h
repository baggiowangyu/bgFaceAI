#ifndef _bgAPIHandler_H_
#define _bgAPIHandler_H_

#include <string>

class bgAPIHandler
{
public:
	bgAPIHandler();
	~bgAPIHandler();

public:
	std::string RequestDispatch(std::string method, std::string uri, std::string request_body);
};

#endif//_bgAPIHandler_H_