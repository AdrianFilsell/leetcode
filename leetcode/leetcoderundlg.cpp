// leetcoderundlg.cpp : implementation file
//

#include "pch.h"
#include "leetcode.h"
#include "afxdialogex.h"
#include "leetcoderundlg.h"
#include "leetcodedlg.h"
#include "hint.h"

// leetcoderundlg dialog

IMPLEMENT_DYNAMIC(leetcoderundlg, CDialogEx)

leetcoderundlg::leetcoderundlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_bInitialised=false;
}

leetcoderundlg::~leetcoderundlg()
{
}

void leetcoderundlg::DoDataExchange(CDataExchange* pDX)
{
	// pDX->m_bSaveAndValidate == save into member variables

	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LEETCODE_RUN_EDIT,m_RunCtrl);

	DDX_Text(pDX,IDC_LEETCODE_RUN_EDIT,m_csRun);
}


BEGIN_MESSAGE_MAP(leetcoderundlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// leetcoderundlg message handlers

BOOL leetcoderundlg::OnInitDialog()
{
	// call the base class
	CDialogEx::OnInitDialog();

	// populate text ctrl
	m_csRun=getrun();
	
	m_bInitialised = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void leetcoderundlg::OnSize(UINT nType, int cx, int cy)
{
	// base class
	CDialogEx::OnSize(nType, cx, cy);
	
	// layout
	updatelayout();
}

void leetcoderundlg::updatelayout(void)
{
	CRect rc;
	GetClientRect(rc);
	if(m_RunCtrl.GetSafeHwnd())
		::SetWindowPos(m_RunCtrl.GetSafeHwnd(),NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
}

void leetcoderundlg::onhint(const hint *p)
{
	switch(p->gettype())
	{
		case hint::t_problem:
		{
			// update members from ui
			m_csRun=getrun();
			
			// update ui from members
			UpdateData(false);
		}
		break;
	}
}

CString leetcoderundlg::getrun(void)const
{
	CString cs;
	leetcodeproblemsel sel(theApp.getdlg());
	if(!sel.isempty())
	{
		ASSERT(sel.getproblems().size()==1);
		const leetcodeproblem *p = sel.getproblems()[0];
		cs=p->getrundescription();
	}
	return cs;
}
