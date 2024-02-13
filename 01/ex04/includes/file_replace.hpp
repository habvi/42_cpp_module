#ifndef FILE_REPLACE_H
#define FILE_REPLACE_H

#include "file.hpp"
#include <string>

class FileReplace {
  public:
	FileReplace(
		const std::string &filename,
		const std::string &src,
		const std::string &replaced
	);
	~FileReplace();

  public:
	void CreateReplacedFile() const;

  private:
	void WriteReplacedToNewfile(File &file) const;
	void WriteEachLine(const std::string &line, File &file) const;

  private:
	FileReplace();

  private:
	const std::string filename_;
	const std::string src_;
	const std::string replaced_;
};

#endif /* FILE_REPLACE_H */
