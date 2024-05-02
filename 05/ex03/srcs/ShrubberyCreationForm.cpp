#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <fstream>
#include <iostream>

const std::string ShrubberyCreationForm::kFormName   = "Shrubbery Creation";
const std::string ShrubberyCreationForm::kFileSuffix = "_shrubbery";

ShrubberyCreationForm::ShrubberyCreationForm() {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm(kFormName, kGradeForSign, kGradeForExecute), target_(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &s)
	: AForm(s.GetName(), s.GetGradeForSign(), s.GetGradeForExecute()),
	  target_(s.GetTarget()) {}

ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &s) {
	if (this != &s) {
		AForm::operator=(s);
		target_ = s.GetTarget();
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

const std::string &ShrubberyCreationForm::GetTarget() const {
	return target_;
}

void ShrubberyCreationForm::WriteTreeToFile() const {
	const std::string filename = GetTarget() + kFileSuffix;
	std::ofstream     out_file(filename.c_str(), std::ios_base::out);

	if (out_file.is_open()) {
		out_file << "     *\n"
					"    ***\n"
					"   *****\n"
					"  *******\n"
					" *********\n"
					"***********\n"
					"    |||\n";
	} else {
		throw std::runtime_error("Error: open failed");
	}
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	AForm::execute(executor);
}

// override
void ShrubberyCreationForm::ExecuteEachForm(Bureaucrat const &executor) const {
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetTarget()
			  << COLOR_END ") write tree to file." COLOR_END;
	try {
		WriteTreeToFile();
		std::cout << COLOR_GREEN " => Success" COLOR_END << std::endl;
	} catch (const std::exception &e) {
		std::cout << COLOR_RED " => Fail" COLOR_END << std::endl;
		throw;
	}
}
