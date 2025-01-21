/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:32:38 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:20:58 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_size(char *other, float max)
{
	if (!other || arc_atof((char *) other) > max || \
		arc_atof((char *) other) < 0)
		return (-1);
	if (arc_atof((char *) other) == 0)
		return (0);
	if (arc_atof((char *) other) > 0)
		return (1);
	return (1);
}

int	check_if_valid(char **split, t_object *obj)
{
	if (!split[0] || obj == NULL)
		return (-1);
	if (ft_strncmp(split[0], "A", 2) == 0)
		return (check_ambient(split, obj));
	else if (ft_strncmp(split[0], "C", 2) == 0)
		return (check_camera(split, obj));
	else if (ft_strncmp(split[0], "L", 2) == 0)
		return (check_light(split, obj));
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		return (check_sphere(split, obj));
	else if (ft_strncmp(split[0], "pl", 3) == 0)
		return (check_plane(split, obj));
	else if (ft_strncmp(split[0], "cy", 3) == 0)
		return (check_cylinder(split, obj));
	return (-1);
}

t_object	*init_object(void)
{
	t_object	*obj;

	obj = (t_object *) malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->coord = (t_coord *) malloc(sizeof(t_coord));
	obj->color = (t_color *) malloc(sizeof(t_color));
	obj->orient = (t_orient *) malloc(sizeof(t_orient));
	if (!obj->coord || !obj->color || !obj->orient)
	{
		free(obj);
		if (obj->coord)
			free(obj->coord);
		if (obj->color)
			free(obj->color);
		return (NULL);
	}
	return (obj);
}

void	set_data(char *file, t_list **list)
{
	t_object	*obj;
	char		**str;
	int			fd;

	fd = open_fd(file);
	str = get_line(fd);
	if (str == NULL)
	{
		print_error(3, NULL);
		exit(1);
	}
	while (str)
	{
		obj = init_object();
		if (check_if_valid(str, obj) == -1)
		{
			free_array(str);
			free_object(obj);
			str = get_line(fd);
			continue ;
		}
		ft_lstadd_back(list, ft_lstnew(obj));
		free_array(str);
		str = get_line(fd);
	}
}
