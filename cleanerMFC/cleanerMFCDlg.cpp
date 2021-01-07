
// cleanerMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "cleanerMFC.h"
#include "cleanerMFCDlg.h"
#include "afxdialogex.h"

#include "Cleaner.h"

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


// CcleanerMFCDlg dialog



CcleanerMFCDlg::CcleanerMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLEANERMFC_DIALOG, pParent)
	, Chk_ClearWindowsTemp(FALSE)
	, Chk_ClearSteamTmp(FALSE)
	, Chk_RemoveHibernation(FALSE)
	, Chk_ClearRecycling(FALSE)
	, Chk_EdgeCookies(FALSE)
	, Chk_ClearEdgeHistory(FALSE)
	, Chk_ChromeCookies(FALSE)
	, Chk_ChromeHistory(FALSE)
	, Chk_FirefoxCookies(FALSE)
	, Chk_FirefoxHistory(FALSE)
	, Chk_OperaCookies(FALSE)
	, Chk_OperaHistory(FALSE)
	, Chk_ClearDownloads(FALSE)
	, Chk_CleanShortcuts(FALSE)
	, Chk_ClearClipboard(FALSE)
	, Chk_ClearDNS(FALSE)
	, Chk_CleanSpotify(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcleanerMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, CListBoxLog);
	DDX_Check(pDX, IDC_CHECK1, Chk_ClearWindowsTemp);
	DDX_Check(pDX, IDC_CHECK3, Chk_ClearSteamTmp);
	DDX_Check(pDX, IDC_CHECK4, Chk_RemoveHibernation);
	DDX_Check(pDX, IDC_CHECK5, Chk_ClearRecycling);
	DDX_Check(pDX, IDC_CHECK16, Chk_EdgeCookies);
	DDX_Check(pDX, IDC_CHECK9, Chk_ClearEdgeHistory);
	DDX_Check(pDX, IDC_CHECK17, Chk_ChromeCookies);
	DDX_Check(pDX, IDC_CHECK18, Chk_ChromeHistory);
	DDX_Check(pDX, IDC_CHECK6, Chk_FirefoxCookies);
	DDX_Check(pDX, IDC_CHECK10, Chk_FirefoxHistory);
	DDX_Check(pDX, IDC_CHECK8, Chk_OperaCookies);
	DDX_Check(pDX, IDC_CHECK12, Chk_OperaHistory);
	DDX_Check(pDX, IDC_CHECK11, Chk_ClearDownloads);
	DDX_Check(pDX, IDC_CHECK15, Chk_CleanShortcuts);
	DDX_Check(pDX, IDC_CHECK7, Chk_CleanShortcuts);
	DDX_Check(pDX, IDC_CHECK15, Chk_ClearClipboard);
	DDX_Check(pDX, IDC_CHECK14, Chk_ClearDNS);
	DDX_Check(pDX, IDC_CHECK13, Chk_CleanSpotify);
}

BEGIN_MESSAGE_MAP(CcleanerMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CcleanerMFCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CcleanerMFCDlg message handlers

BOOL CcleanerMFCDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcleanerMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcleanerMFCDlg::OnPaint()
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
HCURSOR CcleanerMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcleanerMFCDlg::OnBnClickedButton1()
{
	CListBoxLog.AddString(L"YES");
	cleaner::cleanup();
}
