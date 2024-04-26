#include "MutantStack.hpp"
#include "color.hpp"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace test {
	void DisplayTitle(const unsigned int testcase_number, const std::string &title) {
		std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
				  << std::endl;
		std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	}

	void Line() {
		std::cout << "-----------------------------------" << std::endl;
	}

	// -------------------------------------------------------------------------
	// judge
	// -------------------------------------------------------------------------
	template <typename T>
	void JudgeIsSameStack(const MutantStack<T> &s1, const MutantStack<T> &s2) {
		if (&s1 == &s2) {
			std::cerr << "Error: required different stack" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (s1.size() != s2.size()) {
			std::cerr << "Error: not the same stack size" << std::endl;
			exit(EXIT_FAILURE);
		}
		typename MutantStack<T>::const_iterator begin1 = s1.begin();
		typename MutantStack<T>::const_iterator begin2 = s2.begin();
		while (begin1 != s1.end()) {
			if (*begin1 != *begin2) {
				std::cerr << "Error: same stack" << std::endl;
				exit(EXIT_FAILURE);
			}
			++begin1;
			++begin2;
		}
		std::cout << COLOR_GREEN "[OK]" COLOR_END << std::endl;
	}

	template <typename T>
	void JudgeIsSameStack(const MutantStack<T> &s1, std::stack<T> &s2) {
		if (&s1 == &s2) {
			std::cerr << "Error: required different stack" << std::endl;
			exit(EXIT_FAILURE);
		}
		if (s1.size() != s2.size()) {
			std::cerr << "Error: not the same stack size" << std::endl;
			exit(EXIT_FAILURE);
		}
		typename MutantStack<T>::const_iterator end = s1.end();
		while (end != s1.begin()) {
			--end;
			if (*end != s2.top()) {
				std::cerr << "Error: same stack" << std::endl;
				exit(EXIT_FAILURE);
			}
			s2.pop();
		}
		std::cout << COLOR_GREEN "[OK]" COLOR_END << std::endl;
	}

	// -------------------------------------------------------------------------
	// print
	// -------------------------------------------------------------------------
	template <typename T>
	void PrintStack(const std::stack<T> &s) {
		std::stack<T> copy_s(s);
		std::stack<T> tmp;
		while (!copy_s.empty()) {
			tmp.push(copy_s.top());
			copy_s.pop();
		}
		std::cout << COLOR_PINK "stack" COLOR_END " (size:" << tmp.size() << ")"
				  << std::endl;
		std::cout << "==> {";
		while (!tmp.empty()) {
			std::cout << tmp.top();
			if (tmp.size() != 1) {
				std::cout << ", ";
			}
			tmp.pop();
		}
		std::cout << "}" << std::endl;
	}

	template <typename T>
	void PrintQueue(const std::queue<T> &q) {
		std::queue<T> tmp(q);
		std::cout << COLOR_PINK "queue" COLOR_END " (size:" << tmp.size() << ")"
				  << std::endl;
		std::cout << "==> {";
		while (!tmp.empty()) {
			std::cout << tmp.front();
			if (tmp.size() != 1) {
				std::cout << ", ";
			}
			tmp.pop();
		}
		std::cout << "}" << std::endl;
	}

	template <typename T>
	void PrintItr(const std::string &str, const T &container) {
		std::cout << COLOR_PINK << str << COLOR_END " (size:" << container.size()
				  << ")" << std::endl;
		std::cout << "==> {";
		typename T::const_iterator itr = container.begin();
		while (itr != container.end()) {
			if (itr != container.begin()) {
				std::cout << ", ";
			}
			std::cout << *itr;
			++itr;
		}
		std::cout << "}" << std::endl;
	}

	// -------------------------------------------------------------------------
	// subject
	// -------------------------------------------------------------------------
	void RunSubjectTest1() {
		DisplayTitle(1, "subject test (push,top,pop,size,begin,end)");

		MutantStack<int> mstack;
		mstack.push(5);                          // {5}
		mstack.push(17);                         // {5, 17}
		std::cout << mstack.top() << std::endl;  // {5, 17} <- top
		mstack.pop();                            // {5}
		std::cout << mstack.size() << std::endl; // {5}
		mstack.push(3);                          // {5, 3}
		mstack.push(5);                          // {5, 3, 5}
		mstack.push(737);                        // {5, 3, 5, 737}
		mstack.push(0);                          // {5, 3, 5, 737, 0}
		Line();

		// iterator
		MutantStack<int>::iterator it  = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			std::cout << *it << std::endl;
			++it;
		}
		Line();

		// const_iterator
		MutantStack<int>::const_iterator it2  = mstack.begin();
		MutantStack<int>::const_iterator ite2 = mstack.end();
		++it2;
		--it2;
		while (it2 != ite2) {
			std::cout << *it2 << " ";
			++it2;
		}
		std::cout << std::endl;
		std::stack<int> s(mstack);
	}

	void RunSubjectTest2() {
		DisplayTitle(2, "subject test / MutantStack -> std::list");

		std::list<int> mstack;
		mstack.push_back(5);                     // {5}
		mstack.push_back(17);                    // {5, 17}
		std::cout << mstack.back() << std::endl; // {5, 17} <- back
		mstack.pop_back();                       // {5}
		std::cout << mstack.size() << std::endl; // {5}
		mstack.push_back(3);                     // {5, 3}
		mstack.push_back(5);                     // {5, 3, 5}
		mstack.push_back(737);                   // {5, 3, 5, 737}
		mstack.push_back(0);                     // {5, 3, 5, 737, 0}
		Line();

		std::list<int>::iterator it  = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			// std::cout << *it << std::endl;
			++it;
		}
		PrintItr("list", mstack);
	}

	void RunSubjectTest3() {
		DisplayTitle(3, "subject test / MutantStack -> std::deque");

		std::deque<int> mstack;
		mstack.push_back(5);                     // {5}
		mstack.push_back(17);                    // {5, 17}
		std::cout << mstack.back() << std::endl; // {5, 17} <- back
		mstack.pop_back();                       // {5}
		std::cout << mstack.size() << std::endl; // {5}
		mstack.push_back(3);                     // {5, 3}
		mstack.push_back(5);                     // {5, 3, 5}
		mstack.push_back(737);                   // {5, 3, 5, 737}
		mstack.push_back(0);                     // {5, 3, 5, 737, 0}
		Line();

		std::deque<int>::iterator it  = mstack.begin();
		std::deque<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			// std::cout << *it << std::endl;
			++it;
		}
		PrintItr("deque", mstack);
	}

	void RunSubjectTest4() {
		DisplayTitle(4, "subject test / MutantStack -> std::vector");

		std::vector<int> mstack;
		mstack.push_back(5);                     // {5}
		mstack.push_back(17);                    // {5, 17}
		std::cout << mstack.back() << std::endl; // {5, 17} <- back
		mstack.pop_back();                       // {5}
		std::cout << mstack.size() << std::endl; // {5}
		mstack.push_back(3);                     // {5, 3}
		mstack.push_back(5);                     // {5, 3, 5}
		mstack.push_back(737);                   // {5, 3, 5, 737}
		mstack.push_back(0);                     // {5, 3, 5, 737, 0}
		Line();

		std::vector<int>::iterator it  = mstack.begin();
		std::vector<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite) {
			// std::cout << *it << std::endl;
			++it;
		}
		PrintItr("vector", mstack);
	}

	void RunSubjectTest5() {
		DisplayTitle(5, "subject test / MutantStack -> std::queue");

		std::queue<int> mstack;
		mstack.push(5);                          // {5}
		mstack.push(17);                         // {5, 17}
		std::cout << mstack.back() << std::endl; // {5, 17} <- back
		mstack.pop();                            // {17}
		std::cout << mstack.size() << std::endl; // {17}
		mstack.push(3);                          // {17, 3}
		mstack.push(5);                          // {17, 3, 5}
		mstack.push(737);                        // {17, 3, 5, 737}
		mstack.push(0);                          // {17, 3, 5, 737, 0}
		Line();

		PrintQueue(mstack);
	}

	// -------------------------------------------------------------------------
	// original
	// -------------------------------------------------------------------------
	void RunOriginalTest1() {
		DisplayTitle(6, "MutantStack<int> -> MutantStack<int> / copy constructor");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();

		MutantStack<int> tmp(mstack); // copy
		tmp.DebugPrint();

		JudgeIsSameStack(mstack, tmp);
	}

	void RunOriginalTest2() {
		DisplayTitle(7, "MutantStack<int> -> std::stack<int> / copy constructor");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();

		std::stack<int> tmp(mstack); // copy

		JudgeIsSameStack(mstack, tmp);
	}

	void RunOriginalTest3() {
		DisplayTitle(8, "MutantStack<int> -> MutantStack<int> / operator=");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();

		MutantStack<int> tmp = mstack; // copy
		tmp.DebugPrint();

		JudgeIsSameStack(mstack, tmp);
	}

	void RunOriginalTest4() {
		DisplayTitle(9, "MutantStack<int> -> std::stack<int> / operator=");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();

		std::stack<int> tmp = mstack; // copy

		JudgeIsSameStack(mstack, tmp);
	}

	void RunOriginalTest5() {
		DisplayTitle(
			10, "MutantStack<int> -> MutantStack<int> / update value from itr"
		);

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();
		Line();

		MutantStack<int> tmp(mstack); // copy
		PrintStack(tmp);              // before
		Line();

		MutantStack<int>::iterator itr = mstack.begin();
		while (itr != mstack.end()) {
			*itr = 123; // update value
			++itr;
		}
		mstack.DebugPrint(); // updated
		Line();
		PrintStack(tmp); // after. not change
	}

	void RunOriginalTest6() {
		DisplayTitle(11, "MutantStack<int> / size = 0, pop ");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();
		Line();

		for (int i = 0; i < 10; i++) {
			mstack.pop();
		}
		mstack.DebugPrint();

		// pop() with size = 0 is undefined
		// (linux:nothing happened, macOS:Segmentation fault)
		if (mstack.size()) {
			mstack.pop();
		}
	}

	void RunOriginalTest7() {
		DisplayTitle(12, "MutantStack<string> / copy");

		MutantStack<std::string> mstack;
		mstack.push("abcdefghijklmn");
		mstack.push("");
		mstack.push("1234");
		mstack.DebugPrint();
		Line();

		MutantStack<std::string> tmp(mstack); // copy
		tmp.DebugPrint();
		JudgeIsSameStack(mstack, tmp);
		Line();

		MutantStack<std::string> tmp2 = mstack; // copy
		tmp2.DebugPrint();
		JudgeIsSameStack(mstack, tmp2);
	}

	void RunOriginalTest8() {
		DisplayTitle(13, "MutantStack<int> / rbegin,rend ");

		MutantStack<int> mstack;
		for (int i = 0; i < 10; i++) {
			mstack.push(i);
		}
		mstack.DebugPrint();
		Line();

		// reverse_iterator
		MutantStack<int>::reverse_iterator rbegin = mstack.rbegin();
		MutantStack<int>::reverse_iterator rend   = mstack.rend();
		while (rbegin != rend) {
			std::cout << *rbegin << " ";
			*rbegin += 10; // OK
			++rbegin;
		}
		std::cout << std::endl;

		// const_reverse_iterator
		MutantStack<int>::const_reverse_iterator rbegin2 = mstack.rbegin();
		MutantStack<int>::const_reverse_iterator rend2   = mstack.rend();
		while (rbegin2 != rend2) {
			std::cout << *rbegin2 << " ";
			// *rbegin += 10; // NG
			++rbegin2;
		}
		std::cout << std::endl;
	}

	// -------------------------------------------------------------------------

} // namespace test

int main() {
	test::RunSubjectTest1();
	test::RunSubjectTest2();
	test::RunSubjectTest3();
	test::RunSubjectTest4();
	test::RunSubjectTest5();

	test::RunOriginalTest1();
	test::RunOriginalTest2();
	test::RunOriginalTest3();
	test::RunOriginalTest4();
	test::RunOriginalTest5();
	test::RunOriginalTest6();
	test::RunOriginalTest7();
	test::RunOriginalTest8();
	return EXIT_SUCCESS;
}
