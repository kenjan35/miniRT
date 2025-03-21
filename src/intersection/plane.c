/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:22:19 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/21 10:23:04 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_ray	op_quadrique_value_pl(t_coord px, t_prog *prog)
{
	t_ray	result;
	t_prog	*tmp;
  t_coord v;

	tmp = prog;
  result.ro = px;
	result.rso = px;
	v = orientation_ray(px, tmp);
  result.v = v;
  return (result);
}
