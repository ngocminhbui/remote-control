#include "stdafx.h"
#include "ServerSock.h"
#include "Server.h"
#include "ClientSock.h"
#include "ServerDlg.h"

void ServerSock::OnConnect(int nErrorCode){

}
void ServerSock::OnClose(int nErrorCode){

}
void ServerSock::OnAccept(int nErrorCode){
	CString err;
	ClientSock* client = new ClientSock();
	this->Accept(*client);
	theApp.pushNewClient(client, err);
	
	CServerDlg* maindlg = (CServerDlg*)(AfxGetApp()->m_pMainWnd);
	maindlg->updateBoxChat(client->getIPAddress() + CString(" has just connected"));
	maindlg->m_clientSelect.AddString((LPCTSTR)client->getIPAddress());
}