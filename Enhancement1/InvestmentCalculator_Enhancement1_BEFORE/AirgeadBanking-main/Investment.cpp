#include <iostream>
#include <iomanip>
using namespace std;


#include "Investment.h"

// default constructor
Investment::Investment() {
	this->initialInvestment = 0.0;
	this->monthlyDeposit = 0.0;
	this->annualInterest = 0.0;
	this->years = 0;
	this->interest = 0.0;
	this->totalWithoutDeposits = 0.0;
	this->totalWithDeposits = 0.0;
}

void Investment::setInitialInvestment(double initial) {
	this->initialInvestment = initial;
}

void Investment::setMonthlyDeposit(double monthly) {
	this->monthlyDeposit = monthly;
}

void Investment::setAnnualInterest(double annual) {
	this->annualInterest = annual;
}

void Investment::setYears(int years) {
	this->years = years;
}

void Investment::setTotalWithoutDeposits(double total) {
	this->totalWithoutDeposits = total;
}

void Investment::setTotalWithDeposits(double total) {
	this->totalWithDeposits = total;
}

double Investment::getInitialInvestment() {
	return this->initialInvestment;
}

double Investment::getMonthlyDeposit() {
	return this->monthlyDeposit;
}

double Investment::getAnnualInterest() {
	return this->annualInterest;
}

int Investment::getYears() {
	return this->years;
}

double Investment::getTotalWithoutDeposits() {
	return totalWithoutDeposits;
}

double Investment::getTotalWithDeposits() {
	return totalWithDeposits;
}

void Investment::addTotalWithoutDeposits(double total) {
	this->totalWithoutDeposits += total;
}

void Investment::addTotalWithDeposits(double total) {
	this->totalWithDeposits += total;
}

// calculates the interest dollar amount with monthly deposits; if openingAmount = 1.0 and interest = 5.0%, then interest = $0.05
double Investment::getInterest(double openingAmount) {
	return (openingAmount) * ((annualInterest / 100) / 12);
}

void Investment::calcInterestWithoutDeposits(Investment& userInvestment) {
	int y; // used for year loop
	int m; // used for month loop
	double interest;
	double openingAmount;

	// header for balance without additional deposits
	cout << "Balance and Interest Without Additional Monthly Deposits" << endl;
	cout << setfill('=') << setw(100) << '=' << endl;
	cout << setfill(' ') << left << setw(30) << "Year" << "Year End Balance" << right << setw(40) << "Year End Earned Interest" << endl;
	cout << setfill('-') << setw(100) << '-' << endl;

	interest = 0.0;
	openingAmount = userInvestment.getInitialInvestment();

	for (y = 1; y <= this->years; y++) { // iterates over total years
		for (m = 1; m <= 12; m++) { // iterates over months in a year
			interest += userInvestment.getInterest(openingAmount);
			openingAmount += interest; // adds interest to local variable
		}

		userInvestment.addTotalWithoutDeposits(interest); // adds interest to total

		// display information for current year y
		cout << setfill(' ') << left << setw(30) << y;
		cout << "$" << fixed << setprecision(2) << userInvestment.getTotalWithoutDeposits();
		cout << right << setw(28) << "$" << fixed << setprecision(2) << interest << endl;

		interest = 0.0; // reset interest for next loop
	}
}

void Investment::calcInterestWithDeposits(Investment& userInvestment) {
	int y; // used for year loop
	int m; // used for month loop
	double interest;
	double openingAmount;

	// header for balance with additional deposits
	cout << "Balance and Interest With Additional Monthly Deposits" << endl;
	cout << setfill('=') << setw(100) << '=' << endl;
	cout << setfill(' ') << left << setw(30) << "Year" << "Year End Balance" << right << setw(40) << "Year End Earned Interest" << endl;
	cout << setfill('-') << setw(100) << '-' << endl;

	interest = 0.0;
	openingAmount = userInvestment.getInitialInvestment();

	for (y = 1; y <= userInvestment.getYears(); y++) { // iterates over total years
		for (m = 1; m <= 12; m++) { // iterates over months in a year
			userInvestment.addTotalWithDeposits(userInvestment.getMonthlyDeposit());
			interest += userInvestment.getInterest(userInvestment.getTotalWithDeposits());
			userInvestment.addTotalWithDeposits(interest);
		}

		// display information for current year y
		cout << setfill(' ') << left << setw(30) << y;
		cout << "$" << fixed << setprecision(2) << userInvestment.getTotalWithDeposits();
		cout << right << setw(28) << "$" << fixed << setprecision(2) << interest << endl;

		interest = 0.0; // reset interest for next loop
	}
}