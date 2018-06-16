/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:43:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 16:32:16 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include <time.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
#  include <fcntl.h>
# endif

# include "sgl.h"
# include "structures.h"

# define PROGRAM_NAME "RT"

# define KERNEL_FOLDER "./resources/kernels/"
# define IMAGES_FOLDER "./resources/images/"

# define W_WIDTH 1440
# define W_HEIGHT 810

# define EXIT_KEY SDLK_ESCAPE

# define MAX_KERNEL_SIZE 0x400000

# define F3_S sizeof(cl_float3)

typedef struct	s_flag
{
	uint		move_m : 1;
	uint		move_f : 1;
	uint		move_b : 1;
	uint		sidle_l : 1;
	uint		sidle_r : 1;
	uint		move_u : 1;
	uint		move_d : 1;
	uint		sprint : 1;
	uint		obj_info : 1;
	uint		pause : 1;
	uint		kernels_parsed : 1;
	uint		scene_parsed : 1;
	t_effect	effect : sizeof(t_material);
}				t_flag;

typedef enum	e_tab {
	NO_TAB = 0,
	EFFECTS,
	ADD_FIGURE
}				t_tab;

typedef enum	e_f_pos_tab {
	CENTER1 = 0,
	CENTER2,
	CENTER3
}				t_f_pos_tab;

typedef struct	s_cl_core
{
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
}				t_cl_core;

typedef struct	s_cl_kl
{
	cl_program	program;
	cl_kernel	kernel;
	cl_mem		mem;
	cl_mem		mem_out;
}				t_cl_kl;

typedef struct	s_cam
{
	cl_float3	pos;
	cl_float3	rot;
	t_cl_kl		kl;
	t_viewport	*vwp;
}				t_cam;

typedef struct	s_selected
{
	int			drag;
	SDL_Rect	pos;
	t_obj		obj;
	t_cl_kl		kl;
	t_f_pos_tab	active_pos;
}				t_selected;

typedef struct	s_triag
{
	cl_int3	a;
	cl_int3	b;
	cl_int3	c;
	int		material_index;
}				t_triag;

typedef struct	s_mtl_material
{
	char		*name;
	cl_float3	color;
	uint		tex_id;
}				t_mtl_material;

typedef struct	s_texture
{
	uint	w;
	uint	h;
	uint	*pixels;
	char	*source;
}				t_texture;

typedef struct	s_fig
{
	uint			v_c;
	uint			vt_c;
	uint			vn_c;
	cl_float3		*v;
	cl_float3		*vt;
	cl_float3		*vn;
	t_dlist			*f;
	t_mtl_material	*materials;
}				t_fig;

typedef struct	s_scene
{
	uint		objs_c;
	uint		sampls;
	uint		timestamp;
	uint		texs_c;
	uint		texs_bts;
	cl_mem		objs;
	cl_mem		texs_vt;
	cl_mem		texs;
	cl_mem		texs_info;
	cl_mem		colors;
	float		ambient_light;
	uint		*all_texs;
	cl_int2		*texs_info_h;
	t_fig		*fig;
	t_obj		*objs_h;
	t_dlist		*objs_l;
	t_dlist		*tex_l;
	t_dlist		*tex_vt_l;
}				t_scene;

typedef struct	s_time
{
	uint		delta;
}				t_time;

typedef struct	s_env
{
	t_cl_core		cl;
	t_sgl_window	*win;
	t_cam			*cam;
	t_scene			scene;
	t_flag			flags;
	t_selected		sel_obj;
	t_cl_kl			vis_effect;
	t_time			time;
	t_tab			active_tab;
	float			move_speed;
	float			load_progress;
}				t_env;

typedef struct	s_parser_thread_info
{
	char		*file_name;
	t_env		*env;
	pthread_t	thread;
}				t_parser_thread_info;

/*
**				Render.c
**				↓↓↓↓↓↓↓↓
*/

void			apply_effect(t_env *env);

void			init_scene(t_env *env);

void			render_scene(t_env *env);

/*
**				Events.c
**				↓↓↓↓↓↓↓↓
*/

int				poll_events(t_env *env);

/*
**				Scene_1.c
**				↓↓↓↓↓↓↓↓↓
*/

# define ERR(s) ft_err_handler(s, 0, 0, 1)

# define FIND_FUNC(n, s, f, st, d, sc){if(!ft_strcmp(n,s)){f(st, d, sc);break;}}

# define SOB(s){**s!='{'?ERR("Open '{' is missing"):0;++*s;}
# define SCB(s){**s!='}'?ERR("Closing '}' is missing"):0;++*s;}
# define SOBK(s){**s!='['?ERR("Open '[' is missing"):0;++*s;}
# define SCBK(s){**s!=']'?ERR("Closing ']' is missing"):0;++*s;}
# define SC(s, c){c!=','&&c!='}'&&c!=']'?ERR("',' is missing"):0;c==','?++*s:0;}
# define GCI(s)({int i=-1;do{i++;}while((s)[i]&&(s)[i]!=':');i;})

