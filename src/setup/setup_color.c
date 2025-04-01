/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:12:55 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:21:27 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_color(t_object *obj, char **str)
{
	obj->color->red = (arc_atof((char *) str[0])) / 255;
	obj->color->green = (arc_atof((char *) str[1]) / 255);
	obj->color->blue = (arc_atof((char *) str[2]) / 255);
}

int	get_color(char *color, t_object *obj)
{
	char	**str;
	int		i;
	int		err;

	str = ft_split(color, ',');
	if (!str)
		return (-1);
	i = 0;
	err = 0;
	while (str[i] != NULL)
	{
		if (arc_atof((char *) str[i]) < 0 || arc_atof((char *) str[i]) > 255)
		{
			err = -1;
			break ;
		}
		i++;
	}
	if (err != -1 && i == 3)
		set_color(obj, str);
	else if (i < 3)
		err = -1;
	free_array(str);
	return (err);
}
