/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transformation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:22 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:23 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_min_max(t_map_data *map_data);

void	centralize_coordinates(t_map_data *map_data)
{
	int	row;
	int	column;

	row = 0;
	while (row < map_data->rows)
	{
		column = 0;
		while (column < map_data->columns)
		{
			centralize_point(map_data, &map_data->iso_coord[row][column]);
			column++;
		}
		row++;
	}
	update_min_max(map_data);
}

static void	update_min_max(t_map_data *map_data)
{
	float	cx_to_zero;
	float	cy_to_zero;

	cx_to_zero = (map_data->min.x + ((map_data->max.x - map_data->min.x) / 2));
	cy_to_zero = (map_data->min.y + ((map_data->max.y - map_data->min.y) / 2));
	if (cx_to_zero < 0)
	{
		map_data->max.x += (WINDOW_WIDTH / 2) + ft_abs(cx_to_zero);
		map_data->min.x += (WINDOW_WIDTH / 2) + ft_abs(cx_to_zero);
	}
	else
	{
		map_data->max.x += (WINDOW_WIDTH / 2) - ft_abs(cx_to_zero);
		map_data->min.x += (WINDOW_WIDTH / 2) - ft_abs(cx_to_zero);
	}
	if (cy_to_zero < 0)
	{
		map_data->max.y += (WINDOW_HEIGHT / 2) + ft_abs(cy_to_zero);
		map_data->min.y += (WINDOW_HEIGHT / 2) + ft_abs(cy_to_zero);
	}
	else
	{
		map_data->max.y += (WINDOW_HEIGHT / 2) - ft_abs(cy_to_zero);
		map_data->min.y += (WINDOW_HEIGHT / 2) - ft_abs(cy_to_zero);
	}
}

void	scale_min_max(t_map_data *map_data)
{
	map_data->max.x *= map_data->scale_factor;
	map_data->max.y *= map_data->scale_factor;
	map_data->min.x *= map_data->scale_factor;
	map_data->min.y *= map_data->scale_factor;
}
