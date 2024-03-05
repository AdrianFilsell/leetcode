
// leetcode.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "leetcodeproblem.h"

#include <vector>
#include <memory>

class CleetcodeDlg;
class leetcodedescdlg;
class leetcoderundlg;
class leetcodeexamplesdlg;
class leetcodereasoningdlg;
class hint;

// CleetcodeApp:
// See leetcode.cpp for the implementation of this class
//

class CleetcodeApp : public CWinApp
{
public:
	CleetcodeApp();

// Overrides
public:
	virtual BOOL InitInstance();

	CleetcodeDlg *getdlg(void)const;
	leetcodedescdlg *getdescdlg(void)const;
	leetcoderundlg *getrundlg(void)const;
	leetcodeexamplesdlg *getexamplesdlg(void)const;
	leetcodereasoningdlg *getreasoningdlg(void)const;
	const std::vector<std::shared_ptr<const leetcodeproblem>>& getproblems(void)const{return m_vProblems;}

	void broadcasthint(const hint *p);

// Implementation

	DECLARE_MESSAGE_MAP()
protected:
	std::vector<std::shared_ptr<const leetcodeproblem>> m_vProblems;

	void createproblems(void);
	void onhint(const hint *p);
};

class CFocusImmutableSelEdit : public CEdit {
public:
    DECLARE_MESSAGE_MAP()
    afx_msg UINT OnGetDlgCode() {
        // Return default value, removing the DLGC_HASSETSEL flag
        return ( CEdit::OnGetDlgCode() & ~DLGC_HASSETSEL );
    }
};

extern CleetcodeApp theApp;
