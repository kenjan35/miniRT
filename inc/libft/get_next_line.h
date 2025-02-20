/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maandria <maandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:28:00 by atolojan          #+#    #+#             */
/*   Updated: 2025/02/20 14:55:23 by maandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		get_back_words(char *str);
int		read_next(int fd, char *str);
char	*join_shrink(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
