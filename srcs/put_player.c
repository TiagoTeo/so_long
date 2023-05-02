/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:13:52 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 16:06:07 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_player_2(t_game *data, int *side)
{
	if (data->player->move.dir == 1)
		*side = 1;
	if (data->player->move.dir == 3)
		*side = -1;
	if (!check_object_colision(data, data->player))
		move_object(data, data->player);
	if (data->player->move.dir == 2 && data->player->move.ismov)
	{
		put_img_to_canva(data->canva, data->sprites.idle_player_right->content, \
		data->player->x, data->player->y);
		print_map(data, 1);
	}
	if (data->player->move.dir == 1 && data->player->move.ismov && \
	on_ground(data, data->player))
		put_moving_animation(data->sprites.run_player_right, 7, 0, \
		data->player);
	if (data->player->move.dir == 3 && data->player->move.ismov && \
	on_ground(data, data->player))
		put_moving_animation(data->sprites.run_player_left, 7, 0, \
		data->player);
}

void	put_player_3(t_game *data, int *side, int *frame_left, int *frame_right)
{
	if (data->player->move.isjump && *side == -1)
	{
		*frame_left += 1;
		if (*frame_left < 8)
			put_img_to_canva(data->canva, \
				data->sprites.jump_player_left->content, data->player->x, \
				data->player->y);
		else
			put_img_to_canva(data->canva, \
				data->sprites.jump_player_left->next->content, data->player->x, \
				data->player->y);
	}
	if (data->player->move.isjump && *side == 1)
	{
		*frame_right += 1;
		if (*frame_right < 8)
			put_img_to_canva(data->canva, \
				data->sprites.jump_player_right->content, data->player->x, \
				data->player->y);
		else
			put_img_to_canva(data->canva, \
				data->sprites.jump_player_right->next->content, \
				data->player->x, data->player->y);
	}
}

void	put_player_4(t_game *data, int *side)
{
	if (!on_ground(data, data->player) && *side == 1 && \
	!data->player->move.isjump)
		put_img_to_canva(data->canva, \
			&data->sprites.player_falling_right, data->player->x, \
			data->player->y);
	if (!on_ground(data, data->player) && *side == -1 && \
	!data->player->move.isjump)
		put_img_to_canva(data->canva, \
			&data->sprites.player_falling_left, data->player->x, \
			data->player->y);
	if (!data->player->move.ismov && on_ground(data, data->player) && \
	!data->player->move.isjump && !(data->n_frames % (data->g_rate)))
	{
		if (*side == 1)
			put_animation_idle(data->sprites.idle_player_right, 8, \
			data->player, 0);
		else
			put_animation_idle(data->sprites.idle_player_left, 8, \
			data->player, 0);
	}
}

void	put_player(t_game *data)
{
	int static	side;
	int static	frame_right;
	int static	frame_left;

	if (!data->player->life)
	{
		if (data->player->move.dir == 3)
			put_animation_one_time(data->sprites.player_dying_left, 5, \
			data->player, 0);
		else
			put_animation_one_time(data->sprites.player_dying_right, 5, \
			data->player, 0);
		return ;
	}
	if (!data->player->move.isjump)
	{
		frame_left = 0;
		frame_right = 0;
	}
	put_player_2(data, &side);
	put_player_3(data, &side, &frame_left, &frame_right);
	put_player_4(data, &side);
}
