#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

#define ERR_OPEN    "fail to open file"
#define ERR_CREATE  "fail to create file"
#define ERR_GETLINE "fail to getline"

class File {
  public:
	File(const std::string &in_filename, const std::string &out_filename);
	~File();

  public:
	void read_in_file(std::string &line);
	bool is_in_file_eof() const;
	bool is_in_file_error() const;
	void write_out_file(const std::string &line);

  private:
	void open_files(const std::string &in_filename, const std::string &out_filename);

  private:
	File();

  private:
	std::ifstream in_file_;
	std::ofstream out_file_;
};

#endif /* FILE_H */
