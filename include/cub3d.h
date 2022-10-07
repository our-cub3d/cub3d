#ifndef CUB3D_H
# define CUB3D_H

# include "typedef.h"

/*  check_arguments.c  */
void	check_arguments(int argc, char **argv);

/*  print.c  */
void	put_string_fd(char *str, int fd);
void	print_error_and_exit(char *str);

#endif
