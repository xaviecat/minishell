/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:05:57 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/27 13:19:46 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE	21
#endif

static char	*stacking(char *stack, char *buff)
{
	char	*tmp;

	if (!stack)
	{
		stack = ft_strdup(buff);
		return (stack);
	}
	tmp = ft_strdup(stack);
	free(stack);
	stack = NULL;
	stack = ft_strjoin(tmp, buff);
	free(tmp);
	tmp = NULL;
	return (stack);
}

static char	*cleanstack(char *stack)
{
	char	*tmp;

	if (!stack || !ft_strchr(stack, '\n'))
		return (free(stack), stack = NULL, NULL);
	else
	{
		tmp = ft_strdup(stack);
		if (!tmp)
			return (free(stack), stack = NULL, NULL);
		free(stack);
		stack = ft_strdup(ft_strchr(tmp, '\n') + 1);
		if (!stack)
			return (free(tmp), tmp = NULL, NULL);
		if (!stack[0])
			return (free(stack), free(tmp), tmp = NULL, stack = NULL, NULL);
		free(tmp);
		tmp = NULL;
	}
	return (stack);
}

static char	*read_and_stack(int fd, char *stack)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;

	ret = 1;
	while (!ft_strchr(stack, '\n') && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (free(stack), stack = NULL, NULL);
		buff[ret] = '\0';
		stack = stacking(stack, buff);
		if (ret != BUFFER_SIZE)
			break ;
	}
	return (stack);
}

static char	*next_line(char *stack)
{
	size_t	len;
	char	*line;

	len = 0;
	line = NULL;
	if (!stack[0])
		return (NULL);
	if (ft_strchr(stack, '\n'))
	{
		len = ft_strlen(stack) - ft_strlen(ft_strchr(stack, '\n')) + 1;
		line = ft_substr(stack, 0, len);
		return (line);
	}
	else if (!ft_strchr(stack, '\n'))
	{
		line = ft_strdup(stack);
		(void) len;
		return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (free(stack), stack = NULL, NULL);
	stack = read_and_stack(fd, stack);
	if (!stack)
		return (free(stack), stack = NULL, NULL);
	line = next_line(stack);
	stack = cleanstack(stack);
	if (!line)
		return (free(stack), stack = NULL, NULL);
	return (line);
}
