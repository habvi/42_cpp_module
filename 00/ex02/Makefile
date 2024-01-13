NAME		:=	account

SRCS		:=	Account.cpp \
				tests.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDES	:=	-I.

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP

ifdef NO_TIMESTAMP
	CXXFLAGS += -D NO_TIMESTAMP
endif

DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

$(OBJ_DIR)/%.o: %.cpp
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

.PHONEY	: check
check:
	cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

.PHONY : no_time
no_time:
	make re NO_TIMESTAMP=1

.PHONY : diff
diff: no_time
	./$(NAME) > out
	diff out no_timestamp_19920104_091532.log

#--------------------------------------------

-include $(DEPS)
