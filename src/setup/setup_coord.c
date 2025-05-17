/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:26:17 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 22:42:12 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_coord(t_object *obj, char **str)
{
	obj->coord->x = arc_atof((char *) str[0]);
	obj->coord->y = arc_atof((char *) str[1]);
	obj->coord->z = arc_atof((char *) str[2]);
}

int	get_coord(char *coord, t_object *obj)
{
	char	**str;
	int		i;
	int		err;

	str = ft_split(coord, ',');
	if (!str || check_comma(str, coord) == 0)
		return (-1);
	i = 0;
	err = 0;
	while (str[i] != NULL)
	{
		if (arc_atof((char *) str[i]) < -1000000000 || \
			arc_atof((char *) str[i]) > 1000000000)
		{
			err = -1;
			break ;
		}
		i++;
	}
	if (err != -1 && i == 3)
		set_coord(obj, str);
	else if (i < 3)
		err = -1;
	free_array(str);
	return (err);
}
