#include "RPN.hpp"
#include "color.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

namespace {
	// Following the instructions,  output to STDOUT in case of an error.
	void PrintError(const std::string &message) {
		std::cout << COLOR_RED << message << COLOR_END << std::endl;
	}
} // namespace

#ifdef RUN_TEST
namespace test {
	static void DisplayTitle(const std::string &title) {
		std::cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
		std::cout << "┃ " << title << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	}

	void Test(bool is_ok, const int expected, const std::string &str) {
		std::cout << "args   : [" << str << "]" << std::endl;
		try {
			const int result_num = RPN::Calcurate(str);
			if (result_num == expected && is_ok) {
				std::cout << "result : " << result_num << COLOR_GREEN << " [OK]"
						  << COLOR_END << std::endl;
			} else {
				std::exit(EXIT_FAILURE);
			}
		} catch (const std::exception &e) {
			if (is_ok) {
				std::exit(EXIT_FAILURE);
			}
			PrintError("Error");
			PrintError(e.what());
		}
		std::cout << "--------------------" << std::endl;
	}

	void RunTest() {
		//-----------------------------------------------------
		// subject
		//-----------------------------------------------------
		DisplayTitle("subject");
		Test(true, 42, "8 9 * 9 - 9 - 9 - 4 - 1 +");
		Test(true, 42, "7 7 * 7 -");
		Test(true, 0, "1 2 * 2 / 2 * 2 4 - +");
		Test(false, 0, "(1 + 1)");

		//-----------------------------------------------------
		// original / normal
		//-----------------------------------------------------
		DisplayTitle("original / normal");
		Test(true, 0, "0");

		// [add]
		DisplayTitle("original / normal / add");
		Test(true, 6, "123++");
		Test(true, 6, "12+3+");
		Test(true, 0, "000++");

		// [sub]
		DisplayTitle("original / normal / sub");
		Test(true, 2, "123--");
		Test(true, -4, "12-3-");

		// [mul]
		DisplayTitle("original / normal / mul");
		Test(true, 6, "123**");
		Test(true, 6, "12*3*");
		// 8**10
		Test(true, 1073741824, "8888888888*********");
		// 0 * INT_MIN
		Test(true, 0, "08* 8888888888**********");

		// [div]
		DisplayTitle("original / normal / div");
		Test(true, 8, "822//");
		Test(true, 2, "82/2/");
		Test(true, 2, "94/");

		// [mix]
		DisplayTitle("original / normal / mix");
		Test(true, 12, "98+7-6*5/");
		Test(true, -81, "12-9*9*");
		// 8**10 + (8**10 - 1)
		Test(true, 2147483647, "8888888888********* 8888888888********* 1- +");
		// (-1) * 8**10 * 2
		Test(true, -2147483648, "12- 8*8*8*8*8*8*8*8*8*8* 2*");
		// INT_MIN * 0
		Test(true, 0, "12- 8*8*8*8*8*8*8*8*8*8* 2* 0*");

		//-----------------------------------------------------
		// original / error
		//-----------------------------------------------------
		// [invalid argument]
		DisplayTitle("original / error / invalid argument");
		Test(false, 0, "");
		Test(false, 0, "a");
		Test(false, 0, "+");
		Test(false, 0, "123");

		// [add]
		DisplayTitle("original / error: overflow / add");
		// 8**10 + (8**10 - 1) + 1 = 2147483648
		Test(false, 0, "8888888888********* 8888888888********* 1- + 1+");
		// (-1) * 8**10 * 2 + (-1) = 2147483649
		Test(false, 0, "12- 8*8*8*8*8*8*8*8*8*8* 2* 12- +");

		// [sub]
		DisplayTitle("original / error: overflow / sub");
		// 8**10 + (8**10 - 1) - (-1) = 2147483648
		Test(false, 0, "8888888888********* 8888888888********* 1- + 12- -");
		// (-1) * 8**10 * 2 - 1 = -2147483649
		Test(false, 0, "12- 8*8*8*8*8*8*8*8*8*8* 2* 1-");

		// [mul]
		DisplayTitle("original / error: overflow / mul");
		// 8**10 * 2 = 2147483648
		Test(false, 0, "8888888888********* 2*");
		// (-1) * 8**10 * 2 * 2 = -2147483648 * 2
		Test(false, 0, "12- 8*8*8*8*8*8*8*8*8*8* 2* 2*");
		// -1 * INT_MIN
		Test(false, 0, "12- 12- 2*8*8*8*8*8*8*8*8*8*8**");

		// [div]
		DisplayTitle("original / error: zero division / div");
		Test(false, 0, "10/");
		Test(false, 0, "812//");

		// [mix]
		DisplayTitle("original / error: zero division / mix");
		Test(false, 0, "98+7-6*5/4/3/2/1/0/");
	}
} // namespace test

#endif

int main(int argc, char **argv) {

#ifndef RUN_TEST
	if (argc != 2) {
		PrintError("Error: invalid argument");
		return EXIT_FAILURE;
	}

	const std::string rpn_str(argv[1]);
	try {
		const int result_num = RPN::Calcurate(rpn_str);
		std::cout << result_num << std::endl;
	} catch (const std::exception &e) {
		PrintError("Error");
		return EXIT_FAILURE;
	}
#endif

#ifdef RUN_TEST
	(void)argc;
	(void)argv;
	test::RunTest();
#endif

	return EXIT_SUCCESS;
}
