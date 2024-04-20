#include "ScalarConverter.hpp"
template void ScalarConverter::SetConvertToChar<char>(const char &);
template void ScalarConverter::SetConvertToChar<int>(const int &);
template void ScalarConverter::SetConvertToChar<float>(const float &);
template void ScalarConverter::SetConvertToChar<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToChar(const T &scalar) {
	oss_ << scalar << std::endl;
}

template void ScalarConverter::SetConvertToInteger<char>(const char &);
template void ScalarConverter::SetConvertToInteger<int>(const int &);
template void ScalarConverter::SetConvertToInteger<float>(const float &);
template void ScalarConverter::SetConvertToInteger<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToInteger(const T &scalar) {
	oss_ << scalar << std::endl;
}

template void ScalarConverter::SetConvertToFloat<char>(const char &);
template void ScalarConverter::SetConvertToFloat<int>(const int &);
template void ScalarConverter::SetConvertToFloat<float>(const float &);
template void ScalarConverter::SetConvertToFloat<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToFloat(const T &scalar) {
	oss_ << scalar << std::endl;
}

template void ScalarConverter::SetConvertToDouble<char>(const char &);
template void ScalarConverter::SetConvertToDouble<int>(const int &);
template void ScalarConverter::SetConvertToDouble<float>(const float &);
template void ScalarConverter::SetConvertToDouble<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToDouble(const T &scalar) {
	oss_ << scalar << std::endl;
}
