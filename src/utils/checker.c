/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 20:42:27 by maandria          #+#    #+#             */
/*   Updated: 2025/05/17 20:59:03 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_prog	checker(char **av)
{
	t_prog	prog;

	check_file(av[1]);
	if (init_prog(&prog) == 0)
	{
		ft_putstr_fd(RED "Error :\nRendering problem\n" RESET, 2);
		exit(1);
	}
	set_data(av[1], &(prog.obj), &prog);
	if (check_element(&(prog.obj)) == 0)
	{
		ft_putstr_fd(RED "Error :\nWrong number of element\n" RESET, 2);
		exit(1);
	}
	return (prog);
}
