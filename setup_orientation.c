/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_orientation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:24:01 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/15 08:23:26 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

void	set_orient(t_object *obj, char **str)
{
	obj->orient->or_x = arc_atof((char *) str[0]);
	obj->orient->or_y = arc_atof((char *) str[1]);
	obj->orient->or_z = arc_atof((char *) str[2]);
}

int	get_orient(char *orient, t_object *obj)
{
	char	**str;
	int		i;
	int		err;

	str = ft_split(orient, ',');
	if (!str)
		return (-1);
	i = 0;
	err = 0;
	while (str[i] != NULL)
	{
		if (arc_atof((char *) str[i]) < -1 || \
			arc_atof((char *) str[i]) > 1)
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
