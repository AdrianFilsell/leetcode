
// leetcodedlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "leetcode.h"
#include "leetcodedlg.h"
#include "afxdialogex.h"
#include "hint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CleetcodeDlg dialog



CleetcodeDlg::CleetcodeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEETCODE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CleetcodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LEETCODE_LIST,m_ListCtrl);
	DDX_Control(pDX,IDC_LEETCODE_TAB,m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CleetcodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_NOTIFY(LVN_ITEMCHANGED,IDC_LEETCODE_LIST,CleetcodeDlg::OnSelChange)
END_MESSAGE_MAP()


// CleetcodeDlg message handlers

BOOL CleetcodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	{
		// insert columns
		m_ListCtrl.InsertColumn( 0, _T("Title"), LVCFMT_LEFT, 80 );
		m_ListCtrl.InsertColumn( 1, _T("Difficulty"), LVCFMT_LEFT, 65 );
		m_ListCtrl.InsertColumn( 2, _T("Submissions"), LVCFMT_LEFT, 75 );
		m_ListCtrl.InsertColumn( 3, _T("Acceptance Rate"), LVCFMT_LEFT, 100 );
		m_ListCtrl.InsertColumn( 4, _T("Memory Rank"), LVCFMT_LEFT, 100 );
		m_ListCtrl.InsertColumn( 5, _T("Runtime Rank"), LVCFMT_LEFT, 100 );
	}
	
	// add problems
	populatelistctrl();
	
	// update selection
	if(theApp.getproblems().size()>0)
		m_ListCtrl.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CleetcodeDlg::OnSelChange(NMHDR* pNMHDR,LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if(pNMListView->uChanged != LVIF_STATE)
		return;

	// update members from list ctrl sel
	initfromlistctrl();
	
	// update ui from members
	UpdateData(false);
	const hint h(hint::t_problem);
	theApp.broadcasthint(&h);
}

void CleetcodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CleetcodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CleetcodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CleetcodeDlg::clearlistctrlsel(void)
{
	const leetcodeproblemsel s(this);

	auto i = s.getindices().cbegin(),end=s.getindices().cend();
	for(;i!=end;++i)
	{
		UINT nState = m_ListCtrl.GetItemState(*i, LVIS_SELECTED);
		nState &= ~LVIS_SELECTED;
		const BOOL b = m_ListCtrl.SetItemState(*i, nState, LVIS_SELECTED);
	}
}

void CleetcodeDlg::populatelistctrl(void)
{
	const std::vector<std::shared_ptr<const leetcodeproblem>>& v=theApp.getproblems();

	const bool bInsert = (m_ListCtrl.GetItemCount()!=int(v.size()));
	if(bInsert)
	{
		clearlistctrlsel();
		m_ListCtrl.DeleteAllItems();
	}

	auto i=v.cbegin(),end=v.cend(); 
	for(int n=0;i!=end;++i,++n)
	{
		CString csTitle;
		csTitle=(*i)->gettitle();

		if(bInsert)
		{
			LVITEM lvi;
			lvi.mask = LVIF_TEXT;
			lvi.iItem = n;
			lvi.iSubItem = 0;
			lvi.pszText = (LPTSTR)(LPCTSTR)(csTitle);
			const int nItem = m_ListCtrl.InsertItem( &lvi ); // nItem == n because unsorted list ctrl
		}
		else
			setlistctrlcolumntext(&m_ListCtrl,n,0,csTitle);
		setlistctrllayer(n,(*i).get());
	}
}

void CleetcodeDlg::setlistctrllayer(const int n,const leetcodeproblem *pL)
{
	CString cs;
	const BOOL b = m_ListCtrl.SetItemData( n, DWORD_PTR(pL));

	setlistctrlcolumntext(&m_ListCtrl,n,1,CString(pL->getdifficulty()));

	setlistctrlcolumntext(&m_ListCtrl,n,2,CString(pL->getsubmissions()));

	setlistctrlcolumntext(&m_ListCtrl,n,3,CString(pL->getacceptancerate()));

	setlistctrlcolumntext(&m_ListCtrl,n,4,CString(pL->getmemoryrank()));

	setlistctrlcolumntext(&m_ListCtrl,n,5,CString(pL->getruntimerank()));
}

void CleetcodeDlg::setlistctrlcolumntext(CListCtrl *pList,const int n,const int nC,const CString& cs)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = n;
	lvi.iSubItem = nC;
	lvi.pszText = (LPTSTR)(LPCTSTR)(cs);
	const BOOL b = pList->SetItem( &lvi );
}

void CleetcodeDlg::initfromlistctrl(void)
{
}

void CleetcodeDlg::onhint(const hint *p)
{
}

leetcodeproblemsel::leetcodeproblemsel(CleetcodeDlg *p):problemstg()
{
	m_vProblems.reserve(p->getlistctrl()->GetSelectedCount());
	m_vIndices.reserve(p->getlistctrl()->GetSelectedCount());
	POSITION pos = p->getlistctrl()->GetFirstSelectedItemPosition();
	while(pos!=NULL)
	{
		const int nSel = p->getlistctrl()->GetNextSelectedItem(pos);
		const leetcodeproblem *pL = reinterpret_cast<const leetcodeproblem*>(p->getlistctrl()->GetItemData(nSel));
		m_vProblems.push_back(pL);
		m_vIndices.push_back(nSel);
	}
}
