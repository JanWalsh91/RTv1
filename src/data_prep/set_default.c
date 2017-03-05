/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:31:14 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/03 15:54:59 by jwalsh           ###   ########.fr       */
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

void	set_default_pos(t_scene *scene, int type, void *obj, t_vec3 *pos)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default position.");
	else if (type == T_PLANE || type == T_SPHERE || type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj), "Providing default position.");
	else if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj), "Providing default position.");
	*pos = v_new(DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);		
}

void	set_default_col(t_scene *scene, int type, void *obj, t_vec3 *col)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj), "Providing default color.");
	else if (type == T_PLANE || type == T_SPHERE || type == T_CONE || type == T_CYLINDER)
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

void	set_default_fov(t_scene *scene, int type, void *obj, double *fov)
{
	if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj), "Providing default fov.");
	*fov = DEFAULT_FOV;
}