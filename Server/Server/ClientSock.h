#pragma once
#include "Server.h"

class ClientSock :public CSocket{
public:

	CString getIPAddress();
	int sendMessage(char *message);
	int receiveExactlyNByte(char* buffer, int nByte){
		int sum = 0;
		do{
			if (sum == nByte)
				break;
			sum+=this->Receive(buffer + sum, nByte - sum, 0);
		} while (1);
		return sum;
	}
};


