/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:31:12 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/15 08:21:16 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

int	check_sphere(char **split, t_object *obj)
{
	if (!split[1] || !split[2] || !split[3])
		return (-1);
	if (get_coord(split[1], obj) == -1)
		return (-1);
	if (get_size(split[2], 100) == -1 || \
		get_size(split[2], 100) == 0)
		return (-1);
	if (get_color(split[3], obj) == -1)
		return (-1);
	obj->id[0] = 's';
	obj->id[1] = 'p';
	obj->id[2] = '\0';
	obj->size[0] = arc_atof((char *) split[2]);
	return (1);
}

int	check_plane(char **split, t_object *obj)
{
	if (!split[1] || !split[2] || !split[3])
		return (-1);
	if (get_coord(split[1], obj) == -1)
		return (-1);
	if (get_orient(split[2], obj) == -1)
		return (-1);
	if (get_color(split[3], obj) == -1)
		return (-1);
	obj->id[0] = 'p';
	obj->id[1] = 'l';
	obj->id[2] = '\0';
	return (1);
}

int	check_cylinder(char **split, t_object *obj)
{
	if (!split[1] || !split[2] || !split[3] || !split[4] || !split[5])
		return (-1);
	if (get_coord(split[1], obj) == -1)
		return (-1);
	if (get_orient(split[2], obj) == -1)
		return (-1);
	if (get_size(split[3], 100) == -1 || \
		get_size(split[3], 100) == 0)
		return (-1);
	if (get_size(split[4], 100) == -1 || \
		get_size(split[4], 100) == 0)
		return (-1);
	if (get_color(split[5], obj) == -1)
		return (-1);
	obj->id[0] = 'c';
	obj->id[1] = 'y';
	obj->id[2] = '\0';
	obj->size[0] = arc_atof((char *) split[3]);
	obj->size[1] = arc_atof((char *) split[4]);
	return (1);
}
