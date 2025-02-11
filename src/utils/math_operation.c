/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:39:36 by maandria          #+#    #+#             */
/*   Updated: 2025/02/11 14:40:14 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	op_vpixel_unit(t_viewport view, t_coord u, t_coord v, int index)
{
	t_coord	result;
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
	result.x = coord.x * (nbr / (view * op_norm_pv(u, v, (90 * (PI / 180)))));
	result.y = coord.y * (nbr / (view * op_norm_pv(u, v, (90 * (PI / 180)))));
	result.z = coord.z * (nbr / (view * op_norm_pv(u, v, (90 * (PI / 180)))));
	return (result);
}

t_coord	op_vector_use(t_coord u, t_coord v, t_viewport view)
{
	t_coord	result;

	result = - ((view.length / 2) * u) - ((view.width / 2) * v);
	return (result);
}
