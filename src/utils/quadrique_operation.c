/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrique_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:54:25 by maandria          #+#    #+#             */
/*   Updated: 2025/03/18 14:25:31 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*********** calcul du discriminant Delta **********************/
double	op_delta(double A, double B, double C)
{
	double	delta;

	delta = (B * B) - (4 * (A * C));
	return (delta);
}

/********** calcul des solutions possible de t *************/
double	op_solution_quad(double A, double B, double C)
{
	double	result;
	double	delta;
	double	tmp;

	delta = op_delta(A, B, C);
	result = -1;
	if (delta < 0)
		return (-1);
	else if (delta == 0)
		result = (-1 * B) / (2 * A);
	else if (delta > 0)
	{
		result = ((-1 * B) - sqrtf(delta)) / (2 * A);
		tmp = ((-1 * B) + sqrtf(delta)) / (2 * A);
		if (result < 0 && tmp > 0)
			result = tmp;
		else if (tmp < result && tmp > 0)
			result = tmp;
		else if (result < 0 && tmp < 0)
			return (-1);
	}
	return (result);
}
