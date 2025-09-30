#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
using namespace std;

#include "Investment.h"

void userInterface(); // takes input, creates Investment object

int main() {

	// attempt to run userInterface()
	try {
		userInterface();
	}
	catch (const std::exception& exc) {
		cout << exc.what() << endl;
		cout << "An error occurred with dataInterface()" << endl;
		system("pause");
	}

	return 0;
}

void userInterface() {
	Investment userInvestment;
	
	// variables to store user input
	double initialAmount;
	double monthlyDeposit;
	double annualInterest;
	int years;

	// variables to manipulate while loop
	bool c = "true";
	string userInput;

	while (c) {
		// clear screen, take user inputs
		system("cls");
		cout << setfill('*') << setw(40) << '*' << endl;
		cout << setw(26) << " Data Input " << setw(14) << left << '*' << endl;
		cout << setfill('-') << setw(40) << '-' << endl;

		//cout << "Initial Investment Amount: $";
		//cin >> initialAmount;
		//cout << endl;
		cout << "Initial Investment Amount: $";
		while (!(cin >> initialAmount) || initialAmount < 0 || cin.peek() != '\n') { // input validation to ensure input is number and isn't negative; cin.peek() checks to make sure whole input is integer
			cin.clear(); // clear input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore characters in buffer
			cout << "Invalid input. Please enter a valid positive number: $"; // prompt again
		}

		cout << "Monthly Deposit: $";
		while (!(cin >> monthlyDeposit) || monthlyDeposit < 0 || cin.peek() != '\n') { // input validation to ensure input is number and isn't negative; cin.peek() checks to make sure whole input is integer
			cin.clear(); // clear input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore characters in buffer
			cout << "Invalid input. Please enter a valid positive number: $"; // prompt again
		}

		cout << "Annual Interest: %";
		while (!(cin >> annualInterest) || annualInterest < 0 || cin.peek() != '\n') { // input validation to ensure input is number and isn't negative; cin.peek() checks to make sure whole input is integer
			cin.clear(); // clear input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore characters in buffer
			cout << "Invalid input. Please enter a valid positive number: $"; // prompt again
		}

		cout << "Number of years: ";
		while (!(cin >> years) || years < 0 || cin.peek() != '\n') { // input validation to ensure input is number and isn't negative; cin.peek() checks to make sure whole input is integer
			cin.clear(); // clear input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore characters in buffer
			cout << "Invalid input. Please enter a valid positive number: $"; // prompt again
		}

		// clear screen and display data with cleaner formatting (useful if input validation was triggered for neatness)
		system("cls");
		cout << setfill('*') << setw(40) << '*' << endl;
		cout << setw(26) << " Data Input " << setw(14) << left << '*' << endl;
		cout << setfill('-') << setw(40) << '-' << endl;
		cout << "Initial Investment Amount: $" << initialAmount << endl;
		cout << "Monthly Deposit: $" << monthlyDeposit << endl;
		cout << "Annual Interest: %" << annualInterest << endl;
		cout << "Number of years: " << years << endl;

		// set the inputs to the Investment object
		userInvestment.setInitialInvestment(initialAmount);
		userInvestment.setMonthlyDeposit(monthlyDeposit);
		userInvestment.setAnnualInterest(annualInterest);
		userInvestment.setYears(years);
		userInvestment.setTotalWithoutDeposits(userInvestment.getInitialInvestment());
		userInvestment.setTotalWithDeposits(userInvestment.getInitialInvestment() + userInvestment.getMonthlyDeposit());

		system("pause"); // wait for user input before continuing

		system("cls"); // clear screen for formatting

		// display table for interest without deposits
		userInvestment.calcInterestWithoutDeposits(userInvestment);

		// display table for interest with deposits
		userInvestment.calcInterestWithDeposits(userInvestment);

		system("pause"); // wait for user input before continuing

		system("cls"); // clear screen for formatting

		// determine if user wants to quit or check another investment
		cout << "To quit, type q, to continue, type any other key." << endl;
		cin >> userInput;
		if (userInput == "q") {
			c = false;
		}
		else {
			continue; // if anything other than "n" is entered, the loop will continue
		}
	}
}