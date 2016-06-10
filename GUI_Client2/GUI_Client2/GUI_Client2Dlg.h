
// GUI_Client2Dlg.h : header file
//

#pragma once
#include <afxsock.h>
#pragma warning(disable: 4996) 
#include <string>
# include <conio.h>
# include <windows.h>
# include <winuser.h>
using namespace std;

// CGUI_Client2Dlg dialog
class CGUI_Client2Dlg : public CDialogEx
{
// Construction
public:
	CGUI_Client2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GUI_CLIENT2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedconnect();
	
	void updateBoxChat(CString moreline);
	void updateBoxChat(char* cmoreline);


	
	//DWORD WINAPI thread_keyboardcatch(LPVOID);

	
};
