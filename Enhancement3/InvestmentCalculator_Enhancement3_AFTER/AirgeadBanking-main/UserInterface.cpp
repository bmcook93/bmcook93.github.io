/************************************************************
** Name: UserInterface.cpp                                 **
** Author: Brandon Cook                                    **
*************************************************************/

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cstdlib>

#include "UserInterface.h"
#include "Import.h"
#include "Export.h"

constexpr double MAX_INITIAL_INVESTMENT = 10000000.0; // max initial investment amount
constexpr double MAX_MONTHLY_DEPOSIT = 10000.0; // max monthly deposit amount
constexpr double MAX_INTEREST = 100.0; // max interest amount
constexpr int MAX_YEARS = 30; // max number of years

// default constructor 
// UPDATE: using X DevAPI
UserInterface::UserInterface(mysqlx::Schema schema) : db(schema), currentUser(schema) {}

// display menu, simulate user interface
void UserInterface::ui() {
	bool run = true;
	std::string choice;

    if (!loginMenu()) { // run loginmenu first
        std::cout << "Exiting.";
        return;
    }

	while (run) {
        std::cout << std::string(39, '*') << "\n";
        std::cout << "*              Main Menu              *\n";
        std::cout << std::string(39, '-') << "\n";
        std::cout << std::endl;
        std::cout << "1. Calculate Investment" << std::endl;
        std::cout << "2. Display Investment Report" << std::endl;
		std::cout << "3. Import Data" << std::endl;
		std::cout << "4. Export Data" << std::endl;
		std::cout << "5. Quit" << std::endl;
		std::cin >> choice;

		if (choice == "1") { // take investment data
			inputInvestmentData();
		}
        else if (choice == "2") { // display investment data, ensure investment data has been created
            if (userInvestment.getInitialInvestment() == 0) { // if initial investment is 0, has not yet been created
                std::cout << "No investment data available. Please create or import one first." << std::endl;
            }
            else {
                displayReport();
            }
		}
		else if (choice == "3") { // import a report to csv file
            importReport();
		}
		else if (choice == "4") { // export a report from csv file
            exportReport();
		} 
        else if (choice == "5") {// end loop
            run = false;
        }
		else { // error out
			std::cout << "Invalid choice. Try again." << std::endl;
            std::cout << "Press Enter to continue..."; // simulated pause
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
		}

        std::cout << std::string(10, '\n'); // clear screen with newlines
	}
}

// collect investment information
void UserInterface::inputInvestmentData() {
    double initialAmount, monthlyDeposit, annualInterest;
    int years;

    std::cout << "Initial Investment Amount (Max $10,000,000): $";
    while (!(std::cin >> initialAmount) || initialAmount <= 0 || initialAmount > MAX_INITIAL_INVESTMENT || std::cin.peek() != '\n') { // limited max initial amount to $10M
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number between 1 and 10,000,000: $";
    }

    std::cout << "Monthly Deposit (Max $10,000): $";
    while (!(std::cin >> monthlyDeposit) || monthlyDeposit <= 0 || monthlyDeposit > MAX_MONTHLY_DEPOSIT || std::cin.peek() != '\n') { // limited max monthly deposit to $10,000
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number between 1 and 10,000: $";
    }

    std::cout << "Annual Interest (Max 100%): %";
    while (!(std::cin >> annualInterest) || annualInterest <= 0 || annualInterest > MAX_INTEREST || std::cin.peek() != '\n') { // limited interest to 100%
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number: %";
    }

    std::cout << "Number of years (Max 30 years): ";
    while (!(std::cin >> years) || years <= 0 || years > MAX_YEARS || std::cin.peek() != '\n') { // limited years to 30
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a valid positive number between 1 and 30: ";
    }

    userInvestment.setInitialInvestment(initialAmount);
    userInvestment.setMonthlyDeposit(monthlyDeposit);
    userInvestment.setAnnualInterest(annualInterest);
    userInvestment.setYears(years);
    try {
        userInvestment.calcInterestWithoutDeposits();
    }
    catch (const std::exception& e) { // catch errors with overflow
        std::cout << "Error when calculating total without deposits, possible overflow." << std::endl;
        return;
    }
    try {
        userInvestment.calcInterestWithDeposits();
    }
    catch (const std::exception& e) { // catch errors with overflow
        std::cout << "Error when calculating total with deposits, possible overflow." << std::endl;
        return;
    }
}

