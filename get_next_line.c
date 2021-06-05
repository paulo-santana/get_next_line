/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 22:40:08 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/01 23:19:05 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Searches the buffer for a newline character and moves all of the subsequent
 * characteres to the beginning of the buffer, filling the end with nul
 * characteres.
 * Returns the amount of valid characters left, which can be 0 if the buffer
 * was completely wiped out, BUFFER_SIZE, or
 * any number in between.
 * */

static size_t	move_buffer(char buffer[])
{
	size_t	i;
	size_t	j;
	int		bytes_left;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\n')
		i++;
	if (i == BUFFER_SIZE)
		return (0);
	bytes_left = BUFFER_SIZE - i - 1;
	j = 0;
	while (j < BUFFER_SIZE)
	{
		if (i < BUFFER_SIZE)
			buffer[j++] = buffer[++i];
		else
			buffer[j++] = 0;
	}
	return (bytes_left);
}

static char	*merge_buffer_n(char *dest, char *src, size_t n)
{
	size_t	dest_len;
	size_t	result_len;
	char	*result;

	dest_len = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	result_len = dest_len + n;
	result = malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	result[0] = '\0';
	if (dest)
		ft_strlcat(result, dest, dest_len + 1);
	ft_strlcat(result, src, result_len + 1);
	return (result);
}

static int	append_next_chunk(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			n;
	int			i;
	char		*result;

	n = move_buffer(buffer);
	if (n == 0)
		n = read(fd, buffer, BUFFER_SIZE);
	if (n == 0)
		return (GNL_END_OF_FILE);
	else if (n == -1)
		return (GNL_ERROR);
	i = 0;
	while (i < n && buffer[i] != '\n')
		i++;
	result = merge_buffer_n(*line, buffer, i);
	if (!result)
		return (GNL_ERROR);
	if (*line)
		free(*line);
	*line = result;
	if (buffer[i] == '\n')
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char	*new_line;
	int		finished;

	new_line = NULL;
	finished = 0;
	while (!finished)
	{
		finished = append_next_chunk(fd, &new_line);
		if (finished == GNL_END_OF_FILE)
			return (0);
		if (finished == GNL_ERROR)
			return (-1);
	}
	*line = new_line;
	return (1);
}
