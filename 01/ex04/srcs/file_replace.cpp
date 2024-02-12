#include "file_replace.hpp"
#include "error.hpp"
#include "file.hpp"
#include <cstdlib>
#include <string>

FileReplace::FileReplace() {}

FileReplace::FileReplace(
	const std::string &filename, const std::string &src, const std::string &replaced
)
	: filename_(filename), src_(src), replaced_(replaced) {}

FileReplace::~FileReplace() {}

void FileReplace::create_replaced_file() const {
	static const std::string replaced_extension = ".replace";
	const std::string        new_filename       = filename_ + replaced_extension;
	File                     file(filename_, new_filename);

	write_replaced_to_newfile(file);
}

void FileReplace::write_replaced_to_newfile(File &file) const {
	std::string line;

	while (!file.is_in_file_eof()) {
		file.read_in_file(line);
		if (!file.is_in_file_eof()) {
			line += "\n";
		}
		write_each_line_(line, file);
	}
	if (file.is_in_file_error()) {
		put_error(ERR_GETLINE);
		exit(EXIT_FAILURE);
	}
}

void FileReplace::write_each_line_(const std::string &line, File &file) const {
	std::string::size_type head       = 0;
	std::string::size_type pos        = 0;
	const size_t           src_length = src_.length();

	while ((pos = line.find(src_, head)) != std::string::npos) {
		file.write_out_file(line.substr(head, pos - head));
		file.write_out_file(replaced_);
		pos += src_length;
		head = pos;
	}
	file.write_out_file(line.substr(head));
}
