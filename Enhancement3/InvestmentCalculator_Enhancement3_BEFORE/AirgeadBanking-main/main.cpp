/************************************************************
** Name: main.cpp                                          **
** Author: Brandon Cook                                    **
*************************************************************/

#include <iostream>
#include <stdexcept>

#include "UserInterface.h"

// UPDATE: refactored main to include new UI class
int main() {

	// attempt to build ui
	try {
		UserInterface ui;
		ui.ui();
	}
	catch (const std::exception& exc) {
		std::cout << exc.what() << std::endl;
		std::cout << "An error occurred with userInterface()" << std::endl;
		std::cout << "Press Enter to continue..."; // UPDATE: replaced system("pause") with simulated pause using cin.get()
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	return 0;
}