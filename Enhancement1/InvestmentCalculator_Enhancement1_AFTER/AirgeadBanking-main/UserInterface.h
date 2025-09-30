/************************************************************
** UPDATE: Header file for UI                              **
** Name: UserInterface.h                                   **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Investment.h"

class UserInterface {
public:
	UserInterface();
	void ui(); // main menu loop

private:
	Investment userInvestment;

	// menu handlers
	void inputInvestmentData(); // take user input for investment data
	void displayReport(); // display report to user
	void importReport(); // import report from csv file
	void exportReport(); // export report to csv file
};

#endif