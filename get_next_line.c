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
#include <stdio.h>

char	*free_memory(char *memory)
{
	if (memory != NULL)
		free(memory);
	return (NULL);
}

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

char	*get_line(const char *s, int idx)
{
	char	*line;
	int		i;

	if (ft_strlen(s) == 0)
		return (NULL);
	if (idx == -1)
		idx = ft_strlen(s) - 1;
	line = ft_strdup_idx(s, idx);
	if (line == NULL)
		return (NULL);
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
		free_memory(storage);
		free_memory(line);
		return (NULL);
	}
	while (j + k < i)
	{
		new[k] = storage[j + k];
		k++;
	}
	new[k] = '\0';
	free_memory(storage);
	return (new);
}

char	*read_bufsize(char *storage, int fd, int *size)
{
	char	*temp;
	char	*buf;
	
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (free_memory(storage));
	*size = read(fd, buf, BUFFER_SIZE);
	buf[*size] = '\0';
	temp = storage;
	storage = ft_strjoin(storage, buf);
	free_memory(buf);
	free_memory(storage);
	return (storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;
	int			idx;
	int			size;

	if (fd < 0 || fd > 256)
		return (NULL);
	idx = search_storage_idx(storage, '\n');
	size = 1;
	while (idx == -1 && size != 0)
	{
		storage = read_bufsize(storage, fd, &size);
		if (storage == NULL)
			return (free_memory(storage));
		idx = search_storage_idx(storage, '\n');
	}
	line = get_line(storage, idx);
	if (line == NULL)
		return (free_memory(storage));
	storage = storage_update(storage, idx, line);
	if (storage == NULL)
		return (free_memory(storage));
	if (idx == -1 && size == 0)
		free_memory(storage);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main(void)
// {
// 	int fd;
// 	char *str;
// 	fd = open("./test", O_RDONLY);
// 	str = get_next_line(2);
// 	while (str != NULL)
// 	{
// 		printf("%s", str);
// 		str = get_next_line(fd);
// 	}
// 	return (0);
// }