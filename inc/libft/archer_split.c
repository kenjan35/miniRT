/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archer_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:59:41 by atolojan          #+#    #+#             */
/*   Updated: 2025/01/15 08:39:28 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**check_malloc(char **tab, int i)
{
	if (!tab[i])
	{
		while (--i >= 0)
			free(tab[i]);
		free(tab);
	}
	return (tab);
}

static int	is_space(const char *s, int i)
{
	if (s[i] == ' ' || s[i] == '\t' || \
		s[i] == '\v' || s[i] == '\r' || s[i] == '\f')
		return (1);
	return (0);
}

static void	take_word(char **tab, const char *s)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!is_space(s, i[0]))
		{
			i[2] = 0;
			while (s[i[0]] != '\0' && !is_space(s, i[0]))
			{
				i[2]++;
				i[0]++;
			}
			tab[i[1]] = ft_substr(s, i[0] - i[2], i[2]);
			check_malloc(tab, i[1]);
			i[1]++;
		}
		else
			i[0]++;
	}
	if (tab)
		tab[i[1]] = NULL;
}

char	**arc_split(char const *s)
{
	char	**tab;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!is_space(s, i) && (s[i + 1] == '\0' || is_space(s, i + 1)))
			count++;
		i++;
	}
	tab = malloc(sizeof (char *) * (count + 1));
	if (!tab)
		return (NULL);
	take_word(tab, s);
	return (tab);
}
