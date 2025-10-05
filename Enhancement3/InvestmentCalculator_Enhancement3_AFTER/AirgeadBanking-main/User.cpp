/************************************************************
** UPDATE: cpp file for User                               **
** Name: User.cpp                                          **
** Author: Brandon Cook                                    **
*************************************************************/

#include "User.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#include <openssl/sha.h> // SHA-256 hashing for password

User::User(mysqlx::Schema schema) : db(schema), userId(0) {} // default constructor

// SHA-256 password hashing
std::string User::hashPassword(const std::string& password) {
	unsigned char hash[SHA256_DIGEST_LENGTH]; // hash function
	SHA256(reinterpret_cast<const unsigned char*>(password.c_str()), password.size(), hash);

	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

	return ss.str();
}

// register a new user, store into database
bool User::registerUser(const std::string& uname, const std::string& password) {
	try {
		mysqlx::Table usersTable = db.getTable("users"); // store users table for operations
		usersTable.insert("username", "password_hash").values(uname, hashPassword(password)).execute(); // add new user to table

		std::cout << "Registration successful." << std::endl;
		return true;
	}
	catch (const mysqlx::Error& e) { // error when adding to table
		std::cout << "Registration failed: " << e.what() << std::endl;
		return false;
	}
}

// login an existing user, check with database
bool User::loginUser(const std::string& uname, const std::string& password) {
	try {
		mysqlx::Table usersTable = db.getTable("users"); // store users table for operations
		mysqlx::RowResult res = usersTable.select("user_id", "password_hash").where("username = :uname").bind("uname", uname).execute(); // check table if user exists and password correct

		mysqlx::Row row = res.fetchOne();
		if (!row.isNull()) {
			std::string dbHash = row[1].get<std::string>();
			if (dbHash == hashPassword(password)) { // check that password hashes match
				userId = row[0].get<int>();
				username = uname;
				std::cout << "Login successful." << std::endl;
				return true;
			}
			else { // password is incorrect
				std::cout << "Incorrect password." << std::endl;
				return false;
			}
		}
		else { // user does not exist in database
			std::cout << "User not found." << std::endl;
			return false;
		}
	}
	catch (const mysqlx::Error& e) { // other error
		std::cout << "Login error: " << e.what() << std::endl;
		return false;
	}
}