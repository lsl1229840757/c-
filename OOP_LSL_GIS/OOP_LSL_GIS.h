
// OOP_LSL_GIS.h : OOP_LSL_GIS Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COOP_LSL_GISApp:
// �йش����ʵ�֣������ OOP_LSL_GIS.cpp
//

class COOP_LSL_GISApp : public CWinApp
{
public:
	COOP_LSL_GISApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COOP_LSL_GISApp theApp;
