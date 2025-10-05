/************************************************************
** UPDATE: Header file for User                            **
** Name: User.h                                            **
** Author: Brandon Cook                                    **
*************************************************************/

#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <mysqlx/xdevapi.h> // X DevAPI

class User {
public:
	User(mysqlx::Schema schema); // constructor

	bool registerUser(const std::string& uname, const std::string& password); // register a new user
	bool loginUser(const std::string& uname, const std::string& password); // login an existing user

	int getUserId() const { return userId; } // return user id
	std::string getUsername() const { return username; } // return username

private:
	mysqlx::Schema db; // initialize database variable
	int userId; // variable to store user id
	std::string username; // variable to store username

	std::string hashPassword(const std::string& password); // hash the password for security
};

#endif