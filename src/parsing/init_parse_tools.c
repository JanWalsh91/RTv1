/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:43:48 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:48:03 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initializes t_parse_tools including token list, attribute lists and
** list of function pointers for parsing each token.
*/

static void	init_attributes(t_parse_tools *t);
static void	init_parse_functions(t_parse_tools *t);
static void	init_parse_functions2(t_parse_tools *t);

void		init_parse_tools(t_parse_tools *t)
{
	t->in_scene = false;
	t->in_object = false;
	t->input = NULL;
	t->input_head = NULL;
	t->scenes = NULL;
	t->current_scene = NULL;
	t->current_object = NULL;
	t->current_camera = NULL;
	t->current_light = NULL;
	t->current_type = T_INVALID_TOKEN;
	t->fd = -1;
	t->file_name = NULL;
	t->colors = NULL;
	init_attributes(t);
	init_tokens(t);
	init_parse_functions(t);
}

static void	init_attributes(t_parse_tools *t)
{
	t->global_attributes = NULL;
	t->scene_attributes = NULL;
	t->object_attributes = NULL;
	if (!(t->global_attributes =
		(t_attributes *)ft_memalloc(sizeof(t_attributes))))
		ft_errno_exit();
	if (!(t->scene_attributes =
		(t_attributes *)ft_memalloc(sizeof(t_attributes))))
		ft_errno_exit();
	if (!(t->object_attributes =
		(t_attributes *)ft_memalloc(sizeof(t_attributes))))
		ft_errno_exit();
	reset_attributes(t->global_attributes);
	reset_attributes(t->scene_attributes);
	reset_attributes(t->object_attributes);
}

static void	init_parse_functions(t_parse_tools *t)
{
	if (!(t->parse = malloc(sizeof(t->parse) * T_COUNT)))
		ft_errno_exit();
	t->parse[T_CLOSE_BRACKET] = &parse_close_bracket;
	t->parse[T_OPEN_BRACKET] = &parse_open_bracket;
	t->parse[T_EMPTY_LINE] = &parse_empty_line;
	t->parse[T_SCENE] = &parse_scene;
	t->parse[T_CAMERA] = &parse_camera;
	t->parse[T_LIGHT] = &parse_light;
	t->parse[T_PLANE] = &parse_plane;
	t->parse[T_DISK] = &parse_disk;
	t->parse[T_SPHERE] = &parse_sphere;
	t->parse[T_CYLINDER] = &parse_cylinder;
	t->parse[T_CONE] = &parse_cone;
	t->parse[T_RESOLUTION] = &parse_resolution;
	t->parse[T_RAY_DEPTH] = &parse_ray_depth;
	t->parse[T_BACKGROUND_COLOR] = &parse_background_color;
	t->parse[T_AMBIENT_LIGHT_COLOR] = &parse_ambient_light_color;
	t->parse[T_KA] = &parse_ka;
	init_parse_functions2(t);
}

static void	init_parse_functions2(t_parse_tools *t)
{
	t->parse[T_POSITION] = &parse_position;
	t->parse[T_DIRECTION] = &parse_direction;
	t->parse[T_ROTATION] = &parse_rotation;
	t->parse[T_LOOK_AT] = &parse_look_at;
	t->parse[T_COLOR] = &parse_color;
	t->parse[T_RADIUS] = &parse_radius;
	t->parse[T_HEIGHT] = &parse_height;
	t->parse[T_DIFFUSE_COEF] = &parse_diffuse_coef;
	t->parse[T_REFRACTION] = &parse_refraction;
	t->parse[T_REFLECTION] = &parse_reflection;
	t->parse[T_SPECULAR_EXPONENT] = &parse_specular_exponent;
	t->parse[T_SPECULAR_COEF] = &parse_specular_coef;
	t->parse[T_TRANSPARENCY] = &parse_transparency;
	t->parse[T_FOV] = &parse_fov;
	t->parse[T_INTENSITY] = &parse_intensity;
	t->parse[T_IMPORT_RT_FILE] = &import_rt_file;
	t->parse[T_READ_RT_FILE] = &read_rt_file;
	t->parse[T_READ_OBJ_FILE] = &read_obj_file;
	t->parse[T_READ_TEXTURE_FILE] = &read_texture_file;
	t->parse[T_READ_MATERIAL_FILE] = &read_material_file;
	t->parse[T_HASHTAG] = &hashtag;
	t->parse[T_INVALID_TOKEN] = &invalid_token;
}
