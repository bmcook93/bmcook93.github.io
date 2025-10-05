/************************************************************
** Name: Investment.h                                      **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <vector>

class Investment {
public:
	Investment();
	void setInitialInvestment(double initial);
	void setMonthlyDeposit(double monthly);
	void setAnnualInterest(double annual);
	void setYears(int years);
	void setTotalWithoutDeposits(double total);
	void setTotalWithDeposits(double total);

	double getInitialInvestment();
	double getMonthlyDeposit();
	double getAnnualInterest();
	int getYears();
	double getTotalWithoutDeposits();
	double getTotalWithDeposits();

	std::vector<double>& getYearlyBalancesWithoutDeposits();
	std::vector<double>& getYearlyInterestsWithoutDeposits();
	std::vector<double>& getYearlyBalancesWithDeposits();
	std::vector<double>& getYearlyInterestsWithDeposits();

	void calcInterestWithoutDeposits(); // calculates total without deposit
	void calcInterestWithDeposits();// calculates total with deposit

private:
	double getInterest(double openingAmount); // calculates the interest dollar amount

	double initialInvestment;
	double monthlyDeposit;
	double annualInterest;
	int years;
	double interest;
	double totalWithoutDeposits;
	double totalWithDeposits;
	std::vector<double> yearlyBalancesWithoutDeposits; // UPDATE: vector to store year over year balances without deposits
	std::vector<double> yearlyInterestsWithoutDeposits; // UPDATE: vector to store year over year interests without deposits
	std::vector<double> yearlyBalancesWithDeposits; // UPDATE: vector to store year over year balances with deposits
	std::vector<double> yearlyInterestsWithDeposits; // UPDATE: vector to store year over year interests with deposits
};

#endif