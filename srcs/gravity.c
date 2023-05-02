/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:10:01 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 17:21:11 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	apply_gravity(t_game *data)
{
	int	y;

	y = 0;
	data->player->gravity_force += data->gravity->accel_gravity;
	if (data->player->gravity_force > data->gravity->max_gravity)
		data->player->gravity_force = data->gravity->max_gravity;
	data->player->y += data->player->gravity_force;
	y = (data->player->y + SIZE - 1) / SIZE;
	if (data->map[y][(data->player->x + 22) / SIZE] == '1' || \
	data->map[y][(data->player->x + 40) / SIZE] == '1')
		data->player->y = (data->player->y / SIZE) * SIZE;
	if (data->map[y][(data->player->x + 22) / SIZE] == 'E' || \
	data->map[y][(data->player->x + 40) / SIZE] == 'E')
		data->player->y = (data->player->y / SIZE) * SIZE;
}

int	on_ground(t_game *data, t_object *object)
{
	int	x;
	int	y;
	int	res;

	res = 0;
	x = (object->x + 40) / SIZE;
	y = (object->y + SIZE) / SIZE;
	if (data->map[y][x] == '1' || data->map[y][x] == 'E')
		res++;
	x = (object->x + 22) / SIZE;
	if (data->map[y][x] == '1' || data->map[y][x] == 'E')
		res++;
	if (res)
		object->gravity_force = 0;
	return (res);
}

t_gravity	*init_gravity(void)
{
	t_gravity	*res;

	res = malloc(sizeof(t_gravity));
	if (!res)
		return (NULL);
	res->accel_gravity = 1;
	res->max_gravity = 15;
	return (res);
}
