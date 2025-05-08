/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:19:14 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/18 10:42:27 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	set_cy_time(t_ray *ray, t_prog *prog, t_object *obj)
{
	double		time;
	double		time_caps;
	double		min;
	t_coord		rt;

	(void) prog;
	min = INFINITY;
	time = INFINITY;
	time_caps = INFINITY;
	time = inter_cy(ray, obj);
	rt = ray_launch(ray->ro, ray->v, time);
	if (get_extremity(&(ray->ro), &rt, obj) == 1)
		min = time;
	time_caps = inter_cy_caps(obj, ray);
	if (time_caps != 0 && time_caps < min)
		min = time_caps;
	if (min != INFINITY)
		time = min;
	else
		return (0);
	return (time);
}

double	set_shape_time(t_coord *px_position, t_prog *prog, t_object *obj)
{
	double	time;
	t_ray	ray;

	time = INFINITY;
	if (obj->id[1] == 'l')
	{
		ray = op_quadrique_value_pl(*px_position, prog);
		time = time_inter_pl(&ray, obj);
	}
	else if (obj->id[1] == 'y')
	{
		ray = op_quadrique_value_cy(*px_position, prog, obj);
		time = set_cy_time(&ray, prog, obj);
	}
	else if (obj->id[1] == 'p')
	{
		ray = op_quadrique_value_sp(*px_position, prog, obj);
		time = inter_sp(&ray, obj);
	}
	return (time);
}

t_object	*get_closest(t_prog *prog, t_viewport *view, double *xy)
{
	t_object	*obj;
	double		time;
	t_list		*tmp;

	time = INFINITY;
	obj = NULL;
	prog->px_pos = mr_pixel_position(prog, *view, xy);
	tmp = prog->shapes;
	while (tmp != NULL)
	{
		obj = (t_object *) (tmp->content);
		obj->time = set_shape_time(&(prog->px_pos), prog, obj);
		if (obj->time < INFINITY && obj->time > 0)
		{
			if (obj->time < time)
			{
				time = obj->time;
				prog->current_obj = obj;
			}
		}
		tmp = tmp->next;
	}
	obj = prog->current_obj;
	return (obj);
}
