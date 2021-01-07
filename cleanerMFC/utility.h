#pragma once

namespace util
{
	enum file_types
	{
		file_readonly = 0x1,
		file_hidden = 0x2,
		file_normal = 0x80,
	};

	//settings
	extern bool b_logging_enabled;

	//Logger
	void ulog(std::string message);

	//Timer
	extern int i_time_clean_start;
	int time_get();

	//Conversion
	std::wstring str_to_wstring(std::string str);

	//File
	void file_change_attributes(std::string path, file_types type);
	bool path_exists(std::string path);
	void file_elevated_delete(std::string path);
	void file_delete(std::string path);
	void directory_clear(std::string directory);
	std::string get_shortcut_path(std::string input_string);
	std::string get_first_file_name(std::string path, std::string findName);

	namespace registry
	{
		std::string registry_read(std::string reg_path, std::string reg_key, HKEY reg_section);
	}
}