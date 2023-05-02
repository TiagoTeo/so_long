/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canva.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:54:03 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:29:33 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_color(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

void	my_mlx_pixel_put(t_img *canva, int x, int y, int color)
{
	char	*dst;

	if (color == TRANSPARENT)
		return ;
	dst = canva->addr + (y * canva->line_length + x * \
	(canva->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	put_img_to_canva(t_img *canva, t_img *img, int x1, int y1)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_mlx_pixel_put(canva, x1 + x, y1 + y, get_color(img, x, y));
			x++;
		}
		y++;
	}
}

t_img	*new_canva(t_game *data)
{
	t_img	*canva;

	canva = malloc(sizeof(t_img));
	if (!canva)
		return (NULL);
	canva->img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	canva->width = data->width;
	canva->height = data->height;
	canva->addr = mlx_get_data_addr(canva->img, &canva->bits_per_pixel, \
		&canva->line_length, &canva->endian);
	return (canva);
}

void	free_canva(t_game *data)
{
	mlx_destroy_image(data->mlx_ptr, data->canva->img);
	free(data->canva);
}
