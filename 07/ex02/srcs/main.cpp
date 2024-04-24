#include "Array.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

namespace test {
	void DisplayTitle(const unsigned int testcase_number, const std::string &title) {
		std::cout << "\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
		std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	}

	void Line() {
		std::cout << "-----------------------------" << std::endl;
	}

	template <typename T>
	void PrintArray(const std::string &title, const T &array) {
		std::cout << title << " = {";
		const unsigned int size = array.size();
		for (size_t i = 0; i < size; i++) {
			std::cout << array[i];
			if (i != size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "}" << std::endl;
	}

	template <typename T>
	void
	PrintArray(const std::string &title, const T &array, const unsigned int size) {
		std::cout << title << " = {";
		for (size_t i = 0; i < size; i++) {
			std::cout << array[i];
			if (i != size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "}" << std::endl;
	}

	// --------------------------------------------------------------------
	template <typename T>
	void JudgeIsSameArray(const Array<T> &a, const Array<T> &b) {
		if (a.size() != b.size()) {
			std::cerr << COLOR_RED "Error: Not the same array" COLOR_END
					  << std::endl;
			exit(EXIT_FAILURE);
		}
		for (unsigned int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) {
				std::cerr << COLOR_RED "Error: Not the same array" COLOR_END
						  << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		std::cout << COLOR_GREEN "Same array!" COLOR_END << std::endl;
		Line();
	}

	template <typename T>
	void JudgeIsSameArray(const Array<T> &a, const T *b, const unsigned int b_size) {
		if (a.size() != b_size) {
			std::cerr << COLOR_RED "Error: Not the same array" COLOR_END
					  << std::endl;
			exit(EXIT_FAILURE);
		}
		for (unsigned int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) {
				std::cerr << COLOR_RED "Error: Not the same array" COLOR_END
						  << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		std::cout << COLOR_GREEN "Same array!" COLOR_END << std::endl;
		Line();
	}

	// --------------------------------------------------------------------
	void RunSubjectTest() {
		DisplayTitle(1, "int Array");

		const unsigned int kArraySize = 5;

		Array<int> numbers(kArraySize);
		int       *mirror = new int[kArraySize];
		for (unsigned int i = 0; i < kArraySize; i++) {
			const int value = rand() % 100;
			numbers[i]      = value;
			mirror[i]       = value;
		}
		PrintArray("numbers", numbers);
		PrintArray("mirror ", mirror, kArraySize);
		JudgeIsSameArray(numbers, mirror, kArraySize);

		// copy
		{
			Array<int> tmp = numbers;
			PrintArray("numbers", numbers);
			PrintArray("tmp    ", tmp);
			JudgeIsSameArray(tmp, numbers);

			Array<int> test(tmp);
			PrintArray("tmp ", tmp);
			PrintArray("test", test);
			JudgeIsSameArray(test, tmp);
		}

		// error1
		try {
			numbers[-2] = 0;
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
		}
		Line();

		// error2
		try {
			numbers[kArraySize] = 0;
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
		}

		delete[] mirror;
	}

	// --------------------------------------------------------------------
	void RunOriginalTest1() {
		DisplayTitle(2, "string Array");

		const unsigned int kArraySize = 7;

		Array<std::string> strs(kArraySize);
		std::string       *mirror = new std::string[kArraySize];
		for (unsigned int i = 0; i < kArraySize; i++) {
			const std::string &s = "a";
			strs[i]              = s;
			strs[i].push_back('a' + i);
			mirror[i] = s;
			mirror[i].push_back('a' + i);
		}
		PrintArray("strs  ", strs);
		PrintArray("mirror", mirror, kArraySize);
		JudgeIsSameArray(strs, mirror, kArraySize);
		delete[] mirror;

		// copy
		Array<std::string> tmp1 = strs;
		PrintArray("strs", strs);
		PrintArray("tmp1", tmp1);
		JudgeIsSameArray(strs, tmp1);

		Array<std::string> tmp2(tmp1);
		PrintArray("tmp1", tmp1);
		PrintArray("tmp2", tmp2);
		JudgeIsSameArray(tmp1, tmp2);

		// error
		try {
			strs[1000] = "errrrr";
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
		}
	}

	void RunOriginalTest2() {
		DisplayTitle(3, "empty Array");

		const unsigned int kArraySize = 0;

		Array<double> arr;
		double       *mirror = new double[kArraySize];
		PrintArray("arr   ", arr);
		PrintArray("mirror", mirror, kArraySize);
		JudgeIsSameArray(arr, mirror, kArraySize);
		delete[] mirror;

		// copy
		Array<double> tmp1 = arr;
		PrintArray("arr ", arr);
		PrintArray("tmp1", tmp1);
		JudgeIsSameArray(arr, tmp1);

		Array<double> tmp2(tmp1);
		PrintArray("tmp1", tmp1);
		PrintArray("tmp2", tmp2);
		JudgeIsSameArray(tmp1, tmp2);

		// error
		for (int i = -2; i < 2; i++) {
			try {
				arr[i] = 123.456;
			} catch (const std::exception &e) {
				std::cerr << COLOR_RED << i << ": " << e.what() << COLOR_END
						  << std::endl;
			}
		}
	}

	// --------------------------------------------------------------------
	template <typename T>
	void JudgeIsSame2DArray(const Array<Array<T> > &a, const Array<Array<T> > &b) {
		if (a.size() != b.size()) {
			std::cerr << COLOR_RED "Error: Not the same array" COLOR_END
					  << std::endl;
			exit(EXIT_FAILURE);
		}
		for (unsigned int i = 0; i < a.size(); i++) {
			std::cout << "raw " << i << ": ";
			JudgeIsSameArray(a[i], b[i]);
		}
	}

	void Print2DArray(const std::string &title, const Array<Array<int> > &array2D) {
		std::cout << title << " = {" << std::endl;
		for (unsigned int i = 0; i < array2D.size(); ++i) {
			std::cout << "   ";
			for (unsigned int j = 0; j < array2D[i].size(); ++j) {
				std::cout << array2D[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "}" << std::endl;
	}

	void RunOriginalTest3() {
		DisplayTitle(4, "2D Array");

		const unsigned int kRowSize = 3;
		const unsigned int kColSize = 5;

		Array<Array<int> > array2D(kRowSize);
		for (unsigned int i = 0; i < kRowSize; i++) {
			array2D[i] = Array<int>(kColSize);
			for (unsigned int j = 0; j < kColSize; ++j) {
				array2D[i][j] = rand() % 100;
			}
		}
		Print2DArray("2D array", array2D);
		Line();

		// copy
		Array<Array<int> > tmp(array2D);
		Print2DArray("tmp", tmp);
		Line();

		JudgeIsSame2DArray(array2D, tmp);

		// error
		try {
			array2D[2][kColSize] = 5;
		} catch (const std::exception &e) {
			std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
		}
	}

} // namespace test

// --------------------------------------------------------------------
int main() {
	srand(time(NULL));

	test::RunSubjectTest();
	test::RunOriginalTest1();
	test::RunOriginalTest2();
	test::RunOriginalTest3();

	return EXIT_SUCCESS;
}
