#include "Bureaucrat.hpp"
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
	DisplayTitle("IncrementGrade(), throw exception / too high");

	unsigned int grade = 2;

	Bureaucrat alice(ALICE, grade);
	JudgeResult(alice, ALICE, grade); // [OK]

	ExecGradeTest(alice, &Bureaucrat::IncrementGrade);
	JudgeResult(alice, ALICE, grade - 1); // [OK]

	ExecGradeTest(alice, &Bureaucrat::IncrementGrade); // catch exception
	JudgeResult(alice, ALICE, grade - 1);              // [OK] nothing changed
}

/* === Expect ===
[OK]
[OK]
Error: grade is too low
[OK]
*/
static void RunTest2() {
	DisplayTitle("DecrementGrade(), throw exception / too low");

	unsigned int grade = 149;

	Bureaucrat bob = Bureaucrat(BOB, grade);
	JudgeResult(bob, BOB, grade); // [OK]

	ExecGradeTest(bob, &Bureaucrat::DecrementGrade);
	JudgeResult(bob, BOB, grade + 1); // [OK]

	ExecGradeTest(bob, &Bureaucrat::DecrementGrade); // catch exception
	JudgeResult(bob, BOB, grade + 1);                // [OK] nothing changed
}

/* === Expect ===
[OK]
[OK]
[OK]
*/
static void RunTest3() {
	DisplayTitle("Bureaucrat copy test");

	static const unsigned int kGrade = 123;

	Bureaucrat alice = Bureaucrat(ALICE, kGrade);
	JudgeResult(alice, ALICE, kGrade); // [OK]

	Bureaucrat alice2(alice);
	JudgeResult(alice2, ALICE, kGrade); // [OK]

	Bureaucrat alice3 = alice;
	JudgeResult(alice3, ALICE, kGrade); // [OK]
}

/* === Expect ===
Error: grade is too high
*/
static void RunTest4() {
	DisplayTitle("constructor: throw exception / grade too high");

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
	DisplayTitle("constructor: throw exception / grade too low");

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
	DisplayTitle("operator<< overload");

	unsigned int grade = 123;

	Bureaucrat alice(ALICE, grade);
	std::cout << alice << std::endl;  // operator<<
	JudgeResult(alice, ALICE, grade); // [OK]

	// increment 3 times
	for (unsigned int i = 0; i < 3; i++) {
		ExecGradeTest(alice, &Bureaucrat::IncrementGrade);
		std::cout << alice << std::endl;          // operator<<
		JudgeResult(alice, ALICE, grade - i - 1); // [OK]
	}

	// decrement
	ExecGradeTest(alice, &Bureaucrat::DecrementGrade);
	std::cout << alice << std::endl;          // operator<<
	JudgeResult(alice, ALICE, grade - 3 + 1); // [OK]
}

static void RunOriginalTest() {
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();
	RunTest6();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}
