/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 18:06:57 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/08 07:57:52 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_buffer(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

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
	int		i;
	int		j;
	int		bytes_left;
	size_t	buffer_len;

	i = 0;
	buffer_len = ft_strlen(buffer);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		bytes_left = 0;
	else
		bytes_left = buffer_len - i;
	j = 0;
	while (j < BUFFER_SIZE)
	{
		if (buffer[i] == '\0')
		{
			bytes_left = i - (i - bytes_left);
			buffer[j++] = 0;
			break ;
		}
		buffer[j++] = buffer[++i];
	}
	return (bytes_left);
}

/**
 * Merges at most `n` chars from the buffer `buf` with the destination string
 * `dest`
 */

static char	*merge_buffer_n(char *dest, char *buf, size_t n)
{
	size_t	dest_len;
	size_t	result_len;
	char	*result;

	dest_len = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	result_len = dest_len + n;
	result = malloc(sizeof(char) * (result_len + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	if (dest)
		ft_strlcat(result, dest, dest_len + 1);
	ft_strlcat(result + dest_len, buf, n + 1);
	return (result);
}

/**
 * Fetches `BUFFER_SIZE` characters from file `fd` and append them to the
 * string *new_line. If a \n is found during the read() call, it appends only
 * the text until this \n and returns `GNL_LINE_READ`. If no newline character
 * is found, it appends the whole buffer and returns `GNL_NO_NEWLINE`. If an
 * error occurs, `GNL_ERROR` will be returned. And if we reached `fd`s end,
 * `GNL_END_OF_FILE` will be returned.
 * */

static int	append_next_chunk(int fd, char **new_line, char *buffer)
{
	int			bytes_left;
	int			i;
	char		*merged_str;

	bytes_left = move_buffer(buffer);
	if (bytes_left == 0)
		bytes_left = read(fd, buffer, BUFFER_SIZE);
	if (bytes_left == -1)
		return (GNL_ERROR);
	if (bytes_left < BUFFER_SIZE)
		buffer[bytes_left] = '\0';
	i = 0;
	while (i < bytes_left && buffer[i] != '\n')
		i++;
	merged_str = merge_buffer_n(*new_line, buffer, i);
	if (merged_str == NULL)
		return (GNL_ERROR);
	if (*new_line)
		free(*new_line);
	*new_line = merged_str;
	if (buffer[i] == '\n')
		return (GNL_LINE_READ);
	if (bytes_left == 0)
		return (GNL_END_OF_FILE);
	return (GNL_NO_NEWLINE);
}

/**
 * Fetches the next string from file `fd` and put it in *line. The string
 * will be truncated on the first \n encountered, or by the end of file.
 * */

int	get_next_line(int fd, char **line)
{
	char		*new_line;
	int			result;
	static char	*buffers[FD_SETSIZE];

	new_line = NULL;
	*line = new_line;
	if (fd < 0 || fd >= FD_SETSIZE)
		return (GNL_ERROR);
	if (buffers[fd] == NULL)
		buffers[fd] = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffers[fd] == NULL)
		return (GNL_ERROR);
	result = GNL_NO_NEWLINE;
	while (result == GNL_NO_NEWLINE)
	{
		result = append_next_chunk(fd, &new_line, buffers[fd]);
		*line = new_line;
	}
	if (result == GNL_END_OF_FILE || result == GNL_ERROR)
		clear_buffer(&buffers[fd]);
	return (result);
}
