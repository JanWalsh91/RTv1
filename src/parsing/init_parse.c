/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:43:48 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/25 15:16:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void	init_parse(t_parse_tools *t)
{
	if (!(t->f = malloc(sizeof(t->f) * T_COUNT)))
		ft_errno_exit();
	t->f[T_CLOSE_BRACKET] = &parse_close_bracket;
	t->f[T_OPEN_BRACKET] = &parse_open_bracket;
	t->f[T_SCENE] = &parse_scene;
	t->f[T_CAMERA] = &parse_camera;
	t->f[T_LIGHT] = &parse_light;
	t->f[T_PLANE] = &parse_plane;
	t->f[T_SPHERE] = &parse_sphere;
	t->f[T_CYLINDER] = &parse_cylinder;
	t->f[T_CONE] = &parse_cone;
	t->f[T_RESOLUTION] = &parse_resolution;
	t->f[T_RAY_DEPTH] = &parse_ray_depth;
	t->f[T_BACKGROUND_COLOR] = &parse_background_color;
	t->f[T_POSITION] = &parse_position;
	t->f[T_DIRECTION] = &parse_direction;
	t->f[T_ROTATION] = &parse_rotation;
	t->f[T_LOOK_AT] = &parse_look_at;
	t->f[T_COLOR] = &parse_color;
	t->f[T_RADIUS] = &parse_radius;
	t->f[T_HEIGHT] = &parse_height;
	t->f[T_REFRACTION] = &parse_refraction;
	t->f[T_REFLECTION] = &parse_reflection;
	t->f[T_SPECULAR] = &parse_specular;
	t->f[T_TRANSPARENCY] = &parse_transparency;
	t->f[T_FOV] = &parse_fov;
	t->f[T_INTENSITY] = &parse_intensity;
	t->f[T_IMPORT_RT_FILE] = &import_rt_file;
	t->f[T_READ_RT_FILE] = &read_rt_file;
	t->f[T_READ_OBJ_FILE] = &read_obj_file;
	t->f[T_READ_TEXTURE_FILE] = &read_texture_file;
	t->f[T_READ_MATERIAL_FILE] = &read_material_file;
	t->f[T_INVALID_TOKEN] = &invalid_token;
}