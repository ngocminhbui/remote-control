
// ServerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "appDlg.h"
#include "serviceDlg.h"
#include "keylogDlg.h"
// CServerDlg dialog
class CServerDlg : public CDialogEx
{
// Construction
public:
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SERVER_DIALOG };

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
	CEdit m_logBox;
	afx_msg void OnBnClickedButton1();

	void updateBoxChat(CString moreline){
		CString BoxChatContent;
		GetDlgItemText(IDC_log, BoxChatContent);

		BoxChatContent = BoxChatContent + moreline + CString("\r\n");
		SetDlgItemText(IDC_log, (LPCTSTR)BoxChatContent);
	}
	void updateBoxChat(char* cmoreline){
		updateBoxChat(CString(cmoreline));
	}
	CComboBox m_clientSelect;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeclientselect();
	afx_msg void OnBnClickedshutdown();
	afx_msg void OnBnClickedservices();
	afx_msg void OnBnClickedapplication();
	afx_msg void OnBnClickeddisconnect();
	afx_msg void OnBnClickedkeylog();
	afx_msg void OnBnClickedButton7();
};
