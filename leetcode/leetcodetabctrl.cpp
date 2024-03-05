// tabctrl.cpp : implementation file
//

#include "pch.h"
#include "leetcode.h"
#include "leetcodetabctrl.h"


// leetcodetabctrl

IMPLEMENT_DYNAMIC(leetcodetabctrl, CTabCtrl)

leetcodetabctrl::leetcodetabctrl()
{
}

leetcodetabctrl::~leetcodetabctrl()
{
}


BEGIN_MESSAGE_MAP(leetcodetabctrl, CTabCtrl)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE,leetcodetabctrl::OnSelChange)
END_MESSAGE_MAP()



// leetcodetabctrl message handlers


void leetcodetabctrl::OnSize(UINT nType, int cx, int cy)
{
	// base class
	CTabCtrl::OnSize(nType, cx, cy);
	
	// layout
	updatelayout();
}

int leetcodetabctrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// base class
	const int nRetVal = CTabCtrl::OnCreate(lpCreateStruct);

	// init
	commoninit();

	return nRetVal;
}

BOOL leetcodetabctrl::OnEraseBkgnd(CDC *pDC)
{
	// child dialogs
	if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
	{
		CRect rcCtrl;
		m_spDescDlg->GetWindowRect(rcCtrl);
		::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcCtrl,2);
		pDC->ExcludeClipRect(rcCtrl);
	}
	if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
	{
		CRect rcCtrl;
		m_spExamplesDlg->GetWindowRect(rcCtrl);
		::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcCtrl,2);
		pDC->ExcludeClipRect(rcCtrl);
	}
	if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
	{
		CRect rcCtrl;
		m_spRunDlg->GetWindowRect(rcCtrl);
		::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcCtrl,2);
		pDC->ExcludeClipRect(rcCtrl);
	}
	if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
	{
		CRect rcCtrl;
		m_spReasoningDlg->GetWindowRect(rcCtrl);
		::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcCtrl,2);
		pDC->ExcludeClipRect(rcCtrl);
	}
	
	// base class
	return CTabCtrl::OnEraseBkgnd( pDC );
}

BOOL leetcodetabctrl::OnSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	// show hide
	if(pResult)
		*pResult = 0;
	showhide();

	return FALSE;
}

void leetcodetabctrl::PreSubclassWindow(void)
{
	// Call the base class
	CTabCtrl::PreSubclassWindow();

	// init
	commoninit();
}

void leetcodetabctrl::commoninit(void)
{
	// needs to be a control parent because of child sub dialogs
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE)|WS_EX_CONTROLPARENT);

	// add tabs
	InsertItem(0,CString("Description"));
	InsertItem(1,CString("Examples"));
	InsertItem(2,CString("Run"));
	InsertItem(3,CString("Reasoning"));
	
	// create the dlgs
	createdlgs();
	
	// layout
	updatelayout();
	
	// selected tab
	const int nTab = 0;
	SetCurSel(nTab);
	OnSelChange(NULL,NULL);
}

void leetcodetabctrl::createdlgs()
{
	m_spDescDlg = std::shared_ptr<leetcodedescdlg>(new leetcodedescdlg(this));
	m_spExamplesDlg = std::shared_ptr<leetcodeexamplesdlg>(new leetcodeexamplesdlg(this));
	m_spRunDlg = std::shared_ptr<leetcoderundlg>(new leetcoderundlg(this));
	m_spReasoningDlg = std::shared_ptr<leetcodereasoningdlg>(new leetcodereasoningdlg(this));
	m_spDescDlg->Create(leetcodedescdlg::IDD,this);
	m_spExamplesDlg->Create(leetcodeexamplesdlg::IDD,this);
	m_spRunDlg->Create(leetcoderundlg::IDD,this);
	m_spReasoningDlg->Create(leetcodereasoningdlg::IDD,this);
}

