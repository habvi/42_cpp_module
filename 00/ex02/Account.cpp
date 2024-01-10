#include "Account.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#define MSG_CREATED "created"
#define MSG_CLOSED  "closed"
#define MSG_REFUSED "refused"

typedef struct info {
	std::string name;
	int         value;
} t_info;

int Account::_nbAccounts         = 0;
int Account::_totalAmount        = 0;
int Account::_totalNbDeposits    = 0;
int Account::_totalNbWithdrawals = 0;

static void
put_log_account(const int index, const int amount, const std::string &message) {
	std::cout << "index:" << index << ";"
			  << "amount:" << amount << ";" << message << std::endl;
}

static void put_log_account(const t_info (&info)[], const size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << info[i].name << ":" << info[i].value;
		if (i != size - 1) {
			std::cout << ";";
		}
	}
	std::cout << std::endl;
}

Account::Account(void) {
	_accountIndex  = _nbAccounts;
	_amount        = 0;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_account(_accountIndex, _amount, MSG_CREATED);

	_nbAccounts++;
}

Account::Account(int initial_deposit) {
	_accountIndex  = _nbAccounts;
	_amount        = initial_deposit;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_account(_accountIndex, _amount, MSG_CREATED);

	_nbAccounts++;
	_totalAmount += _amount;
}

Account::~Account(void) {
	_displayTimestamp();
	put_log_account(_accountIndex, _amount, MSG_CLOSED);
}

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

void Account::displayAccountsInfos(void) {
	_displayTimestamp();
	const t_info infos[] = {
		{"accounts", _nbAccounts},
		{"total", _totalAmount},
		{"deposits", _totalNbDeposits},
		{"withdrawals", _totalNbWithdrawals}
	};
	put_log_account(infos, sizeof(infos) / sizeof(infos[0]));
}

void Account::makeDeposit(int deposit) {
	const int pre_amount = _amount;

	_amount += deposit;
	_nbDeposits++;

	_totalAmount += deposit;
	_totalNbDeposits++;

	_displayTimestamp();
	const t_info infos[] = {
		{"index", _accountIndex},
		{"p_amount", pre_amount},
		{"deposits", deposit},
		{"amount", _amount},
		{"nb_deposits", _nbDeposits},
	};
	put_log_account(infos, sizeof(infos) / sizeof(infos[0]));
}

bool Account::makeWithdrawal(int withdrawal) {
	const int pre_amount = _amount;

	// todo: call checkAmount?
	if (pre_amount - withdrawal < 0) {
		_displayTimestamp();
		// todo
		std::cout << MSG_REFUSED << std::endl;
		return false;
	}

	_amount -= withdrawal;
	_nbWithdrawals++;

	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;

	_displayTimestamp();
	const t_info infos[] = {
		{"index", _accountIndex},
		{"p_amount", pre_amount},
		{"withdrawals", withdrawal},
		{"amount", _amount},
		{"nb_withdrawals", _nbWithdrawals},
	};
	put_log_account(infos, sizeof(infos) / sizeof(infos[0]));
	return true;
}

int Account::checkAmount(void) const {
	return 0;
}

void Account::displayStatus(void) const {
	_displayTimestamp();
	const t_info infos[] = {
		{"index", _accountIndex},
		{"amount", _amount},
		{"deposits", _nbDeposits},
		{"withdrawals", _nbWithdrawals}
	};
	put_log_account(infos, sizeof(infos) / sizeof(infos[0]));
}

// todo: get current time like a sample log file
void Account::_displayTimestamp(void) {
	std::cout << "[time] ";
}
