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

static void put_log_with_no_endl(const t_info (&info)[], const size_t size) {
	for (size_t i = 0; i < size; i++) {
		std::cout << info[i].name << ":" << info[i].value;
		if (i != size - 1) {
			std::cout << ";";
		}
	}
}

static void put_log(const t_info (&info)[], const size_t size) {
	put_log_with_no_endl(info, size);
	std::cout << std::endl;
}

static void
put_log(const t_info (&info)[], const size_t size, const std::string &message) {
	put_log_with_no_endl(info, size);
	std::cout << message << std::endl;
}

static void put_log_create(const int account_index, const int amount) {
	const t_info infos[] = {{"index", account_index}, {"amount", amount}};

	put_log(infos, sizeof(infos) / sizeof(infos[0]), ";" MSG_CREATED);
}

Account::Account(void) {
	_accountIndex  = _nbAccounts;
	_amount        = 0;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_create(_accountIndex, _amount);

	_nbAccounts++;
}

Account::Account(int initial_deposit) {
	_accountIndex  = _nbAccounts;
	_amount        = initial_deposit;
	_nbDeposits    = 0;
	_nbWithdrawals = 0;
	_displayTimestamp();
	put_log_create(_accountIndex, _amount);

	_nbAccounts++;
	_totalAmount += _amount;
}

static void put_log_close(const int account_index, const int amount) {
	const t_info infos[] = {{"index", account_index}, {"amount", amount}};

	put_log(infos, sizeof(infos) / sizeof(infos[0]), ";" MSG_CLOSED);
}

Account::~Account(void) {
	_displayTimestamp();
	put_log_close(_accountIndex, _amount);
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
	put_log(infos, sizeof(infos) / sizeof(infos[0]));
}

static void put_log_deposit(
	const int account_index,
	const int pre_amount,
	const int deposit,
	const int amount,
	const int nb_deposits
) {
	const t_info infos[] = {
		{"index", account_index},
		{"p_amount", pre_amount},
		{"deposit", deposit},
		{"amount", amount},
		{"nb_deposits", nb_deposits},
	};
	put_log(infos, sizeof(infos) / sizeof(infos[0]));
}

void Account::makeDeposit(int deposit) {
	const int pre_amount = _amount;

	_amount += deposit;
	_nbDeposits++;

	_totalAmount += deposit;
	_totalNbDeposits++;

	_displayTimestamp();
	put_log_deposit(_accountIndex, pre_amount, deposit, _amount, _nbDeposits);
}

static void put_log_error_withdrawal(const int account_index, const int pre_amount) {
	const t_info infos[] = {{"index", account_index}, {"p_amount", pre_amount}};

	put_log(infos, sizeof(infos) / sizeof(infos[0]), ";withdrawal:" MSG_REFUSED);
}

static void put_log_withdrawals(
	const int account_index,
	const int pre_amount,
	const int withdrawal,
	const int amount,
	const int nb_withdrawals
) {
	const t_info infos[] = {
		{"index", account_index},
		{"p_amount", pre_amount},
		{"withdrawal", withdrawal},
		{"amount", amount},
		{"nb_withdrawals", nb_withdrawals},
	};
	put_log(infos, sizeof(infos) / sizeof(infos[0]));
}

bool Account::makeWithdrawal(int withdrawal) {
	const int pre_amount = _amount;

	_amount -= withdrawal;
	if (checkAmount() == AMOUNT_ERROR) {
		_amount += withdrawal;
		_displayTimestamp();
		put_log_error_withdrawal(_accountIndex, pre_amount);
		return false;
	}
	_nbWithdrawals++;

	_totalAmount -= withdrawal;
	_totalNbWithdrawals++;

	_displayTimestamp();
	put_log_withdrawals(
		_accountIndex, pre_amount, withdrawal, _amount, _nbWithdrawals
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
	const t_info infos[] = {
		{"index", _accountIndex},
		{"amount", _amount},
		{"deposits", _nbDeposits},
		{"withdrawals", _nbWithdrawals}
	};
	put_log(infos, sizeof(infos) / sizeof(infos[0]));
}

#ifdef NO_TIMESTAMP
void Account::_displayTimestamp(void) {}
#else
static void
display_with_fill(const int num, const unsigned int width, const char fill_char) {
	std::cout << std::setw(width) << std::setfill(fill_char) << num;
}

void Account::_displayTimestamp(void) {
	std::time_t       t         = std::time(NULL);
	std::tm          *now       = std::localtime(&t);
	static const char fill_char = '0';

	std::cout << "[" << (now->tm_year + 1900);
	display_with_fill(now->tm_mon + 1, 2, fill_char);
	display_with_fill(now->tm_mday, 2, fill_char);
	std::cout << "_";
	display_with_fill(now->tm_hour, 2, fill_char);
	display_with_fill(now->tm_min, 2, fill_char);
	display_with_fill(now->tm_sec, 2, fill_char);
	std::cout << "] ";
}
#endif
