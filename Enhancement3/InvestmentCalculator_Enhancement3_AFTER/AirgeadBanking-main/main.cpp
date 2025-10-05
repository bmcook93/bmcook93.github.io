/************************************************************
** Name: main.cpp                                          **
** Author: Brandon Cook                                    **
*************************************************************/

#include <iostream>
#include <stdexcept>
#include <mysqlx/xdevapi.h> // using mysql-connector-cpp 9.1 X DevAPI

#include "UserInterface.h"

int main() {

	// UPDATE: attempt to connect to database and start program loop
	try {
		// connect using x devapi
		mysqlx::Session session("127.0.0.1", 33060, "root", ""); // database only stored on local machine at the moment

		std::cout << "Connected to MySQL server." << std::endl; // debug message

		// access Investment schema
		mysqlx::Schema db = session.getSchema("Investment");

		std::cout << "Accessed 'Investment' schema." << std::endl; // debug message
		
		// show tables (for testing purposes) | Comment out if unneeded
		/*
		mysqlx::SqlResult res = session.sql("SHOW TABLES FROM Investment;").execute();

		std::cout << "Tables in 'Investment' schema:" << std::endl;;
		for (mysqlx::Row row : res) {
			std::cout << row[0] << std::endl;
		}
		*/

		// start user interface loop
		UserInterface ui(db);
		ui.ui();
	}
	catch (const mysqlx::Error &e) { // database error
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception& e) { // standard exception
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (...) { // catch other errors
		std::cout << "Unknown error." << std::endl;
		return 1;
	}

	return 0;
}