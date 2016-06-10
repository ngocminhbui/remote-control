#pragma once


// keylogDlg dialog

class keylogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(keylogDlg)

public:
	keylogDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~keylogDlg();

// Dialog Data
	enum { IDD = IDD_keylogdlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedhook();
	afx_msg void OnBnClickedunhook();
	afx_msg void OnBnClickedshow();
};