int				get_primitive_end(char *string);

char			*get_object_or_array_string(char *string, int type,
											void *place_to_save);

char			*parse_text_as(char *string, int type, void *place_to_save);

/*
**				Scene_1.c
**				↓↓↓↓↓↓↓↓↓
*/

void			read_scene(t_parser_thread_info *d);

void			parse_source(char **string, t_env *env);

/*
**				Scene_2.c
**				↓↓↓↓↓↓↓↓↓
*/

void			parse_float(char **string, float *pts);

void			parse_string(char **string, char **pts);

void			parse_figure_type(char **string, short int *pts);

void			parse_material(char **string, t_material *pts);

void			parse_cl_float3(char **string, cl_float3 *pts);

/*
**				Scene_3.c
**				↓↓↓↓↓↓↓↓↓
*/

void			parse_scene(char **string, t_env *env);

/*
**				Obj_parser_1.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			read_obj_scene(int fd, t_env *env, char *mat_folder_name);

t_dlist			*get_content(int fd);

uint			add_texture(t_dlist **tex_l, char *source);

/*
**				Obj_parser_2.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			parse_texture(char **string, uint *pts, t_scene *scene);

cl_float3		parse_float2(char *string);

cl_float3		parse_float3(char *string);

cl_int3			parse_float3_facet(char *string);

void			add_triag(char *string, int material_index, t_dlist **triags);

/*
**				Obj_parser_3.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			malloc_fig(t_dlist *rows, t_fig *fig);

t_mtl_material	*get_materials(char *string, t_env *env, char *mat_folder_name);

/*
**				Obj_parser_4.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			parse_obj_figure(t_dlist *row, t_dlist *rows,
									t_env *e, char *mat_folder_name);

t_triag			*create_triag(char *a, char *b, char *c, int material_index);

/*
**				Mtl_parser.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

t_mtl_material	parse_newmtl(char *string, t_dlist *rows);

/*
**				Stats.c
**				↓↓↓↓↓↓↓
*/

void			display_fps(SDL_Renderer *rend, t_env *env);

uint			stats_handler(int x, int y);

void			display_stats(t_env *env, SDL_Renderer *rend);

/*
**				Movement.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			move(t_env *env, char state, t_point dir);

void			movement_keys(SDL_Scancode key, t_env *env, char state);

void			handle_movement(t_env *env);

void			view_mousemove(t_env *env);

/*
**				Vec.c
**				↓↓↓↓↓
*/

cl_float3		vec_add(cl_float3 v1, cl_float3 v2);

cl_float3		vec_sub(cl_float3 v1, cl_float3 v2);

cl_float3		cross(cl_float3 v1, cl_float3 v2);

cl_float3		vec_mult_num(cl_float3 v1, float num);

/*
**				Utils_1.c
**				↓↓↓↓↓↓↓↓↓
*/

cl_float3		tofloat3(t_point point);

t_point			topoint(cl_float3 point);

void			display_usage(t_uchar help);

void			resize_viewport(t_viewport *vwp, int width, int height);

void			init_env(t_env *env);

/*
**				Utils_2.c
**				↓↓↓↓↓↓↓↓↓
*/

cl_float3		dir_vector(t_point dir, t_env *env);

void			screenshot(t_env *env);

int				count_splitted(char **arr);

void			free_splitted(char **arr);

void			allocate_textures(t_env *env);

/*
**				Utils_3.c
**				↓↓↓↓↓↓↓↓↓
*/
const char		**get_obj_type(long id, t_uchar clear, long *size);

t_obj			*dlist_to_obj_array(t_dlist *dlst, uint count);

void			parse_all_kernels(t_env *env);

void			add_figure(t_scene *scene, t_obj *new);

double			r0to1(void);

/*
**				Obj_info.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			draw_info(SDL_Rect *p, t_env *env);

uint			obj_info_mouse_click_handler(int x, int y, t_env *e);

void			obj_info_mouse_move_handler(int x, int y, t_env *e);

uint			find_obj(t_env *env);

/*
**				OpenCl.c
**				↓↓↓↓↓↓↓↓
*/

void			cl_reinit_mem(t_cl_core *cl, cl_mem *mem,
								size_t size, void *ptr);

void			cl_init(t_cl_core *cl, cl_device_type dev_type);

void			cl_parse_kernel(t_cl_core *cl, t_cl_kl *kl,
						const char *kernel_name, const char *func_name);

/*
**				Sys_handler.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			ft_err_handler(const char *msg, const char *add,
								int err, t_uchar stop);

/*
**				Save.c
**				↓↓↓↓↓↓
*/

void			save_scene(t_env *env);

void			init_controls(t_env *env);

