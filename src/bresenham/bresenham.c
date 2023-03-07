/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:28 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:29 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_x(t_bresenham *bre, t_map_data *map_data, int row, int column);
static void	put_y(t_bresenham *bre, t_map_data *map_data, int row, int column);

void	bresenham(t_map_data *map_data, t_point *point0, t_point *point1,
			t_matrix *mtx)
{
	t_bresenham	bre;

	bre.x0 = point0->x;
	bre.y0 = point0->y;
	bre.inc_x = 1;
	bre.inc_y = 1;
	bre.dx = point1->x - bre.x0;
	bre.dy = point1->y - bre.y0;
	bre.abs_dx = ft_abs(bre.dx);
	bre.abs_dy = ft_abs(bre.dy);
	if (bre.dx < 0)
		bre.inc_x = -1;
	if (bre.dy < 0)
		bre.inc_y = -1;
	if (bre.abs_dx > bre.abs_dy)
		put_x(&bre, map_data, mtx->row, mtx->column);
	else
		put_y(&bre, map_data, mtx->row, mtx->column);
}

static void	put_x(t_bresenham *bre, t_map_data *map_data, int row, int column)
{
	int	i;

	i = 0;
	img_pixel_put(&map_data->img, bre->x0, bre->y0,
		map_data->iso_coord[row][column].color);
	bre->pk = (2 * bre->abs_dy) - bre->abs_dx;
	while (i < bre->abs_dx)
	{
		bre->x0 += bre->inc_x;
		if (bre->pk < 0)
			bre->pk = bre->pk + (2 * bre->abs_dy);
		else
		{
			bre->pk = bre->pk + (2 * bre->abs_dy) - (2 * bre->abs_dx);
			bre->y0 += bre->inc_y;
		}
		img_pixel_put(&map_data->img, bre->x0, bre->y0,
			map_data->iso_coord[row][column].color);
		i++;
	}
}

static void	put_y(t_bresenham *bre, t_map_data *map_data, int row, int column)
{
	int	i;

	i = 0;
	img_pixel_put(&map_data->img, bre->x0, bre->y0,
		map_data->iso_coord[row][column].color);
	bre->pk = (2 * bre->abs_dx) - bre->abs_dy;
	while (i < bre->abs_dy)
	{
		bre->y0 += bre->inc_y;
		if (bre->pk < 0)
			bre->pk = bre->pk + (2 * bre->abs_dx);
		else
		{
			bre->pk = bre->pk + (2 * bre->abs_dx) - (2 * bre->abs_dy);
			bre->x0 += bre->inc_x;
		}
		img_pixel_put(&map_data->img, bre->x0, bre->y0,
			map_data->iso_coord[row][column].color);
		i++;
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

float	ft_abs(float value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}
