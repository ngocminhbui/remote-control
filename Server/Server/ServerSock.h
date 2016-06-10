#pragma once
#include "Server.h"
#include "stdafx.h"
class ServerSock:public CSocket{
protected:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode); 
	virtual void OnAccept(int nErrorCode);
public:

};