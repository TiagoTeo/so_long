/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:41:55 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/04 11:35:37 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_err	new_map_err(void)
{
	t_err	res;

	res.inv_rowlen = 0;
	res.inv_char = 0;
	res.inv_n_players = 0;
	res.inv_n_enemies = 0;
	res.inv_n_collect = 0;
	res.inv_n_exits = 0;
	res.inv_borders = 0;
	return (res);
}

char	**get_map(int fd, t_lay *layout)
{
	char	*map_str;
	char	**map;
	t_err	map_err;

	map = NULL;
	map_str = NULL;
	map_err = new_map_err();
	*layout = new_layout();
	readlayout(fd, &map_err, layout, &map_str);
	maybe_print_error(&map_err, &map_str);
	map = ft_split(map_str, '\n');
	check_path(map, *layout);
	free(map_str);
	return (map);
}

void	put_map(t_game *data, int x, int y, int flag)
{
	if (data->map[y][x] != '1' && !flag)
		put_img_to_canva(data->canva, &data->sprites.empty, x * SIZE, y * SIZE);
	if (data->map[y][x] == '1' && !flag)
		put_img_to_canva(data->canva, \
		&data->sprites.wall, x * SIZE, y * SIZE);
	if (data->map[y][x] == 'E')
		put_img_to_canva(data->canva, \
		&data->sprites.exit, x * SIZE, y * SIZE);
}

int	print_map(t_game *data, int flag)
{
	int	x;
	int	y;

	y = 0;
	(void) flag;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			put_map(data, x, y, flag);
			x++;
		}
		y++;
	}
	put_collect(data);
	return (0);
}
