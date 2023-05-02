/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:38:16 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 19:27:54 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_game(t_game *data)
{
	if (!(data->n_frames % data->g_rate) && data->layout.n_en)
	{
		check_enemys(data);
		put_enemies(data);
	}
	if (!(data->n_frames % data->g_rate) || data->n_frames == 3)
	{
		if (on_ground(data, data->player) && data->player->move.dir == 4)
			data->player->move.ismov = 0;
		put_player(data);
	}
	if (!(data->n_frames % data->g_rate) && !data->player->move.isjump)
	{
		if (on_ground(data, data->player))
			data->player->jump.jump_decel = 0;
		else
			apply_gravity(data);
	}
	if (!(data->n_frames % data->g_rate) && check_ending(data) == 2)
		end_game(data);
	if (!(data->n_frames % (data->g_rate * 180)) && !data->player->life)
		end_game(data);
}

char	*put_movements(int nbr)
{
	int		temp;
	int		i;
	char	*res;

	temp = nbr;
	i = 1;
	while (temp >= 10)
	{
		i++;
		temp /= 10;
	}
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		return (NULL);
	res[i] = 0;
	while (--i >= 0)
	{
		res[i] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (res);
}

int	render(t_game *data)
{
	char	*res;

	res = NULL;
	data->n_frames++;
	if ((data->redraw && !(data->n_frames % data->g_rate)) || \
	(!(data->n_frames % (data->g_rate))))
	{
		print_map(data, 0);
		data->redraw = 0;
	}
	update_game(data);
	if (!(data->n_frames % data->g_rate))
	{
		res = put_movements(data->moves);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->canva->img, 0, 0);
		mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 36, \
		0xFFFFF, res);
		free(res);
	}
	return (0);
}

t_game	*game(void)
{
	static t_game	data;

	return (&data);
}

int	main(int ac, char **av)
{
	t_lay	layout;

	(game()->map) = check_map(ac, av, &layout);
	game()->map_og = ft_matrix_dup(game()->map);
	game_init(game(), layout);
	return (0);
}
