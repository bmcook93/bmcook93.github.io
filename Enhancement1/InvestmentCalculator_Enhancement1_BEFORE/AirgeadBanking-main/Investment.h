#pragma once
#ifndef INVESTMENT_H
#define INVESTMENT_H
#endif

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

	void calcInterestWithoutDeposits(Investment& userInvestment); // calculates and displays the year, year end balance, and year end interest in a table format
	void calcInterestWithDeposits(Investment& userInvestment);// calculates and displays the year, year end balance, and year end interest in a table format

private:
	double getInterest(double openingAmount); // calculates the interest dollar amount
	void addTotalWithoutDeposits(double total);
	void addTotalWithDeposits(double total);

	double initialInvestment;
	double monthlyDeposit;
	double annualInterest;
	int years;
	double interest;
	double totalWithoutDeposits;
	double totalWithDeposits;
};