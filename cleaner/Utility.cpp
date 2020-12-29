#include "Utility.h"

namespace Util
{
	//checks if the path (file or directory) exists
	bool path_exists(std::string path)
	{
		return std::experimental::filesystem::exists(path);
	}

	//Weak logging system
	void ulog(std::string message)
	{
		if (!b_logging_enabled)
			return;

		std::cout << ("Log: %s", message) << '\n';
	}

	void file_change_attributes(std::string path, file_types type)
	{
		//Building path with \\.\ before the directory. This (sometimes) allows for deletion even if in-use
		std::string s_temp = "\\\\.\\" + path;

		//Converting string to LPCWSTR
		std::wstring ws_temp = std::wstring(path.begin(), path.end());
		LPCWSTR directory = ws_temp.c_str();
		SetFileAttributes(directory, type);
	}

	//Delete system-protected files or in-use files
	void file_elevated_delete(std::string path)
	{
		if (!b_elevated_remove_enabled)
		{
			ulog("Elevated remove is disabled.");
			return;
		}

		//Building path with \\.\ before the directory. This (sometimes) allows for deletion even if in-use
		std::string s_temp = "\\\\.\\" + path;

		//Converting string to LPCWSTR
		std::wstring ws_temp = std::wstring(path.begin(), path.end());
		LPCWSTR directory = ws_temp.c_str();

		SetFileAttributes(directory, file_normal);

		try
		{
			//I'm not sure. Some files just refuse to be deleted. Will fix later
			DeleteFile(directory);
			std::experimental::filesystem::remove(path);
		}
		catch (std::exception e)
		{
			return;
		}
	}

	//Delete method
	void file_delete(std::string path)
	{
		if (path_exists(path))
		{
			ulog("Attempting to delete " + path);
			remove(path.c_str());
			if (path_exists(path))
			{
				ulog("Failed to delete " + path);
				ulog("Attempting elevated remove");
				file_elevated_delete(path);

				if (path_exists(path))
				{
					ulog("Failed to delete with elevation " + path);
					return;
				}
			}
			ulog("Removed " + path);
		}
	}

	//Iterate a directory and clear it's contents
	void directory_clear(std::string directory)
	{
		for (const auto& entry : std::experimental::filesystem::directory_iterator(directory))
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

					ulog("Failed to find registry directory");
					return "Error";
				}

				char path_reg[MAX_PATH]; path_reg[0] = '-'; //Idk dude
				DWORD reg_path_size = sizeof(path_reg) - sizeof(char);

				if (RegQueryValueExA(h_key, reg_key.c_str(), nullptr, nullptr, (LPBYTE)(path_reg + 1), &reg_path_size) != ERROR_SUCCESS)
				{
					RegCloseKey(h_key);
					ulog("Failed to read registry key");
					return "error";

				}
				RegCloseKey(h_key);

				auto return_reg = std::string(path_reg);
				return_reg = return_reg.erase(0, 1); //remove idk dude
				return return_reg;
			}
			catch (std::exception e)
			{
				ulog("Registry read failure");
				return "Error";
			}
		}
	}
}