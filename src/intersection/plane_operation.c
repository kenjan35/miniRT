/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:54:26 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/18 10:11:39 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_orient	take_orient_id(t_prog *prog, char *str)
{
	t_object	*position;
	t_orient	position_px;
	t_list		*tmp;

	tmp = prog->obj;
	position = find_id(prog, str);
	if (!position)
	{
		position_px.or_x = INFINITY;
		position_px.or_y = INFINITY;
		position_px.or_z = INFINITY;
		prog->obj = tmp;
		return (position_px);
	}
	position_px.or_x = position->orient->or_x;
	position_px.or_y = position->orient->or_y;
	position_px.or_z = position->orient->or_z;
	prog->obj = tmp;
	return (position_px);
}

double	vector_numer(t_coord n, t_coord rp, t_coord px)
{
	double	res;

	res = 0;
	res += (n.x * (rp.x - px.x));
	res += (n.y * (rp.y - px.y));
	res += (n.z * (rp.z - px.z));
	return (res);
}

double	vector_denom(t_coord n, t_coord v)
{
	double	res;

	res = 0;
	res += (n.x * v.x);
	res += (n.y * v.y);
	res += (n.z * v.z);
	return (res);
}

double	time_inter_pl(t_ray *ray, t_object *pl)
{
	t_coord		rp;
	t_coord		n;
	t_orient	or;
	double		res;
	double		denom;

	res = INFINITY;
	rp = *(pl->coord);
	if (rp.x == INFINITY)
		return (INFINITY);
	or = *(pl->orient);
	if (or.or_x == INFINITY)
		return (INFINITY);
	n = orient2coord(&or);
	denom = vector_denom(n, ray->v);
	if (denom != 0)
		res = vector_numer(n, rp, ray->ro) / denom;
	return (res);
}
