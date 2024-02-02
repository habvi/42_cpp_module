#include "file.hpp"
#include "error.hpp"
#include <fstream>
#include <iostream>
#include <string>

// todo: need?
File::File() {}

File::File(const std::string &filename, const std::string &s1, const std::string &s2)
	: filename_(filename), s1_(s1), s2_(s2) {}

File::~File() {}

bool File::create_replaced_file() const {
	std::ifstream in_file;
	if (!open_file_(in_file)) {
		return false;
	}

	std::ofstream     out_file;
	const std::string new_filename = filename_ + REPLACED_EXTENSION;
	if (!create_file_(out_file, new_filename)) {
		in_file.close();
		return false;
	}

	write_replaced_s1_to_s2_(in_file, out_file);

	in_file.close();
	out_file.close();
	return true;
}

bool File::open_file_(std::ifstream &in_file) const {
	in_file.open(filename_.c_str());
	if (!in_file) {
		put_error(ERR_OPEN);
		return false;
	}
	return true;
}

bool File::create_file_(std::ofstream &out_file, const std::string &new_filename)
	const {
	out_file.open(new_filename.c_str());
	if (!out_file) {
		put_error(ERR_CREATE);
		return false;
	}
	return true;
}

// todo: replace s1 to s2 & handle error
bool File::write_replaced_s1_to_s2_(std::ifstream &in_file, std::ofstream &out_file)
	const {
	out_file << in_file.rdbuf();
	return true;
}
