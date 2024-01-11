#include "Account.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#define MSG_CREATED    "created"
#define MSG_CLOSED     "closed"
#define MSG_REFUSED    "refused"
#define AMOUNT_SUCCESS 0
#define AMOUNT_ERROR   1

typedef struct info {
	std::string name;
	int         value;
} t_info;

int Account::_nbAccounts         = 0;
int Account::_totalAmount        = 0;
int Account::_totalNbDeposits    = 0;
int Account::_totalNbWithdrawals = 0;

static void putLogWithNoEndl(const t_info (&info)[], const size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << info[i].name << ":" << info[i].value;
		if (i != size - 1) {
			std::cout << ";";
		}
	}
}

static void putLog(const t_info (&info)[], const size_t size) {
	putLogWithNoEndl(info, size);
	std::cout << std::endl;
}

static void
putLog(const t_info (&info)[], const size_t size, const std::string &message) {
	putLogWithNoEndl(info, size);
	std::cout << message << std::endl;
}

static void putLogForCreate(const int accountIndex, const int amount) {
	const t_info info[] = {{"index", accountIndex}, {"amount", amount}};

	putLog(info, sizeof(info) / sizeof(info[0]), ";" MSG_CREATED);
}

Account::Account(void) {
	_accountIndex  = _nbAccounts;
	_amount        = 0;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	putLogForCreate(_accountIndex, _amount);

	_nbAccounts++;
}

Account::Account(int initial_deposit) {
	_accountIndex  = _nbAccounts;
	_amount        = initial_deposit;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	putLogForCreate(_accountIndex, _amount);

	_nbAccounts++;
	_totalAmount += _amount;
}

static void putLogForClose(const int accountIndex, const int amount) {
	const t_info info[] = {{"index", accountIndex}, {"amount", amount}};

	putLog(info, sizeof(info) / sizeof(info[0]), ";" MSG_CLOSED);
}

Account::~Account(void) {
	_displayTimestamp();
	putLogForClose(_accountIndex, _amount);
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
	const t_info info[] = {
		{"accounts", _nbAccounts},
		{"total", _totalAmount},
		{"deposits", _totalNbDeposits},
		{"withdrawals", _totalNbWithdrawals}
	};
	putLog(info, sizeof(info) / sizeof(info[0]));
}

static void putLogForDeposit(
	const int accountIndex,
	const int preAmount,
	const int deposit,
	const int amount,
	const int nbDeposits
) {
	const t_info info[] = {
		{"index", accountIndex},
		{"p_amount", preAmount},
		{"deposit", deposit},
		{"amount", amount},
		{"nb_deposits", nbDeposits},
	};
	putLog(info, sizeof(info) / sizeof(info[0]));
}

void Account::makeDeposit(int deposit) {
	const int preAmount = _amount;

	_amount += deposit;
	_nbDeposits++;

	_totalAmount += deposit;
	_totalNbDeposits++;

	_displayTimestamp();
	putLogForDeposit(_accountIndex, preAmount, deposit, _amount, _nbDeposits);
}

static void putLogForErrorWithdrawal(const int accountIndex, const int preAmount) {
	const t_info info[] = {{"index", accountIndex}, {"p_amount", preAmount}};

	putLog(info, sizeof(info) / sizeof(info[0]), ";withdrawal:" MSG_REFUSED);
}

static void putLogForWithdrawals(
	const int accountIndex,
	const int preAmount,
	const int withdrawal,
	const int amount,
	const int nbWithdrawals
) {
	const t_info info[] = {
		{"index", accountIndex},
		{"p_amount", preAmount},
		{"withdrawal", withdrawal},
		{"amount", amount},
		{"nb_withdrawals", nbWithdrawals},
	};
	putLog(info, sizeof(info) / sizeof(info[0]));
}

bool Account::makeWithdrawal(int withdrawal) {
	const int preAmount = _amount;

	_amount -= withdrawal;
	if (checkAmount() == AMOUNT_ERROR) {
		_amount += withdrawal;
		_displayTimestamp();
		putLogForErrorWithdrawal(_accountIndex, preAmount);
		return false;
	}
	_nbWithdrawals++;

	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;

	_displayTimestamp();
	putLogForWithdrawals(
		_accountIndex, preAmount, withdrawal, _amount, _nbWithdrawals
	);
	return true;
}

int Account::checkAmount(void) const {
	if (_amount < 0) {
		return AMOUNT_ERROR;
	}
	return AMOUNT_SUCCESS;
}

void Account::displayStatus(void) const {
	_displayTimestamp();
	const t_info info[] = {
		{"index", _accountIndex},
		{"amount", _amount},
		{"deposits", _nbDeposits},
		{"withdrawals", _nbWithdrawals}
	};
	putLog(info, sizeof(info) / sizeof(info[0]));
}

#ifdef NO_TIMESTAMP
void Account::_displayTimestamp(void) {}
#else
static void
displayWithFill(const int num, const unsigned int width, const char fillChar) {
	std::cout << std::setw(width) << std::setfill(fillChar) << num;
}

void Account::_displayTimestamp(void) {
	std::time_t       t        = std::time(NULL);
	std::tm          *now      = std::localtime(&t);
	static const char fillChar = '0';

	std::cout << "[" << (now->tm_year + 1900);
	displayWithFill(now->tm_mon + 1, 2, fillChar);
	displayWithFill(now->tm_mday, 2, fillChar);
	std::cout << "_";
	displayWithFill(now->tm_hour, 2, fillChar);
	displayWithFill(now->tm_min, 2, fillChar);
	displayWithFill(now->tm_sec, 2, fillChar);
	std::cout << "] ";
}
#endif
