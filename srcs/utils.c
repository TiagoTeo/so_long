/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiago-s <mtiago-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:36:15 by mtiago-s          #+#    #+#             */
/*   Updated: 2023/04/05 15:33:45 by mtiago-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//funtcion to add to libft
int	ft_strnfind(char *s1, char *s2, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!n || !s1 || !s2)
		return (-1);
	while (s1[i])
	{
		if (s1[i] == s2[j])
			j++;
		else if (j && s1[i])
			j = 0;
		if (j == n)
			return (1);
		i++;
	}
	return (0);
}

//funtcion to add to libft
char	*ft_str_add(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*res;

	i = 0;
	if (!s2)
		return (NULL);
	s1_len = (int)ft_strlen(s1);
	s2_len = (int)ft_strlen(s2);
	res = (char *)malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			res[i] = s1[i];
		if (i < s2_len)
			res[s1_len + i] = s2[i];
		i++;
	}
	res[s1_len + s2_len] = 0;
	free(s1);
	free(s2);
	return (res);
}

//funtcion to add to libft
int	ft_countchar(char *str, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			res++;
		i++;
	}
	return (res);
}

//function to add to libft
void	ft_free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

//function to add to libft
char	**ft_matrix_dup(char **m)
{
	char	**res;
	int		j;

	j = 0;
	while (m[j])
		j++;
	res = malloc(sizeof(char *) * j + 1);
	if (!res)
		return (NULL);
	res[j] = NULL;
	while (--j >= 0)
		res[j] = ft_strdup(m[j]);
	return (res);
}
