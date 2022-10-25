/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehwkim <jaehwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:39:02 by jaehwkim          #+#    #+#             */
/*   Updated: 2022/10/24 14:42:30 by jaehwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define WIN_W 800
# define WIN_H 400

# define TILE_SIZE	7
# define TEX_SIZE	64

# define MOV_SPEED	0.05
# define ROT_SPEED	0.05

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_ESC	53

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17

typedef struct s_cube_info		t_cube_info;
typedef struct s_player			t_player;
typedef struct s_parsing_info	t_parsing_info;
typedef struct s_tex			t_tex;
typedef struct s_raycasting		t_raycasting;
typedef struct s_img			t_img;
typedef struct s_mlx			t_mlx;
typedef struct s_game			t_game;

typedef enum e_element			t_element;
typedef enum e_cube_dir			t_cube_dir;

enum	e_element
{
	E_ROAD,
	E_WALL,
	E_VOID
};

enum	e_cube_dir{
	D_NO,
	D_SO,
	D_WE,
	D_EA
};

struct	s_cube_info
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	long long	f;
	long long	c;
};

struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
};

struct	s_parsing_info
{
	int			width;
	int			height;
	char		**map;
};

struct s_tex
{
	double	pos;
	int		x;
	int		y;
};

struct s_raycasting
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	int		tex_width;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
};

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
};

struct	s_game
{
	t_cube_info		*cube_info;
	t_player		*player;
	t_parsing_info	*parsing_info;
	t_mlx			*mlx;
	int				*wall_texture[4];
	t_img			*minimap;
	t_img			*screen;
};

#endif
