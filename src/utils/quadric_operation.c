/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:17:18 by atolojan          #+#    #+#             */
/*   Updated: 2025/05/17 22:17:21 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	op_delta(double a, double b, double c)
{
	double	delta;

	delta = (b * b) - (4 * (a * c));
	return (delta);
}

double	op_solution_quad(double a, double b, double c)
{
	double	result;
	double	delta;
	double	tmp;

	delta = op_delta(a, b, c);
	result = -1;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		result = (-1 * b) / (2 * a);
	else if (delta > 0)
	{
		result = ((-1 * b) - sqrtf(delta)) / (2 * a);
		tmp = ((-1 * b) + sqrtf(delta)) / (2 * a);
		if (result < 0 && tmp > 0)
			result = tmp;
		else if (tmp < result && tmp > 0)
			result = tmp;
		else if (result < 0 && tmp < 0)
			return (-1);
	}
	return (result);
}
