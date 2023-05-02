/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:17:02 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:33:57 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_pos
{
	int	y;
	int	x;
}		t_pos;

void	find_letter(char **map, t_pos *pos, char c)
{
	pos->y = 0;
	while (map[pos->y])
	{
		pos->x = 0;
		while (map[pos->y][pos->x])
		{
			if (map[pos->y][pos->x] == c)
				return ;
			pos->x += 1;
		}
		pos->y += 1;
	}
}

void	check_surroundings(char **map, int y, int x, t_lay *layout)
{
	if (map[y][x] == 'C')
		layout->n_collect++;
	if (map[y + 1][x] == 'E')
		layout->n_exit++;
}

int	find_path(char **map, int y, int x, t_lay *layout)
{
	check_surroundings(map, y, x, layout);
	map[y][x] = '2';
	if (map[y][x + 1] != '1' && map[y][x + 1] != '2' && map[y][x + 1] != 'E')
		find_path(map, y, x + 1, layout);
	if (map[y][x - 1] != '1' && map[y][x - 1] != '2' && map[y][x - 1] != 'E')
		find_path(map, y, x - 1, layout);
	if (map[y - 1][x] != '1' && map[y - 1][x] != '2' && map[y - 1][x] != 'E')
		find_path(map, y - 1, x, layout);
	if (map[y + 1][x] != '1' && map[y + 1][x] != '2' && map[y + 1][x] != 'E')
		find_path(map, y + 1, x, layout);
	return (0);
}

int	check_path(char **map, t_lay layout)
{
	t_lay	temp_lay;
	t_pos	pos;
	char	**temp_map;

	temp_lay = new_layout();
	temp_map = ft_matrix_dup(map);
	find_letter(temp_map, &pos, 'P');
	find_path(temp_map, pos.y, pos.x, &temp_lay);
	ft_free_matrix(&temp_map);
	if (temp_lay.n_collect != layout.n_collect || \
	temp_lay.n_exit != layout.n_exit)
		error_msg("Zombie has no valid path grrrr", NULL);
	return (0);
}
