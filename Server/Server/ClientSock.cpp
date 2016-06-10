#include "stdafx.h"
#include "ClientSock.h"

CString ClientSock::getIPAddress(){
	CString peerAdd;
	UINT port;
	this->GetPeerName(peerAdd, port);
	return peerAdd;

}
int ClientSock::sendMessage(char *message){
	char temp[100];
	strcpy(temp, message);
	return this->Send(temp,100 , 0);
}