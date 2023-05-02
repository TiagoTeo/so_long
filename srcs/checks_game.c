/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:29:07 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:32:17 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_collect_dead(t_game *data)
{
	t_list				*start;
	t_object			*temp;
	int					i;

	temp = NULL;
	i = 0;
	start = data->collect;
	while (++i <= data->layout.n_collect)
	{
		temp = (t_object *)data->collect->content;
		if (temp->life)
		{
			data->collect = start;
			return (0);
		}
		data->collect = data->collect->next;
	}
	data->collect = start;
	return (1);
}

int	check_ending(t_game *data)
{
	int			x;
	int			y;

	if (!check_collect_dead(data))
		return (0);
	x = (data->player->x + 31) / SIZE;
	y = (data->player->y) / SIZE;
	if (data->map[y][x] == 'E')
		return (2);
	x = (data->player->x + 22) / SIZE;
	y = (data->player->y + SIZE) / SIZE;
	if (data->map[y][x] == 'E' && \
	data->map[y][(data->player->x + 40) / SIZE] == 'E')
		return (1);
	return (0);
}
