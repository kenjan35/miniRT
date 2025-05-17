/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_orientation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:24:01 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 22:41:05 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_orient(t_object *obj, char **str)
{
	double	norm;
	t_coord	cy_axis;

	obj->orient->or_x = arc_atof((char *) str[0]);
	obj->orient->or_y = arc_atof((char *) str[1]);
	obj->orient->or_z = arc_atof((char *) str[2]);
	cy_axis = orient2coord(obj->orient);
	norm = op_norm(cy_axis);
	obj->orient->or_x /= norm;
	obj->orient->or_y /= norm;
	obj->orient->or_z /= norm;
}

int	check_comma(char **str, char *orient)
{
	int	i;

	i = 0;
	while (orient[i] != '\0')
	{
		if (orient[i] == ',')
		{
			if (orient[i + 1] && orient[i + 1] == ',')
			{
				free_array(str);
				return (0);
			}
			else if (!orient[i + 1])
			{
				free_array(str);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	get_orient(char *orient, t_object *obj)
{
	char	**str;
	int		i;
	int		err;

	str = ft_split(orient, ',');
	if (!str || check_comma(str, orient) == 0)
		return (-1);
	i = 0;
	err = 0;
	while (str[i] != NULL)
	{
		if ((arc_atof((char *) str[i]) < -1 || \
			arc_atof((char *) str[i]) > 1))
		{
			err = -1;
			break ;
		}
		i++;
	}
	if (err != -1 && i == 3)
		set_orient(obj, str);
	else if (i < 3)
		err = -1;
	free_array(str);
	return (err);
}

t_coord	orient2coord(t_orient *orient)
{
	t_coord	result;

	result.x = orient->or_x;
	result.y = orient->or_y;
	result.z = orient->or_z;
	return (result);
}
