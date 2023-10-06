/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasserar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:01:46 by yasserar          #+#    #+#             */
/*   Updated: 2023/10/06 10:01:50 by yasserar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	int			chars_read;
	int			nl_pos;

	if (!next_line)
		next_line = ft_strdup("");
	chars_read = read(fd, buff, BUFFER_SIZE);
	while (chars_read >= 0)
	{
		buff[chars_read] = 0;
		next_line = ft_strjoin(next_line, buff);
		nl_pos = find_newline(next_line);
		if (nl_pos != -1)
			return (prepare_lines(&line, &next_line, nl_pos));
		if (!chars_read && !next_line[0])
			break ;
		if (!chars_read)
			return (save_nextline(&next_line, 0));
		chars_read = read(fd, buff, BUFFER_SIZE);
	}
	free(next_line);
	next_line = NULL;
	return (NULL);
}

char	*prepare_lines(char **line, char **next_line, int nl)
{
	*line = ft_substr(*next_line, 0, nl + 1);
	*next_line = save_nextline(next_line, nl + 1);
	return (*line);
}

char	*save_nextline(char **str, int nl)
{
	char	*reminder;
	int		rlen;

	rlen = ft_strlen(*str + nl);
	reminder = ft_substr(*str, nl, rlen);
	free(*str);
	*str = NULL;
	return (reminder);
}

int	find_newline(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}
