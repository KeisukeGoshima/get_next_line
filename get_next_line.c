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

int	get_line_len(char *storage)
{
	int	i;

	if (storage == NULL)
		return (0);
	i = 0;
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n')
			return (i+1);
		i++;
	}
	return (0);
}
#include <stdio.h>
char	*read_stock(char *storage, int fd, int *end)
{
	char	*buf;
	char	*new;

	buf =  malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
	{
		if (storage != NULL)
			free(storage);
		return (NULL);
	}
	*end = read(fd, buf, BUFFER_SIZE);
	buf[*end] = '\0';
	new = ft_strjoin(storage, buf);
	free(buf);
	if (storage != NULL)
		free(storage);
	return (new);
}

char	*get_line_and_update(char **storage, int len)
{
	char	*line;
	char	*temp;
	int		i;

	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
	{
		free(*storage);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		line[i] = (*storage)[i];
		i++;
	}
	temp = *storage;
	*storage = ft_strdup(&temp[len]);
	free(temp);
	if (*storage == NULL)
		return (NULL);
	return (line);
}

char	*get_endline(char **storage)
{
	char	*line;

	line = ft_strdup(*storage);
	free(*storage);
	*storage = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char *storage;
	int			len;
	int			end[1];

	if (fd < 0)
		return (NULL);
	len = get_line_len(storage);
	*end = 1;
	while (len == 0 && *end != 0)
	{
		storage = read_stock(storage, fd, end);
		if (storage == NULL)
			return (NULL);
		len = get_line_len(storage);
	}
	if (len != 0)
		line = get_line_and_update(&storage, len);
	else if (ft_strlen(storage) != 0)
		line = get_endline(&storage);
	else
		return (NULL);
	return (line);
}


#include <fcntl.h>
int main(void)
{
	int fd;
	char *str;
	fd = open("./test", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	return (0);
}