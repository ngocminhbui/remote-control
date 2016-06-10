#pragma once


// appDlg dialog

class appDlg : public CDialogEx
{
	DECLARE_DYNAMIC(appDlg)

public:
	appDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~appDlg();

// Dialog Data
	enum { IDD = IDD_appdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedappsee();
	afx_msg void OnBnClickedappclear();
	afx_msg void OnBnClickedappstart();
	afx_msg void OnBnClickedappkill();
};
