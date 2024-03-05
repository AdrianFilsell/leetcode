// leetcodereasoningdlg.cpp : implementation file
//

#include "pch.h"
#include "leetcode.h"
#include "afxdialogex.h"
#include "leetcodereasoningdlg.h"
#include "leetcodedlg.h"
#include "hint.h"

// leetcodereasoningdlg dialog

IMPLEMENT_DYNAMIC(leetcodereasoningdlg, CDialogEx)

leetcodereasoningdlg::leetcodereasoningdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_bInitialised=false;
}

leetcodereasoningdlg::~leetcodereasoningdlg()
{
}

void leetcodereasoningdlg::DoDataExchange(CDataExchange* pDX)
{
	// pDX->m_bSaveAndValidate == save into member variables

	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LEETCODE_REASONING_EDIT,m_ReasoningCtrl);

	DDX_Text(pDX,IDC_LEETCODE_REASONING_EDIT,m_csReasoning);
}


BEGIN_MESSAGE_MAP(leetcodereasoningdlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// leetcodereasoningdlg message handlers

BOOL leetcodereasoningdlg::OnInitDialog()
{
	// call the base class
	CDialogEx::OnInitDialog();

	// populate text ctrl
	m_csReasoning=getreasoning();
	
	m_bInitialised = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void leetcodereasoningdlg::OnSize(UINT nType, int cx, int cy)
{
	// base class
	CDialogEx::OnSize(nType, cx, cy);
	
	// layout
	updatelayout();
}

void leetcodereasoningdlg::updatelayout(void)
{
	CRect rc;
	GetClientRect(rc);
	if(m_ReasoningCtrl.GetSafeHwnd())
		::SetWindowPos(m_ReasoningCtrl.GetSafeHwnd(),NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
}

void leetcodereasoningdlg::onhint(const hint *p)
{
	switch(p->gettype())
	{
		case hint::t_problem:
		{
			// update members from ui
			m_csReasoning=getreasoning();
			
			// update ui from members
			UpdateData(false);
		}
		break;
	}
}

CString leetcodereasoningdlg::getreasoning(void)const
{
	CString cs;
	leetcodeproblemsel sel(theApp.getdlg());
	if(!sel.isempty())
	{
		ASSERT(sel.getproblems().size()==1);
		const leetcodeproblem *p = sel.getproblems()[0];
		cs=p->getreasoningdescription();
	}
	return cs;
}
