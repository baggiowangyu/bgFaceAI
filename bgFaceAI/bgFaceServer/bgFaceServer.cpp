// bgFaceServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "bgHttpServer.h"


int _tmain(int argc, _TCHAR* argv[])
{
	bgServerApp app;
	return app.run(argc, argv);
}

