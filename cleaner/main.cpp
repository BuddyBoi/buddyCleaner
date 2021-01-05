#include "stdafx.h"
#include "Cleaner.h"
#include "Utility.h"
#include <ShObjIdl_core.h>
#include <sysinfoapi.h>

//Not used ATM
void display_computer_info()
{
	std::cout << "Computer Info:" << std::endl;

	//Motherboard info
	printf("Motherboard: %s. Manufactured by %s.\n",
		   util::registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardProduct", HKEY_LOCAL_MACHINE).c_str(),
		   util::registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardManufacturer", HKEY_LOCAL_MACHINE).c_str());

	//Processor info
	printf("Processor: %s. Manufactured by %s.\n", 
		   util::registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", HKEY_LOCAL_MACHINE).c_str(),
		   util::registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "VendorIdentifier", HKEY_LOCAL_MACHINE).c_str());

	//Graphics card info
	printf("Graphcis Card: %s\n",
		util::registry::registry_read("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\WinSAT", "PrimaryAdapterString", HKEY_LOCAL_MACHINE).c_str());

	//Ram
	ULONGLONG kbRam{};
	GetPhysicallyInstalledSystemMemory(&kbRam);
	ULONGLONG gbRam = ((kbRam / 1024) / 1024);
	std::cout << "Ram: " << gbRam << "GB" << std::endl;
	

	//Boot info
	std::string s_boot_temp = util::registry::registry_read("SYSTEM\\CurrentControlSet\\Control\\SecureBoot\\State", "UEFISecureBootEnabled", HKEY_LOCAL_MACHINE).c_str();
	bool secure_boot_enabled = !s_boot_temp.empty();
	std::cout << std::boolalpha << "Secure boot enabled: " << secure_boot_enabled << std::endl;

	std::cout << std::endl << std::endl;
}

int main()
{
	display_computer_info();

	//Display Message
	std::cout << "==Buddy cleaner==\nIt is recommended to run this program as admin.\nDoing so allows for more files to be cleaned.\nThe following questions are to be answered as 1=yes, 0=no\n\n";

	//Get settings from input
	std::cout << "Logging=";
	std::cin >> util::b_logging_enabled;

	std::cout << "Disable hibernation mode=";
	std::cin >> cleaner::b_remove_hibernation;

	std::cout << "Clear steam temp=";
	std::cin >> cleaner::b_clear_steam_temp;

	std::cout << "Clear temp directories=";
	std::cin >> cleaner::b_clear_temp;

	std::cout << "Empty Recycling Bin=";
	std::cin >> cleaner::b_empty_recycling_bin;

	std::cout << "Clear Clipboard=";
	std::cin >> cleaner::b_clear_clipboard;

	std::cout << "Clear downloads folder=";
	std::cin >> cleaner::b_clean_downloads;

	std::cout << "Clear Microsoft Edge cookies and cache=";
	std::cin >> cleaner::b_clean_edge;

	std::cout << "Clear Microsoft Edge history=";
	std::cin >> cleaner::b_clean_edge_history;

	std::cout << "Clear Google Chrome cookies and cache=";
	std::cin >> cleaner::b_clean_chrome;

	std::cout << "Clear Google Chrome history=";
	std::cin >> cleaner::b_clean_chrome_history;

	std::cout << "Clear Firefox cookies and cache=";
	std::cin >> cleaner::b_clean_firefox;

	std::cout << "Clear Firefox history=";
	std::cin >> cleaner::b_clean_firefox_history;

	std::cout << "Clear Opera cookies and cache=";
	std::cin >> cleaner::b_clean_opera;

	std::cout << "Clear Opera history=";
	std::cin >> cleaner::b_clean_opera_history;	

	std::cout << "Remove broken shortcuts=";
	std::cin >> cleaner::b_clean_shortcuts;

	//Start cleaner timer
	util::i_time_clean_start = util::time_get();

	//Run cleaner	
	cleaner::cleanup();
	std::cout << "================" << std::endl;
	std::cout << "Program finished.\n";

	//Display how long program took
	int program_duration = util::time_get() - util::i_time_clean_start;
	std::cout << "Cleaner took " << program_duration << " seconds.";	

	//User manually close program
	while (1){}
}