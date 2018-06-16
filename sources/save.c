/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 17:36:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 15:43:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

long	print_camera(char *buf, t_cam *cam)
{
	return (sprintf(buf,
		"\t\"camera\": {\n\t\t\"position\": [%.2f, %.2f, %.2f],\n"
		"\t\t\"angles\": [%.2f, %.2f, %.2f]\n\t},\n",
		cam->pos.x, cam->pos.y, cam->pos.z,
		cam->rot.x, cam->rot.y, cam->rot.z));
}

long	print_object_rest(char *buf, t_obj o, t_env *e)
{
	const char	*mts[] = {"\"diffuse\"", "\"emissive\"",
		"\"reflect\"", "\"transparent\"", "\"glass\"", "\"negative\""};
	long		ln;

	ln = 0;
	if (o.material < sizeof(mts) / sizeof(char *))
		ln = sprintf(buf, "\t\t\t\"material\": %s", mts[o.material]);
	if (o.id_tex != 0)
	{
		ln += sprintf(buf + ln, ",\n\t\t\t\"texture\": \"%s\"",
			((t_texture *)ft_dlstindex(e->scene.tex_l,
										o.id_tex - 1)->content)->source);
		ln += sprintf(buf + ln, ",\n\t\t\t\"scale\": %.2f", o.scale);
	}
	ln += sprintf(buf + ln, "\n\t\t}");
	return (ln);
}

long	print_object(char *buf, t_obj o, t_env *e)
{
	long		ln;

	ln = sprintf(buf, "\t\t{\n\t\t\t\"type\": %s,\n",
		*get_obj_type(o.type, 0, 0));
	ln += sprintf(buf + ln, "\t\t\t\"center\": [%.2f, %.2f, %.2f],\n",
		o.pos.x, o.pos.y, o.pos.z);
	o.type == PLANE ?
		(ln += sprintf(buf + ln, "\t\t\t\"normal\": [%.2f, %.2f, %.2f],\n",
			o.dir.x, o.dir.y, o.dir.z)) :
		(ln += sprintf(buf + ln, "\t\t\t\"center2\": [%.2f, %.2f, %.2f],\n",
			o.dir.x, o.dir.y, o.dir.z));
	ln += sprintf(buf + ln, "\t\t\t\"center3\": [%.2f, %.2f, %.2f],\n",
			o.dir2.x, o.dir2.y, o.dir2.z);
	o.type == CONE ?
		(ln += sprintf(buf + ln, "\t\t\t\"angle\": %.2f,\n", o.rad)) :
		(ln += sprintf(buf + ln, "\t\t\t\"radius\": %.2f,\n", o.rad));
	ln += sprintf(buf + ln, "\t\t\t\"radius2\": %.2f,\n", o.rad2);
	ln += sprintf(buf + ln, "\t\t\t\"emission\": %.2f,\n", o.emission);
	ln += sprintf(buf + ln, "\t\t\t\"color\": [%.2f, %.2f, %.2f],\n",
		o.color.x, o.color.y, o.color.z);
	ln += print_object_rest(buf + ln, o, e);
	return (ln);
}

long	print_objects(char *buf, int objs_c, t_obj *objs_h, t_env *e)
{
	int		i;
	long	len;

	len = 0;
	i = -1;
	if (objs_c)
	{
		len = sprintf(buf, "\t\"figures\": [\n");
		while (++i < objs_c - 1)
		{
			len += print_object(buf + len, objs_h[i], e);
			len += sprintf(buf + len, ",\n");
		}
		len += print_object(buf + len, objs_h[i], e);
		len += sprintf(buf + len, "\n	]\n}\n");
	}
	else
		len += sprintf(buf + len, "\t\"figures\": []\n}\n");
	return (len);
}

void	save_scene(t_env *e)
{
	char	*buf;
	long	len;
	char	scene_path[256];
	int		fd;

	buf = (char *)ft_memalloc(0x4000000);
	len = sprintf(buf,
		"{\n\t\"ambient_light\": %.2f,\n", e->scene.ambient_light);
	len += print_camera(buf + len, e->cam);
	len += print_objects(buf + len, e->scene.objs_c, e->scene.objs_h, e);
	sprintf(scene_path, "./resources/scenes/scene_%ld.sc", time(NULL));
	if ((fd = open(scene_path, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR)) != -1)
	{
		write(fd, buf, len);
		ft_printf("{green}Scene successfully saved to '%s'{nc}\n", scene_path);
	}
	free(buf);
}
