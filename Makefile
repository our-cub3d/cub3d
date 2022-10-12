NAME 				=	cub3d
LIBFT				=	./libft/libft.a

CC 					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g3
MLX_FLAGS			=	
# MLX_FLAGS			=	-lmlx -framework OpenGL -framework AppKit

# INCLUDE			:= ./include/
# INCLUDE_FILE	:= $(addprefix $(INCLUDE), cub3d.h, typedef.h)

RM					=	rm -f

SRC_DIR 			= 	./srcs/

FILES 					=	check_arguments.c \
	 						check_valid_map.c \
							get_fc.c \
							get_map_array.c \
							init.c \
							main.c \
							print.c \
							read_map_utils.c \
							read_map.c \
							read_wall_texture.c \
							test_print.c \

SRCS					=	$(addprefix $(SRC_DIR), $(FILES))

OBJS					=	$(SRCS:%.c=%.o)

.PHONY: all clean fclean re

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^
	
$(LIBFT) :
	make -C ./libft/

clean:
	$(RM) $(OBJS) $(BOBJ)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re:
	make fclean
	make all
