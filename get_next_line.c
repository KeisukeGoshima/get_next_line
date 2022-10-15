/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoshima <kgoshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:59:20 by kgoshima          #+#    #+#             */
/*   Updated: 2022/10/10 08:59:46 by kgoshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_storage_idx(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == (char )c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_line(const char *s, int idx, char *buf)
{
	char	*line;
	int		i;

	free(buf);
	if (ft_strlen(s) == 0)
		return (NULL);
	if (idx == -1)
		idx = ft_strlen(s) - 1;
	line = malloc(sizeof(char) * (idx + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i <= idx)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*storage_update(char *storage, int idx, char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*new;

	i = ft_strlen(storage);
	if (idx == -1)
		idx = ft_strlen(storage) - 1;
	j = (size_t)idx + 1;
	k = 0;
	new = malloc(sizeof(char) * (i - j + 1));
	if (new == NULL)
	{
		free(storage);
		free(line);
		return (NULL);
	}
	while (j + k < i)
	{
		new[k] = storage[j + k];
		k++;
	}
	new[k] = '\0';
	free(storage);
	return (new);
}

char	*read_bufsize(char *storage, char *buf, int fd, int *size)
{
	char	*temp;

	*size = read(fd, buf, BUFFER_SIZE);
	buf[*size] = '\0';
	temp = storage;
	storage = ft_strjoin(storage, buf);
	if (temp != NULL)
		free(temp);
	if (storage == NULL)
	{
		free(buf);
		return (NULL);
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*storage;
	int			idx;
	int			size;

	if (fd < 0 || fd > 256)
		return (NULL);
	idx = search_storage_idx(storage, '\n');
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	size = 1;
	while (idx == -1 && size != 0)
	{
		storage = read_bufsize(storage, buf, fd, &size);
		if (storage == NULL)
			return (NULL);
		idx = search_storage_idx(storage, '\n');
	}
	line = get_line(storage, idx, buf);
	if (line == NULL)
		return (NULL);
	storage = storage_update(storage, idx, line);
	if (storage == NULL)
		return (NULL);
	if (ft_strlen(storage) == 0)
		free(storage);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main(void)
// {
// 	int fd;
// 	char *str;
// 	fd = open("./test", O_RDONLY);
// 	str = get_next_line(fd);
// 	while (str != NULL)
// 	{
// 		printf("%s", str);
// 		str = get_next_line(fd);
// 	}
// 	return (0);
// }