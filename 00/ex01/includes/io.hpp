#ifndef __IO_H__
#define __IO_H__

#include <string>

typedef enum e_result {
	SUCCESS,
	FAILURE,
	EOF,
} t_result;

t_result input_line(std::string &dst);
t_result
input_left_align(const std::string &title, std::string &dst, const int width);
t_result input_left_align(const std::string &title, int &dst, const int width);

void output_left_align(
	const std::string &title, const std::string &s, const int width
);

void put_error(const std::string &message);

#endif /*__IO_H__*/
