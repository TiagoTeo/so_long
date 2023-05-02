/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:07:50 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/04 16:45:32 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_init(t_game *data, t_lay layout)
{
	data->mlx_ptr = mlx_init();
	data->layout = layout;
	data->win_ptr = mlx_new_window(data->mlx_ptr, layout.n_col * SIZE, \
					layout.n_row * SIZE, "so_long");
	new_game(data);
}

int	end_game(t_game *data)
{
	free_sprites(data);
	ft_free_matrix(&data->map);
	ft_free_matrix(&data->map_og);
	if (!data->player->life)
		printf("You dead for real now.\n");
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	printf("Game ended!\n");
	exit(0);
	return (0);
}

void	new_game(t_game *data)
{
	data->n_frames = 1;
	data->width = data->layout.n_col * SIZE;
	data->height = data->layout.n_row * SIZE;
	data->sprites = initsprites(data);
	data->g_rate = GAME_RATE;
	data->redraw = 1;
	data->moves = 0;
	data->player = new_player(data);
	data->collect = init_collects(data);
	data->gravity = init_gravity();
	if (data->layout.n_en)
		data->enemies = init_enemies(data);
	data->canva = new_canva(data);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_hook(data->win_ptr, 17, 0, end_game, data);
	mlx_hook(data->win_ptr, 02, (1L << 0), handle_keypress, data);
	mlx_hook(data->win_ptr, 03, (1L << 1), handle_keyrele, data);
	mlx_loop(data->mlx_ptr);
}
