/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:40:52 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/11 18:29:37 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_camera(char **string, t_cam *pts)
{
	int		colon_index;
	char	*name;

	SOB(string);
	while (**string && **string != '}')
	{
		colon_index = GCI(*string);
		name = ft_strsub(*string, 0, colon_index);
		*string = *string + colon_index + 1;
		if (!ft_strcmp(name, "\"position\""))
			parse_cl_float3(string, &pts->pos);
		else if (!ft_strcmp(name, "\"angles\""))
			parse_cl_float3(string, &pts->rot);
		else
			ERR("Unknown camera property");
		SC(string, **string);
		free(name);
	}
	SCB(string);
}

void		parse_figure(char **string, t_obj *p, t_scene *scene)
{
	int			i;
	char		*name;
	const char	*sys[] = {"\"type\"", "\"center\"", "\"center2\"", "\"normal\"",
	"\"emission\"", "\"radius\"", "\"angle\"", "\"color\"", "\"material\"",
	"\"radius2\"", "\"specular\"", "\"texture\"", "\"scale\"", "\"center3\""};
	const void	*data[] = {&p->type, &p->pos, &p->dir, &p->dir, &p->emission,
		&p->rad, &p->rad, &p->color, &p->material, &p->rad2, &p->spec,
		&p->id_tex, &p->scale, &p->dir2};
	static void	(*func[])() = {parse_figure_type, parse_cl_float3,
		parse_cl_float3, parse_cl_float3, parse_float, parse_float,
		parse_float, parse_cl_float3, parse_material, parse_float, parse_float,
		parse_texture, parse_float, parse_cl_float3};

	SOB(string);
	while (**string && **string != '}' && (i = -1)
		&& (name = ft_strsub(*string, 0, GCI(*string))))
	{
		*string = *string + GCI(*string) + 1;
		while (++i < (int)(sizeof(sys) / sizeof(char *)))
			FIND_FUNC(name, sys[i], func[i], string, data[i], scene);
		i >= (int)(sizeof(sys) / sizeof(char *)) ? ERR("Figure property") : 0;
		SC(string, **string);
		free(name);
	}
	SCB(string);
}

int			count_objects(char *string)
{
	int	i;
	int	count;
	int	end;
	int	open_brackets;

	count = 0;
	while (*string && *string != ']')
	{
		i = -1;
		open_brackets = 0;
		while (string[++i])
		{
			string[i] == '{' ? open_brackets++ : 0;
			string[i] == '}' ? open_brackets-- : 0;
			if (string[i] == '}' && open_brackets == 0)
				break ;
		}
		if ((end = (string[i] == 0 ? -1 : i + 1)) == -1)
			break ;
		string = string + end;
		count++;
	}
	return (count);
}

void		parse_figure_array(char **string, t_scene *pts)
{
	t_obj	*new;
	uint	i;

	i = 0;
	if (pts->objs_l)
		i = ((t_obj *)pts->objs_l->prev->content)->id + 1;
	SOBK(string);
	while (**string && **string != ']')
	{
		new = ft_memalloc(sizeof(t_obj));
		new->id = i++;
		parse_figure(string, new, pts);
		!new->scale ? new->scale = 1.0F : 0;
		ft_dlstpush_back(&pts->objs_l, ft_dlstnew(new, sizeof(t_obj)));
		SC(string, **string);
	}
	SCBK(string);
}

void		parse_scene(char **string, t_env *env)
{
	int		colon_index;
	char	*name;

	SOB(string);
	while (**string && **string != '}')
	{
		colon_index = GCI(*string);
		name = ft_strsub(*string, 0, colon_index);
		*string = *string + colon_index + 1;
		if (!ft_strcmp(name, "\"camera\""))
			parse_camera(string, env->cam);
		else if (!ft_strcmp(name, "\"figures\""))
			parse_figure_array(string, &env->scene);
		else if (!ft_strcmp(name, "\"ambient_light\""))
			parse_float(string, &env->scene.ambient_light);
		else if (!ft_strcmp(name, "\"external_object\""))
			parse_source(string, env);
		else
			ERR("Unknown scene property");
		SC(string, **string);
		free(name);
	}
	SCB(string);
}
