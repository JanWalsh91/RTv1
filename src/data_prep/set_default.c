/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:31:14 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/12 14:00:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void	set_default_resolution(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default resolution.");
	scene->res.x = DEFAULT_RES_H;
	scene->res.y = DEFAULT_RES_W;
}

void	set_default_ray_depth(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default ray depth.");
	scene->ray_depth = DEFAULT_RAY_DEPTH;
}

void	set_default_ambient_light_coef(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default ambient light coefficient.");
	scene->ambient_light_coef = DEFAULT_AMBIENT_LIGHT_COEF;
}

void	set_default_ambient_light_color(t_scene *scene)
{
	data_warning(scene, 0, NULL, "Providing default ambient light color.");
	scene->ambient_light_color = v_new(DEFAULT_AMBIENT_LIGHT_COLOR_R,
										DEFAULT_AMBIENT_LIGHT_COLOR_G,
										DEFAULT_AMBIENT_LIGHT_COLOR_B);
}

void	set_default_pos(t_scene *scene, int type, void *obj, t_vec3 *pos)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default position.");
	else if (type == T_PLANE || type == T_DISK || type == T_SPHERE || type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj), "Providing default position.");
	else if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj), "Providing default position.");
	*pos = v_new(DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);		
}

void	set_default_col(t_scene *scene, int type, void *obj, t_vec3 *col)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default color.");
	else if (type == T_PLANE || type == T_DISK || type == T_SPHERE || type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj), "Providing default color.");
	else if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj), "Providing default color.");
	*col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);		
}

void	set_default_intensity(t_scene *scene, int type, void *obj, double *intensity)
{
	data_warning(scene, type, ((t_light *)obj), "Providing default intensity.");
	*intensity = DEFAULT_INTENSITY;
}

void	set_default_radius(t_scene *scene, int type, void *obj, double *radius)
{
	if (type == T_CONE || type == T_CYLINDER || type == T_SPHERE)
		data_warning(scene, type, ((t_object *)obj), "Providing default radius.");
	*radius = DEFAULT_RADIUS;
}

void	set_default_height(t_scene *scene, int type, void *obj, double *height)
{
	if (type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj), "Providing default height.");
	*height = DEFAULT_HEIGHT;
}

void	set_default_cam_dir(t_scene *scene, int type, void *cam, t_vec3 *dir)
{
	data_warning(scene, type, ((t_camera *)cam), "Providing default direction.");
	*dir = v_new(DEFAULT_CAM_DIR_X, DEFAULT_CAM_DIR_Y, DEFAULT_CAM_DIR_Z);
}

void	set_default_obj_dir(t_scene *scene, int type, void *obj, t_vec3 *dir)
{
	if (type != T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default direction.");
	else
		return ;
	*dir = v_new(DEFAULT_DIR_X, DEFAULT_DIR_Y, DEFAULT_DIR_Z);
}

void	set_default_light_dir(t_scene *scene, int type, void *obj, t_vec3 *dir)
{
	if (type != T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default direction.");
	else
		return ;
	*dir = v_new(DEFAULT_DIR_X, -DEFAULT_DIR_Y, DEFAULT_DIR_Z);
}

void	set_default_fov(t_scene *scene, int type, void *obj, double *fov)
{
	if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj), "Providing default fov.");
	*fov = DEFAULT_FOV;
}

void	set_default_ks(t_scene *scene, int type, void *obj, double *ks)
{
	if (type == T_CONE || type == T_CYLINDER || type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj), "Providing default specular coefficient.");
	*ks = DEFAULT_KS;
}

void	set_default_kd(t_scene *scene, int type, void *obj, double *kd)
{
	if (type == T_CONE || type == T_CYLINDER || type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj), "Providing default diffuse coefficient.");
	*kd = DEFAULT_KD;
}

void	set_default_specular_exp(t_scene *scene, int type, void *obj, double *specular_exp)
{
	if (type == T_CONE || type == T_CYLINDER || type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj), "Providing default specular exponent.");
	*specular_exp = DEFAULT_SPECULAR_EXP;
}