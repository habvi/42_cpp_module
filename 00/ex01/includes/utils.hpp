#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

void input_left_align(const std::string &title, std::string &dst, const int width);
void input_left_align(const std::string &title, unsigned int &dst, const int width);

void output_left_align(
	const std::string &title, const std::string &s, const int width
);

#endif /*__UTILS_H__*/