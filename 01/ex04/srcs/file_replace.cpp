#include "file_replace.hpp"
#include "error.hpp"
#include "file.hpp"
#include <string>

FileReplace::FileReplace() {}

FileReplace::FileReplace(
	const std::string &filename, const std::string &src, const std::string &replaced
)
	: filename_(filename), src_(src), replaced_(replaced) {}

FileReplace::~FileReplace() {}

bool FileReplace::CreateReplacedFile() const {
	static const std::string kReplacedExtension = ".replace";
	const std::string        new_filename       = filename_ + kReplacedExtension;
	File                     file(filename_, new_filename);

	std::string infile_content;
	const bool  result = file.ReadInfileToBuf(infile_content);
	if (!result) {
		return false;
	}

	WriteReplacedToNewfile(infile_content, file);
	return true;
}

void FileReplace::WriteReplacedToNewfile(const std::string &content, File &file)
	const {
	std::string::size_type head       = 0;
	std::string::size_type pos        = 0;
	const size_t           src_length = src_.length();

	while ((pos = content.find(src_, head)) != std::string::npos) {
		file.WriteOutfile(content.substr(head, pos - head));
		file.WriteOutfile(replaced_);
		pos += src_length;
		head = pos;
	}
	file.WriteOutfile(content.substr(head));
}
