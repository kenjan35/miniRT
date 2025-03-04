/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadrique_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:54:25 by maandria          #+#    #+#             */
/*   Updated: 2025/03/03 17:17:12 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*********** calcul du discriminant Delta **********************/
float	op_delta(float A, float B, float C)
{
	float	delta;

	delta = (B * B) - (4 * (A * C));
	return (delta);
}

/********** calcul des solutions possible de t *************/
float	op_solution_quad(float A, float B, float C)
{
	float	result;
	float	delta;
	float	tmp;

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
