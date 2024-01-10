NAME		:=	account

SRCS		:=	Account.cpp \
				tests.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDES	:=	-I.

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP
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

.PHONE	: check
check:
	cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------

-include $(DEPS)
