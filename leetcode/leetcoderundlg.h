#pragma once
#include "afxdialogex.h"
#include "resource.h"


class hint;

// leetcoderundlg dialog

class leetcoderundlg : public CDialogEx
{
	DECLARE_DYNAMIC(leetcoderundlg)

public:
	leetcoderundlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~leetcoderundlg();

	void setactive(const bool b){}
	void onhint(const hint *p);

// Dialog Data
	enum { IDD = IDD_LEETCODE_RUN_DIALOG };
	CFocusImmutableSelEdit m_RunCtrl;
	CString m_csRun;

protected:
	bool m_bInitialised;

	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override {}
	virtual void OnCancel() override {}

	// Generated message map functions
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	
	// run
	CString getrun(void)const;

	// layout
	void updatelayout(void);
};
