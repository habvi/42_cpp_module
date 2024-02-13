#include "file.hpp"
#include "error.hpp"
#include <cstdlib>
#include <string>

File::File() {}

File::File(const std::string &in_filename, const std::string &out_filename) {
	OpenFiles(in_filename, out_filename);
}

File::~File() {
	in_file_.close();
	out_file_.close();
}

// The user should check errors in getline()
void File::ReadInfile(std::string &line) {
	std::getline(in_file_, line);
}

bool File::IsInfileEof() const {
	return in_file_.eof();
}

bool File::IsInfileError() const {
	return in_file_.bad();
}

void File::WriteOutfile(const std::string &line) {
	out_file_ << line;
}

void File::OpenFiles(
	const std::string &in_filename, const std::string &out_filename
) {
	in_file_.open(in_filename.c_str());
	if (!in_file_) {
		PutError(ERR_OPEN);
		exit(EXIT_FAILURE);
	}

	out_file_.open(out_filename.c_str());
	if (!out_file_) {
		PutError(ERR_CREATE);
		exit(EXIT_FAILURE);
	}
}