/*
**				Async_read.c
**				↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			process_scene(int ac, char *scene_name, t_env *env);

void			process_kernels(t_env *env);

/*
**				Design_2.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			init_color_textbox(t_env *env);

void			init_minus_button(t_env *env);

void			init_plus_button(t_env *env);

/*
**				Design_3.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_pause_btn_click(t_env *env, t_control *c);

void			init_render_pause_button(t_env *env);

void			init_emission_minus_button(t_env *env);

void			init_emission_plus_button(t_env *env);

/*
**				Design_4.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			init_x_textbox(t_env *env);

void			init_x_minus_button(t_env *env);

void			init_x_plus_button(t_env *env);

/*
**				Design_5.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			init_y_textbox(t_env *env);

void			init_y_minus_button(t_env *env);

void			init_y_plus_button(t_env *env);

/*
**				Design_6.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			init_z_textbox(t_env *env);

void			init_z_minus_button(t_env *env);

void			init_z_plus_button(t_env *env);

/*
**				Design_7.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			init_emission_textbox(t_env *env);

void			init_p1_textbox(t_env *env);

void			init_p2_textbox(t_env *env);

/*
**				Design_8.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_material_click(t_env *env, t_control *c);

void			init_defuse_material_button(t_env *env);

void			init_emissive_material_button(t_env *env);

void			init_reflection_material_button(t_env *env);

void			init_transp_material_button(t_env *env);

/*
**				Design_9.c
**				↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_scroll(t_env *env, t_control *c, int y);

void			init_glass_material_button(t_env *env);

void			init_negative_material_button(t_env *env);

void			init_actions_panel(t_env *env);

void			init_effects_panel(t_env *env);

/*
**				Design_10.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_effect_click(t_env *env, t_control *c);

void			init_negative_effect_button(t_env *env);

void			init_sepia_effect_button(t_env *env);

void			init_grayscale_effect_button(t_env *env);

void			init_comic_effect_button(t_env *env);

/*
**				Design_11.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_tabs_click(t_env *env, t_control *c);

void			init_screenshot_button(t_env *env);

void			init_save_scene_button(t_env *env);

/*
**				Design_12.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_effects_tab_button(t_env *env);

void			init_bnw_effect_button(t_env *env);

void			init_casting_effect_button(t_env *env);

void			init_fxaa_effect_button(t_env *env);

void			init_oil_effect_button(t_env *env);

/*
**				Design_13.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_spec_textbox(t_env *env);

void			init_spec_minus_button(t_env *env);

void			init_spec_plus_button(t_env *env);

/*
**				Design_14.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_scale_textbox(t_env *env);

void			init_scale_minus_button(t_env *env);

void			init_scale_plus_button(t_env *env);

/*
**				Design_15.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_first_pos_button(t_env *env);

void			init_second_pos_button(t_env *env);

void			init_third_pos_button(t_env *env);

/*
**				Design_16.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_x_pos_scroll(t_env *env, t_control *c, int y);

void			ctrl_y_pos_scroll(t_env *env, t_control *c, int y);

void			ctrl_z_pos_scroll(t_env *env, t_control *c, int y);

/*
**				Design_17.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_obj_add_tab_button(t_env *env);

void			init_obj_add_panel(t_env *env);

void			init_add_sphere_button(t_env *env);

void			init_add_cylinder_button(t_env *env);

void			init_add_cone_button(t_env *env);

/*
**				Design_18.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_add_plane_button(t_env *env);

void			init_add_elips_button(t_env *env);

void			init_add_parabol_button(t_env *env);

void			init_add_hyperbol_button(t_env *env);

void			init_add_disc_button(t_env *env);

/*
**				Design_19.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_add_cube_button(t_env *env);

void			init_add_torus_button(t_env *env);

void			init_add_mebius_button(t_env *env);

void			init_add_julia_button(t_env *env);

void			init_add_pyramid_button(t_env *env);

/*
**				Design_20.c
**				↓↓↓↓↓↓↓↓↓↓↓
*/

void			init_add_mandelbulb_button(t_env *env);

void			init_add_tetrahedron_button(t_env *env);

/*
**				Add_figure_1.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_add_sphere(t_env *e);

void			ctrl_add_cylinder(t_env *e);

void			ctrl_add_cone(t_env *e);

void			ctrl_add_plane(t_env *e);

void			ctrl_add_elips(t_env *e);

/*
**				Add_figure_2.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_add_parabol(t_env *e);

void			ctrl_add_hyperbol(t_env *e);

void			ctrl_add_disc(t_env *e);

void			ctrl_add_cube(t_env *e);

void			ctrl_add_torus(t_env *e);

/*
**				Add_figure_3.c
**				↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

void			ctrl_add_mebius(t_env *e);

void			ctrl_add_julia(t_env *e);

void			ctrl_add_pyramid(t_env *e);

void			ctrl_add_mandelbulb(t_env *e);

void			ctrl_add_tetrahedron(t_env *e);

#endif
