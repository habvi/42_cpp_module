#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

#define ALICE "Alice"
#define BOB   "Bob"

static void DisplayTitle(const std::string &title) {
	static unsigned int testcase_number = 1;

	std::cout << "\n\n┃ test " << testcase_number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	testcase_number++;
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
	DisplayTitle("Bureaucrat IncrementGrade(), throw exception / too high");

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
	DisplayTitle("Bureaucrat DecrementGrade(), throw exception / too low");

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
	DisplayTitle("Bureaucrat copy test");

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
	DisplayTitle("Bureaucrat constructor: throw exception / grade too high");

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
	DisplayTitle("Bureaucrat constructor: throw exception / grade too low");

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
	DisplayTitle("Bureaucrat operator<< overload");

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

static bool IsEqualNameAndGrade(const Form &target, const Form &expected) {
	return target.GetName() == expected.GetName() &&
		   target.GetIsSigned() == expected.GetIsSigned() &&
		   target.GetGradeForSign() == expected.GetGradeForSign() &&
		   target.GetGradeForExecute() == expected.GetGradeForExecute();
}

static void JudgeResult(const Form &target, const Form &expected) {
	if (IsEqualNameAndGrade(target, expected)) {
		std::cout << COLOR_GREEN "[OK]" << COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "[NG]" << COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
}

/* === Expect ===
Error: Grade is too high
Error: Grade is too high
Error: Grade is too high
*/
static void RunTest7() {
	DisplayTitle("Form constructor: throw exception / grade too high");

	Form alice = Form(ALICE, 150, 1); // normal, normal

	try {
		Form alice = Form(ALICE, 0, 123); // too high, normal
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
	try {
		Form alice = Form(ALICE, 123, 0); // normal, too high
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
	try {
		Form alice = Form(ALICE, 0, 0); // too high, too high
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

/* === Expect ===
Error: grade is too low
Error: grade is too low
Error: grade is too low
*/
static void RunTest8() {
	DisplayTitle("Form constructor: throw exception / grade too low");

	Form bob = Form(BOB, 1, 150); // normal, normal

	try {
		Form bob = Form(BOB, 151, 1); // too low, normal
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
	try {
		Form bob = Form(BOB, 151, 1); // normal, too low
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}

	try {
		Form bob = Form(BOB, 151, 12345); // too low, too low
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}
}

/* === Expect ===
[OK]
[OK]
*/
static void RunTest9() {
	DisplayTitle("Form copy test");

	static const unsigned int kGradeForSign    = 5;   // normal
	static const unsigned int kGradeForExecute = 123; // normal

	Form alice = Form(ALICE, kGradeForSign, kGradeForExecute);

	Form alice2(alice);
	JudgeResult(alice2, alice); // [OK]

	Form alice3 = alice;
	JudgeResult(alice3, alice); // [OK]
}

/* === Expect ===
Form Alice(not signed), grade for sign is 5, grade for execute is 123
*/
static void RunTest10() {
	DisplayTitle("Form operator<< overload");

	Form alice = Form(ALICE, 5, 123);
	std::cout << alice << std::endl;
}

/* === Expect ===
Alice, bureaucrat grade 5.
Form: F1(not signed), grade for sign is 4, grade for execute is 50
Alice couldn't sign F1 because lower than the required Form grade.
Form: F1(not signed), grade for sign is 4, grade for execute is 50
Alice, bureaucrat grade 4.
Alice signed F1
Form: F1(signed), grade for sign is 4, grade for execute is 50
*/
static void RunTest11() {
	DisplayTitle("Bureaucrat try to sign the Form");

	Bureaucrat alice(ALICE, 5);
	std::cout << alice << std::endl;

	Form form("F1", 4, 50);
	std::cout << form << std::endl;

	alice.signForm(form);
	std::cout << form << std::endl;

	alice.IncrementGrade();
	std::cout << alice << std::endl;

	alice.signForm(form);
	std::cout << form << std::endl;
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
	RunTest7();
	RunTest8();
	RunTest9();
	RunTest10();
	RunTest11();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}
