/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:05:05 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/03/29 18:29:27 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_object	*new_collect(t_game *data)
{
	t_object	*collect;

	collect = malloc(sizeof(t_object));
	if (!collect)
		return (NULL);
	collect->type = 'C';
	collect->life = 1;
	object_init(data, collect, 'C');
	collect->gravity_force = 0;
	return (collect);
}

void	put_collect_idle(t_game *data, t_list *animation, int *n, \
t_object *object)
{
	int		j;
	t_list	*temp;

	j = 0;
	temp = animation;
	while (j < *n)
	{
		temp = temp->next;
		j++;
	}
	if (temp->content)
		put_img_to_canva(data->canva, temp->content, object->x, object->y);
}

t_list	*init_collects(t_game *data)
{
	int		i;
	t_list	*res;

	res = NULL;
	i = 0;
	while (++i <= data->layout.n_collect)
		ft_lstadd_back(&res, ft_lstnew(new_collect(data)));
	return (res);
}

int	put_collect(t_game *data)
{
	t_list				*start;
	t_object			*temp;
	int					i;
	static int			frame;

	temp = NULL;
	i = 0;
	start = data->collect;
	while (++i <= data->layout.n_collect)
	{
		temp = (t_object *)data->collect->content;
		if (temp->life)
			put_collect_idle(data, data->sprites.idle_collect, &frame, temp);
		data->collect = data->collect->next;
	}
	if (!(data->n_frames % (data->g_rate * 10)))
		frame++;
	if (frame > 3)
		frame = 0;
	data->collect = start;
	return (0);
}

int	kill_collect(t_game *data, int x, int y)
{
	t_list		*start;
	t_object	*temp;
	int			i;

	i = 0;
	start = data->collect;
	while (++i <= data->layout.n_collect)
	{
		temp = (t_object *)data->collect->content;
		if (temp->x / SIZE == x && temp->y / SIZE == y)
			temp->life = 0;
		data->collect = data->collect->next;
	}
	data->collect = start;
	return (0);
}
