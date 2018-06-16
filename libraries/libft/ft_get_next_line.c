/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:32:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/13 14:57:17 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	n_l_found(char *str)
{
	long	it;

	if (!str)
		return (-1);
	it = -1;
	while (str[++it])
		if (str[it] == '\n')
			return (it);
	return (-1);
}

t_list		*ft_find_file(t_list **files, const int fd)
{
	while (*files)
	{
		if ((int)(*files)->content_size == fd)
			return (*files);
		files = &(*files)->next;
	}
	ft_lstadd(files, ft_lstnew(NULL, 0));
	(*files)->content_size = fd;
	return (*files);
}

static int	sync_buff(t_list *file, char **line)
{
	long			n_l_pos;

	if ((n_l_pos = n_l_found(file->content)) != -1)
	{
		if (!(*line = ft_strsub(file->content, 0, n_l_pos)))
			return (-1);
		ft_strshift(file->content, n_l_pos + 1);
		return (1);
	}
	else if (file->content)
	{
		if (!(*line = ft_strdup(file->content)))
			return (-1);
		ft_memdel(&file->content);
	}
	return (0);
}

static int	cut_to_n_l(t_list *file, char **line, char *buff, long bytes)
{
	long	n_l_pos;
	char	*tmp;

	tmp = *line;
	buff[bytes] = 0;
	if ((n_l_pos = n_l_found(buff)) != -1)
	{
		if (!(*line = ft_strnjoin(tmp, buff, '\n')))
			return (-1);
		ft_memdel((void **)&tmp);
		ft_strshift(buff, n_l_pos + 1);
		if (ft_strlen(buff))
			file->content = ft_strdup(buff);
		return (1);
	}
	if (*line)
	{
		*line = ft_strjoin(*line, buff);
		ft_memdel((void **)&tmp);
	}
	else
		*line = ft_strdup(buff);
	return (0);
}

int			ft_get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static t_list	*files;
	t_list			*tmp_f;
	long			bytes;
	int				tmp;

	if (!line || fd < 0)
		return (-1);
	*line = NULL;
	tmp_f = ft_find_file(&files, fd);
	if ((bytes = sync_buff(tmp_f, line)))
		return (bytes);
	while ((bytes = read(fd, buff, BUFF_SIZE)))
		if (bytes == -1)
			return (-1);
		else if ((tmp = cut_to_n_l(tmp_f, line, buff, bytes)))
			return (tmp);
	return ((*line && **line) ? 1 : 0);
}
