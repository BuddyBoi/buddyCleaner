#include "pch.h"
#include "systeminfo.h"

namespace systeminfo
{
	std::string s_computer_name;
	std::string s_user_dir;
	std::string s_directory_temp;
	std::string s_windows_dir;
	std::string s_mboard_name;
	std::string s_mboard_manufacturer;
	ULONGLONG u_memory_gb;
	std::string s_cpu_name;
	std::string s_cpu_manufacturer;
	DWORD dw_cpu_cores;
	std::string s_gpu_name;
	bool b_secureboot;

	void get_system_info()
	{
		//Store system info for later use
		s_mboard_name = util::registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardProduct", HKEY_LOCAL_MACHINE);
		s_mboard_manufacturer = util::registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardManufacturer", HKEY_LOCAL_MACHINE);

		SYSTEM_INFO s_info{};
		GetSystemInfo(&s_info);
		s_cpu_name = util::registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", HKEY_LOCAL_MACHINE);
		s_cpu_manufacturer = util::registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "VendorIdentifier", HKEY_LOCAL_MACHINE);
		dw_cpu_cores = s_info.dwNumberOfProcessors;

		s_gpu_name = util::registry::registry_read("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT", "PrimaryAdapterString", HKEY_LOCAL_MACHINE);
		ULONGLONG kbRam{};
		GetPhysicallyInstalledSystemMemory(&kbRam);
		ULONGLONG gbRam = ((kbRam / 1024) / 1024);
		u_memory_gb = gbRam;

		std::string s_boot_temp = util::registry::registry_read("SYSTEM\\CurrentControlSet\\Control\\SecureBoot\\State", "UEFISecureBootEnabled", HKEY_LOCAL_MACHINE);
		b_secureboot = (s_boot_temp == "0");

		#pragma warning(disable:4996)

		s_computer_name = getenv("COMPUTERNAME");
		s_user_dir = getenv("USERPROFILE");
		s_directory_temp = getenv("TEMP");
		s_windows_dir = getenv("SYSTEMROOT");
	}
}