/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:40:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/12 17:45:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_float(char **string, float *pts)
{
	int		end;
	char	*head;

	end = get_primitive_end(*string);
	head = ft_strsub(*string, 0, end);
	*pts = ft_atof(head);
	free(head);
	*string = *string + end;
}

void		parse_string(char **string, char **pts)
{
	int		end;

	end = get_primitive_end(*string);
	if ((*string)[0] != '"' || (*string)[end - 1] != '"')
		ERR("String values should be in quotes");
	*pts = ft_strsub(*string, 1, end - 2);
	*string = *string + end;
}

void		parse_figure_type(char **string, short int *pts)
{
	int			end;
	char		*figure_name;
	int			i;
	const char	**types;
	long		size;

	types = get_obj_type(-1, 0, &size);
	end = get_primitive_end(*string);
	figure_name = ft_strsub(*string, 0, end);
	i = -1;
	while (++i < size)
		if (!ft_strcmp(figure_name, types[i]) && ((*pts = i) + 1))
			break ;
	i >= size ? ERR("Unknown figure type") : 0;
	free(figure_name);
	*string = *string + end;
}

void		parse_material(char **string, t_material *pts)
{
	int			end;
	char		*material_name;
	int			i;
	const char	*types[] = {"\"diffuse\"", "\"emissive\"", "\"reflect\"",
		"\"transparent\"", "\"glass\"", "\"negative\""};

	end = get_primitive_end(*string);
	material_name = ft_strsub(*string, 0, end);
	i = -1;
	while (++i < (int)(sizeof(types) / sizeof(char *)))
		if (!ft_strcmp(material_name, types[i]) && ((*pts = i) + 1))
			break ;
	i >= (int)(sizeof(types) / sizeof(char *)) ? ERR("Unknown material") : 0;
	free(material_name);
	*string = *string + end;
}

void		parse_cl_float3(char **string, cl_float3 *pts)
{
	int			i;
	const void	*data[] = {&pts->x, &pts->y, &pts->z};

	SOBK(string);
	i = -1;
	while (++i < 3 && **string && **string != ']')
	{
		parse_float(string, (void *)data[i]);
		SC(string, **string);
	}
	i != 3 ? ERR("Point must have 3 values") : (SCBK(string));
}
