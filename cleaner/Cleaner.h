#pragma once
#include "stdafx.h"
#include "Utility.h"

namespace Cleaner
{
	//List of directories to clear
	static std::vector<std::string> vec_clear_dirs;
	static std::vector<std::string> vec_delete_files;

	//Cleaner settings
	extern bool b_clear_temp;
	extern bool b_remove_hibernation;
	extern bool b_clear_steam_temp;
	extern bool b_empty_recycling_bin;
	extern bool b_clean_chrome;
	extern bool b_clean_firefox;
	extern bool b_clean_opera;

	void clean_temp_files();
	void empty_recycling_bin();
	void clean_chrome();
	void clean_firefox();
	void clean_opera();
	void Cleanup();
}