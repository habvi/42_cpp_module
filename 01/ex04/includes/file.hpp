#ifndef FILE_H
#define FILE_H

#include <string>

#define REPLACED_EXTENSION ".replace"
#define ERR_OPEN           "fail to open file"
#define ERR_CREATE         "fail to create file"

class File {
  public:
	File();
	File(const std::string &filename, const std::string &s1, const std::string &s2);
	~File();

  public:
	bool create_replaced_file() const;

  private:
	bool open_file_(std::ifstream &in_file) const;
	bool
	create_file_(std::ofstream &out_file, const std::string &new_filename) const;
	bool
	write_replaced_s1_to_s2_(std::ifstream &in_file, std::ofstream &out_file) const;

  private:
	const std::string filename_;
	const std::string s1_;
	const std::string s2_;
};

#endif /* FILE_H */
