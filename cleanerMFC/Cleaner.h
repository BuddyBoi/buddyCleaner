#pragma once
#include "Utility.h"

namespace cleaner
{
	//List of directories to clear
	static std::vector<std::string> vec_clear_dirs;
	static std::vector<std::string> vec_delete_files;

	void clean_files();
	void check_shortcuts();
	void cleanup();
}