#include <iostream>
#include <string>
#include <Windows.h>
#include <fileapi.h>


#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <experimental/filesystem>
#pragma warning(disable:4996)

namespace Util
{
	//settings
	static bool b_logging_enabled = true;
	static bool b_elevated_remove_enabled = true;

	static std::string s_computer_name = getenv("COMPUTERNAME");
	static std::string s_user_dir = getenv("USERPROFILE");
	static std::string s_directory_temp = getenv("TEMP");
	static auto i_computer_processor_cores = getenv("NUMBER_OF_PROCESSORS");
	
	//checks if the path (file or directory) exists
	bool path_exists(std::string path)
	{
		return std::experimental::filesystem::exists(path);
	}

	//Weak logging system
	void log(std::string message)
	{
		if (!b_logging_enabled)
			return;

		std::cout << ("Log: %s", message) << '\n';
	}

	//Delete system-protected files or in-use files
	void file_elevated_delete(std::string path)
	{
		if (!b_elevated_remove_enabled)
		{
			log("Elevated remove is disabled.");
			return;
		}

		//Building path with \\.\ before the directory. This (sometimes) allows for deletion even if in-use
		std::string s_temp = "\\\\.\\" + path;

		//Converting string to LPCWSTR
		std::wstring ws_temp = std::wstring(path.begin(), path.end());
		LPCWSTR directory = ws_temp.c_str();

		DeleteFile(directory);
	}

	//Delete method
	void file_delete(std::string path)
	{
		if (path_exists(path))
		{
			log("Attempting to delete " + path);
			remove(path.c_str());
			if (path_exists(path))
			{
				log("Failed to delete " + path);
				log("Attempting elevated remove");
				file_elevated_delete(path);

				if (path_exists(path))
				{
					log("Failed to delete with elevation " + path);
					return;
				}
			}
			log("Removed " + path);
		}			
	}

	//Iterate a directory and clear it's contents
	void directory_clear(std::string directory)
	{
		for (const auto &entry : std::experimental::filesystem::directory_iterator(directory))
		{
			auto path = entry.path();
			std::string s_path_name = entry.path().string();
			file_delete(s_path_name);
		}
	}

	namespace Registry
	{
		std::string registry_read_current_user(std::string reg_path, std::string reg_key)
		{
			try
			{
				HKEY h_key = nullptr;
				if (RegOpenKeyExA(HKEY_CURRENT_USER, reg_path.c_str(), 0, KEY_QUERY_VALUE, &h_key) != ERROR_SUCCESS)
				{
					RegCloseKey(h_key);

					log("Failed to find registry directory");
					return "Error";
				}

				char path_reg[MAX_PATH]; path_reg[0] = '-'; //Idk dude
				DWORD reg_path_size = sizeof(path_reg) - sizeof(char);

				if (RegQueryValueExA(h_key, reg_key.c_str(), nullptr, nullptr, (LPBYTE)(path_reg + 1), &reg_path_size) != ERROR_SUCCESS)
				{
					RegCloseKey(h_key);
					log("Failed to read registry key");
					return "error";
					
				}
				RegCloseKey(h_key);

				auto return_reg = std::string(path_reg);
				return_reg = return_reg.erase(0, 1); //remove idk dude
				return return_reg;
			}
			catch (std::exception e)
			{
				log("Registry read failure");
				return "Error";
			}			
		}
	}
}

namespace Cleaner
{
	//List of directories to clear
	static std::vector<std::string> vec_clear_dirs;
	static std::vector<std::string> vec_delete_files;

	//Cleaner settings
	static bool b_clear_temp = false;
	static bool b_remove_hibernation = false;
	static bool b_clear_steam_temp = true;

	//Removing hibernation from your computer frees up a lot of space
	void remove_hibernation()
	{
		static std::string hibernation_file = "C:\\hiberfil.sys";
		Util::log("Checking if hibernation file exists");
		if (Util::path_exists(hibernation_file))
		{
			Util::log("Hibernation file exists. Attempting to remove");

			try
			{
				remove("C:\\hiberfil.sys");
				Util::log("Hibernation file successfully removed.");
			}
			catch (std::exception e)
			{
				Util::log("Failed to remove hibernation file. Try running as admin or manually removing");
			}
		}
		else
		{
			Util::log("Failed to find hibernation file");
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
			if (Util::path_exists(x))
			{
				Util::log("File " + x + " exists. Attempting to delete");
				remove(x.c_str());
				if (Util::path_exists(x))
					Util::log("Do not have permissions to delete file. Run as administrator");
			}
			else
			{
				Util::log("Can not find " + x);
			}				
		}
	}

	//If setting is enabled do operation
	void Cleanup()
	{
		if (b_remove_hibernation)
			remove_hibernation();		

		if (b_clear_temp)
			remove_temp_files();
	}	
}

int main()
{	
	//Display Message
	std::cout << "==Buddy cleaner==\n\nIt is recommended to run this program as admin.\nDoing so allows for more files to be cleaned.\nThe following questions are to be answered as 1=yes, 0=no\n\n";
	
	//Get settings from input
	std::cout << "Clear temp directories=";
	std::cin >> Cleaner::b_clear_temp;

	std::cout << "Disable hibernation mode=";
	std::cin >> Cleaner::b_remove_hibernation;

	std::cout << "Elevated removal(requires admin)=";
	std::cin >> Util::b_elevated_remove_enabled;

	std::cout << "Clear steam temp(requires clear temp directories on)=";
	std::cin >> Cleaner::b_clear_temp;

	//Run cleaner	
	Cleaner::Cleanup();
	std::cout << "Program finished.\n";

	//Never exit program
	while (1){}
}