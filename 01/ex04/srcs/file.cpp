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

static bool open_file_(std::ifstream &in_file, const std::string &filename) {
	in_file.open(filename.c_str());
	if (!in_file) {
		put_error(ERR_OPEN);
		return false;
	}
	return true;
}

static bool create_file_(std::ofstream &out_file, const std::string &new_filename) {
	out_file.open(new_filename.c_str());
	if (!out_file) {
		put_error(ERR_CREATE);
		return false;
	}
	return true;
}

bool File::create_replaced_file() const {
	std::ifstream in_file;
	if (!open_file_(in_file, filename_)) {
		return false;
	}

	std::ofstream     out_file;
	const std::string new_filename = filename_ + REPLACED_EXTENSION;
	if (!create_file_(out_file, new_filename)) {
		in_file.close();
		return false;
	}

	const bool result = write_replaced_s1_to_s2_(in_file, out_file);
	in_file.close();
	out_file.close();
	return result;
}

// todo: replace s1 to s2 & handle error
bool File::write_replaced_s1_to_s2_(std::ifstream &in_file, std::ofstream &out_file)
	const {
	out_file << in_file.rdbuf();
	return true;
}
