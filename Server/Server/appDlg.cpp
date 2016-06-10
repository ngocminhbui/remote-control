// appDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "appDlg.h"
#include "afxdialogex.h"

// appDlg dialog

IMPLEMENT_DYNAMIC(appDlg, CDialogEx)

appDlg::appDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(appDlg::IDD, pParent)
{

}

appDlg::~appDlg()
{
}

void appDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(appDlg, CDialogEx)
	ON_BN_CLICKED(IDC_appsee, &appDlg::OnBnClickedappsee)
	ON_BN_CLICKED(IDC_appclear, &appDlg::OnBnClickedappclear)
	ON_BN_CLICKED(IDC_appstart, &appDlg::OnBnClickedappstart)
	ON_BN_CLICKED(IDC_appkill, &appDlg::OnBnClickedappkill)
END_MESSAGE_MAP()


// appDlg message handlers


void appDlg::OnBnClickedappsee()
{
	// TODO: Add your control notification handler code here
	theApp.SeeApplication(this);
}


void appDlg::OnBnClickedappclear()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_applist, LPCTSTR(CString("")));
}


void appDlg::OnBnClickedappstart()
{
	// TODO: Add your control notification handler code here
	theApp.startApplication(this);
}


void appDlg::OnBnClickedappkill()
{
	// TODO: Add your control notification handler code here
	theApp.killApplication(this);
}
