/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:49:20 by maandria          #+#    #+#             */
/*   Updated: 2025/03/03 15:06:25 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/************* produit vectoriel *****************/
t_coord	op_cross_prod(t_coord u, t_coord v)
{
	t_coord	result;

	result.x = (u.y * v.z) - (u.z * v.y);
	result.y = (u.z * v.x) - (u.x * v.z);
	result.z = (u.x * v.y) - (u.y * v.x);
	return (result);
}

/************* norme d'un produit vectoriel ********/
float	op_norm_pv(t_coord u, t_coord v, float teta)
{
	float	result;

	result = op_norm(u) * op_norm(v) * sinf(teta);
	return (result);
}

/************* norme d'un vecteur *****************/
float	op_norm(t_coord u)
{
	float	result;

	result = sqrtf((u.x * u.x) + (u.y * u.y) + (u.z * u.z));
	return (result);
}

/************* addition de vecteur *****************/
t_coord	op_vector_addition(t_coord u, t_coord v)
{
	t_coord	result;
	
	result.x = u.x + v.x;
	result.y = u.y + v.y;
	result.z = u.z + v.z;
	return (result);
}

/************* produit d'un vecteur et un nbr *******/
t_coord	op_vect_n_lamda(float x, t_coord u)
{
	t_coord	result;

	result.x = x * u.x;
	result.y = x * u.y;
	result.z = x * u.z;
	return (result);
}
