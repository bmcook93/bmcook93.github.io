/************************************************************
** UPDATE: Import file                                     **
** Name: Import.cpp                                        **
** Author: Brandon Cook                                    **
*************************************************************/

#include "pch.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Import.h"
#include "Investment.h"

// helper function to split a comma-separated line into a vector of doubles
std::vector<double> splitLineToDoubles(const std::string& line) {
    std::vector<double> values;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, ',')) {
        if (!token.empty()) {
            values.push_back(std::stod(token)); // convert string to double and store
        }
    }

    return values;
}

// import report from CSV into userInvestment
void Import::run(Investment& userInvestment) {
    std::ifstream inFile("investment_report.csv");
    if (!inFile.is_open()) { // ensure file opens correctly
        std::cout << "Error: Unable to open import file." << std::endl;
        return;
    }

    std::string line;

    // read basic values first
    std::getline(inFile, line); // skip header line
    if (std::getline(inFile, line)) { // read actual values row
        std::stringstream ss(line);
        std::string token;

        // try catch blocks to error out if values are mismatched in csv - should not assume all values to be expected correct
        try {
            std::getline(ss, token, ',');
            userInvestment.setInitialInvestment(std::stod(token)); // convert initial investment to double
        }
        catch (const std::exception& e) { // initial investment error caught
            std::cout << "Error parsing initial investment from file: " << e.what() << std::endl;
            return;
        }

        try {
            std::getline(ss, token, ','); 
            userInvestment.setMonthlyDeposit(std::stod(token)); // convert monthly deposit to double
        }
        catch (const std::exception& e) { // monthly deposit error caught
            std::cout << "Error parsing monthly deposit from file: " << e.what() << std::endl;
            return;
        }

        try {
            std::getline(ss, token, ','); 
         userInvestment.setAnnualInterest(std::stod(token)); // convert annual interest to double
        }
        catch (const std::exception& e) { // annual interest error caught
            std::cout << "Error parsing annual interest from file: " << e.what() << std::endl;
            return;
        }

        try {
            std::getline(ss, token, ','); 
            userInvestment.setYears(std::stoi(token)); // convert years to integer
        }
        catch (const std::exception& e) { // year error caught
            std::cout << "Error parsing years from file: " << e.what() << std::endl;
            return;
        }

        try {
            std::getline(ss, token, ','); 
            userInvestment.setTotalWithoutDeposits(std::stod(token)); // convert total without deposits to double
        }
        catch (const std::exception& e) { // total without deposits error caught
            std::cout << "Error parsing total without deposits from file: " << e.what() << std::endl;
            return;
        }

        try {
            std::getline(ss, token, ','); 
            userInvestment.setTotalWithDeposits(std::stod(token)); // convert total with deposits to double
        }
        catch (const std::exception& e) { // total with deposits error caught
            std::cout << "Error parsing total with deposits from file: " << e.what() << std::endl;
            return;
        }
    }

    // read year over year vectors
    std::vector<double> tempVector;

    // skip blank line before vectors
    std::getline(inFile, line);

    userInvestment.getYearlyBalancesWithoutDeposits().clear();
    userInvestment.getYearlyInterestsWithoutDeposits().clear();
    userInvestment.getYearlyBalancesWithDeposits().clear();
    userInvestment.getYearlyInterestsWithDeposits().clear();

    // vector read, wrap in try-catch to catch any errors with data being handled
    // read yearly balances without deposits - "YearlyBalancesWithoutDeposits"
    try {
        std::getline(inFile, line);
        if (std::getline(inFile, line)) {
            tempVector = splitLineToDoubles(line);
            for (double val : tempVector) userInvestment.getYearlyBalancesWithoutDeposits().push_back(val);
        }
    }
    catch (const std::exception& e) { // yearly balances without deposits vector error caught
        std::cout << "Error parsing yearly balances without deposits from file: " << e.what() << std::endl;
        return;
    }

    // read yearly interests without deposits - "YearlyInterestsWithoutDeposits"
    try {
        std::getline(inFile, line);
        if (std::getline(inFile, line)) {
            tempVector = splitLineToDoubles(line);
            for (double val : tempVector) userInvestment.getYearlyInterestsWithoutDeposits().push_back(val);
        }
    }
    catch (const std::exception& e) { // yearly interests without deposits vector error caught
        std::cout << "Error parsing yearly interests without deposits from file: " << e.what() << std::endl;
        return;
    }

    // read yearly balances with deposits - "YearlyBalancesWithDeposits"
    try {
        std::getline(inFile, line);
        if (std::getline(inFile, line)) {
            tempVector = splitLineToDoubles(line);
            for (double val : tempVector) userInvestment.getYearlyBalancesWithDeposits().push_back(val);
        }
    }
    catch (const std::exception& e) { // yearly balances with deposits vector error caught
        std::cout << "Error parsing yearly balances with deposits from file: " << e.what() << std::endl;
        return;
    }

    // read yearly interests with deposits - "YearlyInterestsWithDeposits"
    try {
        std::getline(inFile, line);
        if (std::getline(inFile, line)) {
            tempVector = splitLineToDoubles(line);
            for (double val : tempVector) userInvestment.getYearlyInterestsWithDeposits().push_back(val);
        }
    }
    catch (const std::exception& e) { // yearly interests with deposits vector error caught
        std::cout << "Error parsing yearly interests with deposits from file: " << e.what() << std::endl;
        return;
    }

    inFile.close();
    std::cout << "Report successfully imported from investment_report.csv" << std::endl;
}