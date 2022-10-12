#ifndef TYPEDEF_H
# define TYPEDEF_H

#define	NULL 0
typedef	struct s_cube_info		t_cube_info;
typedef struct s_player			t_player;
typedef struct s_parsing_info	t_parsing_info;
typedef struct s_game			t_game;

typedef enum e_element			t_element;
typedef enum e_angle			t_angle;

enum	e_element
{
	E_ROAD,
	E_WALL,
	E_VOID
	// E_PLAYER,
};

struct	s_cube_info
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	long long	F;
	long long	C;
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
