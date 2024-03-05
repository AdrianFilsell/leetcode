// leetcodeexamplesdlg.cpp : implementation file
//

#include "pch.h"
#include "leetcode.h"
#include "afxdialogex.h"
#include "leetcodeexamplesdlg.h"
#include "leetcodedlg.h"
#include "hint.h"

// leetcodeexamplesdlg dialog

IMPLEMENT_DYNAMIC(leetcodeexamplesdlg, CDialogEx)

leetcodeexamplesdlg::leetcodeexamplesdlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_bInitialised=false;
}

leetcodeexamplesdlg::~leetcodeexamplesdlg()
{
}

void leetcodeexamplesdlg::DoDataExchange(CDataExchange* pDX)
{
	// pDX->m_bSaveAndValidate == save into member variables

	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LEETCODE_EXAMPLES_EDIT,m_ExamplesCtrl);

	DDX_Text(pDX,IDC_LEETCODE_EXAMPLES_EDIT,m_csExamples);
}


BEGIN_MESSAGE_MAP(leetcodeexamplesdlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// leetcodeexamplesdlg message handlers

BOOL leetcodeexamplesdlg::OnInitDialog()
{
	// call the base class
	CDialogEx::OnInitDialog();

	// populate text ctrl
	m_csExamples=getexamples();
	
	m_bInitialised = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void leetcodeexamplesdlg::OnSize(UINT nType, int cx, int cy)
{
	// base class
	CDialogEx::OnSize(nType, cx, cy);
	
	// layout
	updatelayout();
}

void leetcodeexamplesdlg::updatelayout(void)
{
	CRect rc;
	GetClientRect(rc);
	if(m_ExamplesCtrl.GetSafeHwnd())
		::SetWindowPos(m_ExamplesCtrl.GetSafeHwnd(),NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
}

void leetcodeexamplesdlg::onhint(const hint *p)
{
	switch(p->gettype())
	{
		case hint::t_problem:
		{
			// update members from ui
			m_csExamples=getexamples();
			
			// update ui from members
			UpdateData(false);
		}
		break;
	}
}

CString leetcodeexamplesdlg::getexamples(void)const
{
	CString cs;
	leetcodeproblemsel sel(theApp.getdlg());
	if(!sel.isempty())
	{
		ASSERT(sel.getproblems().size()==1);
		const leetcodeproblem *p = sel.getproblems()[0];
		cs=p->getexamplesdescription();
	}
	return cs;
}
