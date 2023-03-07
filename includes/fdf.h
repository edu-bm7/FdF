/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:26:16 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/05 01:47:32 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

// Window Params
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 900
# define WINDOW_COVARAGE 0.85
# define DEFAULT_COLOR 0xCACACA
// Mlx Events
# define KEY_RELEASE 3
# define KEY_RELEASE_MASK 2
# define DESTROY_NOTIFY 17
# define STRUCTURE_NOTIFY_MASK 131072
// Mlx Key Symbol
# define XK_ESCAPE 0xff1b
//Mlx Error
# define MLX_ERROR 1
// Bresenham Params
# define LINE_SIZE 50
# define Z_ANGLE 0.785
# define X_ANGLE 0.955

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_map_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	**initial_coord;
	t_point	**iso_coord;
	t_point	max;
	t_point	min;
	t_img	img;
	double	scale_factor;
	int		rows;
	int		columns;
	int		row;
	int		column;
	int		error;
}				t_map_data;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	abs_dx;
	int	abs_dy;
	int	pk;
	int	x0;
	int	y0;
	int	color;
	int	inc_x;
	int	inc_y;

}				t_bresenham;

typedef struct s_matrix
{
	int	row;
	int	column;
}				t_matrix;

void	initialize_data(t_map_data *map_data, char *file);
void	initialize_map_data(const char *file, t_map_data *map_data);
int		open_file(const char *file);
void	allocate_initial_coord(t_map_data *map_data);
void	allocate_iso_coord(t_map_data *map_data);
t_bool	validate_map(const char *file, t_map_data *map_data);
void	rotate_point(t_point *point);
void	centralize_point(t_map_data *map_data, t_point *point);
void	find_min(t_map_data *map_data);
void	find_max(t_map_data *map_data, int x, int y);
void	scale_min_max(t_map_data *map_data);
float	ft_abs(float value);
void	centralize_coordinates(t_map_data *map_data);
int		draw(t_map_data *map_data);
void	bresenham(t_map_data *map_data, t_point *point0, t_point *point1,
			t_matrix *mtx);
void	scale_coordinates(t_point *point);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	free_map(void **map);
int		handle_keyrelease(int keysym, t_map_data *map_data);
int		handle_mouse(t_map_data *map_data);
void	initialize_mlx(t_map_data *map_data);

#endif