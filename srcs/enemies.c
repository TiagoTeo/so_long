/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:55 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 16:05:42 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_object	*new_enemy(t_game *data)
{
	t_object	*enemy;

	enemy = malloc(sizeof(t_object));
	if (!enemy)
		return (NULL);
	enemy->type = 'e';
	enemy->life = 1;
	object_init(data, enemy, 'e');
	enemy->gravity_force = 0;
	enemy->move.ismov = 0;
	enemy->speed = 2;
	enemy->move.isjump = 0;
	enemy->move.dir = 1;
	return (enemy);
}

t_list	*init_enemies(t_game *data)
{
	int		i;
	t_list	*res;

	res = NULL;
	i = 0;
	while (++i <= data->layout.n_en)
		ft_lstadd_back(&res, ft_lstnew(new_enemy(data)));
	return (res);
}

void	move_enemy(t_game *data, t_object *enemy, int i, int *move)
{
	if (!check_object_colision(data, enemy))
	{
		move_object(data, enemy);
		*move += 1;
		if (enemy->move.dir == 1)
			put_moving_animation(data->sprites.run_enemy_right, \
			8, i, enemy);
		if (enemy->move.dir == 3)
			put_moving_animation(data->sprites.run_enemy_left, \
			8, i, enemy);
	}
	else
		enemy->move.ismov = 0;
}

int	put_enemies(t_game *data)
{
	t_list		*start;
	t_object	*temp;
	int			i;

	temp = NULL;
	i = 0;
	start = data->enemies;
	while (++i <= data->layout.n_en && data->enemies)
	{
		temp = (t_object *)data->enemies->content;
		if (temp->life)
			enemy_patrol(data, temp, i);
		data->enemies = data->enemies->next;
	}
	data->enemies = start;
	return (0);
}

int	check_enemys(t_game *data)
{
	t_list		*start;
	t_object	*temp;
	int			i;

	temp = NULL;
	i = 0;
	start = data->enemies;
	while (++i <= data->layout.n_en && data->enemies)
	{
		temp = (t_object *)data->enemies->content;
		if ((data->player->x + 31) / SIZE == (temp->x + 31) / SIZE && \
		(data->player->y + 31) / SIZE == (temp->y + 31) / SIZE && \
		++temp->move.isjump)
			data->player->life = 0;
		data->enemies = data->enemies->next;
	}
	data->enemies = start;
	return (0);
}
