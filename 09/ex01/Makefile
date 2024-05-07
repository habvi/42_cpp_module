NAME		:=	RPN

SRCS_DIR	:=	srcs
SRCS		:=	main.cpp \
				RPN.cpp

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
	$(RM) -r $(OBJ_DIR)

.PHONY	: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY	: re
re: fclean all

#--------------------------------------------
.PHONY	: run
run: all
	@./$(NAME)

.PHONY	: val
val: all
	@valgrind ./$(NAME)

.PHONY	: check
check:
	@cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------
.PHONY	: t1
t1: all
	@./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"

.PHONY	: t2
t2: all
	@./$(NAME) "7 7 * 7 -"

.PHONY	: t3
t3: all
	@./$(NAME) "1 2 * 2 / 2 * 2 4 - +"

.PHONY	: t4
t4: all
	@./$(NAME) "(1 + 1)"

#--------------------------------------------

-include $(DEPS)
