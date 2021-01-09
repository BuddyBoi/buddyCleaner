
// cleanerMFCDlg.h : header file
//

#pragma once


// CcleanerMFCDlg dialog
class CcleanerMFCDlg : public CDialogEx
{
// Construction
public:
	CcleanerMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLEANERMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
public:
	// Listbox for logging
	CListBox CListBoxLog;
	// Bool if is checked
	BOOL Chk_ClearWindowsTemp;
	BOOL Chk_ClearSteamTmp;
	BOOL Chk_RemoveHibernation;
	BOOL Chk_ClearRecycling;
	BOOL Chk_EdgeCookies;
	BOOL Chk_ClearEdgeHistory;
	BOOL Chk_ChromeCookies;
	BOOL Chk_ChromeHistory;
	BOOL Chk_FirefoxCookies;
	BOOL Chk_FirefoxHistory;
	BOOL Chk_OperaCookies;
	BOOL Chk_OperaHistory;
	BOOL Chk_ClearDownloads;
	BOOL Chk_CleanShortcuts;
	BOOL Chk_ClearClipboard;
	BOOL Chk_ClearDNS;
	BOOL Chk_CleanSpotify;
	CButton chk_test123;
	CButton chk_ClearClipboard;
	CButton btn_StartCleaner;
	CButton chk_FirefoxHistory;
	CButton chk_FirefoxCookies;
	CButton chk_ChromeHistory;
	CButton chk_ChromeCookies;
	CButton chk_EdgeHistory;
	CButton chk_EdgeCookies;
	CButton chk_ClearRecycling;
	CButton chk_RemoveHibernation;
	CButton chk_ClearSteamTemp;
	CButton chk_WindowsTemp;
	CButton chk_OperaHistory;
	CButton chk_OperaCookies;
	CButton chk_Downloads;
	CButton chk_Shortcuts;
	CButton chk_DNS;
	CButton chk_Spotify;
};
