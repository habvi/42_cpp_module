#include "Account.hpp"
#include <cstdlib>
#include <iostream>

int Account::_nbAccounts         = 0;
int Account::_totalAmount        = 0;
int Account::_totalNbDeposits    = 0;
int Account::_totalNbWithdrawals = 0;

static void put_log_account(const int index, const int amount) {
	std::cout << "index:" << index << ";"
			  << "amount:" << amount << ";"
			  << "created" << std::endl;
}

Account::Account(void) {
	_accountIndex  = _nbAccounts;
	_amount        = 0;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_account(_nbAccounts, _amount);

	_nbAccounts++;
}

Account::Account(int initial_deposit) {
	_accountIndex  = _nbAccounts;
	_amount        = initial_deposit;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_account(_nbAccounts, _amount);

	_nbAccounts++;
	_totalAmount += _amount;
}

Account::~Account(void) {}

int Account::getNbAccounts(void) {
	return _nbAccounts;
}

int Account::getTotalAmount(void) {
	return _totalAmount;
}

int Account::getNbDeposits(void) {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos(void) {}

void Account::makeDeposit(int deposit) {
	(void)deposit;
}

bool Account::makeWithdrawal(int withdrawal) {
	(void)withdrawal;
	return true;
}

int Account::checkAmount(void) const {
	return 0;
}

void Account::displayStatus(void) const {}

// todo: get current time like a sample log file
void Account::_displayTimestamp(void) {
	std::cout << "[time] ";
}
