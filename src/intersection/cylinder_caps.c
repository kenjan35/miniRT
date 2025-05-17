/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:27:09 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 19:31:44 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	inter_caps_up(t_coord *c_caps, t_object *cy, t_ray *ray)
{
	t_coord	cy_axis;
	double	height;
	double	t;

	t = 0;
	cy_axis = orient2coord(cy->orient);
	height = cy->size[1] / 2;
	c_caps->x = (cy->coord->x + height * cy_axis.x);
	c_caps->y = (cy->coord->y + height * cy_axis.y);
	c_caps->z = (cy->coord->z + height * cy_axis.z);
	t = vector_numer(cy_axis, *c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	return (t);
}

double	inter_caps_low(t_coord *c_caps, t_object *cy, t_ray *ray)
{
	t_coord	cy_axis;
	double	height;
	double	t;

	t = 0;
	cy_axis = orient2coord(cy->orient);
	height = cy->size[1] / 2;
	c_caps->x = (cy->coord->x - height * cy_axis.x);
	c_caps->y = (cy->coord->y - height * cy_axis.y);
	c_caps->z = (cy->coord->z - height * cy_axis.z);
	t = vector_numer(cy_axis, *c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	return (t);
}

double	inter_cy_caps(t_object *cy, t_ray *ray)
{
	double	t;
	double	t2;
	t_coord	c_caps;
	t_coord	ray_caps;
	t_coord	tmp[2];

	t = inter_caps_up(&c_caps, cy, ray);
	ray_caps = ray_launch(ray->ro, ray->v, t);
	tmp[0] = op_vector_substraction(ray_caps, c_caps);
	t2 = inter_caps_low(&c_caps, cy, ray);
	ray_caps = ray_launch(ray->ro, ray->v, t2);
	tmp[1] = op_vector_substraction(ray_caps, c_caps);
	if (op_norm(tmp[0]) <= (cy->size[0] / 2) + EPSILON && \
		t < t2 && t > pow(10, -6))
	{
		cy->id[0] = '1';
		return (t);
	}
	else if (op_norm(tmp[1]) <= (cy->size[0] / 2) + EPSILON && \
		t2 < t && t2 > pow(10, -6))
	{
		cy->id[0] = '2';
		return (t2);
	}
	return (0);
}

t_coord	get_extremity_upper(t_object *obj)
{
	t_coord	x;
	double	height;

	height = obj->size[1];
	x.x = obj->coord->x + height / 2 * obj->orient->or_x;
	x.y = obj->coord->y + height / 2 * obj->orient->or_y;
	x.z = obj->coord->z + height / 2 * obj->orient->or_z;
	return (x);
}

int	get_extremity(t_coord *px, t_coord *rt, t_object *cy)
{
	t_coord	x;
	t_coord	axis;
	double	norm;
	double	height;
	t_coord	*center;

	(void) px;
	center = cy->coord;
	height = cy->size[1];
	axis = orient2coord(cy->orient);
	axis.x /= op_norm(axis);
	axis.y /= op_norm(axis);
	axis.z /= op_norm(axis);
	x = op_vector_substraction(*rt, *center);
	norm = op_dot_prod(x, axis);
	if (-(height / 2) <= norm && norm <= (height / 2))
		return (1);
	return (0);
}
