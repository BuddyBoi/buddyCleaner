#include "Cleaner.h"

namespace Cleaner
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

	//Remove all temp files in temp directories
	void clean_files()
	{
		//Windows temp
		if (b_clear_temp)
		{
			vec_clear_dirs.push_back(Util::s_directory_temp);
			vec_clear_dirs.push_back("C:\\Windows\\Temp");
			vec_clear_dirs.push_back("C:\\Windows\\SoftwareDistribution\\Download");
			vec_clear_dirs.push_back("C:\\Windows\\Minidump");
			vec_clear_dirs.push_back("C:\\Windows\\Prefetch");
			vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\History");
			vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\WebCache");
			vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\");

			vec_delete_files.push_back("C:\\Windows\\Debug\\PASSWD.LOG");
		}		

		//steam
		if (b_clear_steam_temp)
		{
			vec_clear_dirs.push_back(Util::Registry::registry_read("SOFTWARE\\Valve\\Steam", "SteamPath", HKEY_CURRENT_USER) + "/steamapps/temp/");
		}		

		//Hibernation
		if (b_remove_hibernation)
		{
			vec_delete_files.push_back("C:\\hiberfil.sys");
		}	

		//Clear the recycling bin
		if (b_empty_recycling_bin)
		{
			if (SHEmptyRecycleBin(NULL, Util::str_to_wstring(Util::s_windows_dir).c_str(), SHERB_NOCONFIRMATION != 0)) //ignore
			{
				Util::ulog("Failed to empty recycling bin");
			}
			else
			{
				Util::ulog("Recycling bin successfully emptied");
			}
		}

		//Chrome
		if (b_clean_chrome)
		{
			vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies-journal");

			if (b_clean_chrome_history)
			{

			}
		}

		//firefox
		if (b_clean_firefox)
		{
			WIN32_FIND_DATAA findFileData;
			std::string firefoxPath = Util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\*";
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
						vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\entries");
						vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + fd + "\\cache2\\doomed");
					}
					else
					{
						Util::ulog("Failed to find Mozilla Firefox Profile");
					}
				} while (FindNextFileA(find, &findFileData));
				FindClose(find);
			}
			else
			{
				Util::ulog("Failed to find Mozilla Firefox Profile");
			}
		}

		//opera
		if (b_clean_opera)
		{
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies-journal");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Extension Cookies-journal");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Favicons-journal");

			if (b_clean_opera_history)
			{
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History");
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History-journal");
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History");
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History-journal");
			}
		}

		//edge
		if (b_clean_edge)
		{
			vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies");
			vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cookies-journal");

			if (b_clean_edge_history)
			{
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History");
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History-journal");
				vec_delete_files.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\History Provider Cache");
			}
		}

		//Iterate directory list and clear each
		for (std::string s : vec_clear_dirs)
		{
			Util::directory_clear(s);
		}
		for (std::string x : vec_delete_files)
		{
			Util::file_delete(x);
		}
	}

	//Start method for cleaner
	void Cleanup()
	{
		clean_files();
	}
}