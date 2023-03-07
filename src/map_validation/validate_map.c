/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:25:12 by ebezerra          #+#    #+#             */
/*   Updated: 2023/01/04 20:25:13 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_digits(const char *s, char c);
static void	validate_xdigit(const char **s);
static int	count_map_rows(const char *file, t_map_data *map_data);

t_bool	validate_map(const char *file, t_map_data *map_data)
{
	if (count_map_rows(file, map_data) < 0)
	{
		return (false_);
	}
	return (true_);
}

static int	count_map_columns(char *str, char separator)
{
	int	digits;

	str = ft_strtrim(str, "\n");
	digits = count_digits(str, separator);
	free(str);
	return (digits);
}

static int	count_map_rows(const char *file, t_map_data *map_data)
{
	int		flag;
	char	*map_row;
	int		fd;

	fd = open_file(file);
	map_data->rows = 0;
	map_row = get_next_line(fd);
	map_data->error = 0;
	map_data->columns = count_map_columns(map_row, ' ');
	while (map_row != NULL)
	{
		flag = count_map_columns(map_row, ' ');
		if (flag != map_data->columns || flag < 0)
			map_data->error = -1;
		free(map_row);
		map_row = get_next_line(fd);
		map_data->rows++;
	}
	if (map_data->error < 0)
	{
		close(fd);
		return (-1);
	}
	return (close(fd));
}

static void	validate_xdigit(const char **s)
{
	if (s[0][1] != '0' || ft_tolower(s[0][2]) != 'x')
	{
		ft_printf("Error: map is invalid\n");
		exit(1);
	}
	*s += 3;
	while ((**s && **s != ' '))
	{
		if (!ft_isxdigit(**s))
		{
			ft_printf("Error: map is invalid\n");
			exit(1);
		}
		(*s)++;
	}
	(*s)--;
}

static int	count_digits(const char *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
			{
				if ((!ft_isxdigit(*s) && *s != '-') && *s != ',')
					return (-1);
				if (*s == ',')
					validate_xdigit(&s);
				s++;
			}
			word_count++;
			s--;
		}
		s++;
	}
	return (word_count);
}
