/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_patrol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:04:07 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:36:24 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	idle_enemy(t_game *data, t_object *enemy, int i, int *move)
{
	if (enemy->move.dir == 1)
		put_animation_idle(data->sprites.idle_enemy_right, 8, enemy, i);
	if (enemy->move.dir == 3)
		put_animation_idle(data->sprites.idle_enemy_left, 8, enemy, i);
	if (!(data->n_frames % (data->g_rate * (i * 50))))
	{
		*move = 0;
		enemy->move.ismov++;
		if (enemy->move.dir == 1)
			enemy->move.dir = 3;
		else
			enemy->move.dir = 1;
	}
}

int	enemy_patrol(t_game *data, t_object *enemy, int i)
{
	static int	attack[10];
	static int	move[10];

	if (attack[i] >= 32)
		enemy->move.isjump = 0;
	if (move[i] >= 50 || (move[i] != 0 && !on_ground(data, enemy)))
		enemy->move.ismov = 0;
	if (enemy->move.ismov && !enemy->move.isjump)
		move_enemy(data, enemy, i, &move[i]);
	if (!enemy->move.ismov && !enemy->move.isjump)
		idle_enemy(data, enemy, i, &move[i]);
	if (enemy->move.isjump)
	{
		attack[i]++;
		if (data->player->move.dir == 1)
			put_animation_idle(data->sprites.enemy_attack_left, 4, \
			enemy, i + 10);
		if (data->player->move.dir == 3)
			put_animation_idle(data->sprites.enemy_attack_right, 4, \
			enemy, i + 10);
	}
	return (0);
}
