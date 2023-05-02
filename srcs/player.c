/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:35:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 17:21:03 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_object	*new_player(t_game *data)
{
	t_object	*player;

	player = malloc(sizeof(t_object));
	if (!player)
		return (NULL);
	player->type = 'P';
	player->life = 1;
	object_init(data, player, 'P');
	player->move.ismov = 0;
	player->move.dir = 1;
	player->move.isjump = 0;
	player->speed = 5;
	player->gravity_force = 0;
	player->jump.accel_jump = 1;
	player->jump.max_jump_speed = 17;
	player->jump.jump_decel = 0;
	return (player);
}

int	player_jump(t_game *data, int flag)
{
	int			keep_1;
	int			temp;

	keep_1 = data->player->jump.jump_decel;
	data->player->jump.jump_decel += data->player->jump.accel_jump;
	if (data->player->jump.max_jump_speed - data->player->jump.jump_decel <= 0 \
	&& flag)
	{
		data->player->move.isjump = 0;
		data->player->jump.jump_decel = 0;
		return (0);
	}
	if (!flag)
	{
		temp = data->player->jump.max_jump_speed - \
		data->player->jump.jump_decel;
		data->player->jump.jump_decel = keep_1;
		return (temp);
	}
	return (data->player->jump.max_jump_speed - data->player->jump.jump_decel);
}