// display investment report
void UserInterface::displayReport() {
    std::cout << std::string(10, '\n'); // replaced system("cls") with newlines

    // grab references to vectors
    const auto& balancesWithoutDeposits = userInvestment.getYearlyBalancesWithoutDeposits();
    const auto& interestsWithoutDeposits = userInvestment.getYearlyInterestsWithoutDeposits();
    const auto& balancesWithDeposits = userInvestment.getYearlyBalancesWithDeposits();
    const auto& interestsWithDeposits = userInvestment.getYearlyInterestsWithDeposits();

    // header for balance without additional deposits
    // refactored the formatting
    std::cout << "Balance and Interest Without Additional Monthly Deposits" << std::endl;
    std::cout << std::setfill('=') << std::setw(100) << '=' << std::endl;
    std::cout << std::setfill(' ')
        << std::left << std::setw(8) << "Year"
        << std::left << std::setw(30) << "Year End Balance"
        << std::left << std::setw(30) << "Year End Earned Interest" << std::endl;
    std::cout << std::setfill('-') << std::setw(100) << '-' << std::endl;

    std::cout << std::setfill('.'); // create neat formatting for display
    for (size_t i = 0; i < balancesWithoutDeposits.size(); ++i) { // display year over year balances and interest
        std::cout << std::left << std::setw(8) << (i + 1)
            << "$" << std::setw(29) << std::fixed << std::setprecision(2)
            << balancesWithoutDeposits[i]
            << "$" << std::setw(29) << std::fixed << std::setprecision(2)
            << interestsWithoutDeposits[i]
            << std::endl;
    }

    std::cout << std::endl;

    // header for balance with additional deposits
    // refactored the formatting
    std::cout << "Balance and Interest With Additional Monthly Deposits" << std::endl;
    std::cout << std::setfill('=') << std::setw(100) << '=' << std::endl;
    std::cout << std::setfill(' ')
        << std::left << std::setw(8) << "Year"
        << std::left << std::setw(30) << "Year End Balance"
        << std::left << std::setw(30) << "Year End Earned Interest" << std::endl;
    std::cout << std::setfill('-') << std::setw(100) << '-' << std::endl;

    std::cout << std::setfill('.'); // create neat formatting for display
    for (size_t i = 0; i < balancesWithDeposits.size(); ++i) { // display year over year balances and interest
        std::cout << std::left << std::setw(8) << (i + 1)
            << "$" << std::setw(29) << std::fixed << std::setprecision(2)
            << balancesWithDeposits[i]
            << "$" << std::setw(29) << std::fixed << std::setprecision(2)
            << interestsWithDeposits[i]
            << std::endl;
    }

}

void UserInterface::importReport() {
    Import::run(userInvestment);
    std::cout << "Press Enter to continue..."; // replaced system("pause") with simulated pause using cin.get()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void UserInterface::exportReport() {
    Export::run(userInvestment);
    std::cout << "Press Enter to continue..."; // replaced system("pause") with simulated pause using cin.get()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// UPDATE: display loginmenu, login required before accessing system
bool UserInterface::loginMenu() {
    std::string choice; 
    while (true) { // loop until registered or logged in
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Quit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == "1") { // login, take username and password to log in
            std::string uname, password;
            std::cout << "Username: ";
            std::cin >> uname;
            std::cout << "Password: ";
            std::cin >> password;

            if (currentUser.loginUser(uname, password)) { // method checks login with database
                return true; // successful login
            }
        }
        else if (choice == "2") { // register a new username and password
            std::string uname, password;
            std::cout << "Choose a username: ";
            std::cin >> uname;
            std::cout << "Choose a password: ";
            std::cin >> password;

            currentUser.registerUser(uname, password); // adds new user to database if doesn't exist
        }
        else if (choice == "3") { // exit
            return false;
        }
        else { // invalid input
            std::cout << "Invalid choice." << std::endl;
        }
    }
}