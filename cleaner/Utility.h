#pragma once
#include "stdafx.h"

namespace Util
{
	enum file_types
	{
		file_normal = 0x80,
		file_readonly = 0x1,
		file_hidden = 0x2
	};

	//settings
	extern bool b_logging_enabled;
	extern bool b_elevated_remove_enabled;

	//Timer
	extern int i_time_clean_start;

	//Computer and user variables
	static std::string s_computer_name = getenv("COMPUTERNAME");
	static std::string s_user_dir = getenv("USERPROFILE");
	static std::string s_directory_temp = getenv("TEMP");
	static std::string s_windows_dir = getenv("SYSTEMROOT");

	//Conversion
	LPCWSTR str_to_lpcwstr(std::string str);

	bool path_exists(std::string path);
	void ulog(std::string message);
	void file_change_attributes(std::string path, file_types type);

	void file_elevated_delete(std::string path);
	void file_delete(std::string path);
	void directory_clear(std::string directory);

	int time_get();

	namespace Registry
	{
		std::string registry_read(std::string reg_path, std::string reg_key, HKEY reg_section);
	}
}