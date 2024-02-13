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

void FileReplace::CreateReplacedFile() const {
	static const std::string replaced_extension = ".replace";
	const std::string        new_filename       = filename_ + replaced_extension;
	File                     file(filename_, new_filename);

	WriteReplacedToNewfile(file);
}

void FileReplace::WriteReplacedToNewfile(File &file) const {
	std::string line;

	while (!file.IsInfileEof()) {
		file.ReadInfile(line);
		if (!file.IsInfileEof()) {
			line += "\n";
		}
		WriteEachLine(line, file);
	}
	if (file.IsInfileError()) {
		PutError(ERR_GETLINE);
		exit(EXIT_FAILURE);
	}
}

void FileReplace::WriteEachLine(const std::string &line, File &file) const {
	std::string::size_type head       = 0;
	std::string::size_type pos        = 0;
	const size_t           src_length = src_.length();

	while ((pos = line.find(src_, head)) != std::string::npos) {
		file.WriteOutfile(line.substr(head, pos - head));
		file.WriteOutfile(replaced_);
		pos += src_length;
		head = pos;
	}
	file.WriteOutfile(line.substr(head));
}
