/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:42:11 by mcygan            #+#    #+#             */
/*   Updated: 2025/04/29 14:22:58 by mcygan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <sys/time.h>

#define BUFFER_SIZE		32
#define MAP_MAX			255
#define CFG_MAX			6

#define WIN_W			1200
#define WIN_H			800

#define FOV				60
#define MOVE_SPEED		0.03

#define MINIMAP			true
#define MINIMAP_SCALE	300

#define WEAPON			false
#define WEAPON_POS		0.55

#define MOUSE			false
#define SENS			0.005

#define KEY_W			0x0077
#define KEY_A			0x0061
#define KEY_S			0x0073
#define KEY_D			0x0064
#define KEY_LEFT		0xff51
#define KEY_RIGHT		0xff53
#define KEY_SPACE		0x0020
#define KEY_ESCAPE		0xff1b

typedef struct s_img
{
	void	*ptr;
	char	*addr;

	int		bpp;
	int		line_len;
	int		endian;

	int		w;
	int		h;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;

	char	***cfg;
	char	**map;
	char	**map_check;

	int		fd;
	int		error;

	char	*tex_no_path;
	char	*tex_so_path;
	char	*tex_we_path;
	char	*tex_ea_path;

	t_img	tex_no;
	t_img	tex_so;
	t_img	tex_we;
	t_img	tex_ea;

	int		ceiling_colour;
	int		floor_colour;

	int		map_w;
	int		map_h;

	double	pos_x;
	double	pos_y;
	double	pos_a;
	double	fov;

	bool	w_press;
	bool	a_press;
	bool	s_press;
	bool	d_press;
	bool	left_press;
	bool	right_press;

	size_t	last_frame_time;

	int		map_scale;

	bool	animation;
	int		frame;
	size_t	last_sprite_time;
	t_img	sprite[5];

	int		mouse_lastpos;
	int		mouse_move;
}	t_data;

typedef struct s_ray_info
{
	double	angle;
	double	raydir_x;
	double	raydir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	step_x;
	double	step_y;
	double	perp_dist;
	int		side;
}	t_ray_info;

// parser.cfg.c
void	free_cfg(char ***cfg);
char	***get_cfg(t_data *data);
int		fill_data(t_data *data, char *s1, char *s2);

// parser/gnl.c
char	*get_next_line(int fd);

// parser/init.c
void	init_data(t_data *data);
int		init_img(t_data *data, char *path, t_img *addr);
void	load_textures(t_data *data);

// parser/map.c
char	**get_map(int fd);
void	set_map_size(t_data *data);
int		parse_cluster(t_data *data, int x, int y);

// parser/parse.c
void	parse(t_data *data);

// parser/split.c
char	**ft_split(char const *s, char c);

// parser/utils1.c
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);

// parser/utils2.c
void	free_str_array(char **strs);
int		ft_atoi(const char *str);
int		copy_line(char *src, char *dst);
char	*next_nonempty_line(int fd);

// raycaster/close.c
void	close_handler(t_data *data, char *error);

// raycaster/handlers.c
void	init_events(t_data *data);

// raycaster/minimap.c
void	draw_minimap(t_data *data);

// raycaster/move.c
void	player_move(t_data *data);

// raycaster/render.c
int		render(t_data *data);

// raycaster/sprite.c
void	load_sprites(t_data *data);
void	put_sprite_to_img(t_img *dst, t_img *src, int x, int y);
void	animate_sprite(t_data *data);

// raycaster/texture.c
int		get_texel(t_data *data, t_ray_info *info, int y, int wall_h);

// raycaster/utils.c
size_t	time_ms(void);
void	pxl_put(t_img *img, int x, int y, int colour);
int		get_pxl(t_img *img, int x, int y);
