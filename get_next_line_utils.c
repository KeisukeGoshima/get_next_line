/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:48:01 by marvin            #+#    #+#             */
/*   Updated: 2022/10/14 21:48:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
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
		return (NULL);
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

char	*ft_strdup_idx(const char *s, int idx)
{
	char	*str;

	str = malloc(sizeof(char) * (idx + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <= idx)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
