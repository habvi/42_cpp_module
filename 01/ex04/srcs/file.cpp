#include "file.hpp"
#include "error.hpp"
#include <cstdlib>
#include <string>

File::File() {}

File::File(const std::string &in_filename, const std::string &out_filename) {
	open_files(in_filename, out_filename);
}

File::~File() {
	in_file_.close();
	out_file_.close();
}

void File::read_in_file(std::string &line) {
	std::getline(in_file_, line);
}

bool File::is_in_file_eof() {
	return in_file_.eof();
}

void File::write_out_file(const std::string &line) {
	out_file_ << line;
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
