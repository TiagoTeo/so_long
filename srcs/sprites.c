/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:56:12 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:37:11 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*add_number_xpm(char *s1, char c)
{
	char	*res;
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = ".xpm";
	res = malloc((ft_strlen(s1) + 6));
	if (!res)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = c;
	i++;
	while (temp[j])
	{
		res[i + j] = temp[j];
		j++;
	}
	res[i + j] = 0;
	return (res);
}

void	load_img(t_img *img, char *filename)
{
	img->img = mlx_xpm_file_to_image(game()->mlx_ptr, filename, \
	&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
}

t_sprite	initsprites_2(t_game *data)
{
	data->sprites.jump_player_left = load_animation(data, \
		"sprites/zombie/jump_animation/left/", 2, 0);
	data->sprites.jump_player_right = load_animation(data, \
		"sprites/zombie/jump_animation/right/", 2, 0);
	data->sprites.idle_collect = load_animation(data, \
		"sprites/undead icons/idle_animation/", 4, 0);
	data->sprites.idle_enemy_left = load_animation(data, \
		"sprites/soldier/idle_animation/left/", 8, 0);
	data->sprites.idle_enemy_right = load_animation(data, \
		"sprites/soldier/idle_animation/right/", 8, 0);
	data->sprites.run_enemy_left = load_animation(data, \
		"sprites/soldier/run_animation/left/", 8, 0);
	data->sprites.run_enemy_right = load_animation(data, \
		"sprites/soldier/run_animation/right/", 8, 0);
	data->sprites.player_dying_left = load_animation(data, \
		"sprites/zombie/dying_animation/left/", 5, 0);
	data->sprites.player_dying_right = load_animation(data, \
		"sprites/zombie/dying_animation/right/", 5, 0);
	data->sprites.enemy_attack_left = load_animation(data, \
		"sprites/soldier/attack_animation/left/", 4, 0);
	data->sprites.enemy_attack_right = load_animation(data, \
		"sprites/soldier/attack_animation/right/", 4, 0);
	return (data->sprites);
}

t_sprite	initsprites(t_game *data)
{
	load_img(&data->sprites.wall, "sprites/Industrial/Tile_1.xpm");
	load_img(&data->sprites.exit, "sprites/Industrial/Tile_E.xpm");
	load_img(&data->sprites.empty, "sprites/Industrial/Tile_0.xpm");
	load_img(&data->sprites.player_falling_right, \
	"sprites/zombie/falling_animation/right/1.xpm");
	load_img(&data->sprites.player_falling_left, \
	"sprites/zombie/falling_animation/left/1.xpm");
	data->sprites.idle_player_left = load_animation(data, \
		"sprites/zombie/idle_animation/left/", 8, 0);
	data->sprites.idle_player_right = load_animation(data, \
		"sprites/zombie/idle_animation/right/", 8, 0);
	data->sprites.run_player_left = load_animation(data, \
		"sprites/zombie/run_animation/left/", 7, 0);
	data->sprites.run_player_right = load_animation(data, \
		"sprites/zombie/run_animation/right/", 7, 0);
	return (initsprites_2(data));
}

int	free_sprites(t_game *data)
{
	mlx_destroy_image(data->mlx_ptr, data->sprites.empty.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.wall.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.exit.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.player_falling_left.img);
	mlx_destroy_image(data->mlx_ptr, data->sprites.player_falling_right.img);
	free_animation(data, data->sprites.idle_player_left);
	free_animation(data, data->sprites.idle_player_right);
	free_animation(data, data->sprites.run_player_left);
	free_animation(data, data->sprites.run_player_right);
	free_animation(data, data->sprites.jump_player_left);
	free_animation(data, data->sprites.jump_player_right);
	free_animation(data, data->sprites.idle_collect);
	free_animation(data, data->sprites.idle_enemy_left);
	free_animation(data, data->sprites.idle_enemy_right);
	free_animation(data, data->sprites.run_enemy_left);
	free_animation(data, data->sprites.run_enemy_right);
	free_animation(data, data->sprites.player_dying_left);
	free_animation(data, data->sprites.player_dying_right);
	return (0);
}
