/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftstring.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:04:12 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/28 12:58:18 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSTRING_H
# define FTSTRING_H

# include <string.h>
# include <stdlib.h>

typedef struct	s_string
{
	struct s_string	*prev;
	char			symb;
	struct s_string	*next;
}				t_string;

t_string		*ft_string_push_back(t_string **dst, const char *s);

#endif
