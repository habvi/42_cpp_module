#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

#define ERR_OPEN   "fail to open file"
#define ERR_CREATE "fail to create file"

class File {
  public:
	File(const std::string &in_filename, const std::string &out_filename);
	~File();

  public:
	std::ifstream &get_in_file();
	std::ofstream &get_out_file();

  private:
	void open_files(const std::string &in_filename, const std::string &out_filename);

  private:
	File();

  private:
	std::ifstream in_file_;
	std::ofstream out_file_;
};

#endif /* FILE_H */
