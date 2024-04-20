#include "ScalarConverter.hpp"
#include <cstdlib>
#include <iostream>

static void
DisplayTitle(const unsigned int testcase_number, const std::string &title) {
	std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void RunLikeSubject(const std::string &str) {
	ScalarConverter::convert(str);
}

static void RunTest(const std::string &str) {
	std::cout << "======== [" << str << "] ========" << std::endl;
	RunLikeSubject(str);
	std::cout << std::endl;
}

static void RunCharTest() {
	DisplayTitle(1, "Char");

	RunTest("'a'");
	RunTest("'5'");
	RunTest("' '");
	RunTest("'!'");
	RunTest("'\n'");
}

static void RunIntTest() {
	DisplayTitle(2, "Integer");

	RunTest("0");
	RunTest("42");
	RunTest("+42");
	RunTest("-42");
	RunTest("2147483647");
	RunTest("-2147483648");
}

static void RunFloatTest() {
	DisplayTitle(3, "Float");

	RunTest("5.0f");
	RunTest("42.000f");
	RunTest("42.003f");
	RunTest("-123f");
	RunTest("123.f");
	RunTest("123.456f");
	RunTest("2147483648f");
	RunTest("-2147483649f");
	RunTest("inff");
	RunTest("+inff");
	RunTest("INFF");
	RunTest("+INFF");
	RunTest("-inff");
	RunTest("-INFF");
	RunTest("nanf");
	RunTest("NANF");
	RunTest("NaNF");
}

static void RunDoubleTest() {
	DisplayTitle(4, "Double");

	RunTest("0.0");
	RunTest("42.000");
	RunTest("42.003");
	RunTest("123.");
	RunTest("123.45678");
	RunTest("2147483648");
	RunTest("-2147483649");
	RunTest("inf");
	RunTest("INF");
	RunTest("+inf");
	RunTest("+INF");
	RunTest("-inf");
	RunTest("-INF");
	RunTest("-iNF");
	RunTest("nan");
	RunTest("NAN");
}

static void RunErrorTest() {
	DisplayTitle(5, "All Impossible");

	RunTest("");
	RunTest("  ");
	RunTest("  12");
	RunTest("12   ");
	RunTest("  42.0000f");
	RunTest("42.0000f   ");
	RunTest("  42.0000");
	RunTest("42.0000   ");
	RunTest("   42.0000   ");
	RunTest("'ア'");
	RunTest("e+");
	RunTest("e+10");
	RunTest("12e+10");
	RunTest("12.e-10");
	RunTest("12e-10f");
	RunTest("0x123");
	RunTest("-0x123");
	RunTest("123f.");
	RunTest("123ff");
	RunTest("123fx");
	RunTest("123.fx");
	RunTest("123.ffx");
	RunTest("123..");
	RunTest("123..f");
	RunTest("123.f.f");
	RunTest(".");
	RunTest("f");
	RunTest(".f");
	RunTest("infff");
	RunTest("--inf");
	RunTest("nnan");
	RunTest("NANN");
}

static void RunOriginalTest() {
	RunCharTest();
	RunIntTest();
	RunFloatTest();
	RunDoubleTest();
	RunErrorTest();
}

int main(int argc, const char **argv) {
	if (argc == 1) {
		RunOriginalTest();
	} else if (argc == 2) {
		RunLikeSubject(std::string(argv[1]));
	} else {
		std::cerr << "Usage:\n"
				  << "  [subject] ./convert <argument>\n"
				  << "  [test]    ./convert" << std::endl;
	}
	return EXIT_SUCCESS;
}
