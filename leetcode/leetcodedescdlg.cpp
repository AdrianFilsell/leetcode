// leetcodedescdlg.cpp : implementation file
//

#include "pch.h"
#include "leetcode.h"
#include "afxdialogex.h"
#include "leetcodedescdlg.h"
#include "leetcodedlg.h"
#include "hint.h"

// descdlg dialog

IMPLEMENT_DYNAMIC(leetcodedescdlg, CDialogEx)

leetcodedescdlg::leetcodedescdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_bInitialised=false;
}

leetcodedescdlg::~leetcodedescdlg()
{
}

void leetcodedescdlg::DoDataExchange(CDataExchange* pDX)
{
	// pDX->m_bSaveAndValidate == save into member variables

	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LEETCODE_DESC_EDIT,m_DescCtrl);

	DDX_Text(pDX,IDC_LEETCODE_DESC_EDIT,m_csDesc);
}


BEGIN_MESSAGE_MAP(leetcodedescdlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// leetcodedescdlg message handlers

BOOL leetcodedescdlg::OnInitDialog()
{
	// call the base class
	CDialogEx::OnInitDialog();

	// populate text ctrl
	m_csDesc=getdescription();
	
	m_bInitialised = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void leetcodedescdlg::OnSize(UINT nType, int cx, int cy)
{
	// base class
	CDialogEx::OnSize(nType, cx, cy);
	
	// layout
	updatelayout();
}

void leetcodedescdlg::updatelayout(void)
{
	CRect rc;
	GetClientRect(rc);
	if(m_DescCtrl.GetSafeHwnd())
		::SetWindowPos(m_DescCtrl.GetSafeHwnd(),NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
}

void leetcodedescdlg::onhint(const hint *p)
{
	switch(p->gettype())
	{
		case hint::t_problem:
		{
			// update members from ui
			m_csDesc=getdescription();
			
			// update ui from members
			UpdateData(false);
		}
		break;
	}
}

CString leetcodedescdlg::getdescription(void)const
{
	CString cs;
	leetcodeproblemsel sel(theApp.getdlg());
	if(!sel.isempty())
	{
		ASSERT(sel.getproblems().size()==1);
		const leetcodeproblem *p = sel.getproblems()[0];
		cs=p->getdescription();
	}
	return cs;
}
