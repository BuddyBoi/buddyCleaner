#pragma once
#include "stdafx.h"
#include "Utility.h"

namespace cleaner
{
	//List of directories to clear
	static std::vector<std::string> vec_clear_dirs;
	static std::vector<std::string> vec_delete_files;

	//Cleaner settings
	extern bool b_clear_temp;
	extern bool b_remove_hibernation;
	extern bool b_clear_steam_temp;
	extern bool b_empty_recycling_bin;
	extern bool b_clean_edge;
	extern bool b_clean_edge_history;
	extern bool b_clean_chrome;
	extern bool b_clean_chrome_history;
	extern bool b_clean_firefox;
	extern bool b_clean_firefox_history;
	extern bool b_clean_opera;
	extern bool b_clean_opera_history;
	extern bool b_clean_downloads;
	extern bool b_clean_shortcuts;
	extern bool b_clear_clipboard;

	void clean_files();
	void check_shortcuts();
	void cleanup();
}