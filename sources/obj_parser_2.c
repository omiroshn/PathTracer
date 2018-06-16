/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:10:04 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/08 17:31:44 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_texture(char **string, uint *pts, t_scene *scene)
{
	int		end;
	char	*source;

	end = get_primitive_end(*string);
	if ((*string)[0] != '"' || (*string)[end - 1] != '"')
		ERR("String values should be in quotes");
	source = ft_strsub(*string, 1, end - 2);
	*pts = add_texture(&scene->tex_l, source);
	free(source);
	*string = *string + end;
}

cl_float3	parse_float2(char *string)
{
	char		**splitted;
	cl_float3	point;

	splitted = ft_strsplit(string, ' ');
	if (count_splitted(splitted) != 3)
	{
		free_splitted(splitted);
		return (parse_float3(string));
	}
	point.x = ft_atof(splitted[1]);
	point.y = ft_atof(splitted[2]);
	point.z = 0;
	free_splitted(splitted);
	return (point);
}

cl_float3	parse_float3(char *string)
{
	char		**splitted;
	cl_float3	point;

	splitted = ft_strsplit(string, ' ');
	if (count_splitted(splitted) != 4)
		ERR("Invalid obj or mtl point");
	point.x = ft_atof(splitted[1]);
	point.y = ft_atof(splitted[2]);
	point.z = ft_atof(splitted[3]);
	free_splitted(splitted);
	return (point);
}

cl_int3		parse_float3_facet(char *string)
{
	char	**splitted;
	int		coord_amount;
	cl_int3	point;

	splitted = ft_strsplit(string, '/');
	coord_amount = count_splitted(splitted);
	if (coord_amount > 3)
		ERR("Invalid obj facet index");
	point.x = ft_atoi(splitted[0]);
	point.y = -1;
	point.z = -1;
	if (coord_amount >= 2)
		point.y = ft_atoi(splitted[1]);
	if (coord_amount == 3)
		point.z = ft_atoi(splitted[2]);
	free_splitted(splitted);
	return (point);
}

void		add_triag(char *string, int material_index, t_dlist **triags)
{
	int			count;
	char		**splitted;
	t_triag		*triag;

	splitted = ft_strsplit(string, ' ');
	count = count_splitted(splitted);
	if (count < 4 || count > 6)
		ERR("Invalid obj facet");
	triag = create_triag(splitted[1], splitted[2], splitted[3], material_index);
	ft_dlstpush_back(triags, ft_dlstnew(triag, sizeof(t_triag)));
	if (count > 4)
	{
		triag = create_triag(splitted[1], splitted[3], splitted[4],
			material_index);
		ft_dlstpush_back(triags, ft_dlstnew(triag, sizeof(t_triag)));
	}
	if (count > 5)
	{
		triag = create_triag(splitted[1], splitted[4], splitted[5],
			material_index);
		ft_dlstpush_back(triags, ft_dlstnew(triag, sizeof(t_triag)));
	}
	free_splitted(splitted);
}
