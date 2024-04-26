#include "Span.hpp"
#include "color.hpp"
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
	void JudgeResult(const unsigned int num, const T &expected, const T &result) {
		if (expected == result) {
			std::cout << COLOR_GREEN "[add " << num << " : OK]" COLOR_END
					  << std::endl;
		} else {
			std::cout << COLOR_RED "[add " << num << " : NG]" COLOR_END << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	// -------------------------------------------------------------------------
	void AddNumber(Span &span, const unsigned int num, Result expected) {
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
		if (&s1 == &s2) {
			std::cerr << COLOR_RED << "Error: same Span instance" << COLOR_END;
			exit(EXIT_FAILURE);
		}
		// judge map's all elements
		Span::Elems elems_s1 = s1.orderd_elems();
		Span::Elems elems_s2 = s2.orderd_elems();
		if (elems_s1.size() != elems_s2.size()) {
			std::cerr << COLOR_RED << "Error: not the same map size" << COLOR_END;
			exit(EXIT_FAILURE);
		}
		Span::Elems::const_iterator itr_s1;
		Span::Elems::const_iterator itr_s2 = elems_s2.begin();
		for (itr_s1 = elems_s1.begin(); itr_s1 != elems_s1.end(); ++itr_s1) {
			if (*itr_s1 != *itr_s2) {
				std::cerr << COLOR_RED << "Error: not the same map" << COLOR_END;
				exit(EXIT_FAILURE);
			}
			++itr_s2;
		}
		// judge other members
		if (s1.max_elem_size() != s2.max_elem_size() ||
			s1.elem_count() != s2.elem_count() ||
			s1.shortest_span() != s2.shortest_span() ||
			s1.longest_span() != s2.longest_span()) {
			std::cerr << COLOR_RED << "Error: not the same member variables"
					  << COLOR_END;
			exit(EXIT_FAILURE);
		}
		std::cout << COLOR_GREEN "[copy: OK]" COLOR_END << std::endl;
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
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest3() {
		DisplayTitle(3, "capacity: 2 / add same number 3 times");

		Span span = Span(2);
		AddNumber(span, 9, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
		Line();
		AddNumber(span, 9, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 0, SUCCESS, 0, SUCCESS);
		Line();
		AddNumber(span, 9, FAIL);
		span.PutElems();
		ShortestAndLongest(span, 0, FAIL, 0, FAIL);
	}

	void RunOriginalTest4() {
		DisplayTitle(4, "capacity: 4 / add hightst 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		span.PutElems();
		Line();
		AddNumber(span, 3, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest5() {
		DisplayTitle(5, "capacity: 4 / add lowest 2 times. shortest to 0");

		Span span = Span(4);
		AddNumber(span, 1, SUCCESS);
		span.PutElems();
		Line();
		AddNumber(span, 3, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 2, SUCCESS, 2, SUCCESS);
		Line();
		AddNumber(span, 5, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 2, SUCCESS, 4, SUCCESS);
		Line();
		AddNumber(span, 1, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 0, SUCCESS, 4, SUCCESS);
	}

	void RunOriginalTest6() {
		DisplayTitle(6, "capacity: 3 / update longest by higher number");

		Span span = Span(4);
		AddNumber(span, 0, SUCCESS);
		span.PutElems();
		Line();
		AddNumber(span, 5, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		Line();
		AddNumber(span, 50, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

	void RunOriginalTest7() {
		DisplayTitle(7, "capacity: 3 / update longest by lower number");

		Span span = Span(4);
		AddNumber(span, 100, SUCCESS);
		span.PutElems();
		Line();
		AddNumber(span, 95, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 5, SUCCESS, 5, SUCCESS);
		Line();
		AddNumber(span, 50, SUCCESS);
		span.PutElems();
		ShortestAndLongest(span, 5, SUCCESS, 50, SUCCESS);
	}

	void RunOriginalTest8() {
		DisplayTitle(8, "capacity: 3 / copy constructor");

		Span span1 = Span(3);
		AddNumber(span1, 2, SUCCESS);
		span1.PutElems();
		Line();
		AddNumber(span1, 10, SUCCESS);
		span1.PutElems();
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
		Line();

		// copy
		Span span2(span1);
		JudgeIsSameMembers(span1, span2);
		AddNumber(span2, 4, SUCCESS);
		span2.PutElems();
		ShortestAndLongest(span2, 2, SUCCESS, 8, SUCCESS);

		Line();
		// The changes to span2 aren't being reflected span1
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
	}

	void RunOriginalTest9() {
		DisplayTitle(9, "capacity: 3 / operator= ");

		Span span1 = Span(3);
		AddNumber(span1, 2, SUCCESS);
		span1.PutElems();
		Line();
		AddNumber(span1, 10, SUCCESS);
		span1.PutElems();
		ShortestAndLongest(span1, 8, SUCCESS, 8, SUCCESS);
		Line();

		// copy
		Span span2 = span1;
		JudgeIsSameMembers(span1, span2);
		AddNumber(span2, 4, SUCCESS);
		span2.PutElems();
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
		span.Insert(kCapacity, 3);
		ShortestAndLongest(span, 0, SUCCESS, 0, SUCCESS);
	}

	void RunOriginalTest12() {
		DisplayTitle(11, "capacity: 7 / Insert() / range of iterators");

		static const unsigned int kCapacity = 10;

		unsigned int              arr[7] = {12, 377, 41, 9999, 215, 0, 3146};
		std::vector<unsigned int> vec(arr, arr + 7);

		Span span = Span(kCapacity);
		span.Insert<std::vector<unsigned int> >(vec.begin(), vec.end());
		span.PutElems();
		ShortestAndLongest(span, 12, SUCCESS, 9999, SUCCESS);
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
	}
	return EXIT_SUCCESS;
}