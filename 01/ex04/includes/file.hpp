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
	bool ReadInfileToBuf(std::string &buf);
	void WriteOutfile(const std::string &line);

  private:
	bool IsInfileEof() const;
	bool IsInfileError() const;
	void OpenFiles(const std::string &in_filename, const std::string &out_filename);

  private:
	File();

  private:
	std::ifstream in_file_;
	std::ofstream out_file_;
};

#endif /* FILE_H */
