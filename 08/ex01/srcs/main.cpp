#include "Span.hpp"
#include "color.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <sstream> // stringstream
#include <vector>

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
	void JudgeResult(const T &expected, const T &result) {
		if (expected == result) {
			std::cout << COLOR_GREEN "[OK]" COLOR_END << std::endl;
		} else {
			std::cout << COLOR_RED "[NG]" COLOR_END << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	template <typename T>
	void JudgeResult(const int num, const T &expected, const T &result) {
		if (expected == result) {
			std::cout << COLOR_GREEN "[add " << num << " : OK]" COLOR_END
					  << std::endl;
		} else {
			std::cout << COLOR_RED "[add " << num << " : NG]" COLOR_END << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// -------------------------------------------------------------------------
	void AddNumber(Span &span, const int num, Result expected) {
		try {
			span.addNumber(num);
			JudgeResult(num, expected, SUCCESS);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult(num, expected, FAIL);
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
			std::cout << COLOR_PINK "shortest: " << exec_ret << " " COLOR_END;
			JudgeResult(expected_shortest, exec_ret);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult(expected_shortest_result, FAIL);
		}
		// longestSpan()
		try {
			std::stringstream ss;
			ss << span.longestSpan();
			unsigned int exec_ret;
			ss >> exec_ret;
			std::cout << COLOR_PINK "longest : " << exec_ret << " " COLOR_END;
			JudgeResult(expected_longest, exec_ret);
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << "Error: " << e.what() << " " << COLOR_END;
			JudgeResult(expected_longest_result, FAIL);
		}
	}

	// -------------------------------------------------------------------------
	void JudgeIsSameMembers(const Span &s1, const Span &s2) {
		if (s1.IsSameSpan(s2)) {
			std::cout << COLOR_GREEN "[copy: OK]" COLOR_END << std::endl;
		} else {
			std::cerr << COLOR_RED << "Error: not the same Span" << COLOR_END;
			exit(EXIT_FAILURE);
		}
	}
	// -------------------------------------------------------------------------
	void RunExactlySubjectTest() {
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
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
		AddNumber(span, 5, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest3() {
		DisplayTitle(3, "capacity: 2 / add same number 3 times");

		Span span = Span(2);
		AddNumber(span, 9, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		Line();
		AddNumber(span, 9, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, SUCCESS, 0, SUCCESS);
		Line();
		AddNumber(span, 9, FAIL);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest4() {
		DisplayTitle(4, "capacity: 4 / add hightst 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		std::cout << span << std::endl;
		Line();
		AddNumber(span, 3, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest5() {
		DisplayTitle(5, "capacity: 4 / add lowest 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		std::cout << span << std::endl;
		Line();
		AddNumber(span, 3, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);
		Line();
		AddNumber(span, 1, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest6() {
		DisplayTitle(6, "capacity: 3 / update longest by higher number");

		Span span = Span(4);
		AddNumber(span, 0, SUCCESS);
		std::cout << span << std::endl;
		Line();
		AddNumber(span, 5, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		Line();
		AddNumber(span, 50, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

	void RunOriginalTest7() {
		DisplayTitle(7, "capacity: 3 / update longest by lower number");

		Span span = Span(4);
		AddNumber(span, 100, SUCCESS);
		std::cout << span << std::endl;
		Line();
		AddNumber(span, 95, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		Line();
		AddNumber(span, 50, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

	void RunOriginalTest8() {
		DisplayTitle(8, "capacity: 3 / copy constructor");

		Span span1 = Span(3);
		AddNumber(span1, 2, SUCCESS);
		std::cout << span1 << std::endl;
		Line();
		AddNumber(span1, 10, SUCCESS);
		std::cout << span1 << std::endl;
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
		Line();

		// copy
		Span span2(span1);
		JudgeIsSameMembers(span1, span2);
		AddNumber(span2, 4, SUCCESS);
		std::cout << span2 << std::endl;
		ShortestAndLongest(span2, 2, SUCCESS, 8, SUCCESS);

		Line();
		// The changes to span2 aren't being reflected span1
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
	}

	void RunOriginalTest9() {
		DisplayTitle(9, "capacity: 3 / operator= ");

		Span span1 = Span(3);
		AddNumber(span1, 2, SUCCESS);
		std::cout << span1 << std::endl;
		Line();
		AddNumber(span1, 10, SUCCESS);
		std::cout << span1 << std::endl;
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
		Line();

		// copy
		Span span2 = span1;
		JudgeIsSameMembers(span1, span2);
		AddNumber(span2, 4, SUCCESS);
		std::cout << span2 << std::endl;
		ShortestAndLongest(span2, 2, SUCCESS, 8, SUCCESS);

		Line();
		// The changes to span2 aren't being reflected span1
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
	}

	void RunOriginalTest10() {
		DisplayTitle(10, "capacity: 10000 / by addNumber()");

		static const unsigned int kCapacity = 100000;

		Span span = Span(kCapacity);
		for (unsigned int i = 0; i < kCapacity; i++) {
			span.addNumber(i);
		}
		ShortestAndLongest(span, 1, SUCCESS, kCapacity - 1, SUCCESS);
	}

	void RunOriginalTest11() {
		DisplayTitle(11, "capacity: 10000 / Insert() / add at once");

		static const unsigned int kCapacity = 100000;

		Span span = Span(kCapacity);
		span.Insert(123, 1000);
		ShortestAndLongest(span, 1, SUCCESS, 1000 - 123 - 1, SUCCESS);
	}

	void RunOriginalTest12() {
		DisplayTitle(11, "capacity: 7 / Insert() / range of iterators");

		static const unsigned int kCapacity = 10;

		int              arr[7] = {12, 377, 41, 9999, 215, 0, 3146};
		std::vector<int> vec(arr, arr + 7);

		Span span = Span(kCapacity);
		span.Insert<std::vector<int> >(vec.begin(), vec.end());
		std::cout << span << std::endl;
		ShortestAndLongest(span, 12, SUCCESS, 9999, SUCCESS);
	}

	void RunOriginalTest13() {
		DisplayTitle(13, "capacity: 6 / INT_MIN, INT_MAX");

		int              arr[2] = {INT_MIN, INT_MAX};
		std::vector<int> vec(arr, arr + 2);

		Span span = Span(6);
		span.Insert<std::vector<int> >(vec.begin(), vec.end());
		std::cout << span << std::endl;
		ShortestAndLongest(span, UINT_MAX, SUCCESS, UINT_MAX, SUCCESS);
		Line();

		AddNumber(span, INT_MAX, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, SUCCESS, UINT_MAX, SUCCESS);
		Line();

		AddNumber(span, 0, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 0, SUCCESS, UINT_MAX, SUCCESS);
	}

	void RunOriginalTest14() {
		DisplayTitle(14, "capacity: 6 / minus elems");

		Span span = Span(6);
		AddNumber(span, -10, SUCCESS);
		std::cout << span << std::endl;
		AddNumber(span, -30, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 20, SUCCESS, 20, SUCCESS);
		Line();
		AddNumber(span, -12, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 20, SUCCESS);
		Line();
		AddNumber(span, -100, SUCCESS);
		std::cout << span << std::endl;
		ShortestAndLongest(span, 2, SUCCESS, 90, SUCCESS);
	}
} // namespace test

int main(int argc, char **argv) {
	(void)argv;
	if (argc == 1) {
		test::RunExactlySubjectTest();
	} else {
		test::RunSubjectTest();
		test::RunOriginalTest1();
		test::RunOriginalTest2();
		test::RunOriginalTest3();
		test::RunOriginalTest4();
		test::RunOriginalTest5();
		test::RunOriginalTest6();
		test::RunOriginalTest7();
		test::RunOriginalTest8();
		test::RunOriginalTest9();
		test::RunOriginalTest10();
		test::RunOriginalTest11();
		test::RunOriginalTest12();
		test::RunOriginalTest13();
		test::RunOriginalTest14();
	}
	return EXIT_SUCCESS;
}
