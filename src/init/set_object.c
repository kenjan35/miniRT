/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:48:08 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/18 09:54:11 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_shape_size(t_prog *prog, char *id_search)
{
	t_list		*obj;
	t_object	*content;
	int			len;

	len = 0;
	obj = prog->obj;
	while (obj)
	{
		content = (t_object *) obj->content;
		if (ft_strncmp(content->id, id_search, 3) == 0)
			len++;
		obj = obj->next;
	}
	return (len);
}

t_object	*doppel_object(t_object *src)
{
	t_object	*new;

	if (!src)
		return (NULL);
	new = init_object();
	if (!new)
		return (NULL);
	ft_memcpy(new->id, src->id, 3);
	new->time = src->time;
	new->num = src->num;
	new->size[0] = src->size[0];
	new->size[1] = src->size[1];
	*(new->coord) = *(src->coord);
	*(new->color) = *(src->color);
	*(new->orient) = *(src->orient);
	return (new);
}

t_list	*all_shape(t_prog *prog)
{
	t_list		*obj;
	t_list		*tab;
	t_object	*content;
	t_object	*doppel;

	if (!prog || prog->obj == NULL)
		return (NULL);
	obj = prog->obj;
	tab = NULL;
	while (obj)
	{
		content = (t_object *) obj->content;
		if (content->id[0] != 'A' && content->id[0] != 'L' && content->id[0] != 'C')
		{
			doppel = doppel_object(content);
			ft_lstadd_back(&tab, ft_lstnew(doppel));
		}
		obj = obj->next;
	}
	return (tab);
}
