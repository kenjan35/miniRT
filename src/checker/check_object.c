/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:32:38 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/21 11:11:09 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
		if (obj->coord)
			free(obj->coord);
		if (obj->color)
			free(obj->color);
		if (obj->orient)
			free(obj->orient);
		free(obj);
		return (NULL);
	}
	return (obj);
}

void	failed_data(t_prog *prog, char **str, t_object *obj, t_list **list)
{
	t_list		*tmp;
	t_list		*current;

	free_array(str);
	free_object(obj);
	tmp = *list;
	while (tmp)
	{
		current = tmp;
		obj = current->content;
		free_object(obj);
		tmp = tmp->next;
		free(current);
	}
	mlx_destroy_window(prog->mlx, prog->mlx_win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	ft_putstr_fd(RED "Error :\nComponent problems\n" RESET, 2);
	exit(1);
}

char	**get_fd_line(char *file, int *fd)
{
	char	**str;

	*fd = open_fd(file);
	str = get_line(*fd);
	if (str == NULL)
	{
		print_error(3, NULL);
		exit(1);
	}
	return (str);
}

void	set_data(char *file, t_list **list, t_prog *prog)
{
	t_object	*obj;
	char		**str;
	int			fd;
	static int	i = 0;

	str = get_fd_line(file, &fd);
	while (str)
	{
		obj = init_object();
		if (str[0] && !ft_strncmp(str[0], "\n", 2))
		{
			free_array(str);
			free_object(obj);
			str = get_line(fd);
			continue ;
		}
		else if (check_if_valid(str, obj) == -1 || !obj)
			failed_data(prog, str, obj, list);
		ft_lstadd_back(list, ft_lstnew(obj));
		obj->num = i;
		i++;
		free_array(str);
		str = get_line(fd);
	}
}
