
// MangoPro.h : MangoPro Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMangoProApp:
// �йش����ʵ�֣������ MangoPro.cpp
//

class CMangoProApp : public CWinApp
{
public:
	CMangoProApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMangoProApp theApp;
