/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:46:38 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/06 17:59:56 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);

/**
 * Retrieves a string that ends with a newline charactere from the file
 * descriptor `fd` and make the pointer `line` point to it
 * */

int		get_next_line(int fd, char **line);

//# define GNL_ERROR -1
//# define GNL_END_OF_LINE 1
//# define GNL_END_OF_FILE 2
# define GNL_ERROR -1
# define GNL_END_OF_FILE 0
# define GNL_LINE_READ 1
# define GNL_NO_NEWLINE 2

#endif
