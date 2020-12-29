//For changing file properties
#include "stdafx.h"
#include "Cleaner.h"
#include "Utility.h"

int main()
{
	//Display Message
	std::cout << "==Buddy cleaner==\n\nIt is recommended to run this program as admin.\nDoing so allows for more files to be cleaned.\nThe following questions are to be answered as 1=yes, 0=no\n\n";

	//Get settings from input
	std::cout << "Clear temp directories=";
	std::cin >> Cleaner::b_clear_temp;

	std::cout << "Disable hibernation mode=";
	std::cin >> Cleaner::b_remove_hibernation;

	std::cout << "Elevated removal(requires admin)=";
	std::cin >> Util::b_elevated_remove_enabled;

	std::cout << "Clear steam temp(requires clear temp directories on)=";
	std::cin >> Cleaner::b_clear_steam_temp;

	//Run cleaner	
	Cleaner::Cleanup();
	std::cout << "Program finished.\n";

	//User manually close program
	while (1){}
}