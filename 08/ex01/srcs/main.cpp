#include "Span.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream> // stringstream

namespace test {
	typedef enum e_result {
		SUCCESS,
		FAIL
	} Result;

	// -------------------------------------------------------------------------
	void DisplayTitle(const unsigned int testcase_number, const std::string &title) {
		std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
				  << std::endl;
		std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	}

	void Line() {
		std::cout << "-----------------------------------" << std::endl;
	}

	template <typename T>
	void JudgeResult(const std::string &msg, const T &expected, const T &result) {
		if (expected == result) {
			std::cout << COLOR_GREEN "[" << msg << "OK]" COLOR_END << std::endl;
		} else {
			std::cout << COLOR_RED "[" << msg << "NG]" COLOR_END << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// -------------------------------------------------------------------------
	void AddNumber(Span &span, const unsigned int num, Result expected) {
		try {
			span.addNumber(num);
			JudgeResult("add: ", expected, SUCCESS);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult("add: ", expected, FAIL);
		}
	}

	// -------------------------------------------------------------------------
	void ShortestAndLongest(
		const Span        &span,
		const unsigned int expected_shortest,
		Result             expected_shortest_result,
		const unsigned int expected_longest,
		Result             expected_longest_result
	) {
		// shortestSpan()
		try {
			std::stringstream ss;
			ss << span.shortestSpan();
			unsigned int exec_ret;
			ss >> exec_ret;
			std::cout << "shortest: " << exec_ret << " ";
			JudgeResult("", expected_shortest, exec_ret);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult("", expected_shortest_result, FAIL);
		}
		// longestSpan()
		try {
			std::stringstream ss;
			ss << span.longestSpan();
			unsigned int exec_ret;
			ss >> exec_ret;
			std::cout << "longest : " << exec_ret << " ";
			JudgeResult("", expected_longest, exec_ret);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult("", expected_longest_result, FAIL);
		}
	}

	// -------------------------------------------------------------------------
	void RunSubjectTest() {
		DisplayTitle(0, "subject test");

		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	void RunOriginalTest1() {
		DisplayTitle(1, "capacity: 0 / shortestSpan() / longestSpan()");

		Span span = Span(0);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest2() {
		DisplayTitle(2, "capacity: 1 / shortestSpan() /longestSpan()");

		Span span = Span(1);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest3() {
		DisplayTitle(3, "capacity: 2 / add same number 3 times");

		Span span = Span(2);
		AddNumber(span, 9, SUCCESS);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		AddNumber(span, 9, SUCCESS);
		ShortestAndLongest(span, 0, SUCCESS, 0, SUCCESS);
		Line();
		AddNumber(span, 9, FAIL);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest4() {
		DisplayTitle(4, "capacity: 4 / add hightst 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		AddNumber(span, 3, SUCCESS);
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		AddNumber(span, 5, SUCCESS);
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);

		AddNumber(span, 5, SUCCESS);
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest5() {
		DisplayTitle(5, "capacity: 4 / add lowest 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		AddNumber(span, 3, SUCCESS);
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		AddNumber(span, 5, SUCCESS);
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);
		AddNumber(span, 1, SUCCESS);
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest6() {
		DisplayTitle(6, "capacity: 3 / update longest by higher number");

		Span span = Span(4);
		AddNumber(span, 0, SUCCESS);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		AddNumber(span, 5, SUCCESS);
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		AddNumber(span, 50, SUCCESS);
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

	void RunOriginalTest7() {
		DisplayTitle(7, "capacity: 3 / update longest by lower number");

		Span span = Span(4);
		AddNumber(span, 100, SUCCESS);
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		AddNumber(span, 95, SUCCESS);
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		AddNumber(span, 50, SUCCESS);
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

} // namespace test

int main() {
	test::RunSubjectTest();

	test::RunOriginalTest1();
	test::RunOriginalTest2();
	test::RunOriginalTest3();
	test::RunOriginalTest4();
	test::RunOriginalTest5();
	test::RunOriginalTest6();
	test::RunOriginalTest7();

	return EXIT_SUCCESS;
}