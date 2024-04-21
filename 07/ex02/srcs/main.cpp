#include "Array.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

static void Line() {
	std::cout << "-----------------------------" << std::endl;
}

template <typename T>
static void PrintArray(const std::string &title, const T &array) {
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
static void
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
static void JudgeIsSameArray(const Array<T> &a, const Array<T> &b) {
	if (a.size() != b.size()) {
		std::cerr << COLOR_RED "Error: Not the same array" COLOR_END << std::endl;
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
static void
JudgeIsSameArray(const Array<T> &a, const T *b, const unsigned int b_size) {
	if (a.size() != b_size) {
		std::cerr << COLOR_RED "Error: Not the same array" COLOR_END << std::endl;
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
static void RunSubjectTest() {
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
	Line();

	delete[] mirror;
}

// --------------------------------------------------------------------
int main() {
	srand(time(NULL));

	RunSubjectTest();
	// Line();
	// RunOriginalTest();
	return EXIT_SUCCESS;
}