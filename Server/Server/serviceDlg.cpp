// serviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "serviceDlg.h"
#include "afxdialogex.h"


// serviceDlg dialog

IMPLEMENT_DYNAMIC(serviceDlg, CDialogEx)

serviceDlg::serviceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(serviceDlg::IDD, pParent)
{

}

serviceDlg::~serviceDlg()
{
}

void serviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(serviceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_srunning, &serviceDlg::OnBnClickedsrunning)
	ON_BN_CLICKED(IDC_startservice, &serviceDlg::OnBnClickedstartservice)
	ON_BN_CLICKED(IDC_stopservice, &serviceDlg::OnBnClickedstopservice)
END_MESSAGE_MAP()


// serviceDlg message handlers


void serviceDlg::OnBnClickedsrunning()
{
	// TODO: Add your control notification handler code here
	theApp.seeService(this);
}


void serviceDlg::OnBnClickedstartservice()
{
	// TODO: Add your control notification handler code here
	theApp.startService(this);
}


void serviceDlg::OnBnClickedstopservice()
{

	// TODO: Add your control notification handler code here
	theApp.stopService(this);
}
