/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 19:14:00 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/03/29 19:14:26 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keyrele(int keysym, t_game *data)
{
	if (data->player->life && data->player->move.dir != 2)
	{
		if (keysym == KEY_A)
		{
			data->player->move.ismov = 0;
			data->player->move.dir = 3;
		}
		if (keysym == KEY_D)
		{
			data->player->move.ismov = 0;
			data->player->move.dir = 1;
		}		
	}
	return (0);
}

int	handle_keypress(int keysym, t_game *data)
{
	if (keysym == KEY_ESC || keysym == KEY_Q)
		end_game(data);
	if (data->player->life)
	{
		if (keysym == KEY_S && check_ending(data) && ++data->player->move.ismov)
			data->player->move.dir = 2;
		if (data->player->move.dir != 2)
		{
			if (keysym == KEY_A && ++data->player->move.ismov)
				data->player->move.dir = 3;
			if (keysym == KEY_D && ++data->player->move.ismov)
				data->player->move.dir = 1;
			if ((keysym == KEY_W || keysym == KEY_ESPACE) && \
				on_ground(data, data->player) && ++data->player->move.isjump)
				data->player->move.dir = 4;
		}
	}
	return (0);
}
