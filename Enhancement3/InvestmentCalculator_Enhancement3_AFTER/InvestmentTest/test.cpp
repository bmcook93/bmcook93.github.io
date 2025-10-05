/************************************************************
** UPDATE: Test file using Google Tests                    **
** Name: test.cpp                                          **
** Author: Brandon Cook                                    **
*************************************************************/

#include "pch.h"

#include <fstream>
#include <memory>
#include "Investment.h"
#include "Import.h"
#include "Export.h"

// *******************************************
// Global test environment setup and teardown
// Runs before tests begin and after finishing
// *******************************************
class Environment : public ::testing::Environment {
public:
	~Environment() override {}

	void TearDown() override {}
};

// *******************************************
// Test fixture for Investment
// Creates an Investment object for testing
// *******************************************
class InvestmentTest : public ::testing::Test {
protected:
	std::unique_ptr<Investment> investment;

	// runs before each test
	void SetUp() override {
		investment.reset(new Investment());
	}

	// runs after each test
	void TearDown() override {
		investment.reset(nullptr); // frees memory
	}

	// write sample CSV file for import testing
	void writeSampleCSV(const std::string& filename = "investment_report.csv") {
		std::ofstream file(filename);
		file << "InitialInvestment,MonthlyDeposit,AnnualInterest,Years,TotalWithoutDeposits,TotalWithDeposit\n";
		file << "1000,100,5,3,1157.63,1466.36\n"; // Initial investment: 1000 || Montly deposit: 100 || Annual interest: 5 || Years: 3 || TotalWithoutDeposits: 1157.63 || TotalWithDeposits: 1466.36
		file << "\n"; // blank line before vector
		file << "YearlyBalancesWithoutDeposits\n";
		file << "1050.0,1102.5,1157.63\n"; // expected balances without deposits
		file << "YearlyInterestsWithoutDeposits\n";
		file << "50.0,52.5,55.13\n"; // expected interests without deposits
		file << "YearlyBalancesWithDeposits\n";
		file << "1165.0,1232.25,1302.86\n"; // expected balances with deposits
		file << "YearlyInterestsWithDeposits\n";
		file << "65.0,67.25,70.61\n"; // expected interests with deposits
		file.close();
	}

	// compare two vectors for equality
	bool vectorsEqual(const std::vector<double>& a, const std::vector<double>& b) {
		if (a.size() != b.size()) return false;
		for (size_t i = 0; i < a.size(); i++) {
			if (std::abs(a[i] - b[i]) > 1e-6) return false;
		}
		return true;
	}
};

// *******************************************
// Investment.cpp Testing
// Getter and Setter tests
// *******************************************
TEST_F(InvestmentTest, InitialInvestmentSetterAndGetter) {
	// Set initial investment to 1000
	investment->setInitialInvestment(1000.0);

	// Check that value is 1000
	EXPECT_DOUBLE_EQ(investment->getInitialInvestment(), 1000.0);
}

TEST_F(InvestmentTest, MonthlyDepositSetterAndGetter) {
	// Set monthly deposit to 500
	investment->setMonthlyDeposit(500.0);

	// Check that value is 500
	EXPECT_DOUBLE_EQ(investment->getMonthlyDeposit(), 500.0);
}

TEST_F(InvestmentTest, AnnualInterestSetterAndGetter) {
	// Set annual interest to 3.5
	investment->setAnnualInterest(3.5);

	// Check that value is 3.5
	EXPECT_DOUBLE_EQ(investment->getAnnualInterest(), 3.5);
}

TEST_F(InvestmentTest, YearsSetterAndGetter) {
	// Set years to 10
	investment->setYears(10);
	
	// Check that value is 10
	EXPECT_EQ(investment->getYears(), 10);
}

TEST_F(InvestmentTest, TotalWithoutDepositsSetterAndGetter) {
	// Set total without deposits to 1500
	investment->setTotalWithoutDeposits(1500.0);

	// Check that value is 1500
	EXPECT_DOUBLE_EQ(investment->getTotalWithoutDeposits(), 1500.0);
}

TEST_F(InvestmentTest, TotalWithDepositsSetterAndGetter) {
	// Set total with deposits to 3000
	investment->setTotalWithDeposits(3000.0);

	// Check that value is 3000
	EXPECT_DOUBLE_EQ(investment->getTotalWithDeposits(), 3000.0);
}

