#include "Cleaner.h"

namespace Cleaner
{
	//settings
	bool b_clear_temp;
	bool b_remove_hibernation;
	bool b_clear_steam_temp;
	bool b_clean_chrome;

	//Remove all temp files in temp directories
	void cleanup_files()
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

	//removes chromes cookies and cache
	void clean_chrome()
	{
		vec_clear_dirs.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache"); //chrome
		vec_delete_files.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies"); //chrome

		for (std::string s : vec_clear_dirs)
		{
			Util::directory_clear(s);
		}

		for (std::string x : vec_delete_files)
		{
			Util::file_delete(x);
		}
	}

	//adding this later my brain is very small
	void clean_firefox()
	{
		vec_clear_dirs.push_back("C:\\Users\\" + Util::s_user_dir + "\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\" + +"\\Cache2"); //firefox
	}

	//If setting is enabled do operation
	void Cleanup()
	{
		cleanup_files();
		clean_chrome();
	}
}