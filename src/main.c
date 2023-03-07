/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:23:56 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/05 21:09:30 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_map_data	map_data;

	if (argc != 2)
	{
		ft_printf("Error: Invalid number of arguments\n");
		return (1);
	}
	if (!validate_map(argv[1], &map_data))
	{
		ft_printf("Error: Map is invalid\n");
		return (1);
	}
	initialize_data(&map_data, argv[1]);
	mlx_loop_hook(map_data.mlx_ptr, &draw, &map_data);
	mlx_hook(map_data.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK,
		&handle_keyrelease, &map_data);
	mlx_hook(map_data.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
		&handle_mouse, &map_data);
	mlx_loop(map_data.mlx_ptr);
	return (0);
}
