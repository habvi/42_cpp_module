#include "file_replace.hpp"
#include "error.hpp"
#include "file.hpp"
#include <fstream>
#include <iostream>
#include <string>

FileReplace::FileReplace() {}

FileReplace::FileReplace(
	const std::string &filename, const std::string &s1, const std::string &s2
)
	: filename_(filename), s1_(s1), s2_(s2) {}

FileReplace::~FileReplace() {}

void FileReplace::create_replaced_file() const {
	static const std::string replaced_extension = ".replace";
	const std::string        new_filename       = filename_ + replaced_extension;

	File           file(filename_, new_filename);
	std::ifstream &in_file  = file.get_in_file();
	std::ofstream &out_file = file.get_out_file();

	write_replaced_s1_with_s2_(in_file, out_file);
}

void FileReplace::write_replaced_s1_with_s2_(
	std::ifstream &in_file, std::ofstream &out_file
) const {
	std::string line;

	while (std::getline(in_file, line)) {
		if (!in_file.eof()) {
			line += "\n";
		}
		write_each_line_(line, out_file);
	}
	// todo: getline error
}

void FileReplace::write_each_line_(const std::string &line, std::ofstream &out_file)
	const {
	std::string::size_type head      = 0;
	std::string::size_type pos       = 0;
	const size_t           s1_length = s1_.length();

	while ((pos = line.find(s1_, head)) != std::string::npos) {
		out_file << line.substr(head, pos - head);
		out_file << s2_;
		pos += s1_length;
		head = pos;
	}
	out_file << line.substr(head);
}
