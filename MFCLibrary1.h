﻿// MFCLibrary1.h: MFCLibrary1 DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMFCLibrary1App
// 有关此类实现的信息，请参阅 MFCLibrary1.cpp
//

class CMFCLibrary1App : public CWinApp
{
public:
	CMFCLibrary1App();

// 重写
public:
	virtual BOOL InitInstance();
	HWND m_hWnd;		//连连看窗口句柄
	WNDPROC m_OldProc;	//旧的窗口回调
	DECLARE_MESSAGE_MAP()
};
