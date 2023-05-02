/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:18:11 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/03/30 19:28:06 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_lay	new_layout(void)
{
	t_lay	res;

	res.n_row = 0;
	res.n_col = 0;
	res.n_exit = 0;
	res.n_pl = 0;
	res.n_en = 0;
	res.n_collect = 0;
	return (res);
}

char	**check_map(int ac, char **av, t_lay *layout)
{
	int	fd;

	if (ac != 2)
		error_msg("Number of arguments wrong!", NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_msg("No such file!\n", NULL);
	if (!ft_strnfind(av[1], ".ber", 4))
		error_msg("Wrong file type, pleas use .ber instead", NULL);
	return (get_map(fd, layout));
}

void	check_layout(char *line, t_err *map_err, t_lay *layout, int is_last)
{
	if (!layout->n_col)
		layout->n_col = ft_strlen(line) - 1;
	if (layout->n_col && ((layout->n_col != (int)ft_strlen(line) - 1 && \
			ft_strchr(line, '\n')) || (layout->n_col != (int)ft_strlen(line) && \
			!ft_strchr(line, '\n'))))
		map_err->inv_rowlen = 1;
	if (line[0] != '1' || line[layout->n_col - 1] != '1' || \
			(ft_countchar(line, '1') != layout->n_col && is_last))
		map_err->inv_borders = 1;
	layout->n_exit += ft_countchar(line, 'E');
	layout->n_pl += ft_countchar(line, 'P');
	layout->n_en += ft_countchar(line, 'e');
	layout->n_collect += ft_countchar(line, 'C');
	map_err->inv_n_exits = layout->n_exit < 1;
	map_err->inv_n_players = layout->n_pl != 1;
	map_err->inv_n_collect = layout->n_collect < 1;
	while (line && *line)
	{
		if (!ft_strchr("01CEPe\n", *line))
			map_err->inv_char = 1;
		line++;
	}
}

void	readlayout(int fd, t_err *map_err, t_lay *layout, char **map_str)
{
	char	*line;
	char	*last_line;

	line = NULL;
	last_line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (!layout->n_col)
				error_msg("This map is so empty :O", NULL);
			else
				check_layout(last_line, map_err, layout, 1);
			free(last_line);
			break ;
		}
		free(last_line);
		check_layout(line, map_err, layout, !layout->n_row);
		last_line = ft_substr(line, 0, ft_strlen(line));
		*map_str = ft_str_add(*map_str, line);
		layout->n_row++;
	}
}

int	maybe_print_error(t_err *map_err, char **map_str)
{
	if (map_err->inv_rowlen)
		error_msg("Rectangular the map it is not!", map_str);
	if (map_err->inv_borders)
		error_msg("Surrounded by walls the map must be!", map_str);
	if (map_err->inv_char)
		error_msg("Only accept this char(s): 01CEPe", map_str);
	if (map_err->inv_n_exits)
		error_msg("Invalid number of exits!", map_str);
	if (map_err->inv_n_players)
		error_msg("There should be only one player!", map_str);
	if (map_err->inv_n_collect)
		error_msg("There has to be at least one collectible!", map_str);
	return (0);
}
