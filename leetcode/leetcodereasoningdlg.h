#pragma once
#include "afxdialogex.h"
#include "resource.h"


class hint;

// leetcodereasoningdlg dialog

class leetcodereasoningdlg : public CDialogEx
{
	DECLARE_DYNAMIC(leetcodereasoningdlg)

public:
	leetcodereasoningdlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~leetcodereasoningdlg();

	void setactive(const bool b){}
	void onhint(const hint *p);

// Dialog Data
	enum { IDD = IDD_LEETCODE_REASONING_DIALOG };
	CFocusImmutableSelEdit m_ReasoningCtrl;
	CString m_csReasoning;

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
	CString getreasoning(void)const;

	// layout
	void updatelayout(void);
};
