/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyatala <beyatala@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:58:20 by beyatala          #+#    #+#             */
/*   Updated: 2026/10/03 16:08:12 by beyatala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(char *s)
{
    size_t i;

    i=0;
    if (!s)
		return (0);
    while(s[i])
        i++;
    return i;
}

char *ft_strchr(char *s, int c)
{
    int i;

    i=0;
    if (!s)
		return (NULL);
    while(s[i] != (char)c)
    {
        if(s[i]=='\0')
            return NULL;
        i++;
    }
    return (char *)&s[i];
}

char *ft_strjoin(char *s1, char *s2)
{
    char *ptr;
    size_t i;
    size_t j;

    i=0;
    j=0;
    if(!s1||!s2)
        return NULL;
    ptr=(char *)malloc(sizeof(char)* (ft_strlen(s1)+ft_strlen(s2)+1));
    if(!ptr)
        return NULL;
    while(s1[i])
    {
        ptr[i]=s1[i];
        i++;
    }
    while(s2[j])
    {
        ptr[i+j]=s2[j];
        j++;
    }
    ptr[i+j] = '\0';
    free(s1);
	return (ptr);
}
char *ft_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}