/************************************************************
** Name: UserInterface.h                                   **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Investment.h"
#include "User.h"
#include <mysqlx/xdevapi.h> // X DevAPI

class UserInterface {
public:
	UserInterface(mysqlx::Schema db); // UPDATE: db added to constructor
	void ui(); // main menu loop

private:
	Investment userInvestment;
	mysqlx::Schema db; // store database for operations
	User currentUser; // store current user info

	// menu handlers
	void inputInvestmentData(); // take user input for investment data
	void displayReport(); // display report to user
	void importReport(); // import report from csv file
	void exportReport(); // export report to csv file

	bool loginMenu(); // UPDATE: login/register
};

#endif