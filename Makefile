NAME = ft_shmup

SRCS_DIR = srcs
SRCS = main.cpp \
		game.cpp \
		gameobject.cpp \
		position.cpp \
		bullet.cpp \
		player.cpp

CFLAGS = -MMD -MP -I includes

OUTDIR = obj
OBJECTS = ${SRCS:%.cpp=$(OUTDIR)/%.o}

DEPS_FILES = ${OBJECTS:.o=.d}


all: $(NAME)

-include $(DEPS_FILES)

${NAME}: $(OBJECTS)
	c++ $(CFLAGS) -lncurses -o $(NAME) $(OBJECTS)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.cpp | $(OUTDIR)
	c++ $(CFLAGS) -o $@ -c $<

$(OUTDIR):
	mkdir -p $(OUTDIR)
clean:
	rm -f $(OBJECTS) $(DEPS_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all libft
