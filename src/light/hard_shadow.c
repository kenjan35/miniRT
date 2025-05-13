/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_shadow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:33:27 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/22 17:02:48 by atolojan         ###   ########.fr       */
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

double	set_shadow_time(t_coord *origin, t_coord *shad, t_prog *prog, t_object *obj)
{
	double	time;
	t_ray	ray;

	ray = op_quadrique_value_sp(*origin, prog, obj);
	ray.v = *shad;
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
	t_coord	shad;
	t_coord	origin;
	double	time;
	t_object	*obj;
	t_list	*tmp;

	origin = set_origin(rt, normal);
	shad = op_vector_substraction(*(light->coord), *rt);
	shad.x /= op_norm(shad);
	shad.y /= op_norm(shad);
	shad.z /= op_norm(shad);
	tmp = prog->shapes;
	while (tmp)
	{
		obj = (t_object *) (tmp->content);
		if (obj->num != prog->current_obj->num)
		{
			time = set_shadow_time(&origin, &shad, prog, obj);
			if (time > 0 && time < op_norm(shad))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
