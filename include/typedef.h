#ifndef TYPEDEF_H
# define TYPEDEF_H

# define	NULL		0
# define	WIN_W		800
# define	WIN_H		640

# define	TILE_SIZE	7

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define KEY_ESC				53

typedef	struct s_cube_info		t_cube_info;
typedef struct s_player			t_player;
typedef struct s_parsing_info	t_parsing_info;
typedef struct s_img			t_img;
typedef struct s_mlx			t_mlx;
typedef struct s_game			t_game;

typedef enum e_element			t_element;
typedef enum e_angle			t_angle;

/* parsing */

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

/* mlx */

struct s_img
{
	void	*img_ptr;
	int		*img_data;
	int		img_width;
	int		img_height;

	int		size_l;
	int		bpp;
	int		endian;
};

struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img_minimap;
};

/* game */

struct	s_game
{
	t_cube_info		*cube_info;
	t_player		*player;
	t_parsing_info	*parsing_info;
	t_mlx			*mlx;
};

#endif
