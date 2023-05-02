/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:15:54 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/04 17:17:09 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_colision_point(t_game *data, int x, int y, t_object *object)
{
	if (object->move.dir == 2)
		return (0);
	if (object->move.dir == 1)
		x += object->speed;
	if (object->move.dir == 3)
		x -= object->speed;
	if (object->type == 'P' && object->move.isjump)
		y -= player_jump(data, 0);
	x /= SIZE;
	y /= SIZE;
	if (data->map[y][x] == '1' || data->map[y][x] == 'E')
	{
		if (object->type == 'P' && object->move.isjump)
			object->move.isjump = 0;
		return (1);
	}
	if (object->type == 'P' && data->map_og[y][x] == 'C')
		kill_collect(data, x, y);
	return (0);
}

int	check_object_colision(t_game *data, t_object *object)
{
	int		i;
	int		temp_x;
	int		temp_y;

	i = 0;
	temp_x = object->x + 22;
	temp_y = object->y;
	i += check_colision_point(data, temp_x, temp_y, object);
	temp_x = object->x + 40;
	temp_y = object->y;
	i += check_colision_point(data, temp_x, temp_y, object);
	temp_x = object->x + 40;
	temp_y = object->y + SIZE - 1;
	i += check_colision_point(data, temp_x, temp_y, object);
	temp_x = object->x + 22;
	temp_y = object->y + SIZE - 1;
	i += check_colision_point(data, temp_x, temp_y, object);
	return (i);
}

void	move_object(t_game *data, t_object *object)
{
	if (object->move.ismov || (object->type == 'P' && object->move.isjump))
	{
		if (object->move.dir == 1)
			object->x += object->speed;
		if (object->move.dir == 3)
			object->x -= object->speed;
		if (object->move.dir == 2)
			object->y += 1;
		if (object->type == 'P' && object->move.isjump)
			object->y -= player_jump(data, 1);
		if (data->player->life && object == data->player)
			data->moves++;
	}
}

int	object_init(t_game *data, t_object *object, char c)
{
	int		x;
	int		y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == c)
			{
				data->map[y][x] = '0';
				object->x = x * SIZE;
				object->y = y * SIZE;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}
