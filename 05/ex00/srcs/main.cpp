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


static void RunOriginalTest() {
	RunTest1();
	RunTest2();
	RunTest3();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}
