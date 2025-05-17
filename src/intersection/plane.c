/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:22:19 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/18 02:40:39 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_ray	op_quadric_value_pl(t_coord px, t_prog *prog)
{
	t_ray	result;
	t_prog	*tmp;
	t_coord	v;

	tmp = prog;
	result.ro = px;
	result.rso = px;
	v = orientation_ray(px, tmp);
	result.v = v;
	return (result);
}
