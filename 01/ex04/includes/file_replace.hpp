#ifndef FILE_REPLACE_H
#define FILE_REPLACE_H

#include "file.hpp"
#include <string>

class FileReplace {
  public:
	FileReplace(
		const std::string &filename, const std::string &s1, const std::string &s2
	);
	~FileReplace();

  public:
	void create_replaced_file() const;

  private:
	void write_replaced_s1_with_s2_(File &file) const;
	void write_each_line_(const std::string &line, File &file) const;

  private:
	FileReplace();

  private:
	const std::string filename_;
	const std::string s1_;
	const std::string s2_;
};

#endif /* FILE_REPLACE_H */
