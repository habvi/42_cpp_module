#include "file.hpp"
#include "error.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

File::File() {}

File::File(const std::string &in_filename, const std::string &out_filename) {
	open_files(in_filename, out_filename);
}

File::~File() {
	in_file_.close();
	out_file_.close();
}

std::ifstream &File::get_in_file() {
	return in_file_;
}

std::ofstream &File::get_out_file() {
	return out_file_;
}

void File::open_files(
	const std::string &in_filename, const std::string &out_filename
) {
	in_file_.open(in_filename.c_str());
	if (!in_file_) {
		put_error(ERR_OPEN);
		exit(EXIT_FAILURE);
	}

	out_file_.open(out_filename.c_str());
	if (!out_file_) {
		put_error(ERR_CREATE);
		exit(EXIT_FAILURE);
	}
}
