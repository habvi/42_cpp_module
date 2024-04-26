#include "color.hpp"
#include "easyfind.hpp"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace test {
	typedef enum e_result {
		FOUND,
		NOT_FOUND
	} Result;

	// -------------------------------------------------------------------------
	void DisplayTitle(const unsigned int testcase_number, const std::string &title) {
		std::cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
		std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	}

	template <typename T>
	void PrintInfo(const std::string &name, const T &container, const int &value) {
		std::cout << name << " : {";

		typename T::const_iterator itr;
		for (itr = container.begin(); itr != container.end(); ++itr) {
			if (itr != container.begin()) {
				std::cout << ", ";
			}
			std::cout << *itr;
		}

		std::cout << "}" << std::endl;
		std::cout << "easyfind value : " << COLOR_PINK << value << COLOR_END
				  << std::endl;
	}

	void JudgeResult(Result expected, Result result) {
		if (expected == result) {
			std::cout << COLOR_GREEN "[OK]" COLOR_END << std::endl;
		} else {
			std::cout << COLOR_RED "[NG]" COLOR_END << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// -------------------------------------------------------------------------
	template <typename T>
	void RunEasyfind(
		const std::string &name, T &container, const int &value, Result expected
	) {
		PrintInfo(name, container, value);

		typename T::iterator itr = easyfind(container, value);
		std::cout << "Result : ";
		if (itr != container.end()) {
			std::cout << COLOR_GREEN "found!      " COLOR_END;
			JudgeResult(expected, FOUND);
		} else {
			std::cout << COLOR_PINK "not found.. " COLOR_END;
			JudgeResult(expected, NOT_FOUND);
		}
		std::cout << "--------------------------" << std::endl;
	}

	template <typename T>
	void RunEasyfind(
		const std::string &name,
		const T           &container,
		const int         &value,
		Result             expected
	) {
		PrintInfo(name, container, value);

		typename T::const_iterator itr = easyfind(container, value);
		std::cout << "Result : ";
		if (itr != container.end()) {
			std::cout << COLOR_GREEN "found!      " COLOR_END;
			JudgeResult(expected, FOUND);
		} else {
			std::cout << COLOR_PINK "not found.. " COLOR_END;
			JudgeResult(expected, NOT_FOUND);
		}
		std::cout << "--------------------------" << std::endl;
	}

	// -------------------------------------------------------------------------
	static const unsigned int kSize      = 5;
	int                       arr[kSize] = {1, 2, 3, 4, 5};
	// -------------------------------------------------------------------------

	void RunTest1() {
		DisplayTitle(1, "list<int> / const");

		const std::list<int> list(arr, arr + kSize);

		RunEasyfind("list", list, 1, FOUND);
		RunEasyfind("list", list, 5, FOUND);
		RunEasyfind("list", list, 0, NOT_FOUND);
		RunEasyfind("list", list, 6, NOT_FOUND);
	}

	void RunTest2() {
		DisplayTitle(2, "list<int> / pop_front");

		std::list<int> list(arr, arr + kSize);

		RunEasyfind("list", list, 1, FOUND);
		RunEasyfind("list", list, 5, FOUND);
		RunEasyfind("list", list, 0, NOT_FOUND);
		RunEasyfind("list", list, 6, NOT_FOUND);

		list.pop_front();
		RunEasyfind("list", list, 1, NOT_FOUND);
	}

	void RunTest3() {
		DisplayTitle(3, "vector<int> / const");

		const std::vector<int> vec(arr, arr + kSize);

		RunEasyfind("vector", vec, 1, FOUND);
		RunEasyfind("vector", vec, 5, FOUND);
		RunEasyfind("vector", vec, 0, NOT_FOUND);
		RunEasyfind("vector", vec, 6, NOT_FOUND);
	}

	void RunTest4() {
		DisplayTitle(4, "vector<int> / push_back");

		std::vector<int> vec(arr, arr + kSize);

		RunEasyfind("vector", vec, 1, FOUND);
		RunEasyfind("vector", vec, 5, FOUND);
		RunEasyfind("vector", vec, 0, NOT_FOUND);
		RunEasyfind("vector", vec, 6, NOT_FOUND);

		vec.push_back(100);
		RunEasyfind("vector", vec, 100, FOUND);
	}

	void RunTest5() {
		DisplayTitle(5, "deque<int> / const");

		const std::deque<int> deque(arr, arr + kSize);

		RunEasyfind("deque", deque, 1, FOUND);
		RunEasyfind("deque", deque, 5, FOUND);
		RunEasyfind("deque", deque, 0, NOT_FOUND);
		RunEasyfind("deque", deque, 6, NOT_FOUND);
	}

	void RunTest6() {
		DisplayTitle(6, "deque<int> / same value");

		std::deque<int> deque(arr, arr + kSize);

		RunEasyfind("deque", deque, 1, FOUND);
		RunEasyfind("deque", deque, 5, FOUND);
		RunEasyfind("deque", deque, 0, NOT_FOUND);
		RunEasyfind("deque", deque, 6, NOT_FOUND);

		deque.push_back(3);
		RunEasyfind("deque", deque, 3, FOUND);
	}
} // namespace test

int main() {
	test::RunTest1();
	test::RunTest2();
	test::RunTest3();
	test::RunTest4();
	test::RunTest5();
	test::RunTest6();

	return EXIT_SUCCESS;
}
