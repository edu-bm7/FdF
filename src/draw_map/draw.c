/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:20 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:21 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_map_data *map_data, t_matrix *mtx);
static void	scale_down_map(t_map_data *map_data);

int	draw(t_map_data *map_data)
{
	t_matrix	mtx;

	if (map_data->win_ptr == NULL)
		return (1);
	centralize_coordinates(map_data);
	if (map_data->max.x > WINDOW_WIDTH || map_data->min.x < 0
		|| map_data->max.y > WINDOW_HEIGHT || map_data->min.y < 0)
	{
		scale_down_map(map_data);
		centralize_coordinates(map_data);
	}
	mtx.row = 0;
	while (mtx.row < map_data->rows)
	{
		mtx.column = 0;
		while (mtx.column < map_data->columns)
		{
			draw_line(map_data, &mtx);
			mtx.column++;
		}
		mtx.row++;
	}
	mlx_put_image_to_window(map_data->mlx_ptr, map_data->win_ptr,
		map_data->img.mlx_img, 0, 0);
	return (0);
}

static void	draw_line(t_map_data *map_data, t_matrix *mtx)
{
	if (mtx->column < map_data->columns - 1)
	{
		bresenham(map_data, &map_data->iso_coord[mtx->row][mtx->column],
			&map_data->iso_coord[mtx->row][mtx->column + 1], mtx);
	}
	if (mtx->row < map_data->rows - 1)
	{
		bresenham(map_data, &map_data->iso_coord[mtx->row][mtx->column],
			&map_data->iso_coord[mtx->row + 1][mtx->column], mtx);
	}
}

static void	scale_down_map(t_map_data *map_data)
{
	t_matrix	d;
	double		delta_x;
	double		delta_y;

	delta_x = map_data->max.x - map_data->min.x;
	delta_y = map_data->max.y - map_data->min.y;
	if (WINDOW_WIDTH * WINDOW_COVARAGE / delta_x
		> WINDOW_HEIGHT * WINDOW_COVARAGE / delta_y)
		map_data->scale_factor = WINDOW_HEIGHT * WINDOW_COVARAGE / delta_y;
	else
		map_data->scale_factor = WINDOW_WIDTH * WINDOW_COVARAGE / delta_x;
	d.row = 0;
	while (d.row < map_data->rows)
	{
		d.column = 0;
		while (d.column < map_data->columns)
		{
			map_data->iso_coord[d.row][d.column].x *= map_data->scale_factor;
			map_data->iso_coord[d.row][d.column].y *= map_data->scale_factor;
			map_data->iso_coord[d.row][d.column].z *= map_data->scale_factor;
			d.column++;
		}
		d.row++;
	}
	scale_min_max(map_data);
}
