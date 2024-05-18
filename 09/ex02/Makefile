NAME		:=	PmergeMe

SRCS_DIR	:=	srcs
SRCS		:=	Clock.cpp \
				main.cpp \
				PmergeMe.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP -pedantic -O2

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
ARGS	:= $(shell python3 -c "import random; n = 3000; print(' '.join(map(str, random.sample(range(0, 2147483648), n))))")

# ex) make run ARGS="1 2 3 4 5 6"
.PHONY	: run
run: all
	@./$(NAME) $(ARGS)

.PHONY	: val
val: all
	@valgrind ./$(NAME) $(ARGS)

.PHONY	: check
check:
	@cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------

-include $(DEPS)
