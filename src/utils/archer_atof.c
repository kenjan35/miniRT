/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archer_atof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:38:47 by atolojan          #+#    #+#             */
/*   Updated: 2025/03/18 14:25:31 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	set_sign(const char *nptr, int *i, int *sign)
{
	if (nptr[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (nptr[*i] == '+')
		(*i)++;
}

static void	init_atof(int *i, int *j, int *sign, int *comma)
{
	*i = 0;
	*j = 0;
	*sign = 1;
	*comma = 0;
}

static void	set_add(double *nbr, double to_add, int i[])
{
	*nbr += to_add;
	i[1]++;
	i[0]++;
}

static void	atof_tools(const char *nptr, int i[], double *nbr)
{
	while ((nptr[i[0]] >= '0' && nptr[i[0]] <= '9') || nptr[i[0]] == '.')
	{
		if (nptr[i[0]] == '.')
		{
			if (i[3] == 0)
			{
				i[3] = 1;
				set_add(nbr, 0.0, i);
				continue ;
			}
			return ;
		}
		else if (i[3] == 1)
		{
			set_add(nbr, (nptr[i[0]] - '0') * powf(10.0, -(i[1])), i);
			continue ;
		}
		else
			*nbr += (nptr[i[0]] - '0');
		if (nptr[i[0] + 1] >= '0' && nptr[i[0] + 1] <= '9')
			*nbr *= 10;
		i[0]++;
	}
}

double	arc_atof(const char *nptr)
{
	int		i[4];
	double	nbr;

	nbr = 0;
	init_atof(&i[0], &i[1], &i[2], &i[3]);
	while ((nptr[i[0]] >= 9 && nptr[i[0]] <= 13) || nptr[i[0]] == 32)
		i[0]++;
	set_sign(nptr, &i[0], &i[2]);
	atof_tools(nptr, i, &nbr);
	return (nbr * i[2]);
}