// *******************************************
// Investment.cpp Testing
// Vector tests
// *******************************************
TEST_F(InvestmentTest, VectorsAreEmptyOnCreate) {
	// all vectors should be empty when created
	EXPECT_TRUE(investment->getYearlyBalancesWithoutDeposits().empty());
	EXPECT_TRUE(investment->getYearlyInterestsWithoutDeposits().empty());
	EXPECT_TRUE(investment->getYearlyBalancesWithDeposits().empty());
	EXPECT_TRUE(investment->getYearlyInterestsWithDeposits().empty());
}

TEST_F(InvestmentTest, CanClearVectors) {
	// load sample data into vectors
	investment->getYearlyBalancesWithoutDeposits().push_back(100.0);
	investment->getYearlyInterestsWithoutDeposits().push_back(5.0);
	investment->getYearlyBalancesWithDeposits().push_back(100.0);
	investment->getYearlyInterestsWithDeposits().push_back(5.0);

	// clear the vectors
	investment->getYearlyBalancesWithoutDeposits().clear();
	investment->getYearlyInterestsWithoutDeposits().clear();
	investment->getYearlyBalancesWithDeposits().clear();
	investment->getYearlyInterestsWithDeposits().clear();

	// ensure the vectors are emptied
	EXPECT_TRUE(investment->getYearlyBalancesWithoutDeposits().empty());
	EXPECT_TRUE(investment->getYearlyInterestsWithoutDeposits().empty());
	EXPECT_TRUE(investment->getYearlyBalancesWithDeposits().empty());
	EXPECT_TRUE(investment->getYearlyInterestsWithDeposits().empty());
}

TEST_F(InvestmentTest, VectorOutOfRangeThrowsException) {
	// out of range exception thrown when accessing an empty vector
	EXPECT_THROW(investment->getYearlyBalancesWithoutDeposits().at(0), std::out_of_range);
	EXPECT_THROW(investment->getYearlyInterestsWithoutDeposits().at(0), std::out_of_range);
	EXPECT_THROW(investment->getYearlyBalancesWithDeposits().at(0), std::out_of_range);
	EXPECT_THROW(investment->getYearlyInterestsWithDeposits().at(0), std::out_of_range);
}

// *******************************************
// Investment.cpp Testing
// Calculation tests
// *******************************************
TEST_F(InvestmentTest, CalcInterestWithoutDeposits) {
	investment->setInitialInvestment(1000.0);
	investment->setAnnualInterest(10.0);
	investment->setYears(1);

	// calculate without deposits
	investment->calcInterestWithoutDeposits();

	// total should be 1104.71 - margin of error set to 0.1 due to nature of storing floating values
	EXPECT_NEAR(investment->getTotalWithoutDeposits(), 1104.71, 0.1);
}

TEST_F(InvestmentTest, CalcInterestWithDeposits) {
	investment->setInitialInvestment(1000.0);
	investment->setMonthlyDeposit(100.0);
	investment->setAnnualInterest(10.0);
	investment->setYears(1);

	// calculate with deposits
	investment->calcInterestWithDeposits();

	// total should be 2,371.74 - margin of error set to 0.1 due to nature of storing floating values
	EXPECT_NEAR(investment->getTotalWithDeposits(), 2371.74, 0.1);
}

// *******************************************
// Import.cpp Testing
// Import tests
// *******************************************
TEST_F(InvestmentTest, SuccessfulImport) {
	// write the sample CSV
	writeSampleCSV();

	// import into Investment
	Import importer;
	importer.run(*investment);

	// verify correct values
	EXPECT_DOUBLE_EQ(investment->getInitialInvestment(), 1000.0);
	EXPECT_DOUBLE_EQ(investment->getMonthlyDeposit(), 100.0);
	EXPECT_DOUBLE_EQ(investment->getAnnualInterest(), 5.0);
	EXPECT_EQ(investment->getYears(), 3);

	// verify vector correctness
	EXPECT_TRUE(vectorsEqual(investment->getYearlyBalancesWithoutDeposits(), { 1050.0, 1102.5, 1157.63 }));
	EXPECT_TRUE(vectorsEqual(investment->getYearlyInterestsWithoutDeposits(), { 50.0, 52.5, 55.13 }));
	EXPECT_TRUE(vectorsEqual(investment->getYearlyBalancesWithDeposits(), { 1165.0, 1232.25, 1302.86 }));
	EXPECT_TRUE(vectorsEqual(investment->getYearlyInterestsWithDeposits(), { 65.0, 67.25, 70.61 }));
}

/* SAMPLE TEST
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
*/