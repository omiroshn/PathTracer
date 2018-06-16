/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:36:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/08 16:07:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_source(char **string, t_env *env)
{
	char	*source;
	int		end;
	int		fd;
	char	*mat_folder_name;
	int		i;

	end = get_primitive_end(*string);
	if ((*string)[0] != '"' || (*string)[end - 1] != '"')
		ERR("String values should be in quotes");
	source = ft_strsub(*string, 1, end - 2);
	if (!source)
		ERR("Empty external_object value");
	i = ft_strlen(source) - 1;
	while (i >= 0 && source[i] != '/')
		i--;
	if (i < 0)
		mat_folder_name = NULL;
	else
		mat_folder_name = ft_strsub(source, 0, i + 1);
	(fd = open(source, O_RDONLY)) != -1
		? read_obj_scene(fd, env, mat_folder_name)
		: ft_err_handler("OBJ Format Parser", "OBJ file does not exist!", 0, 0);
	free(source);
	free(mat_folder_name);
	*string = *string + end;
}

int			get_primitive_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ',' && str[i] != '}' && str[i] != ']')
		i++;
	if (str[i] == 0)
		return (-1);
	return (i);
}

char		*remove_whitespaces(char *string)
{
	char	*result;
	int		quote;
	int		i;

	result = (char *)ft_memalloc(ft_strlen(string) + 1);
	quote = 0;
	i = 0;
	while (*string)
	{
		if (*string == '"')
			quote ^= 1;
		if ((*string != ' ' && *string != '\t' && *string != '\n') || quote)
		{
			result[i] = *string;
			i++;
		}
		string++;
	}
	result[i] = 0;
	return (result);
}

char		*get_file_content(char *name)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*result;
	int		empty_file;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		ERR("No such file");
	line = NULL;
	if (read(fd, line, 0) == -1)
		ERR("No such file");
	result = NULL;
	empty_file = 1;
	while (ft_get_next_line(fd, &line) == 1)
	{
		empty_file = 0;
		temp = result;
		result = ft_strjoin(result, line);
		free(temp);
		free(line);
	}
	empty_file ? ERR("The scene is empty") : 0;
	free(line);
	return (result);
}

void		read_scene(t_parser_thread_info *d)
{
	char	*raw;
	char	*no_whitespaces;
	char	*no_whitespaces_start;

	ft_printf("Scene {yellow}'%s'{nc} parsing started...\n", d->file_name);
	raw = get_file_content(d->file_name);
	d->env->load_progress += 0.2;
	no_whitespaces = remove_whitespaces(raw);
	no_whitespaces_start = no_whitespaces;
	free(raw);
	parse_scene(&no_whitespaces, d->env);
	d->env->load_progress += 0.2;
	free(no_whitespaces_start);
	d->env->scene.objs_c = ft_dlstsize(d->env->scene.objs_l);
	d->env->scene.objs_h = dlist_to_obj_array(d->env->scene.objs_l,
											d->env->scene.objs_c);
	allocate_textures(d->env);
	d->env->load_progress += 0.1;
	cl_reinit_mem(&d->env->cl, &d->env->scene.texs_info,
		sizeof(cl_int2) * d->env->scene.texs_c, d->env->scene.texs_info_h);
	cl_reinit_mem(&d->env->cl, &d->env->scene.texs,
		d->env->scene.texs_bts, d->env->scene.all_texs);
	ft_printf("Scene file parsing... {green}DONE{nc}\n");
	d->env->load_progress += 0.2;
	d->env->flags.scene_parsed = 1;
}
