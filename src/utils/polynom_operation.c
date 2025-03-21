/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:54:26 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/21 11:23:55 by atolojan         ###   ########.fr       */
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

double	time_inter_pl(t_coord px, t_prog *prog)
{
	t_coord	v;
	t_coord	rp;
	t_coord	n;
  t_orient  or;
	t_prog	*tmp;
	double	res;

	tmp = prog;
	rp = take_coord_id(tmp, "pl");
  tmp = prog;
	v = orientation_ray(px, tmp);
  or = take_orient_id(prog, "pl");
	n = orient2coord(&or);
	res = vector_numer(n, rp, px) / vector_denom(n, v);
	printf("res = %f\n", res);
	return (res);
}
