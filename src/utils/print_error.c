/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:12:22 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/21 15:23:02 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_error(int cipher, void *ptr)
{
	if (ptr)
		free(ptr);
	if (cipher == 0)
		ft_putstr_fd(RED "Error :\n\tInvalid map components\n" RESET, 2);
	else if (cipher == 1)
		ft_putstr_fd(RED "Error :\n\tMap size invalid\n" RESET, 2);
	else if (cipher == 2)
		ft_putstr_fd(RED "Error :\n\tExit or item inaccessible\n" RESET, 2);
	else if (cipher == 3)
		ft_putstr_fd(RED "Error :\n\tError loading file\n" RESET, 2);
	exit(1);
}
