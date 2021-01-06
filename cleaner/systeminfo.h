#pragma once
#include "stdafx.h"
#include "Utility.h"
namespace systeminfo
{
	//user
	extern std::string s_computer_name;
	extern std::string s_user_dir;
	extern std::string s_directory_temp;
	extern std::string s_windows_dir;

	//motherboard
	extern std::string s_mboard_name;
	extern std::string s_mboard_manufacturer;

	//memory
	extern ULONGLONG u_memory_gb;
	
	//cpu
	extern std::string s_cpu_name;
	extern std::string s_cpu_manufacturer;
	extern DWORD dw_cpu_cores;

	//graphics card
	extern std::string s_gpu_name;

	//boot
	extern bool b_secureboot;

	void get_system_info();
}