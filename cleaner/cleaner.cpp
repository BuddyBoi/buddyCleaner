#include "cleaner.h"

namespace cleaner
{
	//settings
	bool b_clear_temp;
	bool b_remove_hibernation;
	bool b_clear_steam_temp;
	bool b_empty_recycling_bin;
	bool b_clean_edge;
	bool b_clean_edge_history;
	bool b_clean_chrome;
	bool b_clean_chrome_history;
	bool b_clean_firefox;
	bool b_clean_firefox_history;
	bool b_clean_opera;
	bool b_clean_opera_history;
	bool b_clean_downloads;
	bool b_clean_shortcuts;
	bool b_clear_clipboard;

	//Remove all temp files in temp directories
	void clean_files()
	{
		//Windows temp
		if (b_clear_temp)
		{
			vec_clear_dirs.push_back(util::s_directory_temp);
			vec_clear_dirs.push_back("C:\\Windows\\Temp");
			vec_clear_dirs.push_back("C:\\Windows\\SoftwareDistribution\\Download");
			vec_clear_dirs.push_back("C:\\Windows\\Minidump");
			vec_clear_dirs.push_back("C:\\Windows\\Prefetch");
			vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\History");
			vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\WebCache");
			vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\");

			vec_delete_files.push_back("C:\\Windows\\Debug\\PASSWD.LOG");
		}		

		//Downloads folder
		if (b_clean_downloads)
		{
			vec_clear_dirs.push_back(util::s_user_dir + "\\Downloads\\");
		}

		//steam
		if (b_clear_steam_temp)
		{
			vec_clear_dirs.push_back(util::registry::registry_read("SOFTWARE\\Valve\\Steam", "SteamPath", HKEY_CURRENT_USER) + "/steamapps/temp/");
		}		

		//Hibernation
		if (b_remove_hibernation)
		{
			vec_delete_files.push_back("C:\\hiberfil.sys");
		}	

		//Clear the recycling bin
		if (b_empty_recycling_bin)
		{
			if (SHEmptyRecycleBin(NULL, util::str_to_wstring(util::s_windows_dir).c_str(), SHERB_NOCONFIRMATION != 0)) //ignore
			{
				util::ulog("Failed to empty recycling bin");
			}
			else
			{
				util::ulog("Recycling bin successfully emptied");
			}
		}

		//Chrome
		if (b_clean_chrome)
		{
			vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies-journal");

			if (b_clean_chrome_history)
			{

			}
		}

		//firefox
		if (b_clean_firefox)
		{
			WIN32_FIND_DATAA findFileData;
			std::string firefoxPath = util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\*";
			std::string profilePath = ".default-release";
			HANDLE find = FindFirstFileA(firefoxPath.c_str(), &findFileData);
			
			//if needed ill add this to a method for the other firefox options
			if (find != INVALID_HANDLE_VALUE)
			{
				do
				{
					std::string fd(findFileData.cFileName);
					if (fd.find(profilePath) != std::string::npos)
					{
						vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\entries");
						vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\doomed");
						vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\index");
						break;
					}
				} while (FindNextFileA(find, &findFileData));
				FindClose(find);
			}
			else
			{
				util::ulog("Failed to find Mozilla Firefox Profile");
			}
		}

		//opera
		if (b_clean_opera)
		{
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies-journal");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies-journal");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons-journal");

			if (b_clean_opera_history)
			{
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History");
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History-journal");
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History");
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History-journal");
			}
		}

		//edge
		if (b_clean_edge)
		{
			vec_clear_dirs.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies");
			vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies-journal");

			if (b_clean_edge_history)
			{
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History");
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History-journal");
				vec_delete_files.push_back(util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History Provider Cache");
			}
		}

		//check shortcuts - experimental
		if (b_clean_shortcuts)
		{
			std::string str_desktop_dir = util::s_user_dir + "\\Desktop\\";
			for (const auto& entry : std::experimental::filesystem::directory_iterator(str_desktop_dir))
			{
				try
				{
					auto path = entry.path();
					std::string s_path_name = entry.path().string();
					std::string s_path_ext = s_path_name.substr(s_path_name.find_last_of('.'), s_path_name.find_last_of('.') + 3);

					//If path is directory skip to next file
					bool b_is_directory = std::experimental::filesystem::is_directory(s_path_name);
					if (b_is_directory)
						continue;

					bool b_is_shortcut = (s_path_ext == ".lnk");
					if (!b_is_shortcut)
						continue;

					std::string s_shortcut_path = util::get_shortcut_path(s_path_name);
					if (!util::path_exists(s_shortcut_path))
					{
						vec_delete_files.push_back(s_path_name);
					}
				}
				catch (std::exception e) {}
			}
		}

		//clears clipboard
		if (b_clear_clipboard)
		{
			if (OpenClipboard(NULL) != 0)
			{
				EmptyClipboard();
				CloseClipboard();
				util::ulog("Successfully cleared clipboard");
			}
			else
			{
				util::ulog("Failed to clear clipboard");
			}
		}

		//Iterate directory list and clear each
		for (std::string s : vec_clear_dirs)
		{
			util::directory_clear(s);
		}
		for (std::string x : vec_delete_files)
		{
			util::file_delete(x);
		}
	}

	//Check for broken or empty shortcuts on the user's desktop
	void check_shortcuts()
	{
		
	}

	//Start method for cleaner
	void cleanup()
	{
		clean_files();
	}
}