
// bgFaceManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CbgFaceManagerApp: 
// �йش����ʵ�֣������ bgFaceManager.cpp
//

class CbgFaceManagerApp : public CWinApp
{
public:
	CbgFaceManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CbgFaceManagerApp theApp;