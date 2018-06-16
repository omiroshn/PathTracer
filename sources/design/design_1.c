/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:41:11 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 14:22:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	additional_2(t_env *env)
{
	init_add_sphere_button(env);
	init_add_cylinder_button(env);
	init_add_cone_button(env);
	init_add_plane_button(env);
	init_add_elips_button(env);
	init_add_parabol_button(env);
	init_add_hyperbol_button(env);
	init_add_disc_button(env);
	init_add_cube_button(env);
	init_add_torus_button(env);
	init_add_mebius_button(env);
	init_add_julia_button(env);
	init_add_pyramid_button(env);
	init_add_mandelbulb_button(env);
	init_add_tetrahedron_button(env);
}

static void	additional_1(t_env *env)
{
	init_negative_material_button(env);
	init_effects_tab_button(env);
	init_obj_add_tab_button(env);
	init_screenshot_button(env);
	init_save_scene_button(env);
	init_effects_panel(env);
	init_negative_effect_button(env);
	init_sepia_effect_button(env);
	init_grayscale_effect_button(env);
	init_comic_effect_button(env);
	init_bnw_effect_button(env);
	init_casting_effect_button(env);
	init_fxaa_effect_button(env);
	init_oil_effect_button(env);
	init_spec_textbox(env);
	init_spec_minus_button(env);
	init_spec_plus_button(env);
	init_scale_textbox(env);
	init_scale_minus_button(env);
	init_scale_plus_button(env);
	init_first_pos_button(env);
	init_second_pos_button(env);
	init_third_pos_button(env);
	init_obj_add_panel(env);
	additional_2(env);
}

void		init_controls(t_env *env)
{
	init_color_textbox(env);
	init_minus_button(env);
	init_plus_button(env);
	init_actions_panel(env);
	init_render_pause_button(env);
	init_x_textbox(env);
	init_x_minus_button(env);
	init_x_plus_button(env);
	init_y_textbox(env);
	init_y_minus_button(env);
	init_y_plus_button(env);
	init_z_textbox(env);
	init_z_minus_button(env);
	init_z_plus_button(env);
	init_emission_minus_button(env);
	init_emission_plus_button(env);
	init_emission_textbox(env);
	init_p1_textbox(env);
	init_p2_textbox(env);
	init_defuse_material_button(env);
	init_emissive_material_button(env);
	init_reflection_material_button(env);
	init_transp_material_button(env);
	init_glass_material_button(env);
	additional_1(env);
}
