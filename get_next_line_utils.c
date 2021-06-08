/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 00:41:05 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/08 07:57:20 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	j = 0;
	while (src[j] != '\0' && i + 1 < size)
		dest[i++] = src[j++];
	if (size > i)
		dest[i] = '\0';
	while (src[j++])
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
