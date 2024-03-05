
// leetcodedlg.h : header file
//

#pragma once

#include "leetcodetabctrl.h"

class CleetcodeDlg;
class hint;

// problem selection
class problemstg
{
	public:
		bool isempty(void)const{return m_vIndices.size()==0;}
		const std::vector<int>& getindices(void)const{return m_vIndices;}
		const std::vector<const leetcodeproblem*>& getproblems(void)const{return m_vProblems;}
	protected:
		problemstg(){}
		std::vector<int> m_vIndices;
		std::vector<const leetcodeproblem*> m_vProblems;
};
class leetcodeproblemsel:public problemstg { public: leetcodeproblemsel(CleetcodeDlg *p); };

// CleetcodeDlg dialog
class CleetcodeDlg : public CDialogEx
{
// Construction
public:
	CleetcodeDlg(CWnd* pParent = nullptr);	// standard constructor

	const CListCtrl *getlistctrl(void)const{return &m_ListCtrl;}
	const leetcodetabctrl *gettabctrl(void)const{return &m_TabCtrl;}

	void onhint(const hint *p);

// Dialog Data
	enum { IDD = IDD_LEETCODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	CListCtrl m_ListCtrl;
	leetcodetabctrl m_TabCtrl;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelChange(NMHDR* pNMHDR,LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

	void populatelistctrl(void);
	void clearlistctrlsel(void);
	void setlistctrllayer(const int n,const leetcodeproblem *pL);
	void setlistctrlcolumntext(CListCtrl *pList,const int n,const int nC,const CString& cs);
	void initfromlistctrl(void);
};
