/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:46:38 by psergio-          #+#    #+#             */
/*   Updated: 2021/05/31 11:46:38 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * Retrieves a string that ends with a newline charactere from the file
 * descriptor `fd` and make the pointer `line` point to it
 * */

int		get_next_line(int fd, char **line);

# define GNL_ERROR -1
# define GNL_END_OF_LINE 1
# define GNL_END_OF_FILE 2

#endif
