// CMyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCLibrary1.h"
#include "CMyDlg.h"
#include "afxdialogex.h"

// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialogEx)

CMyDlg::CMyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BOMB, &CMyDlg::OnBnClickedBomb)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyDlg::OnBnClickedButton6)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyDlg 消息处理程序
//单次消除
void CMyDlg::OnBnClickedButton2()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_ONECLEAN, 0, 0);
}

//一键秒杀
void CMyDlg::OnBnClickedButton3()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_ONECLEAN, 0, 0);
	//循环消除
	for (int i=0;i<100;++i)
	{
		int nRet = ::SendMessage(pApp->m_hWnd, WM_ONECLEAN, 0, 0);
		if (nRet==-1)
		{
			break;
		}
		
	}
}

//无限炸弹
void CMyDlg::OnBnClickedBomb()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_COMPASS, 0xF4, 0);
}

//重列
void CMyDlg::OnBnClickedButton5()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_COMPASS, 0xF1, 0);
}

//无限指南针

void CMyDlg::OnBnClickedButton4()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_COMPASS, 0xF0, 0);
}


BOOL CMyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(L"QQ连连看游戏辅助");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//重列
void CMyDlg::OnBnClickedButton6()
{
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SendMessage(pApp->m_hWnd, WM_PRACTICE, 0xF0, 0);
}


void CMyDlg::OnClose()
{//恢复窗口回调函数
	CMFCLibrary1App* pApp = (CMFCLibrary1App*)AfxGetApp();
	::SetWindowLong(pApp->m_hWnd, GWL_WNDPROC, (LONG)pApp->m_OldProc);
	CDialogEx::OnClose();
}
