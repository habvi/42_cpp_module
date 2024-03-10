NAME		:=	a.out

SRCS_DIR	:=	srcs
SRCS		:=	AForm.cpp \
				Bureaucrat.cpp \
				GradeException.cpp \
				Intern.cpp \
				main.cpp \
				PresidentialPardonForm.cpp \
				RobotomyRequestForm.cpp \
				ShrubberyCreationForm.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP -pedantic

DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY	: clean
clean:
	$(RM) $(TEST_FILENAME)
	$(RM) -r $(OBJ_DIR)

.PHONY	: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY	: re
re: fclean all

#--------------------------------------------
.PHONY	: run
run: all
	./$(NAME)

.PHONY	: val
val: all
	valgrind ./$(NAME)

.PHONY	: check
check:
	cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------
# test for ShrubberyCreationForm's execute() fail
TEST_FILENAME := Shru_Alice_shrubbery

.PHONY	: chmod
chmod:
	@touch $(TEST_FILENAME)
	@chmod 000 $(TEST_FILENAME)

.PHONY	: back
back:
	@chmod 664 $(TEST_FILENAME)


#--------------------------------------------

-include $(DEPS)
