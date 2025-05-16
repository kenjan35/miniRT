/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:23:17 by maandria          #+#    #+#             */
/*   Updated: 2025/05/16 14:44:12 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_object	**create_object(t_prog *prog)
{
	t_object	*all_object[100];
	t_object	**result;
	t_object	*object;
	t_list		*tmp;
	int			i;

	i = 0;
	tmp = prog->obj;
	while (prog->obj)
	{
		object = prog->obj->content;
		if (!ft_strncmp(object->id, "sp", 2) || !ft_strncmp(object->id, "pl", 2)
			|| !ft_strncmp(object->id, "cy", 2))
		{
			all_object[i] = object;
			printf("build object : Id = %s\n", all_object[i]->id);
			i++;
		}
		prog->obj = prog->obj->next;
	}
	prog->obj = tmp;
	result = all_object;
	return (result);
}

void	put_object(t_prog *prog)
{
	t_object	**all_object;
	int			i;

	i = 0;
	all_object = create_object(prog);
	while (all_object[i])
	{
		if (!ft_strncmp(all_object[i]->id, "pl", 2))
			printf("pl[%d]\n", i);
		if (!ft_strncmp(all_object[i]->id, "sp", 2))
			printf("sp[%d]\n", i);
		i++;
	}
}
