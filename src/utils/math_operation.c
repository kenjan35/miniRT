/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:39:36 by maandria          #+#    #+#             */
/*   Updated: 2025/02/20 13:35:28 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	op_vector_addition(t_coord u, t_coord v)
{
	t_coord	result;
	
	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return (result);
}

t_coord	op_vect_n_lamda(float x, t_coord u)
{
	t_coord	result;

	result.x = x * u.x;
	result.y = x * u.y;
	result.z = x * u.z;
	return (result);
}

t_coord	op_vpixel_unit(t_viewport view, t_coord u, t_coord v, int index)
{
	t_coord	result;
	t_coord	coord;
	float	nbr;
	float	px_nb;

	coord = op_pro_vect(u, v);
	if (index == 0)
	{
		nbr = WIN_LENGTH;
		px_nb = view.length;
	}
	else if (index == 1)
	{
		nbr = WIN_WIDTH;
		px_nb = view.width;
	}
	else
	{
		printf(RED "Error index detected.\n" RESET);
		return ((t_coord){INFINITY, INFINITY, INFINITY});
	}
	result.x = coord.x * (nbr / (px_nb * op_norm_pv(u, v, (90 * (PI / 180)))));
	result.y = coord.y * (nbr / (px_nb * op_norm_pv(u, v, (90 * (PI / 180)))));
	result.z = coord.z * (nbr / (px_nb * op_norm_pv(u, v, (90 * (PI / 180)))));
	return (result);
}

t_coord	op_vector_use(t_coord u, t_coord v, t_viewport view)
{
	t_coord	result;

	result = op_vector_addition((op_vect_n_lamda(-(view.length / 2), u)), (op_vect_n_lamda(-(view.width / 2), v)));
	return (result);
}

t_coord	op_position_px(t_coord pos_cam,t_viewport view, t_camunit cam, int x, int y)
{
	t_coord	u;
	t_coord	v;
	t_coord result;

	u = op_vpixel_unit(view, cam.c_avant, cam.c_haut, 0);
	v = op_vpixel_unit(view, cam.c_avant, u, 1);
	result = (t_coord){0, 0, 0};
	result = op_vector_addition(result, pos_cam);
	result = op_vector_addition(result, cam.c_avant);
	result = op_vector_addition(result, op_vector_use(u, v, view));
	result = op_vector_addition(result, op_vect_n_lamda(x, u));
	result = op_vector_addition(result, op_vect_n_lamda(y, v)); 
	return (result);
}
