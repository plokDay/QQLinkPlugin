// MFCLibrary1.cpp: 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "MFCLibrary1.h"
#include "CMyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()


// CMFCLibrary1App 构造

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCLibrary1App 对象

CMFCLibrary1App theApp;
WNDPROC g_OldProc = 0;



LRESULT CALLBACK WindowProc(
	_In_ HWND hWnd,
	_In_ UINT Msg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	if (Msg == WM_COMPASS)
	{
	//无限指南针0xF0
	//无限炸弹0xF4
	//重列0xF1
//			0x45DEBC
// 			8B86 94040000 MOV EAX, DWORD PTR DS : [ESI + 0x494]
// 			8D8E 94040000 LEA ECX, DWORD PTR DS : [ESI + 0x494]
// 			52            PUSH EDX
// 			53            PUSH EBX
// 			53            PUSH EBX
// 			FF50 28       CALL DWORD PTR DS : [EAX + 0x28];  use tool 411691
		__asm
		{
			MOV ECX, 0x45DEBC
			MOV ECX, [ECX]
			LEA ECX, DWORD PTR DS : [ECX + 0x494]
			MOV EAX,wParam
			push EAX
			push 0
			push 0
			MOV EAX, 0x41E691
			CALL EAX
		}

	}
	else if (Msg == WM_ONECLEAN)
	{//单次消除
		//1. 获得两个连接的点
// 			8B8E F0190000 MOV ECX, DWORD PTR DS : [ESI + 0x19F0];  
// 			8D45 D8       LEA EAX, DWORD PTR SS : [EBP - 0x28]
// 			50            PUSH EAX
// 			8D45 E0       LEA EAX, DWORD PTR SS : [EBP - 0x20]
// 			50            PUSH EAX
// 			E8 CEAA0000   CALL kyodaiNe.0042923F;  get two connectable points
		POINT pt1 = { 0 };
		POINT pt2 = { 0 };
		__asm
		{
			MOV ECX, 0x45DEBC
			MOV ECX, [ECX]
			LEA ECX, DWORD PTR DS : [ECX + 0x494]
			MOV ECX, DWORD PTR DS : [ECX + 0x19F0]
			LEA EAX, pt1.x
			PUSH EAX
			LEA EAX, pt2.x
			PUSH EAX
			MOV EAX, 0x0042923F
			CALL EAX
		}
		CString strCode;
		strCode.Format(L"pt1 x=%d,y=%d,pt2 x=%d,y=%d", pt1.x, pt1.y, pt2.x, pt2.y);
		OutputDebugString(strCode);
		if (pt1.x == 0 && pt1.y == 0)
		{
			return -1;
		}
		//2. 调用消除
// 			00129BB8   00000000
// 			00129BBC   0012BB50
// 			00129BC0   00129BEC  
// 			00129BC4   00129BF4  
// 			00129BC8   0061D728  
// 			00129BCC   00000004
		__asm
		{
			//计算ECX
			MOV ECX, 0x45DEBC
			MOV ECX, [ECX]
			//第一个参数
			PUSH 0x4
			//第二个参数，坐标数组
			LEA EAX, DWORD PTR DS : [ECX + 0x494]
			MOV EAX, DWORD PTR DS : [EAX + 0x19F0]
			ADD EAX, 0x40
			PUSH EAX
			//第三个参数
			LEA EAX, pt1.x
			PUSH EAX
			//第四个参数
			LEA EAX, pt2.x
			PUSH EAX
			//第五个参数，数组地址
			LEA EAX, DWORD PTR DS : [ECX + 0x494]
			MOV EAX, DWORD PTR DS : [EAX + 0x19F0]
			MOV EAX, DWORD PTR DS : [EAX + 0x4]
			PUSH EAX
			//第六参数
			PUSH 0

			MOV EAX, 0x41C68E
			CALL EAX
		}
	}
	else if (Msg== WM_PRACTICE)
	{
	__asm
	{
		MOV ECX, 0x45DEBC
		MOV ECX, [ECX]
		MOV EAX,0x41C9D0
		CALL EAX
	}
	}
	return CallWindowProc(g_OldProc, hWnd, Msg, wParam, lParam);
}

unsigned __stdcall ThreadProc()
{
	//弹出对话框
	CMyDlg* dlg = new CMyDlg;
	dlg->DoModal();
	return 0;
}

// CMFCLibrary1App 初始化

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();

	//1. 通过查找窗口，获取窗口句柄4
	m_hWnd = ::FindWindow(NULL, L"QQ连连看");
	if (NULL == m_hWnd)
	{
		MessageBox(0, L"无法找到窗口", 0, 0);
		return FALSE;
	}
	//2. 设置窗口回调函数
	m_OldProc = (WNDPROC)SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)WindowProc);
	g_OldProc = m_OldProc;
	if (NULL == m_OldProc)
	{
		MessageBox(0, L"无法找到窗口回调", 0, 0);
		return FALSE;
	}

	//创建线程弹出对话框
	_beginthreadex(0, 0, (_beginthreadex_proc_type)ThreadProc, 0, 0, 0);
	return TRUE;
}
