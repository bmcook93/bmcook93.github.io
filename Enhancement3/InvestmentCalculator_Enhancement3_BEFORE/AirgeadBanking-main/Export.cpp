/************************************************************
** UPDATE: Export file                                     **
** Name: Export.cpp                                        **
** Author: Brandon Cook                                    **
*************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Export.h"
#include "Investment.h"

// export report into a csv for later import
void Export::run(Investment& userInvestment) {
    std::ofstream outFile("investment_report.csv");
    if (!outFile.is_open()) { // ensure file is opened correctly for writing
        std::cout << "Error: Unable to create export file." << std::endl;
        return;
    }

    // write basic values first
    outFile << "InitialInvestment,MonthlyDeposit,AnnualInterest,Years,TotalWithoutDeposits,TotalWithDeposits\n";
    outFile << std::fixed << std::setprecision(2)
        << userInvestment.getInitialInvestment() << ','
        << userInvestment.getMonthlyDeposit() << ','
        << userInvestment.getAnnualInterest() << ','
        << userInvestment.getYears() << ','
        << userInvestment.getTotalWithoutDeposits() << ','
        << userInvestment.getTotalWithDeposits() << '\n';

    // grab references to vectors
    const auto& balNoDep = userInvestment.getYearlyBalancesWithoutDeposits();
    const auto& intNoDep = userInvestment.getYearlyInterestsWithoutDeposits();
    const auto& balWithDep = userInvestment.getYearlyBalancesWithDeposits();
    const auto& intWithDep = userInvestment.getYearlyInterestsWithDeposits();

    // write yearly balances without deposits
    outFile << "\nYearlyBalancesWithoutDeposits\n";
    for (double val : balNoDep) outFile << val << ',';
    outFile << '\n';

    // write yearly interests without deposits
    outFile << "YearlyInterestsWithoutDeposits\n";
    for (double val : intNoDep) outFile << val << ',';
    outFile << '\n';

    // write yearly balances with deposits
    outFile << "YearlyBalancesWithDeposits\n";
    for (double val : balWithDep) outFile << val << ',';
    outFile << '\n';

    // write yearly interests with deposits
    outFile << "YearlyInterestsWithDeposits\n";
    for (double val : intWithDep) outFile << val << ',';
    outFile << '\n';

    outFile.close(); // close file
    std::cout << "Report successfully exported to investment_report.csv" << std::endl;
}