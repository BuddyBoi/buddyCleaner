
// cleanerMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "cleanerMFC.h"
#include "cleanerMFCDlg.h"
#include "afxdialogex.h"
#include "Cleaner.h"
#include "systeminfo.h"
#include "utility.h"

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
	DDX_Control(pDX, IDC_CHECK2, chk_test123);
	DDX_Control(pDX, IDC_CHECK15, chk_ClearClipboard);
	DDX_Control(pDX, IDC_BUTTON1, btn_StartCleaner);
	DDX_Control(pDX, IDC_CHECK10, chk_FirefoxHistory);
	DDX_Control(pDX, IDC_CHECK6, chk_FirefoxCookies);
	DDX_Control(pDX, IDC_CHECK18, chk_ChromeHistory);
	DDX_Control(pDX, IDC_CHECK17, chk_ChromeCookies);
	DDX_Control(pDX, IDC_CHECK9, chk_EdgeHistory);
	DDX_Control(pDX, IDC_CHECK16, chk_EdgeCookies);
	DDX_Control(pDX, IDC_CHECK5, chk_ClearRecycling);
	DDX_Control(pDX, IDC_CHECK4, chk_RemoveHibernation);
	DDX_Control(pDX, IDC_CHECK3, chk_ClearSteamTemp);
	DDX_Control(pDX, IDC_CHECK1, chk_WindowsTemp);
	DDX_Control(pDX, IDC_CHECK12, chk_OperaHistory);
	DDX_Control(pDX, IDC_CHECK8, chk_OperaCookies);
	DDX_Control(pDX, IDC_CHECK11, chk_Downloads);
	DDX_Control(pDX, IDC_CHECK7, chk_Shortcuts);
	DDX_Control(pDX, IDC_CHECK14, chk_DNS);
	DDX_Control(pDX, IDC_CHECK13, chk_Spotify);
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
	//having all these here is temp while cleaner call doesnt work

	//Windows temp
	if (chk_WindowsTemp.GetCheck())
	{
		//MessageBox(NULL, L"YES", L"YES", 0);
		cleaner::vec_clear_dirs.push_back(systeminfo::s_directory_temp);
		cleaner::vec_clear_dirs.push_back("C:\\Windows\\Temp");
		cleaner::vec_clear_dirs.push_back("C:\\Windows\\SoftwareDistribution\\Download");
		cleaner::vec_clear_dirs.push_back("C:\\Windows\\Minidump");
		cleaner::vec_clear_dirs.push_back("C:\\Windows\\Prefetch");
		cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\History");
		cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\WebCache");
		cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\");

		cleaner::vec_delete_files.push_back("C:\\Windows\\Debug\\PASSWD.LOG");

	}

	//Downloads folder
	if (chk_Downloads.GetCheck())
	{
		cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\Downloads\\");
	}

	//steam
	if (chk_ClearSteamTemp.GetCheck())
	{
		cleaner::vec_clear_dirs.push_back(util::registry::registry_read("SOFTWARE\\Valve\\Steam", "SteamPath", HKEY_CURRENT_USER) + "/steamapps/temp/");
	}

	//Hibernation
	if (chk_RemoveHibernation.GetCheck())
	{
		cleaner::vec_delete_files.push_back("C:\\hiberfil.sys");
	}

	//Clear the recycling bin
	if (chk_ClearRecycling.GetCheck())
	{
		if (SHEmptyRecycleBin(NULL, util::str_to_wstring(systeminfo::s_windows_dir).c_str(), SHERB_NOCONFIRMATION != 0))
		{
			CListBoxLog.AddString(L"Failed to empty recycling bin");
		}
		else
		{
			CListBoxLog.AddString(L"Recycling bin successfully emptied");
		}
	}

	//Chrome
	if (chk_ChromeCookies.GetCheck())
	{
		if (util::path_exists(systeminfo::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default"))
		{
			cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies-journal");

			if (Chk_ChromeHistory)
			{

			}
			else
			{
				CListBoxLog.AddString(L"Chrome directory does not exist");
			}
		}
		else
		{
			CListBoxLog.AddString(L"Chrome directory does not exist");

		}
	}

	//firefox
	if (chk_FirefoxCookies.GetCheck())
	{
		if (util::path_exists(systeminfo::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles"))
		{
			std::string firefoxPath = systeminfo::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\*";
			std::string profilePath = ".default-release";

			std::string fd = util::get_first_file_name(firefoxPath, profilePath);
			cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\entries");
			cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\doomed");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\index");
		}
		else
		{
			CListBoxLog.AddString(L"Firefox directory does not exist");
		}
	}

	//opera
	if (chk_OperaCookies.GetCheck())
	{
		if (util::path_exists(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable"))
		{
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies-journal");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies-journal");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons-journal");

			if (chk_OperaHistory.GetCheck())
			{
				cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History");
				cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History-journal");
				cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History");
				cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History-journal");
			}
			else
			{
				CListBoxLog.AddString(L"Opera directory does not exist");
			}
		}
		else
		{
			CListBoxLog.AddString(L"Opera directory does not exist");
		}
	}

	//edge
	if (chk_EdgeCookies.GetCheck())
	{
		cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache");
		cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies");
		cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies-journal");

		if (chk_EdgeHistory.GetCheck())
		{
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History-journal");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History Provider Cache");
		}
	}

	//check shortcuts - experimental
	if (Chk_CleanShortcuts)
	{
		std::string str_desktop_dir = systeminfo::s_user_dir + "\\Desktop\\";
		for (const auto& entry : std::experimental::filesystem::directory_iterator(str_desktop_dir))
		{
			try
			{
				auto path = entry.path();
				std::string s_path_name = entry.path().string();
				std::string s_path_ext = s_path_name.substr(s_path_name.find_last_of('.'), s_path_name.find_last_of('.') + 3);

				//If path is directory skip to next file
				bool b_is_directory = util::path_exists(s_path_name);
				if (b_is_directory)
					continue;

				bool b_is_shortcut = (s_path_ext == ".lnk");
				if (!b_is_shortcut)
					continue;

				std::string s_shortcut_path = util::get_shortcut_path(s_path_name);
				if (!util::path_exists(s_shortcut_path))
				{
					cleaner::vec_delete_files.push_back(s_path_name);
				}
			}
			catch (std::exception e) {}
		}
	}

	//clears clipboard
	if (chk_ClearClipboard.GetCheck())
	{
		if (OpenClipboard() != 0)
		{
			EmptyClipboard();
			CloseClipboard();
			CListBoxLog.AddString(L"Successfully cleared clipboard");
		}
		else
		{
			CListBoxLog.AddString(L"Failed to clear clipboard");
		}
	}


	//clears dns cache
	if (chk_DNS.GetCheck())
	{
		system("ipconfig /flushdns");
		CListBoxLog.AddString(L"DNS Cache flushed");
	}

	//spotify cache
	if (chk_Spotify.GetCheck())
	{
		//windows version
		if (util::path_exists(systeminfo::s_user_dir + "\\AppData\\Local\\Packages\\SpotifyAB.SpotifyMusic_zpdnekdrzrea0"))
		{
			cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Packages\\SpotifyAB.SpotifyMusic_zpdnekdrzrea0\\LocalCache\\Spotify\\Data");
			cleaner::vec_clear_dirs.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Packages\\SpotifyAB.SpotifyMusic_zpdnekdrzrea0\\LocalCache\\Spotify\\Browser\\Cache");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Packages\\SpotifyAB.SpotifyMusic_zpdnekdrzrea0\\LocalCache\\Spotify\\Browser\\Cookies");
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Local\\Packages\\SpotifyAB.SpotifyMusic_zpdnekdrzrea0\\LocalCache\\Spotify\\Browser\\Cookies-journal");
		}
		else
		{
			CListBoxLog.AddString(L"Spotify windows directory does not exist");
		}

		//official version
		if (util::path_exists(systeminfo::s_user_dir + "\\AppData\\Roaming\\Spotify\\Users\\"))
		{
			std::string profilePath = "-user";
			std::string spotifyPath = systeminfo::s_user_dir + "\\AppData\\Roaming\\Spotify\\Users\\*";
			std::string userName = util::get_first_file_name(spotifyPath, profilePath);
			cleaner::vec_delete_files.push_back(systeminfo::s_user_dir + "\\AppData\\Roaming\\Spotify\\Users\\" + userName + "\\local-files.bnk");
		}
		else
		{
			CListBoxLog.AddString(L"Spotify desktop directory does not exist");
		}
	}

	//Iterate directory list and clear each
	for (std::string s : cleaner::vec_clear_dirs)
	{
		util::directory_clear(s);
	}
	for (std::string x : cleaner::vec_delete_files)
	{
		util::file_delete(x);
	}
}