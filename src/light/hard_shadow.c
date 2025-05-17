/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:27 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/18 02:40:39 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	set_origin(t_coord *rt, t_coord *norm)
{
	t_coord	origin;

	origin.x = rt->x + EPSILON * norm->x;
	origin.y = rt->y + EPSILON * norm->y;
	origin.z = rt->z + EPSILON * norm->z;
	return (origin);
}

double	set_shadow_time(t_coord *org, t_coord *sdw, t_prog *prog, t_object *obj)
{
	double	time;
	t_ray	ray;

	ray = op_quadric_value_sp(*org, prog, obj);
	ray.v = *sdw;
	time = INFINITY;
	if (obj->id[1] == 'l')
		time = time_inter_pl(&ray, obj);
	else if (obj->id[1] == 'y')
		time = set_cy_time(&ray, prog, obj);
	else if (obj->id[1] == 'p')
		time = inter_sp(&ray, obj);
	return (time);
}

int	in_shadow(t_prog *prog, t_object *light, t_coord *rt, t_coord *normal)
{
	t_coord		shad[2];
	t_coord		origin;
	double		time;
	t_object	*obj;
	t_list		*tmp;

	origin = set_origin(rt, normal);
	shad[0] = op_vector_substraction(*(light->coord), *rt);
	shad[1] = op_normalize(shad[0]);
	tmp = prog->shapes;
	while (tmp)
	{
		obj = (t_object *)(tmp->content);
		if (obj->num != prog->current_obj->num)
		{
			time = set_shadow_time(&origin, &shad[1], prog, obj);
			if (time > 0 && time < op_norm(shad[0]))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
