/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:31:12 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/21 10:14:46 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	check_ambient(char **split, t_object *obj)
{
	if (!split[1] || !split[2])
		return (-1);
	if (get_size(split[1], 1) == -1)
		return (-1);
	if (get_color(split[2], obj) == -1)
		return (-1);
	obj->id[0] = 'A';
	obj->id[1] = '\0';
	obj->size[0] = arc_atof((char *) split[1]);
	return (1);
}

int	check_camera(char **split, t_object *obj)
{
	if (!split[1] || !split[2] || !split[3])
		return (-1);
	if (get_coord(split[1], obj) == -1)
		return (-1);
	if (get_orient(split[2], obj) == -1)
		return (-1);
	if (get_size(split[3], 180) == -1)
		return (-1);
	obj->id[0] = 'C';
	obj->id[1] = '\0';
	obj->size[0] = ft_atoi((char *) split[3]);
	return (1);
}

int	check_light(char **split, t_object *obj)
{
	if (!split[1] || !split[2])
		return (-1);
	if (get_coord(split[1], obj) == -1)
		return (-1);
	if (get_size(split[2], 1) == -1)
		return (-1);
	obj->id[0] = 'L';
	obj->id[1] = '\0';
	obj->size[0] = ft_atoi((char *) split[2]);
	return (1);
}
