/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:57:45 by maandria          #+#    #+#             */
/*   Updated: 2025/03/03 15:48:00 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	orientation_ray(t_coord u, t_prog *prog)
{
	t_coord	result;
	t_coord position_cam;

	position_cam = take_coord_id(prog, "C");
	result = op_vect_n_lamda(-1, position_cam);
	result = op_vector_addition(u, result);
	result = op_vect_n_lamda(1 / op_norm(result), result);
	return (result);
}

t_coord	ray_launch(t_coord u, t_coord v, float t)
{
	t_coord	result;

	result = op_vect_n_lamda(t, v);
	result = op_vector_addition(u, result);
	return (result);
}
