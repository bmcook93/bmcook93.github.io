/************************************************************
** Name: Investment.cpp                                    **
** Author: Brandon Cook                                    **
*************************************************************/


#include <iostream>
#include <iomanip>


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

	this->yearlyBalancesWithoutDeposits = std::vector<double>();
	this->yearlyInterestsWithoutDeposits = std::vector<double>();
	this->yearlyBalancesWithDeposits = std::vector<double>();
	this->yearlyInterestsWithDeposits = std::vector<double>();
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

// calculates the interest dollar amount with monthly deposits; if openingAmount = 1.0 and interest = 5.0%, then interest = $0.05
double Investment::getInterest(double openingAmount) {
	return (openingAmount) * ((annualInterest / 100) / 12);
}

std::vector<double>& Investment::getYearlyBalancesWithoutDeposits() {
	return yearlyBalancesWithoutDeposits;
}

std::vector<double>& Investment::getYearlyInterestsWithoutDeposits() {
	return yearlyInterestsWithoutDeposits;
}

std::vector<double>& Investment::getYearlyBalancesWithDeposits() {
	return yearlyBalancesWithDeposits;
}

std::vector<double>& Investment::getYearlyInterestsWithDeposits() {
	return yearlyInterestsWithDeposits;
}

// UPDATE: refactored to use vectors for year over year storage
void Investment::calcInterestWithoutDeposits() {
	yearlyBalancesWithoutDeposits.clear(); // clear balance vector
	yearlyInterestsWithoutDeposits.clear(); // clear interest vector

	double balance = initialInvestment; // store current balance as incremented

	for (int y = 1; y <= years; y++) { // iterate over number of years
		double interest = 0.0;

		for (int m = 1; m <= 12; m++) { // iterate over number of months
			double monthlyInterest = getInterest(balance);
			interest +=  monthlyInterest; // increase interest per month
			balance += monthlyInterest; // update total balance
		}

		yearlyBalancesWithoutDeposits.push_back(balance); // store the end of year balance into vector
		yearlyInterestsWithoutDeposits.push_back(interest); // store the end of year interest into vector
	}

	totalWithoutDeposits = balance; // store total; currently unused, may be viable in future database for quick comparisons
}

// UPDATE: refactored to use vectors for year over year storage
void Investment::calcInterestWithDeposits() {
	yearlyBalancesWithDeposits.clear(); // clear vector for balances with deposits
	yearlyInterestsWithDeposits.clear(); // clear vector for interest with deposits

	double balance = initialInvestment; // set initial balance

	for (int y = 1; y <= years; y++) { // iterate over number of years
		double interest = 0.0;

		for (int m = 1; m <= 12; m++) { // iterate over number of months
			balance += monthlyDeposit; // increase balance over months with monthly deposits
			double monthlyInterest = getInterest(balance);
			interest += monthlyInterest; // increase interest per month - adds monthly deposits
			balance += monthlyInterest; // increase balance per month - adds monthly deposits
		}

		yearlyBalancesWithDeposits.push_back(balance); // store the end of year balance into vector
		yearlyInterestsWithDeposits.push_back(interest); // store the end of year interest into vector
	}

	totalWithDeposits = balance; // store total; currently unused, may be viable in future database for quick comparisons
}