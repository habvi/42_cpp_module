#include "file.hpp"
#include "error.hpp"
#include <cstdlib>
#include <string>

File::File() {}

File::File(const std::string &in_filename, const std::string &out_filename) {
	OpenFiles(in_filename, out_filename);
}

File::~File() {}

bool File::ReadInfileToBuf(std::string &buf) {
	std::string line;

	while (!IsInfileEof()) {
		std::getline(in_file_, line);
		if (IsInfileError()) {
			return false;
		}
		if (!IsInfileEof()) {
			line += "\n";
		}
		buf += line;
	}
	return true;
}

void File::WriteToOutfile(const std::string &line) {
	out_file_ << line;
}

bool File::IsInfileEof() const {
	return in_file_.eof();
}

bool File::IsInfileError() const {
	return in_file_.bad();
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
