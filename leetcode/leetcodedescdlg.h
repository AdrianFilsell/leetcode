#pragma once
#include "afxdialogex.h"
#include "resource.h"

class hint;

// leetcodedescdlg dialog

class leetcodedescdlg : public CDialogEx
{
	DECLARE_DYNAMIC(leetcodedescdlg)
	
public:
	leetcodedescdlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~leetcodedescdlg();

	void setactive(const bool b){}
	void onhint(const hint *p);

// Dialog Data
	enum { IDD = IDD_LEETCODE_DESC_DIALOG };
	CFocusImmutableSelEdit m_DescCtrl;
	CString m_csDesc;

protected:
	bool m_bInitialised;

	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override {}
	virtual void OnCancel() override {}

	// Generated message map functions
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	
	// description
	CString getdescription(void)const;

	// layout
	void updatelayout(void);
};
