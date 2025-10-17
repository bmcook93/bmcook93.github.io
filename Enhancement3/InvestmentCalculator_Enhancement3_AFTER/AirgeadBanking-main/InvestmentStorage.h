/************************************************************
** UPDATE: New header file for InvestmentStorage.h         **
** Name: InvestmentStorage.h                               **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef INVESTMENT_STORAGE_H
#define INVESTMENT_STORAGE_H

#include <mysqlx/xdevapi.h>
#include "Investment.h"
#include "User.h"

class InvestmentStorage {
public:
	InvestmentStorage(mysqlx::Schema schema);

	bool saveInvestment(const User& user, Investment& investment); // store investment information
	bool retrieveInvestment(const User& user, Investment& investment); // retrieve investment information

private:
	mysqlx::Schema db;
};

#endif
