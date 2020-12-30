#include "Cleaner.h"

namespace Cleaner
{
	//settings
	bool b_clear_temp;
	bool b_remove_hibernation;
	bool b_clear_steam_temp;
	bool b_empty_recycling_bin;
	bool b_clean_chrome;
	bool b_clean_firefox;
	bool b_clean_opera;

	//Remove all temp files in temp directories
	void clean_temp_files()
	{
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

	//empties recycling bin 
	void empty_recycling_bin()
	{
		if (b_empty_recycling_bin)
		{
			std::string path = "C:\\Windows";
			std::wstring ws_temp = std::wstring(path.begin(), path.end());
			LPCWSTR drive = ws_temp.c_str();
			if (SHEmptyRecycleBin(NULL, drive, SHERB_NOCONFIRMATION != 0)) //ignore
			{
				Util::ulog("Failed to empty recycling bin");
			}
			else
			{
				Util::ulog("Recycling bin successfully emptied");
			}
		}
	}

	//chromes cookies and cache
	void clean_chrome()
	{
		if (b_clean_chrome)
		{
			vec_clear_dirs.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies-journal");

			for (std::string s : vec_clear_dirs)
			{
				Util::directory_clear(s);
			}

			for (std::string x : vec_delete_files)
			{
				Util::file_delete(x);
			}
		}
	}

	//adding this later my brain is very small
	void clean_firefox()
	{
		if (b_clean_firefox)
		{
			vec_clear_dirs.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + +"\\Cache2");
		}
	}

	//opera cookies and cache
	void clean_opera()
	{
		if (b_clean_opera)
		{
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Media History-journal");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\History-journal");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies");
			vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Roaming\\Opera Software\\Opera Stable\\Cookies-journal");

			for (std::string x : vec_delete_files)
			{
				Util::file_delete(x);
			}
		}
	}

	//If setting is enabled do operation
	void Cleanup()
	{
		clean_temp_files();
		empty_recycling_bin();
		clean_chrome();
		clean_opera();
		
	}
}