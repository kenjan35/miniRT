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

/*double	get_ray_sp(t_prog *prog, t_coord *px_position, t_ray *ray)
{
	t_list		*shape;
	t_list		*tmp;
	t_object	*sp;
	double		time;
	double		low;

	low = INFINITY;
	time = INFINITY;
	shape = all_shape(prog, "sp");
	if (shape == NULL)
		return (time);
	tmp = shape;
	while (tmp != NULL)
	{
		sp = (t_object *) (tmp->content);
		*ray = op_quadrique_value_sp(*px_position, prog, sp);
		time = inter_sp(ray, sp);
		if (time < low)
		{
			low = time;
			prog->current_sp = sp;
		}
		tmp = tmp->next;
	}
	return (low);
}

double	get_ray_cy(t_prog *prog, t_coord *px_position, t_ray *ray)
{
	t_list		*shape;
	t_list		*tmp;
	t_object	*cy;
	double		time;
	double		low;

	time = INFINITY;
	low = INFINITY;
	shape = all_shape(prog, "cy");
	if (shape == NULL)
		return (time);
	tmp = shape;
	while (tmp != NULL)
	{
		cy = (t_object *) (tmp->content);
		*ray = op_quadrique_value_cy(*px_position, prog, cy);
		time = inter_cy(ray, cy);
		if (time < low)
		{
			low = time;
			prog->current_cy = cy;
		}
		tmp = tmp->next;
	}
	return (low);
}

double	get_ray_pl(t_prog *prog, t_coord *px_position, t_ray *ray)
{
	t_list		*shape;
	t_list		*tmp;
	t_object	*pl;
	double		time;
	double		low;

	time = INFINITY;
	low = INFINITY;
	shape = all_shape(prog, "pl");
	if (shape == NULL)
		return (time);
	tmp = shape;
	while (tmp != NULL)
	{
		pl = (t_object *) (tmp->content);
		prog->current_pl = pl;
		*ray = op_quadrique_value_pl(*px_position, prog);
		time = time_inter_pl(ray, pl);
		if (time < low)
		{
			low = time;
			prog->current_pl = pl;
		}
		tmp = tmp->next;
	}
	return (low);
}

double	get_real_time(t_prog *prog, t_viewport *view, double *xy, t_ray *ray)
{
	t_coord		px_position;
	double		time[2];

	px_position = mr_pixel_position(prog, *view, xy);
	time[0] = get_ray_sp(prog, &px_position, ray);
	time[1] = get_ray_cy(prog, &px_position, ray);
	if (time[1] < time[0])
		time[0] = time[1];
	else
		prog->current_cy = prog->current_sp;
	time[1] = get_ray_pl(prog, &px_position, ray);
	if (time[1] < time[0])
	{
		time[0] = time[1];
		prog->current_cy = prog->current_pl;
	}
	return (time[0]);
}*/

double	set_shape_time(t_coord *px_position, t_prog *prog, t_object *obj)
{
	double	time;
	t_ray	ray;
	t_coord		rt;

	time = INFINITY;
	if (obj->id[1] == 'l')
	{
		ray = op_quadrique_value_pl(*px_position, prog);
		time = time_inter_pl(&ray, obj);
	}
	else if (obj->id[1] == 'y')
	{
		ray = op_quadrique_value_cy(*px_position, prog, obj);
		time = inter_cy(&ray, obj);
		rt = ray_launch(ray.ro, ray.v, time);
		if (get_extremity(&(ray.ro), &rt, obj) == 1)
			return (time);
		else
			return (0);
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
	double		obj_time;
	t_list		*tmp;

	time = INFINITY;
	obj_time = INFINITY;
	obj = NULL;
	prog->px_pos = mr_pixel_position(prog, *view, xy);
	tmp = prog->shapes;
	while (tmp != NULL)
	{
		obj = (t_object *) (tmp->content);
		obj_time = set_shape_time(&(prog->px_pos), prog, obj);
		obj->time = obj_time;
		if (obj->time != INFINITY && obj->time > 0)
		{
			if (obj->time < time)
			{
				time = obj->time;
				prog->current_cy = obj;
			}
		}
		tmp = tmp->next;
	}
	obj = prog->current_cy;
	return (obj);
}
