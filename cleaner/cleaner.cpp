#include <iostream>
#include <string>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <experimental/filesystem>
#pragma warning(disable:4996)

namespace Util
{
	static bool b_logging_enabled = true;
	static std::string s_computer_name = getenv("COMPUTERNAME");
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

	//Iterate a directory and clear it's contents
	void directory_clear(std::string directory)
	{
		for (const auto &entry : std::experimental::filesystem::directory_iterator(directory))
		{
			auto path = entry.path();
			std::string s_path_name = entry.path().string();
			try
			{
				remove(path);
				log("Removed: " + s_path_name);
			}
			catch(std::exception e)
			{
				log("Failed to remove " + s_path_name);
				continue;
			}			
		}
	}
}

namespace Cleaner
{
	//List of directories to clear
	static std::vector<std::string> vec_clear_dirs;

	//Cleaner settings
	static bool b_clear_temp = false;
	static bool b_remove_hibernation = false;

	//Remove files. Mostly just temp files for now
	void Cleanup()
	{
		vec_clear_dirs.push_back(Util::s_directory_temp);
		vec_clear_dirs.push_back("C:\\Windows\\Temp");
		vec_clear_dirs.push_back("C:\\Windows\\SoftwareDistribution\\Download");
		vec_clear_dirs.push_back("C:\\Windows\\Minidump");
		
		//Iterate directory list and clear each
		for (std::string s : vec_clear_dirs)
		{
			Util::directory_clear(s);
		}
	}

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
}

int main()
{	
	//Display Message
	std::cout << "==Buddy cleaner==\n\nIt is recommended to run this program as admin.\nDoing so allows for more files to be cleaned.\nThe following questions are to be answered as 1=yes, 0=no\n\n";
	
	//Get settings from input
	std::cout << "Clear temporary folders=";
	std::cin >> Cleaner::b_clear_temp;

	std::cout << "Disable hibernation mode=";
	std::cin >> Cleaner::b_remove_hibernation;

	//Run cleaner
	Cleaner::Cleanup();
	std::cout << "Program finished.\n";

	//Never exit program
	while (1){}
}