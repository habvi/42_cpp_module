#include "Data.hpp"
#include "Serializer.hpp"
#include "color.hpp"
#include <cstdint>
#include <iostream>

static void PutData(const Data *data) {
	std::cout << data << " / [" << data->str << "][" << data->var << "]"
			  << std::endl;
}

static void JudgeIsSame(const Data *data1, const Data *data2) {
	PutData(data1);
	PutData(data2);
	if (data1 == data2 && data1->var == data2->var) {
		std::cout << COLOR_GREEN "Same Data!" COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "Not the same Data..." COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "---------------------------" << std::endl;
}

int main() {
	// set data
	Data data;
	data.var = 42;

	Data *ptr_before = &data;

	// serialize
	std::uintptr_t ptr_tmp = Serializer::serialize(ptr_before);
	// deserialize
	Data *ptr_after = Serializer::deserialize(ptr_tmp);

	// compare before/after
	JudgeIsSame(ptr_before, ptr_after);

	ptr_before->var = -123;
	JudgeIsSame(ptr_before, ptr_after);
	ptr_after->var = 0;
	JudgeIsSame(ptr_before, ptr_after);

	// try pass NULL
	try {
		Serializer::serialize(NULL);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}

	return EXIT_SUCCESS;
}
