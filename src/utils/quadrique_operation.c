/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrique_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   created: 2025/03/03 15:54:25 by maandria          #+#    #+#             */
/*   Updated: 2025/03/18 14:25:31 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*********** calcul du discriminant Delta **********************/
double	op_delta(double a, double b, double c)
{
	double	delta;

	delta = (b * b) - (4 * (a * c));
	return (delta);
}

/********** calcul des solutions possible de t *************/
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
