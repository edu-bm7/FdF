/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:26 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:27 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_z(int *x_to_iso, int *y_to_iso, float angle);
static void	rotate_x(int *y_to_iso, int *z_to_iso, float angle);

void	rotate_point(t_point *point)
{
	rotate_z(&point->x, &point->y, Z_ANGLE);
	rotate_x(&point->y, &point->z, X_ANGLE);
}

static void	rotate_z(int *x_to_iso, int *y_to_iso, float angle)
{
	float	x;
	float	y;

	x = *x_to_iso;
	y = *y_to_iso;
	*x_to_iso = x * cos(angle) - y * sin(angle);
	*y_to_iso = x * sin(angle) + y * cos(angle);
}

static void	rotate_x(int *y_to_iso, int *z_to_iso, float angle)
{
	float	y;
	float	z;

	y = *y_to_iso;
	z = *z_to_iso;
	*y_to_iso = y * cos(angle) - z * sin(angle);
	*z_to_iso = y * sin(angle) + z * cos(angle);
}

void	centralize_point(t_map_data *map_data, t_point *point)
{
	float	cx_to_zero;
	float	cy_to_zero;

	cx_to_zero = (map_data->min.x + ((map_data->max.x - map_data->min.x) / 2));
	cy_to_zero = (map_data->min.y + ((map_data->max.y - map_data->min.y) / 2));
	if (cx_to_zero < 0)
		point->x += (WINDOW_WIDTH / 2) + ft_abs(cx_to_zero);
	else
		point->x += (WINDOW_WIDTH / 2) - ft_abs(cx_to_zero);
	if (cy_to_zero < 0)
		point->y += (WINDOW_HEIGHT / 2) + ft_abs(cy_to_zero);
	else
		point->y += (WINDOW_HEIGHT / 2) - ft_abs(cy_to_zero);
}

void	scale_coordinates(t_point *point)
{
	point->x *= LINE_SIZE;
	point->y *= LINE_SIZE;
	point->z *= LINE_SIZE;
}
