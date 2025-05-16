/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:39:36 by maandria          #+#    #+#             */
/*   Updated: 2025/05/16 14:45:41 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/************* produit scalaire ******************/
double	op_dot_prod(t_coord u, t_coord v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

/************* usage des vecteurs pixels unitaires ******************/
t_coord	op_vpixel_unit(t_viewport view, t_coord u, t_coord v, int index)
{
	t_coord	result;
	t_coord	coord;
	double	nbr;
	double	px_nb;

	coord = op_cross_prod(u, v);
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
	result = op_cross_prod(u, v);
	result = op_vect_n_lamda(1 / op_norm(result), result);
	result = op_vect_n_lamda(px_nb / nbr, result);
	return (result);
}

/************* usage de vecteur ******************/
t_coord	op_vector_use(t_coord u, t_coord v)
{
	t_coord	result;

	result = op_vector_addition((op_vect_n_lamda(-(WIN_LENGTH / 2), u)),
			(op_vect_n_lamda(-(WIN_WIDTH / 2), v)));
	return (result);
}

t_coord	op_position_px(t_coord pos_cam, t_viewport view,
		t_camunit cam, double *xy)
{
	t_coord		u;
	t_coord		v;
	t_coord		result;

	u = op_vpixel_unit(view, cam.c_forward, cam.c_up, 0);
	v = op_vpixel_unit(view, cam.c_forward, u, 1);
	result = (t_coord){0, 0, 0};
	result = op_vector_addition(result, pos_cam);
	result = op_vector_addition(result, cam.c_forward);
	result = op_vector_addition(result, op_vector_use(u, v));
	result = op_vector_addition(result, op_vect_n_lamda(xy[0], u));
	result = op_vector_addition(result, op_vect_n_lamda(xy[1], v));
	return (result);
}

t_coord	op_ortgl_projec_prll(t_coord u, t_coord v)
{
	t_coord	result;
	double	lamda;

	lamda = op_dot_prod(u, v) / op_dot_prod(u, u);
	result = op_vect_n_lamda(lamda, u);
	return (result);
}
