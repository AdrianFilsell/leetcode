#pragma once
#include "afxdialogex.h"
#include "resource.h"


class hint;

// leetcodeexamplesdlg dialog

class leetcodeexamplesdlg : public CDialogEx
{
	DECLARE_DYNAMIC(leetcodeexamplesdlg)

public:
	leetcodeexamplesdlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~leetcodeexamplesdlg();

	void setactive(const bool b){}
	void onhint(const hint *p);

// Dialog Data
	enum { IDD = IDD_LEETCODE_EXAMPLES_DIALOG };
	CFocusImmutableSelEdit m_ExamplesCtrl;
	CString m_csExamples;

protected:
	bool m_bInitialised;

	virtual void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

	virtual BOOL OnInitDialog() override;
	virtual void OnOK() override {}
	virtual void OnCancel() override {}

	// Generated message map functions
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
	
	// examples
	CString getexamples(void)const;

	// layout
	void updatelayout(void);
};
