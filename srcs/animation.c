/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:41:08 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 16:02:52 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_list	*load_animation(t_game *data, char *path, int number, int i)
{
	t_list	*res;
	char	*path_bk;
	char	c;
	char	*temp;
	t_img	*img_temp;

	res = NULL;
	i = 0;
	(void)data;
	while (++i <= number)
	{
		path_bk = ft_strdup(path);
		c = i + 48;
		temp = add_number_xpm(path_bk, c);
		img_temp = malloc(sizeof(t_img));
		load_img(img_temp, temp);
		ft_lstadd_back(&res, ft_lstnew(img_temp));
		free(temp);
		free(path_bk);
	}
	return (res);
}

void	free_animation(t_game *data, t_list *lst)
{
	t_list	*temp;
	t_img	*img_temp;

	temp = NULL;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		img_temp = temp->content;
		if (data && img_temp)
		{
			mlx_destroy_image(data->mlx_ptr, img_temp->img);
			free(img_temp);
		}
		free(temp);
	}
}

void	put_animation_idle(t_list *animation, int n, t_object *object, int id)
{
	static int	i[100];
	int			j;
	t_list		*temp;

	j = 0;
	temp = animation;
	while (j < i[id])
	{
		temp = temp->next;
		j++;
	}
	if (temp->content)
	{
		put_img_to_canva(game()->canva, \
		temp->content, object->x, object->y);
		if (!(game()->n_frames % (game()->g_rate * n)))
			i[id]++;
	}
	if (i[id] == n - 1)
		i[id] = 0;
}

void	put_moving_animation(t_list *animation, int n, int id, t_object *object)
{
	static int	i[10];
	int			j;
	t_list		*temp;

	j = 0;
	temp = animation;
	while (j < i[id])
	{
		temp = temp->next;
		j++;
	}
	if (temp->content)
	{
		put_img_to_canva(game()->canva, \
		temp->content, object->x, object->y);
		if (!(game()->n_frames % (game()->g_rate * n)))
			i[id]++;
	}
	if (i[id] == n - 1)
		i[id] = 0;
}

void	put_animation_one_time(t_list *animation, int n, t_object *object, \
int id)
{
	static int	i[10];
	int			j;
	t_list		*temp;

	j = 0;
	temp = animation;
	while (j < i[id] && temp->next)
	{
		temp = temp->next;
		j++;
	}
	if (temp->content)
	{
		put_img_to_canva(game()->canva, \
		temp->content, object->x, object->y);
		if (!(game()->n_frames % (game()->g_rate * (n * 2)) && i[id] < n - 1))
			i[id]++;
	}
}
