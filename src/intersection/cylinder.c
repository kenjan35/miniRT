/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:41 by maandria          #+#    #+#             */
/*   Updated: 2025/03/19 16:27:31 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	op_vector_substraction(t_coord u, t_coord v)
{
	t_coord	result;

	result.x = u.x - v.x;
	result.y = u.y - v.y;
	result.z = u.z - v.z;
	return (result);
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
	//printf("n %lf height / 2 %lf\n", norm, (height / 2));
	if (-(height / 2) <= norm && norm <= (height / 2))
		return (1);
	return (0);
}

t_quadric	op_values_polynome_cy(t_coord *px, t_coord *axis_cy, t_coord *dir, t_object *cy)
{
	t_quadric	result;
	t_coord		c;
	t_coord		x;
	double		ray;
	double		tmp;

	tmp = 0;
	ray = cy->size[0] / 2;
	c = get_extremity_upper(cy);
	x = op_vector_substraction(*px, c);
	tmp = op_dot_prod(*dir, *dir);
	result.A = tmp - (op_dot_prod(*dir, *axis_cy) * op_dot_prod(*dir, *axis_cy));
	tmp = op_dot_prod(*dir, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.B = 2 * (op_dot_prod(*dir, x) - tmp);
	tmp = op_dot_prod(x, *axis_cy) * op_dot_prod(x, *axis_cy);
	result.C = op_dot_prod(x, x) - tmp - ray * ray;
	return (result);
}

t_ray	op_quadrique_value_cy(t_coord px, t_prog *prog, t_object *cy)
{
	t_ray		result;
	t_coord		rs;
	t_coord		coord;
	t_coord		vector;

	coord = *(cy->coord);
	//printf(CYAN "\nquadrique cy vector : x = %f, y = %f, z = %f\n" RESET, coord.x, coord.y, coord.z);
	vector = orientation_ray(px, prog);
	rs = orient2coord(cy->orient);
	//rs = op_ortgl_projec_prll(rs, coord);
	//result.v = op_cross_prod(vector, rs);
	//result.v = op_cross_prod(rs, result.v);
	result.v = vector;
	result.ro = px;
	/*result.rso = op_vect_n_lamda(-1, coord);
	result.rso = op_vector_addition(result.ro, result.rso);
	result.rso = op_cross_prod(rs, result.rso);
	result.rso = op_cross_prod(rs, result.rso);*/
	result.rso = op_vector_addition(px, op_vect_n_lamda(-1, rs));
	return (result);
}

double	vector_caps(t_coord *point, t_coord *c_caps, t_coord *axis)
{
	double	t;
	t_coord	res;
	t_coord	v_project;

	v_project = op_vector_substraction(*point, *c_caps);
	res.x = v_project.x - op_dot_prod(v_project, *axis) * axis->x;
	res.y = v_project.y - op_dot_prod(v_project, *axis) * axis->y;
	res.z = v_project.z - op_dot_prod(v_project, *axis) * axis->z;
	t = op_norm(res);
	if (t < 0)
		printf("t = %lf\n", t);
	return (t);
}

double	inter_cy_caps(t_object *cy, t_ray *ray)
{
	double	t;
	t_coord	cy_axis;
	double	height;
	t_coord	cy_center;
	t_coord	c_caps;
	t_coord	ray_caps;
	t_coord	tmp;

	cy_center = *(cy->coord);
	cy_axis = orient2coord(cy->orient);
	cy_axis.x /= op_norm(cy_axis);
	cy_axis.y /= op_norm(cy_axis);
	cy_axis.z /= op_norm(cy_axis);
	height = cy->size[1] / 2;
	c_caps.x = (cy_center.x + height * cy_axis.x);
	c_caps.y = (cy_center.y + height * cy_axis.y);
	c_caps.z = (cy_center.z + height * cy_axis.z);
	t = vector_numer(cy_axis, c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	ray_caps = ray_launch(ray->ro, ray->v, t);
	tmp = op_vector_substraction(ray_caps, c_caps);
	if (op_norm(tmp) <= (cy->size[0] / 2))
		return (t);
	c_caps.x = (cy_center.x - height * cy_axis.x);
	c_caps.y = (cy_center.y - height * cy_axis.y);
	c_caps.z = (cy_center.z - height * cy_axis.z);
	t = vector_numer(cy_axis, c_caps, ray->ro) / vector_denom(cy_axis, ray->v);
	ray_caps = ray_launch(ray->ro, ray->v, t);
	tmp = op_vector_substraction(ray_caps, c_caps);
	if (op_norm(tmp) <= (cy->size[0] / 2))
		return (t);
	return (0);
}

double	inter_cy(t_ray *ray, t_object *cy)
{
	double		t;
	t_coord		axis_cy;
	t_quadric	value;

	t = INFINITY;
	axis_cy = orient2coord(cy->orient);
	//value = op_values_polynome(ray, rayon);
	value = op_values_polynome_cy(&(ray->ro), &axis_cy, &(ray->v), cy);
	t = op_solution_quad(value.A, value.B, value.C);
	return (t);
}
