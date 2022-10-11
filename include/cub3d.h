#ifndef CUB3D_H
# define CUB3D_H

# include "typedef.h"

/*  check_arguments.c  */
void	check_arguments(int argc, char **argv);

/*  check_valid_map.c   */
void	check_valid_map(char *line, t_parsing_info *passing_info, int fd);

/*  init.c  */
void	init_all(t_game	*game);

/*  print.c  */
void	put_string_fd(char *str, int fd);
void	print_error_and_exit(char *str);

/*  read_map_arr.c  */
void	init_map_array(t_parsing_info *parsing_info);
void	fill_element(t_game *game, char input, int x, int y);
void	fill_map_array(t_game *game, int fd, char *line);
void	get_map_array(t_game *game, int fd);

/*  read_map_utils.c    */
int		is_space(char	c);
int		is_map(char	*line);
int		is_end_line(char *line);

/*  read_map.c  */
int		compare_and_save(char **splited, t_cube_info *cube_info);
int		read_wall_texture(char *line, t_game *game);
void	read_map(char *name_of_map, t_game *game);
int		count_in_cube_info(t_cube_info *cube_info);
char	*get_front_splited(char *line, char *set);

/*  read_wall_texture.c  */
int		read_wall_texture(char *line, t_game *game);

/*  test_print.c  */
void	print_map(t_game *game);
void	print_cube_info(t_cube_info *cube);

#endif
