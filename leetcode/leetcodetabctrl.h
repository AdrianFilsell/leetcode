#pragma once

#include <memory>
#include "leetcodedescdlg.h"
#include "leetcoderundlg.h"
#include "leetcodeexamplesdlg.h"
#include "leetcodereasoningdlg.h"

// leetcodetabctrl

class leetcodetabctrl : public CTabCtrl
{
	DECLARE_DYNAMIC(leetcodetabctrl)

public:
	leetcodetabctrl();
	virtual ~leetcodetabctrl();

	// accessors	
	leetcodedescdlg *getdescdlg(void)const{return m_spDescDlg.get();}
	leetcodeexamplesdlg *getexamplesdlg(void)const{return m_spExamplesDlg.get();}
	leetcoderundlg *getrundlg(void)const{return m_spRunDlg.get();}
	leetcodereasoningdlg *getreasoningdlg(void)const{return m_spReasoningDlg.get();}
	
	// overrides
	virtual void PreSubclassWindow(void);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg BOOL OnSelChange(NMHDR* pNMHDR, LRESULT* pResult);

	std::shared_ptr<leetcodedescdlg> m_spDescDlg;
	std::shared_ptr<leetcodeexamplesdlg> m_spExamplesDlg;
	std::shared_ptr<leetcoderundlg> m_spRunDlg;
	std::shared_ptr<leetcodereasoningdlg> m_spReasoningDlg;

	void showhide(void);
	void updatelayout(void);
	CRect getchildctrlrect(void);
	void commoninit(void);
	void createdlgs(void);
};


