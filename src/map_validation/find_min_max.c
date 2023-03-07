/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:10 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:11 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_min(t_map_data *map_data)
{
	int	row;
	int	column;

	row = 0;
	map_data->min.x = 0;
	map_data->min.y = 0;
	while (row < map_data->rows)
	{
		column = 0;
		while (column < map_data->columns)
		{
			if (map_data->min.x > map_data->iso_coord[row][column].x)
				map_data->min.x = map_data->iso_coord[row][column].x;
			if (map_data->min.y > map_data->iso_coord[row][column].y)
				map_data->min.y = map_data->iso_coord[row][column].y;
			column++;
		}
		row++;
	}
}

void	find_max(t_map_data *map_data, int x, int y)
{
	if (map_data->max.x < x)
		map_data->max.x = x;
	if (map_data->max.y < y)
		map_data->max.y = y;
}
