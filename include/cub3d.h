#ifndef CUB3D_H
# define CUB3D_H

# include "typedef.h"

/*  check_arguments.c  */
void	check_arguments(int argc, char **argv);

/*  init.c  */
void	init_all(t_game	*game);

/*  print.c  */
void	put_string_fd(char *str, int fd);
void	print_error_and_exit(char *str);

/*  read_map.c  */
int		compare_and_save(char **splited, t_cube_info *cube_info);
int		read_wall_texture(char *line, t_game *game);
void	read_map(char *name_of_map, t_game *game);

/*  test.c  */
void print_cube_info(t_cube_info *cube);

#endif
