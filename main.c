/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:00:07 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/15 09:08:12 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

void	check_file(char *av)
{
	int		sub_len;

	sub_len = (int)ft_strlen(av);
	if (av[sub_len - 1] != 't' || av[sub_len -2] != 'r' || \
		av[sub_len - 3] != '.' || !av[sub_len - 4] || \
		!ft_isalnum(av[sub_len - 4]))
	{
		print_error(3, NULL);
		exit(1);
	}
}

int	main(int ac, char *av[])
{
	t_list	*lst;

	lst = NULL;
	(void)ac;
	if (!av[1])
	{
		print_error(3, NULL);
		exit(1);
	}
	check_file(av[1]);
	set_data(av[1], &lst);
	if (check_element(&lst) == 0)
	{
		ft_putstr_fd(RED "Error :\nWrong number of element\n" RESET, 2);
		exit(1);
	}
	return (0);
}
