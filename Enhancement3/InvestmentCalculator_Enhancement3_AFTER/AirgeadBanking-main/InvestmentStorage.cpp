/************************************************************
** UPDATE: New header file for InvestmentStorage.cpp       **
** Name: InvestmentStorage.cpp                             **
** Author: Brandon Cook                                    **
*************************************************************/

#include <iostream>

#include "InvestmentStorage.h"

InvestmentStorage::InvestmentStorage(mysqlx::Schema schema) : db(schema) {} // constructor

bool InvestmentStorage::saveInvestment(const User& user, Investment& investment) {
	try {
		mysqlx::Table investmentsTable = db.getTable("investments"); // load investments table from database
		mysqlx::Table yearlyResultsTable = db.getTable("yearly_results"); // load yearly_results from database, stores year over year results

		// insert investment
		mysqlx::Result res = investmentsTable.insert(
			"user_id",
			"initial_invesmtent",
			"monthly_deposit",
			"annual_interest",
			"years",
			"total_without_deposits",
			"total_with_deposits"
		).values(
			user.getUserId(),
			investment.getInitialInvestment(),
			investment.getMonthlyDeposit(),
			investment.getAnnualInterest(),
			investment.getYears(),
			investment.getTotalWithoutDeposits(),
			investment.getTotalWithDeposits()
		).execute();

		std::cout << "Investment saved." << std::endl;

		// retrieve yearly vectors
		const auto& balancesWithout = investment.getYearlyBalancesWithoutDeposits();
		const auto& interestsWithout = investment.getYearlyInterestsWithoutDeposits();
		const auto& balancesWith = investment.getYearlyBalancesWithDeposits();
		const auto& interestsWith = investment.getYearlyInterestsWithDeposits();

		int investmentId = static_cast<int>(res.getAutoIncrementValue()); // get investmentId

		// insert yearly_results
		for (size_t i = 0; balancesWith.size(); ++i) {
			yearlyResultsTable.insert(
				"investment_id",
				"year_number",
				"balance_without_deposits",
				"interest_without_deposits",
				"balance_with_deposits",
				"interest_with_deposits"
			).values(
				investmentId,
				static_cast<int>(i + 1),
				balancesWithout[i],
				interestsWithout[i],
				balancesWith[i],
				interestsWith[i]
			).execute();
		}

		std::cout << "Yearly results saved." << std::endl;
		return true;
	}
	catch (const mysqlx::Error& e) { // sql error
		std::cout << "Database error: " << e.what() << std::endl;
		return false;
	}
	catch (const std::exception& e) { // other error
		std::cout << "Error: " << e.what() << std::endl;
		return false;
	}
}

bool InvestmentStorage::retrieveInvestment(const User& user, Investment& investment) {
	try {
		mysqlx::Table investmentsTable = db.getTable("investments"); // load investments table
		mysqlx::Table yearlyResultsTable = db.getTable("yearly_results"); // load yearly_results table; year over year results

		// get recent investment
		mysqlx::RowResult res = investmentsTable.select(
			"investment_id",
			"initial_invesmtent",
			"monthly_deposit",
			"annual_interest",
			"years",
			"total_without_deposits",
			"total_with_deposits"
		).where("user_id = :uid")
			.orderBy("investment_id DESC")
			.limit(1)
			.bind("uid", user.getUserId())
			.execute();

		// verify investment exists
		mysqlx::Row row = res.fetchOne();
		if (row.isNull()) {
			std::cout << "No investments saved." << std::endl;
			return false;
		}

		// load investment
		int investmentId = row[0].get<int>();
		investment.setInitialInvestment(row[1].get<double>());
		investment.setMonthlyDeposit(row[2].get<double>());
		investment.setAnnualInterest(row[3].get<double>());
		investment.setYears(row[4].get<int>());
		investment.setTotalWithoutDeposits(row[5].get<double>());
		investment.setTotalWithDeposits(row[6].get<double>());

		// load yearly results
		mysqlx::RowResult yearlyRows = yearlyResultsTable
			.select(
				"year_number",
				"balance_without_deposits",
				"interest_without_deposits",
				"balance_with_deposits",
				"interest_with_deposits"
			)
			.where("investment_id = :iid")
			.orderBy("year_number ASC")
			.bind("iid", investmentId)
			.execute();

		// get vectors and clear
		auto& balancesWithout = investment.getYearlyBalancesWithoutDeposits();
		auto& interestsWithout = investment.getYearlyInterestsWithoutDeposits();
		auto& balancesWith = investment.getYearlyBalancesWithDeposits();
		auto& interestsWith = investment.getYearlyInterestsWithDeposits();

		balancesWithout.clear();
		interestsWithout.clear();
		balancesWith.clear();
		interestsWith.clear();

		// load vectors from database
		for (mysqlx::Row yr : yearlyRows) {
			balancesWithout.push_back(yr[1].get<double>());
			interestsWithout.push_back(yr[2].get<double>());
			balancesWith.push_back(yr[3].get<double>());
			interestsWith.push_back(yr[4].get<double>());
		}

		std::cout << "Loaded investment from database." << std::endl;
		return true;
	}
	catch (const mysqlx::Error& e) { // sql exception
		std::cout << "Database error: " << e.what() << std::endl;
		return false;
	}
	catch (const std::exception& e) { // other exception
		std::cout << "Error: " << e.what() << std::endl;
		return false;
	}
}