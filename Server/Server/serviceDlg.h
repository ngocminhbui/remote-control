#pragma once


// serviceDlg dialog

class serviceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(serviceDlg)

public:
	serviceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~serviceDlg();

// Dialog Data
	enum { IDD = IDD_servicesDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedsrunning();
	afx_msg void OnBnClickedstartservice();
	afx_msg void OnBnClickedstopservice();
};
