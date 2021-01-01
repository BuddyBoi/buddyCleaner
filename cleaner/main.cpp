#include "stdafx.h"
#include "Cleaner.h"
#include "Utility.h"
#include <ShObjIdl_core.h>

//Not used ATM
void display_computer_info()
{
	std::cout << "Computer Info:" << std::endl;

	//Motherboard info
	printf("Motherboard: %s. Manufactured by %s.\n",
		   Util::Registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardProduct", HKEY_LOCAL_MACHINE).c_str(),
		   Util::Registry::registry_read("SYSTEM\\HardwareConfig\\Current", "BaseBoardManufacturer", HKEY_LOCAL_MACHINE).c_str());

	//Processor info
	printf("Processor: %s. Manufactured by %s.\n", 
		   Util::Registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "ProcessorNameString", HKEY_LOCAL_MACHINE).c_str(),
		   Util::Registry::registry_read("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", "VendorIdentifier", HKEY_LOCAL_MACHINE).c_str());

	//Boot info
	std::string s_boot_temp = Util::Registry::registry_read("SYSTEM\\CurrentControlSet\\Control\\SecureBoot\\State", "UEFISecureBootEnabled", HKEY_LOCAL_MACHINE).c_str();
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
	std::cin >> Util::b_logging_enabled;

	std::cout << "Disable hibernation mode=";
	std::cin >> Cleaner::b_remove_hibernation;

	std::cout << "Clear steam temp=";
	std::cin >> Cleaner::b_clear_steam_temp;

	std::cout << "Clear temp directories=";
	std::cin >> Cleaner::b_clear_temp;

	std::cout << "Empty Recycling Bin=";
	std::cin >> Cleaner::b_empty_recycling_bin;

	std::cout << "Clear Microsoft Edge cookies and cache=";
	std::cin >> Cleaner::b_clean_edge;

	std::cout << "Clear Microsoft Edge history=";
	std::cin >> Cleaner::b_clean_edge_history;

	std::cout << "Clear Google Chrome cookies and cache=";
	std::cin >> Cleaner::b_clean_chrome;

	std::cout << "Clear Google Chrome history=";
	std::cin >> Cleaner::b_clean_chrome_history;

	std::cout << "Clear Firefox cookies and cache=";
	std::cin >> Cleaner::b_clean_firefox;

	std::cout << "Clear Firefox history=";
	std::cin >> Cleaner::b_clean_firefox_history;

	std::cout << "Clear Opera cookies and cache=";
	std::cin >> Cleaner::b_clean_opera;

	std::cout << "Clear Opera history=";
	std::cin >> Cleaner::b_clean_opera_history;	

	//Start cleaner timer
	Util::i_time_clean_start = Util::time_get();

	//Run cleaner	
	Cleaner::Cleanup();
	std::cout << "Program finished.\n";

	//Display how long program took
	int program_duration = Util::time_get() - Util::i_time_clean_start;
	std::cout << "Cleaner took " << program_duration << " seconds.";	

	//User manually close program
	while (1){}
}