void leetcodetabctrl::updatelayout(void)
{
	// child dialogs
	CRect rcListCtrl = getchildctrlrect();
	if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
		::SetWindowPos(m_spDescDlg->GetSafeHwnd(),NULL,rcListCtrl.left,rcListCtrl.top,rcListCtrl.Width(),rcListCtrl.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
	if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
		::SetWindowPos(m_spRunDlg->GetSafeHwnd(),NULL,rcListCtrl.left,rcListCtrl.top,rcListCtrl.Width(),rcListCtrl.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
	if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
		::SetWindowPos(m_spExamplesDlg->GetSafeHwnd(),NULL,rcListCtrl.left,rcListCtrl.top,rcListCtrl.Width(),rcListCtrl.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
	if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
		::SetWindowPos(m_spReasoningDlg->GetSafeHwnd(),NULL,rcListCtrl.left,rcListCtrl.top,rcListCtrl.Width(),rcListCtrl.Height(),SWP_DRAWFRAME|SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER);
}

CRect leetcodetabctrl::getchildctrlrect(void)
{
	CRect rcRetVal;
	rcRetVal.SetRectEmpty();
	if(m_hWnd)
	{
		GetWindowRect(rcRetVal);
		AdjustRect(FALSE,&rcRetVal);
		::MapWindowPoints(NULL,m_hWnd,(LPPOINT)&rcRetVal,2);
	}
	return rcRetVal;
}

void leetcodetabctrl::showhide(void)
{
	// current selection
	const int nSel = GetCurSel();
	switch( nSel )
	{
		case 0:
		{
			if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
			{
				m_spDescDlg->setactive(true);
				m_spDescDlg->ShowWindow(SW_SHOWNA);
			}
			if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
			{
				m_spExamplesDlg->ShowWindow(SW_HIDE);
				m_spExamplesDlg->setactive(false);
			}
			if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
			{
				m_spRunDlg->ShowWindow(SW_HIDE);
				m_spRunDlg->setactive(false);
			}
			if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
			{
				m_spReasoningDlg->ShowWindow(SW_HIDE);
				m_spReasoningDlg->setactive(false);
			}
		}
		break;
		case 1:
		{
			if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
			{
				m_spExamplesDlg->setactive(true);
				m_spExamplesDlg->ShowWindow(SW_SHOWNA);
			}
			if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
			{
				m_spDescDlg->ShowWindow(SW_HIDE);
				m_spDescDlg->setactive(false);
			}
			if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
			{
				m_spRunDlg->ShowWindow(SW_HIDE);
				m_spRunDlg->setactive(false);
			}
			if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
			{
				m_spReasoningDlg->ShowWindow(SW_HIDE);
				m_spReasoningDlg->setactive(false);
			}
		}
		break;
		case 2:
		{
			if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
			{
				m_spRunDlg->setactive(true);
				m_spRunDlg->ShowWindow(SW_SHOWNA);
			}
			if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
			{
				m_spExamplesDlg->ShowWindow(SW_HIDE);
				m_spExamplesDlg->setactive(false);
			}
			if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
			{
				m_spDescDlg->ShowWindow(SW_HIDE);
				m_spDescDlg->setactive(false);
			}
			if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
			{
				m_spReasoningDlg->ShowWindow(SW_HIDE);
				m_spReasoningDlg->setactive(false);
			}
		}
		break;
		case 3:
		{
			if(m_spReasoningDlg && m_spReasoningDlg->GetSafeHwnd())
			{
				m_spReasoningDlg->setactive(true);
				m_spReasoningDlg->ShowWindow(SW_SHOWNA);
			}
			if(m_spRunDlg && m_spRunDlg->GetSafeHwnd())
			{
				m_spRunDlg->ShowWindow(SW_HIDE);
				m_spRunDlg->setactive(false);
			}
			if(m_spExamplesDlg && m_spExamplesDlg->GetSafeHwnd())
			{
				m_spExamplesDlg->ShowWindow(SW_HIDE);
				m_spExamplesDlg->setactive(false);
			}
			if(m_spDescDlg && m_spDescDlg->GetSafeHwnd())
			{
				m_spDescDlg->ShowWindow(SW_HIDE);
				m_spDescDlg->setactive(false);
			}
		}
		break;
		default:ASSERT( FALSE );
	}
}
