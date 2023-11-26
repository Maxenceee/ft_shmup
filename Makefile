NAME			=	ft_shmup

SRCS_DIR 		=	srcs
SRCS			=	$(shell find $(SRCS_DIR) -name "*.cpp")

CFLAGS			=	-MMD -Wall -Wextra -Werror -MP -I includes -g3 -std=c++17

OUTDIR			=	.objs
OBJECTS			=	$(patsubst $(SRCS_DIR)%.cpp, $(OUTDIR)%.o, $(SRCS))

DEPS_FILES		=	${OBJECTS:.o=.d}

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

all: $(NAME)

-include $(DEPS_FILES)

${NAME}: $(OBJECTS) 
	@c++ $(CFLAGS) -lncursesw -o $(NAME) $(OBJECTS)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

$(OUTDIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@c++ $(CFLAGS) -o $@ -c $<
	@printf ${UP}${CUT}

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@rm -f $(OBJECTS) $(DEPS_FILES)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all libft
