NAME		:=	btc

SRCS_DIR	:=	srcs
SRCS		:=	BitcoinExchange.cpp \
				main.cpp

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
INFILE	:= input.txt

.PHONY	: run
run: all
	@./$(NAME) $(INFILE)

.PHONY	: val
val: all
	@valgrind ./$(NAME) $(INFILE)

.PHONY	: check
check:
	@cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

.PHONY	: diff
diff: all
	@./$(NAME) $(INFILE) > out.txt 2>&1
	@-diff expected.txt out.txt
#	@rm out.txt

#--------------------------------------------
.PHONY	: data
data:
	@curl -O https://cdn.intra.42.fr/document/document/24295/cpp_09.tgz
	@tar xvf cpp_09.tgz
	@cp cpp_09/data.csv .

.PHONY	: input
input:
	@echo "\
date | value\n\
----------- subject --------------\n\
2011-01-03 | 3\n\
2011-01-03 | 2\n\
2011-01-03 | 1\n\
2011-01-03 | 1.2\n\
2011-01-09 | 1\n\
2012-01-11 | -1\n\
2001-42-42\n\
2012-01-11 | 1\n\
2012-01-11 | 2147483648\n\
----------- normal value ---------\n\
2012-01-11 | 0\n\
2012-01-11 | 1000\n\
9999-12-31 | 1\n\
----------- normal leap year -----\n\
2020-02-29 | 1\n\
----------- normal date ----------\n\
0000-11-11 | 1\n\
9999-11-11 | 1\n\
1111-01-11 | 1\n\
1111-12-11 | 1\n\
1111-11-01 | 1\n\
1111-11-30 | 1\n\
----------- error ----------------\n\
2012-01-11 | 1001\n\
2019-02-29 | 1\n\
2012-01-11 | inf\n\
2012-01-11 | -inf\n\
2012-01-11 | a\n\
2012-01-11 | 1a\n\
a\n\
2012-01-11|1\n\
2012-01-11   |   1\n\
2012-123-11 | 1\n\
99991-01-11 | 1\n\
2012-00-11 | 1\n\
2012-13-11 | 1\n\
2012-01-00 | 1\n\
2012-01-32 | 1\n\
2012-04-31 | 1\n\
111a-11-11 | 1\n\
1111-1a-11 | 1\n\
1111-11-1a | 1" > $(INFILE)

-include $(DEPS)
