/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:43:48 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:53:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void	init_parse_tools(t_parse_tools *t)
{
	reset_attributes(t->global_attributes);
	reset_attributes(t->scene_attributes);
	if (!(t->parse = malloc(sizeof(t->parse) * T_COUNT)))
		ft_errno_exit();
	t->parse[T_CLOSE_BRACKET] = &parse_close_bracket;
	t->parse[T_OPEN_BRACKET] = &parse_open_bracket;
	t->parse[T_SCENE] = &parse_scene;
	t->parse[T_CAMERA] = &parse_camera;
	t->parse[T_LIGHT] = &parse_light;
	t->parse[T_PLANE] = &parse_plane;
	t->parse[T_SPHERE] = &parse_sphere;
	t->parse[T_CYLINDER] = &parse_cylinder;
	t->parse[T_CONE] = &parse_cone;
	t->parse[T_RESOLUTION] = &parse_resolution;
	t->parse[T_RAY_DEPTH] = &parse_ray_depth;
	t->parse[T_BACKGROUND_COLOR] = &parse_background_color;
	t->parse[T_POSITION] = &parse_position;
	t->parse[T_DIRECTION] = &parse_direction;
	t->parse[T_ROTATION] = &parse_rotation;
	t->parse[T_LOOK_AT] = &parse_look_at;
	t->parse[T_COLOR] = &parse_color;
	t->parse[T_RADIUS] = &parse_radius;
	t->parse[T_HEIGHT] = &parse_height;
	t->parse[T_REFRACTION] = &parse_refraction;
	t->parse[T_REFLECTION] = &parse_reflection;
	t->parse[T_SPECULAR] = &parse_specular;
	t->parse[T_TRANSPARENCY] = &parse_transparency;
	t->parse[T_FOV] = &parse_fov;
	t->parse[T_INTENSITY] = &parse_intensity;
	t->parse[T_IMPORT_RT_FILE] = &import_rt_file;
	t->parse[T_READ_RT_FILE] = &read_rt_file;
	t->parse[T_READ_OBJ_FILE] = &read_obj_file;
	t->parse[T_READ_TEXTURE_FILE] = &read_texture_file;
	t->parse[T_READ_MATERIAL_FILE] = &read_material_file;
	t->parse[T_INVALID_TOKEN] = &invalid_token;
}