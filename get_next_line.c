/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiyu <smiyu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:06:35 by smiyu             #+#    #+#             */
/*   Updated: 2022/10/14 17:37:30 by smiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	endl_check(char *str, char **n_str)
{
	if (str && *str)
	{
		str = ft_strchr(str, '\n');
		if (str)
		{
			if (*(str + 1))
				*n_str = ft_strdup(str + 1);
			*(str + 1) = '\0';
			return (true);
		}
	}
	if (*n_str)
		free(*n_str);
	return (false);
}

void	free_and_assign(char **s1, char **s2, char *result)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	*s1 = result;
}

int	read_and_assign(char **str, int fd)
{
	int	rc;

	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	*str = (char *)malloc(sizeof(char) * (size_t)BUFFER_SIZE + 1);
	rc = read(fd, *str, BUFFER_SIZE);
	*(*str + rc) = '\0';
	return (rc);
}

char	*get_next_line(int fd)
{
	int			rc;
	bool		endl;
	static char	*str;
	char		*n_str;
	char		*result;

	if (fd < 0 || fd > 256)
		return (NULL);
	n_str = NULL;
	endl = endl_check(str, &n_str);
	result = ft_strdup(str);
	if (!endl)
		rc = read_and_assign(&str, fd);
	while (str && rc > 0 && !endl)
	{
		endl = endl_check(str, &n_str);
		free_and_assign(&result, &str, ft_strjoin(result, str));
		if (!result)
			return (NULL);
		if (!endl)
			rc = read_and_assign(&str, fd);
	}
	free_and_assign(&str, &n_str, ft_strdup(n_str));
	return (result);
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	char *str;
	int	fd;

	fd = open("./test", O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	return (0);
}