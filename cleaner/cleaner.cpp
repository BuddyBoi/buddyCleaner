#include "Cleaner.h"

namespace Cleaner
{
	//settings
	bool b_clear_temp;
	bool b_remove_hibernation;
	bool b_clear_steam_temp;

	//Removing hibernation from your computer frees up a lot of space
	void remove_hibernation()
	{
		static std::string hibernation_file = "C:\\hiberfil.sys";
		Util::ulog("Checking if hibernation file exists");
		if (Util::path_exists(hibernation_file))
		{
			Util::ulog("Hibernation file exists. Attempting to remove");

			try
			{
				remove("C:\\hiberfil.sys");
				Util::ulog("Hibernation file successfully removed.");
			}
			catch (std::exception e)
			{
				Util::ulog("Failed to remove hibernation file. Try running as admin or manually removing");
			}
		}
		else
		{
			Util::ulog("Failed to find hibernation file");
		}
	}

	//Remove all temp files in temp directories
	void remove_temp_files()
	{
		vec_clear_dirs.push_back(Util::s_directory_temp);
		vec_clear_dirs.push_back("C:\\Windows\\Temp");
		vec_clear_dirs.push_back("C:\\Windows\\SoftwareDistribution\\Download");
		vec_clear_dirs.push_back("C:\\Windows\\Minidump");
		vec_clear_dirs.push_back("C:\\Windows\\Prefetch");
		vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\History");
		vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Local\\Microsoft\\Windows\\WebCache");
		vec_clear_dirs.push_back(Util::s_user_dir + "\\AppData\\Roaming\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\");

		//steam
		if (b_clear_steam_temp)
		{
			vec_clear_dirs.push_back(Util::Registry::registry_read_current_user("SOFTWARE\\Valve\\Steam", "SteamPath") + "/steamapps/temp/");
		}

		vec_delete_files.push_back("C:\\Windows\\Debug\\PASSWD.LOG");

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

	//If setting is enabled do operation
	void Cleanup()
	{
		if (b_remove_hibernation == 1)
		{
			
			Util::ulog("Is one");
			remove_hibernation();
		}
		std::cout << b_remove_hibernation;

		if (b_clear_temp == 1)
			remove_temp_files();
	}
}