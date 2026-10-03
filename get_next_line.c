/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyatala <beyatala@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:58:25 by beyatala          #+#    #+#             */
/*   Updated: 2026/10/03 18:46:07 by beyatala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *ft_read_stash(int fd, char *stash)
{
    char *buffer;
    int bytes_read;
    
    buffer = malloc(BUFFER_SIZE+1);
    if(!buffer)
        return NULL;
    while(!ft_strchr(stash, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if(bytes_read<0)
        {
            free(stash);
            free(buffer);
            return NULL;
        }
        if(bytes_read==0)
            break;
        buffer[bytes_read]='\0';
        if (!stash)
            stash = ft_strdup(buffer);
        else
             stash = ft_strjoin(stash, buffer);  
    }
    free(buffer);
    return stash;
}
static char *ft_get_line(char *stash)
{
    char *line;
    int i;
    i=-1;
    while(stash[++i] && stash[i]!='\n') 
    line = malloc(i+2);
    if(!line)
        return NULL;
    i=-1;
    while(stash[++i])
    {
        if(stash[i]=='\n')
        {
            line[i++]='\n';
            break;
        }
        line[i] = stash[i];
    }
    line[i]='\0';
    return line;
}
static char *ft_update_stash(char *stash)
{
    char *new;
    int i;
    
    i=0;
    while(stash[i] && stash[i]!='\n')
        i++;
    if (stash[i] == '\0')
    {
        free(stash);
        return NULL;
    }
    new = ft_strdup(&stash[i+1]);
    if(!new)
    {
        free(stash);
        return NULL;
    }
    free(stash);
    return new;
}
char *get_next_line(int fd)
{
    static char *stash;
    char *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    stash = ft_read_stash(fd, stash);
    if(!stash)
        return NULL;    
    line = ft_get_line(stash);
    if (!line)
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }
    stash = ft_update_stash(stash);
    return line;
}