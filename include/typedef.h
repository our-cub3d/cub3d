#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef	struct s_cube_info		t_cube_info;
typedef struct s_player			t_player;
typedef struct s_parsing_info	t_parsing_info;
typedef struct s_game			t_game;

struct	s_cube_info
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
};

struct	s_player
{
	float	angle;
	int		x;
	int		y;
};

struct	s_parsing_info
{
	int			width;
	int			height;
	char		**map;
};

struct	s_game
{
	t_cube_info		*cube_info;
	t_player		*player;
	t_parsing_info	*parsing_info;
};

#endif
