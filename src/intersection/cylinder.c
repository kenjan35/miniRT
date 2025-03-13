/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:38:41 by maandria          #+#    #+#             */
/*   Updated: 2025/03/13 16:15:35 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_ray	op_quadrique_value_cy(t_coord px, t_prog *prog)
{
	t_ray		result;
	t_coord		rs;
	t_coord		coord;
	t_object	*obj;

	obj = find_id(prog, "cy");
	coord = take_coord_id(prog, "cy");
	rs = orient2coord(obj->orient);
	result.v = op_cross_prod(coord, rs);
	result.v = op_cross_prod(rs, result.v);
	result.ro = px;
	result.rso = op_vect_n_lamda(-1, coord);
	result.rso = op_vector_addition(result.ro, result.rso);
	result.rso = op_cross_prod(rs, result.rso);
	result.rso = op_cross_prod(rs, result.rso);
	return (result);
}

float	inter_cy(t_prog	*prog, t_ray ray)
{
	float		t;
	float		rayon;
	t_object	*cy;
	t_prog		*tmp;
	t_quadric	value;

	tmp = prog;
	t = 0.0;
	cy = find_id(tmp, "cy");
	rayon = (cy->size[0] / 2);
	value = op_values_polynome(ray, rayon);
	t = op_solution_quad(value.A, value.B, value.C);
	return (t);
}