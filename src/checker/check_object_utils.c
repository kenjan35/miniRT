/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:39:33 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:20:40 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	init_nbr_element(int nbr[])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		nbr[i] = 0;
		i++;
	}
}

void	set_nbr_element(int nbr[], t_object *obj)
{
	if (obj->id[0] == 'A')
		nbr[0]++;
	else if (obj->id[0] == 'C')
		nbr[1]++;
	else if (obj->id[0] == 'L')
		nbr[2]++;
	else if (obj->id[0] == 's')
		nbr[3]++;
	else if (obj->id[0] == 'p')
		nbr[4]++;
	else
		nbr[5]++;
}

int	check_element(t_list **list)
{
	t_list		*tmp;
	t_object	*obj;
	int			nbr[6];

	tmp = *list;
	if (!(list) || !(*list))
		return (0);
	init_nbr_element(nbr);
	while (tmp)
	{
		obj = (t_object *)(tmp->content);
		if (!obj)
			break ;
		set_nbr_element(nbr, obj);
		tmp = tmp->next;
	}
	if (nbr[0] != 1 || nbr[1] != 1 || nbr[2] != 1)
		return (0);
	if (nbr[3] == 0 && nbr[4] == 0 && nbr[5] == 0)
		return (0);
	return (1);
}
