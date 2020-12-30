//For changing file properties
#include "stdafx.h"
#include "Cleaner.h"
#include "Utility.h"

int main()
{
	//Display Message
	std::cout << "==Buddy cleaner==\n\nIt is recommended to run this program as admin.\nDoing so allows for more files to be cleaned.\nThe following questions are to be answered as 1=yes, 0=no\n\n";

	//Get settings from input
	std::cout << "Logging=";
	std::cin >> Util::b_logging_enabled;

	std::cout << "Clear temp directories=";
	std::cin >> Cleaner::b_clear_temp;

	std::cout << "Empty Recycling Bin=";
	std::cin >> Cleaner::b_empty_recycling_bin;

	std::cout << "Clear Google Chrome cookies and cache=";
	std::cin >> Cleaner::b_clean_chrome;

	std::cout << "Clear Opera cookies and cache=";
	std::cin >> Cleaner::b_clean_opera;

	std::cout << "Disable hibernation mode=";
	std::cin >> Cleaner::b_remove_hibernation;

	std::cout << "Elevated removal(requires admin)=";
	std::cin >> Util::b_elevated_remove_enabled;

	std::cout << "Clear steam temp(requires clear temp directories on)=";
	std::cin >> Cleaner::b_clear_steam_temp;

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