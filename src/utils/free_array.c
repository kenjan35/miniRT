/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:58:39 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:22:33 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_object(void *content)
{
	t_object	*obj;

	if (content == NULL)
		return ;
	obj = (t_object *)content;
	if (obj == NULL)
		return ;
	if (obj->coord)
		free(obj->coord);
	if (obj->color)
		free(obj->color);
	if (obj->orient)
		free(obj->orient);
	free(obj);
}

void	free_array(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
