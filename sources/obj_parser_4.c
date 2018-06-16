/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:43:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/08 15:06:29 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					get_material_index(char *string, t_mtl_material *materials)
{
	char	**splitted;
	int		i;

	if (!materials)
		ERR("No mtlib in obj file");
	splitted = ft_strsplit(string, ' ');
	if (count_splitted(splitted) != 2)
		ERR("Invalid mtl name in obj file");
	i = -1;
	while (materials[++i].name)
		if (!ft_strcmp(splitted[1], materials[i].name))
		{
			free_splitted(splitted);
			return (i);
		}
	free_splitted(splitted);
	return (0);
}

void				parse_obj_figure(t_dlist *row, t_dlist *rows,
										t_env *e, char *f_name)
{
	uint	vt_i;
	uint	vn_i;
	uint	v_i;
	uint	f_i;
	int		i;

	vt_i = 0;
	vn_i = 0;
	v_i = 0;
	f_i = 0;
	i = -1;
	while ((row = row->next) != rows)
		if (!ft_strncmp(row->content, "mtllib ", 7) && !e->scene.fig->materials)
			e->scene.fig->materials = get_materials(row->content, e, f_name);
		else if (!ft_strncmp(row->content, "v ", 2))
			e->scene.fig->v[v_i++] = parse_float3(row->content);
		else if (!ft_strncmp(row->content, "vn ", 3))
			e->scene.fig->vn[vn_i++] = parse_float3(row->content);
		else if (!ft_strncmp(row->content, "vt ", 3))
			e->scene.fig->vt[vt_i++] = parse_float2(row->content);
		else if (!ft_strncmp(row->content, "f ", 2))
			add_triag(row->content, i, &e->scene.fig->f);
		else if (!ft_strncmp(row->content, "usemtl ", 7))
			i = get_material_index(row->content, e->scene.fig->materials);
}

t_dlist				*get_content(int fd)
{
	char	*line;
	char	*trimmed_line;
	t_dlist	*ret;
	int		empty_file;

	ret = NULL;
	empty_file = 1;
	while (ft_get_next_line(fd, &line) > 0 && !(empty_file = 0))
	{
		trimmed_line = ft_strtrim(line);
		ft_dlstpush_back(&ret, ft_dlstnew(trimmed_line, 0));
		free(line);
	}
	empty_file ? ERR("The scene is empty") : 0;
	free(line);
	return (ret);
}

t_triag				*create_triag(char *a, char *b, char *c, int material_index)
{
	t_triag	*triag;

	triag = ft_memalloc(sizeof(t_triag));
	triag->a = parse_float3_facet(a);
	triag->b = parse_float3_facet(b);
	triag->c = parse_float3_facet(c);
	triag->material_index = material_index;
	return (triag);
}
