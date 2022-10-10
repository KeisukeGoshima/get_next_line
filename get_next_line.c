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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (dest == NULL)
		return (0);
	i = 0;
	if (s1 != NULL)
		while (*s1)
			dest[i++] = *s1++;
	if (s2 != NULL)
		while (*s2)
			dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

int	search_storage_idx(const char *s, int c)
{
	int	i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char )c)
			return (i);
		i++;
	}
	if (s[i] == '\0')
		return (-1);


}

char	*get_line(const char *s, int idx)
{
	char	*line;
	int		i;
	
	line = malloc(sizeof(char) * (idx + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < idx)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*storage_update(char* storage, int idx)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = ft_strlen(storage);
	j = (size_t)idx;
	new = malloc(sizeof(char) * (i - j + 1));
	while ()
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*storage;
	int			i;
	int			idx;

	idx = -1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (idx == -1)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		storage = ft_strjoin(storage, buf);
		idx = search_storage(storage, '\n');
	}
	line = get_line(storage, idx);
	if (line == NULL)
	{
		free(buf);
		return (NULL);
	}
	storage_update(storage, idx);
}
