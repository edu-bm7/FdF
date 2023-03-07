/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:01 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:02 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: ");
		exit(1);
	}
	return (fd);
}

void	free_map(void **map)
{
	int				row;
	unsigned char	**map_str;

	map_str = (unsigned char **)map;
	row = 0;
	while (map_str[row] != NULL)
	{
		free(map_str[row]);
		row++;
	}
	free(map_str);
}

void	initialize_data(t_map_data *map_data, char *file)
{
	allocate_initial_coord(map_data);
	initialize_map_data(file, map_data);
	allocate_iso_coord(map_data);
	initialize_mlx(map_data);
}
