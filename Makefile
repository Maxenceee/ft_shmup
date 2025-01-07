NAME			=	ft_shmup

SRCS_DIR 		=	srcs
SRCS			=	$(shell find $(SRCS_DIR) -name "*.cpp")

OUTDIR			=	.objs
OBJECTS			=	$(patsubst $(SRCS_DIR)%.cpp, $(OUTDIR)%.o, $(SRCS))

HEADERS_DIR		=	includes
HEADERS			=	$(shell find $(HEADERS_DIR) -name "*.h")
HEADERS_SOURCES	=	$(shell find $(SRCS_DIR) -name "*.h")

DEPS_FILES		=	${OBJECTS:.o=.d}

CC			=	g++
CFLAGS			=	-MMD -Wall -Wextra -Werror -MP -I$(HEADERS_DIR) -I/usr/include/ncursesw -g3 -std=c++17
LDFLAGS			=	-lncursesw

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

all: $(NAME)

-include $(DEPS_FILES)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS) $(HEADERS_SOURCES) Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf ${UP}${CUT}

${NAME}: $(OBJECTS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@rm -f $(OBJECTS) $(DEPS_FILES)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all libft
