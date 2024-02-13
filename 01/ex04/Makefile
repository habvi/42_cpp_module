NAME		:=	sed

SRCS_DIR	:=	srcs
SRCS		:=	error.cpp \
				file_replace.cpp \
				file.cpp \
				main.cpp

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

COLOR_GREEN := \033[0;32m
COLOR_RED := \033[0;31m
COLOR_END := \033[0m

IN_FILE			:=	"in.txt"
OUT_FILE		:=	"in.txt.replace"
EXPECTED_FILE	:=	"expected_tmp.txt"

define run_test
	@echo "\n======== $(1) ========"
	@echo -n $(2) > $(IN_FILE)
	@echo './$(NAME) $(IN_FILE) $(3) $(4)'
	-@./$(NAME) $(IN_FILE) $(3) $(4) || true
endef

define diff_test
	@echo "\n-------- before -------"
	@cat $(IN_FILE)
	@echo "\n-------- after --------"
	@cat $(OUT_FILE)
	@echo "\n-------- diff ---------"
	@EXPECTED=$$(echo $(1) | sed "s/$(2)/$(3)/g") ; \
	echo -n "$${EXPECTED}" > $(EXPECTED_FILE) ; \

    @if diff $(EXPECTED_FILE) $(OUT_FILE); then \
        echo "$(COLOR_GREEN)[OK]$(COLOR_END)"; \
    else \
        echo "$(COLOR_RED)[NG]$(COLOR_END)"; \
    fi
endef

.PHONY	: test
test: all test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11
	@rm $(EXPECTED_FILE)

##### normal case #####
# simple
IN_1	:=	"test1 test2    test3"
.PHONY	: test1
test1:
	@echo "\n\n$(COLOR_GREEN)************ normal case ************$(COLOR_END)"
	$(call run_test,Test1,$(IN_1),"test","x")
	$(call diff_test,$(IN_1),"test","x")

# S2 -> empty
.PHONY	: test2
test2:
	$(call run_test,Test2,$(IN_1),"test","")
	$(call diff_test,$(IN_1),"test","")

# simple with \n
IN_2	:=	"test1\n\n test2  \n    test3"
.PHONY	: test3
test3:
	$(call run_test,Test3,$(IN_2),"test","zzzzzzzz")
	$(call diff_test,$(IN_2),"test","zzzzzzzz")

# with \n, consecutive word
IN_3	:=	"test1\n\n testtesttest2  \n    test3testtest"
.PHONY	: test4
test4:
	$(call run_test,Test4,$(IN_3),"test",".")
	$(call diff_test,$(IN_3),"test",".")

# with \n, consecutive word, same S1,S2
.PHONY	: test5
test5:
	$(call run_test,Test5,$(IN_3),"test","test")
	$(call diff_test,$(IN_3),"test","test")

# with \n, consecutive word, same S1,S2, not exist in IN_FILE
.PHONY	: test6
test6:
	$(call run_test,Test6,$(IN_3),"aa","aa")
	$(call diff_test,$(IN_3),"aa","aa")

# empty file
.PHONY	: test7
test7:
	$(call run_test,Test7,"","aa","abcde")
	$(call diff_test,"","aa","aa")

# manual...
# with \n, S1 contains \n
IN_4	:=	"test\ntest\ntest"
.PHONY	: test_a
test_a:
	@echo "\n======== Test? ========"
	@echo -n $(IN_4) > $(IN_FILE)
# run below
# ./sed in.txt "$(echo -e 't\nt')" --
.PHONY	: test_b
test_b:
	@echo "\n-------- before -------"
	@cat $(IN_FILE)
	@echo "\n-------- after --------"
	@cat $(OUT_FILE)
	@echo "\n-------- diff ---------"
	@echo -n "tes--es--est" > $(EXPECTED_FILE) ; \
	diff $(EXPECTED_FILE) $(OUT_FILE)

##### error case #####
# S1 -> empty
.PHONY	: test8
test8:
	@echo "\n\n$(COLOR_GREEN)************ error case ************$(COLOR_END)"
	$(call run_test,Test8,$(IN_1),"","abc")

# not 3 arguments
.PHONY	: test9
test9:
	@echo "\n======== Test9 ========"
	-./$(NAME) 1 2 3 4

# empty filename
.PHONY	: test10
test10:
	@echo "\n======== Test10 ======="
	-./$(NAME) "" s1 s2

# empty filename
.PHONY	: test11
test11:
	@echo "\n======== Test11 ======="
	-./$(NAME) "not_exist_filename" s1 s2

#--------------------------------------------

-include $(DEPS)
