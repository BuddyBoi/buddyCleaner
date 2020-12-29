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
	
	void cleanup_files();
	void Cleanup();
}