/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:07:57 by atolojan          #+#    #+#             */
/*   Updated: 2025/04/09 16:31:19 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_coord	set_cylinder_normal(t_coord *rt, t_object *obj)
{
	double	norm;
	t_coord	project_vcp;
	t_coord	v_cp;
	t_coord	axis;
	t_coord	radial;

	axis = orient2coord(obj->orient);
	v_cp = op_vector_substraction(*rt, *(obj->coord));
	project_vcp = op_vect_n_lamda(op_dot_prod(v_cp, axis), axis);
	radial = op_vector_substraction(v_cp, project_vcp);
	norm = op_norm(radial);
	radial.x /= norm;
	radial.x /= norm;
	radial.x /= norm;
	return (radial);
}
