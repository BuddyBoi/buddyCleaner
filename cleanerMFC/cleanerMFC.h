
// cleanerMFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CcleanerMFCApp:
// See cleanerMFC.cpp for the implementation of this class
//

class CcleanerMFCApp : public CWinApp
{
public:
	CcleanerMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CcleanerMFCApp theApp;
