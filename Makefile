NAME 				=	cub3d

CC 					=	cc
CFLAGS				=	-Wall -Wextra -Werror
MLX_FLAGS			=	-lmlx -framework OpenGL -framework AppKit

RM					=	rm -f

SRC_DIR 			= 	./sources/

FILES 					=	check_arguments.c \
							print.c \

SRCS					=	$(addprefix $(SRC_DIR), $(FILES)) \

OBJS					=	$(SRCS:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all
