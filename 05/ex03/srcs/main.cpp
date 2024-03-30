#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "color.hpp"
#include "form_list.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#define ALICE "Alice"
#define BOB   "Bob"

static void
DisplayTitle(const unsigned int testcase_number, const std::string &title) {
	std::cout << "\n\n┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	std::cout << "┃ test " << testcase_number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "------------------------" << std::endl;
}

static bool IsEqualNameAndGrade(
	const Bureaucrat  &target,
	const std::string &expected_name,
	const unsigned int expected_grade
) {
	return target.getName() == expected_name && target.getGrade() == expected_grade;
}

static void JudgeResult(
	const Bureaucrat  &target,
	const std::string &expected_name,
	const unsigned int expected_grade
) {
	if (IsEqualNameAndGrade(target, expected_name, expected_grade)) {
		std::cout << COLOR_GREEN "[OK]" << COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "[NG]" << COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
}

// IncrementGrade() or DecrementGrade()
static void ExecGradeTest(Bureaucrat &target, void (Bureaucrat::*func)()) {
	try {
		(target.*func)();
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

/* === Expect ===
[OK]
[OK]
Error: grade is too high
[OK]
*/
static void RunTest1() {
	DisplayTitle(1, "Bureaucrat IncrementGrade(), throw exception / too high");

	static const unsigned int kGrade = 2;

	Bureaucrat alice(ALICE, kGrade);
	JudgeResult(alice, ALICE, kGrade); // [OK]

	ExecGradeTest(alice, &Bureaucrat::IncrementGrade);
	JudgeResult(alice, ALICE, kGrade - 1); // [OK]

	ExecGradeTest(alice, &Bureaucrat::IncrementGrade); // catch exception
	JudgeResult(alice, ALICE, kGrade - 1);             // [OK] nothing changed
}

/* === Expect ===
[OK]
[OK]
Error: grade is too low
[OK]
*/
static void RunTest2() {
	DisplayTitle(2, "Bureaucrat DecrementGrade(), throw exception / too low");

	static const unsigned int kGrade = 149;

	Bureaucrat bob = Bureaucrat(BOB, kGrade);
	JudgeResult(bob, BOB, kGrade); // [OK]

	ExecGradeTest(bob, &Bureaucrat::DecrementGrade);
	JudgeResult(bob, BOB, kGrade + 1); // [OK]

	ExecGradeTest(bob, &Bureaucrat::DecrementGrade); // catch exception
	JudgeResult(bob, BOB, kGrade + 1);               // [OK] nothing changed
}

/* === Expect ===
[OK]
[OK]
[OK]
[OK]
[OK]
*/
static void RunTest3() {
	DisplayTitle(3, "Bureaucrat copy test");

	static const unsigned int kGrade = 123;

	Bureaucrat alice = Bureaucrat(ALICE, kGrade); // copy
	JudgeResult(alice, ALICE, kGrade);            // [OK]

	Bureaucrat alice2(alice);           // copy
	JudgeResult(alice2, ALICE, kGrade); // [OK]

	Bureaucrat alice3 = alice;          // copy
	JudgeResult(alice3, ALICE, kGrade); // [OK]

	Bureaucrat bob(BOB, kGrade - 10);
	JudgeResult(bob, BOB, kGrade - 10); // [OK]
	bob = alice;                        // copy
	JudgeResult(bob, BOB, kGrade);      // [OK] bob not changed (const name)
}

/* === Expect ===
Error: grade is too high
*/
static void RunTest4() {
	DisplayTitle(4, "Bureaucrat constructor: throw exception / grade too high");

	try {
		Bureaucrat bob = Bureaucrat(BOB, 0);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

/* === Expect ===
Error: grade is too low
*/
static void RunTest5() {
	DisplayTitle(5, "Bureaucrat constructor: throw exception / grade too low");

	try {
		Bureaucrat bob = Bureaucrat(BOB, 151);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

/* === Expect ===
Alice, bureaucrat grade 123.
[OK]
Alice, bureaucrat grade 122.
[OK]
Alice, bureaucrat grade 121.
[OK]
Alice, bureaucrat grade 120.
[OK]
Alice, bureaucrat grade 121.
[OK]
*/
static void RunTest6() {
	DisplayTitle(6, "Bureaucrat operator<< overload");

	static const unsigned int kGrade = 123;

	Bureaucrat alice(ALICE, kGrade);
	std::cout << alice << std::endl;   // operator<<
	JudgeResult(alice, ALICE, kGrade); // [OK]

	// increment 3 times
	for (unsigned int i = 0; i < 3; i++) {
		ExecGradeTest(alice, &Bureaucrat::IncrementGrade);
		std::cout << alice << std::endl;           // operator<<
		JudgeResult(alice, ALICE, kGrade - i - 1); // [OK]
	}

	// decrement
	ExecGradeTest(alice, &Bureaucrat::DecrementGrade);
	std::cout << alice << std::endl;           // operator<<
	JudgeResult(alice, ALICE, kGrade - 3 + 1); // [OK]
}

// -----------------------------------------------------------------------------

// static bool IsEqualNameAndGrade(const AForm &target, const AForm &expected) {
// 	return target.GetName() == expected.GetName() &&
// 		   target.GetIsSigned() == expected.GetIsSigned() &&
// 		   target.GetGradeForSign() == expected.GetGradeForSign() &&
// 		   target.GetGradeForExecute() == expected.GetGradeForExecute();
// }

// static void JudgeResult(const AForm &target, const AForm &expected) {
// 	if (IsEqualNameAndGrade(target, expected)) {
// 		std::cout << COLOR_GREEN "[OK]" << COLOR_END << std::endl;
// 	} else {
// 		std::cout << COLOR_RED "[NG]" << COLOR_END << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// }

// -----------------------------------------------------------------------------

/* === Expect ===
Error: Grade is too high
Error: Grade is too high
Error: Grade is too high
*/
// static void RunTest7() {
// 	DisplayTitle(7, "AForm constructor: throw exception / grade too high");

// 	{
// 		AForm alice = AForm(ALICE, 150, 1); // normal, normal
// 	}

// 	try {
// 		AForm alice = AForm(ALICE, 0, 123); // too high, normal
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}
// 	try {
// 		AForm alice = AForm(ALICE, 123, 0); // normal, too high
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}
// 	try {
// 		AForm alice = AForm(ALICE, 0, 0); // too high, too high
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}
// }

/* === Expect ===
Error: grade is too low
Error: grade is too low
Error: grade is too low
*/
// static void RunTest8() {
// 	DisplayTitle(8, "AForm constructor: throw exception / grade too low");

// 	{
// 		AForm bob = AForm(BOB, 1, 150); // normal, normal
// 	}

// 	try {
// 		AForm bob = AForm(BOB, 151, 1); // too low, normal
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}
// 	try {
// 		AForm bob = AForm(BOB, 1, 151); // normal, too low
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}

// 	try {
// 		AForm bob = AForm(BOB, 151, 12345); // too low, too low
// 	} catch (const std::exception &e) {
// 		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
// 	}
// }

/* === Expect ===
[OK]
[OK]
*/
// static void RunTest9() {
// 	DisplayTitle(9, "AForm copy test");

// 	static const unsigned int kGradeForSign    = 5;   // normal
// 	static const unsigned int kGradeForExecute = 123; // normal

// 	AForm alice = AForm(ALICE, kGradeForSign, kGradeForExecute);

// 	AForm alice2(alice);
// 	JudgeResult(alice2, alice); // [OK]

// 	AForm alice3 = alice;
// 	JudgeResult(alice3, alice); // [OK]
// }

/* === Expect ===
AForm Alice(not signed), grade for sign is 5, grade for execute is 123
*/
// static void RunTest10() {
// 	DisplayTitle(10, "AForm operator<< overload");

// 	AForm alice = AForm(ALICE, 5, 123);
// 	std::cout << alice << std::endl;
// }

static void ExecSignFormTest(Bureaucrat &b, AForm &form) {
	try {
		b.signForm(form);
	} catch (const std::exception &e) {
	}
}

/* === Expect ===
Alice, bureaucrat grade 5.
Form: F1(not signed), grade for sign is 4, grade for execute is 50
Alice couldn't sign F1 because Error: Grade is too low
Form: F1(not signed), grade for sign is 4, grade for execute is 50
Alice, bureaucrat grade 4.
Alice signed F1
Form: F1(signed), grade for sign is 4, grade for execute is 50
*/
static void RunTest11() {
	DisplayTitle(11, "Bureaucrat try to sign the Form");

	Bureaucrat alice(ALICE, 26); // grade 26 is too low for sign
	std::cout << alice << std::endl;

	// AForm form("F1", 4, 50);
	AForm *form = new PresidentialPardonForm("Pre_" ALICE); // sign need grade 25
	std::cout << *form << std::endl;

	ExecSignFormTest(alice, *form); // sign failed
	std::cout << *form << std::endl;

	alice.IncrementGrade(); // alice grade++ -> grade 25
	std::cout << alice << std::endl;

	ExecSignFormTest(alice, *form); // sign success
	std::cout << *form << std::endl;

	delete form;
}

// -----------------------------------------------------------------------------

static void ExecuteAFormWithNoSign(AForm *form) {
	Bureaucrat bob(BOB, 1);
	try {
		form->execute(bob);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

static void ExecuteAFormWithSign(AForm *form, const unsigned int executor_grade) {
	Bureaucrat bob(BOB, executor_grade);

	// add sign
	form->beSigned(bob);
	try {
		form->execute(bob);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

// -----------------------------------------------------------------------------

/* === Expect ===
AForm: Presidential Pardon(not signed), grade for sign is 25, grade for execute is 5
--------------------------------
Error: not signed
--------------------------------
executor(Bob): target(Pre_Alice) has been pardoned by Zaphod Beeblebrox.
Error: Grade is too low
*/
static void RunTest12() {
	DisplayTitle(12, "PresidentialPardonForm class's execute()");

	PresidentialPardonForm p_form("Pre_" ALICE); // 25, 5
	std::cout << p_form << std::endl;            // AForm's operator<<

	Line();
	ExecuteAFormWithNoSign(&p_form); // no sign
	Line();
	ExecuteAFormWithSign(&p_form, 4); // as AForm*, able to execute
	ExecuteAFormWithSign(&p_form, 6); // as AForm*, unable to execute
}

/* === Expect ===
AForm: Robotomy Request(not signed), grade for sign is 72, grade for execute is 45
------------------------
Error: not signed
------------------------ // (change by current time's second.)
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Alice) has been robotomized successfully.
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Alice) Failed to robotomized.
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Alice) has been robotomized successfully.
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Alice) Failed to robotomized.
------------------------
Error: Grade is too low
*/
static void RunTest13() {
	DisplayTitle(13, "RobotomyRequestForm class's execute()");

	RobotomyRequestForm r_form("Robo_" ALICE); // 72, 45
	std::cout << r_form << std::endl;          // AForm's operator<<

	Line();
	ExecuteAFormWithNoSign(&r_form); // no sign
	Line();
	// execute 4 times for 50% success
	ExecuteAFormWithSign(&r_form, 44); // as AForm*, able to execute
	ExecuteAFormWithSign(&r_form, 44); // as AForm*, able to execute
	ExecuteAFormWithSign(&r_form, 44); // as AForm*, able to execute
	ExecuteAFormWithSign(&r_form, 44); // as AForm*, able to execute
	Line();
	ExecuteAFormWithSign(&r_form, 46); // as AForm*, unable to execute
}

/* === Expect ===
AForm: Shrubbery Creation(not signed), grade for sign is 145, grade for execute is
137
--------------------------------
Error: not signed
--------------------------------
executor(Bob): target(Shru_Alice) write tree to file. => Success
Error: Grade is too low
*/
static void RunTest14() {
	DisplayTitle(14, "ShrubberyCreationForm class's execute()");

	ShrubberyCreationForm s_form("Shru_" ALICE); // 145, 137
	std::cout << s_form << std::endl;            // AForm's operator<<

	Line();
	ExecuteAFormWithNoSign(&s_form); // no sign
	Line();
	ExecuteAFormWithSign(&s_form, 136); // as AForm*, able to execute
	ExecuteAFormWithSign(&s_form, 138); // as AForm*, unable to execute
}

// -----------------------------------------------------------------------------

static void ExecuteFormByBureaucratWithNoSign(
	const std::string &name, const unsigned int grade, AForm &form
) {
	const Bureaucrat bob(name, grade);

	// no sign
	bob.executeForm(form);
}

static void ExecuteFormByBureaucratWithSign(
	const std::string &name, const unsigned int grade, AForm &form
) {
	const Bureaucrat bob(name, grade);

	// add sign
	form.beSigned(bob);
	bob.executeForm(form);
}

// -----------------------------------------------------------------------------

/* === Expect ===
Bob failed to execute => Error: not signed
------------------------
executor(Bob): target(Pre_Alice) has been pardoned by Zaphod Beeblebrox.
Bob execute Presidential Pardon
*/
static void RunTest15() {
	DisplayTitle(15, "Bureaucrat executeForm() by PresidentialPardon");

	PresidentialPardonForm form("Pre_" ALICE); // 25, 5

	// no sign
	ExecuteFormByBureaucratWithNoSign(BOB, 1, form);
	Line();
	// with sign
	ExecuteFormByBureaucratWithSign(BOB, 1, form); // 1 : sign OK, execute OK
}

/* === Expect ===
Bob failed to execute => Error: not signed
------------------------
Bob failed to execute => Error: Grade is too low
*/
static void RunTest16() {
	DisplayTitle(16, "Bureaucrat executeForm() by Robotomy less grade");

	RobotomyRequestForm form("Robo_" ALICE); // 72, 45

	// no sign
	ExecuteFormByBureaucratWithNoSign(BOB, 70, form);
	Line();
	// with sign
	ExecuteFormByBureaucratWithSign(BOB, 70, form); // 70 : sign OK, execute NG
}

/* === Expect ===
executor(Bob): target(Shru_Alice) write tree to file. => Success
Bob execute Shrubbery Creation
*/
static void RunTest17() {
	DisplayTitle(17, "Bureaucrat executeForm() by Shrubbery");

	ShrubberyCreationForm form("Shru_" ALICE); // 145, 137

	// with sign
	ExecuteFormByBureaucratWithSign(BOB, 1, form); // 1 : sign OK, execute OK
}

/* === Expect ===
Intern creats robotomy request
AForm: Robotomy Request(not signed), grade for sign is 72, grade for execute is 45
*/
static void RunTest18() {
	DisplayTitle(18, "Intern / subject test");

	Intern someRandomIntern;
	AForm *rrf;

	rrf = someRandomIntern.makeForm(kRobotomyRequestFormName, "Bender");
	if (rrf == NULL) {
		return;
	}
	std::cout << *rrf << std::endl;

	delete rrf;
}

/* === Expect ===
Intern creats presidential pardon
------------------------
AForm: Presidential Pardon(not signed), grade for sign is 25, grade for execute is 5
------------------------
executor(Bob): target(Pre_Bender) has been pardoned by Zaphod Beeblebrox.
Bob execute Presidential Pardon
*/
static void RunTest19() {
	DisplayTitle(19, "Intern / executeForm() PresidentialPardon");

	Intern someRandomIntern;
	AForm *rrf;

	rrf = someRandomIntern.makeForm(kPresidentialPardonFormName, "Pre_Bender");
	if (rrf == NULL) {
		return;
	}
	Line();
	std::cout << *rrf << std::endl;

	Line();
	ExecuteFormByBureaucratWithSign(BOB, 1, *rrf);

	delete rrf;
}

/* === Expect ===
Intern creats robotomy request
------------------------
AForm: Robotomy Request(not signed), grade for sign is 72, grade for execute is 45
------------------------
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Bender) Failed to robotomized.
Drrrrrrrrrrrrrrr....
executor(Bob): target(Robo_Bender) has been robotomized successfully.
*/
static void RunTest20() {
	DisplayTitle(20, "Intern / executeForm() RobotomyRequest");

	Intern someRandomIntern;
	AForm *rrf;

	rrf = someRandomIntern.makeForm(kRobotomyRequestFormName, "Robo_Bender");
	if (rrf == NULL) {
		return;
	}
	Line();
	std::cout << *rrf << std::endl;

	Line();
	ExecuteAFormWithSign(rrf, 1);
	ExecuteAFormWithSign(rrf, 1);

	delete rrf;
}

/* === Expect ===
Intern creats shrubbery creation
------------------------
AForm: Shrubbery Creation(not signed), grade for sign is 145, grade for execute is
137
------------------------
executor(Bob): target(Shru_Bender) write tree to file. => Success
Bob execute Shrubbery Creation
*/
static void RunTest21() {
	DisplayTitle(21, "Intern / executeForm() ShrubberyCreation");

	Intern someRandomIntern;
	AForm *rrf;

	rrf = someRandomIntern.makeForm(kShrubberyCreationFormName, "Shru_Bender");
	if (rrf == NULL) {
		return;
	}
	Line();
	std::cout << *rrf << std::endl;

	Line();
	ExecuteFormByBureaucratWithSign(BOB, 1, *rrf);

	delete rrf;
}

/* === Expect ===
Intern creats Form failed. => Error: invalid Form name
*/
static void RunTest22() {
	DisplayTitle(22, "Intern / non exist form name");

	Intern someRandomIntern;
	AForm *rrf;

	rrf = someRandomIntern.makeForm("non exist form", "Bender");
	if (rrf == NULL) {
		return;
	}
}

static void RunOriginalTest() {
	/* ex00 */
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();
	RunTest6();

	/* ex01 */
	// instance AForm test off
	// RunTest7();
	// RunTest8();
	// RunTest9();
	// RunTest10();
	RunTest11();

	/* ex02 */
	RunTest12();
	RunTest13();
	RunTest14();
	RunTest15();
	RunTest16();
	RunTest17();

	/* ex03 */
	RunTest18();
	RunTest19();
	RunTest20();
	RunTest21();
	RunTest22();
}

int main() {
	// for RobotomyRequestForm's rand()
	std::srand(std::time(NULL));
	RunOriginalTest();
	return EXIT_SUCCESS;
}
