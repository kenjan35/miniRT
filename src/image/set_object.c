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

t_list	*all_shape(t_prog *prog)
{
	t_list		*obj;
	t_list		*tab;
	t_list		*tmp;
	t_object	*content;

	if (!prog || prog->obj == NULL)
		return (NULL);
	obj = prog->obj;
	tab = NULL;
	while (obj)
	{
		content = (t_object *) obj->content;
		if (content->id[0] != 'A' && content->id[0] != 'L' && content->id[0] != 'C')
		{
			tmp = ft_lstnew(obj->content);
			if (!tmp)
				return (NULL);
			ft_lstadd_back(&tab, tmp);
		}
		obj = obj->next;
	}
	return (tab);
}
