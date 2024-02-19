NAME		:=	a.out

SRCS_DIR	:=	srcs
SRCS		:=	bsp.cpp \
				Fixed.cpp \
				main.cpp \
				Point.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP
UNAME 		:= $(shell uname)
ifeq ($(UNAME), Linux)
	CXXFLAGS += -pedantic
endif

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
	./$(NAME)

.PHONY	: val
val: all
	valgrind ./$(NAME)

.PHONY	: check
check:
	cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------
PYTHON	:= python3
VISU	:= visualize.py

.PHONY	: test
test: all test1 test2 test3
# source /myenv/bin/activate
# deactivate

.PHONY	: test1
test1: all
	$(PYTHON) $(VISU) $@

.PHONY	: test2
test2: all
	$(PYTHON) $(VISU) $@

.PHONY	: test3
test3: all
	$(PYTHON) $(VISU) $@

#--------------------------------------------

-include $(DEPS)
