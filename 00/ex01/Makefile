NAME		:=	phonebook

SRCS_DIR	:=	srcs
SRCS		:=	cmd_add.cpp \
				cmd_search.cpp \
				contact.cpp \
				io.cpp \
				main.cpp \
				phonebook.cpp

OBJ_DIR		:=	objs
OBJS		:=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

INCLUDE_DIR	:=	includes
INCLUDES	:=	-I./$(INCLUDE_DIR)/

CXX			:=	c++
CXXFLAGS	:=	-std=c++98 -Wall -Wextra -Werror -MMD -MP
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

.PHONY	: check
check:
	cppcheck --enable=all $$(find . -type f -name "*.cpp" | tr '\n' ' ')

#--------------------------------------------

-include $(DEPS)
