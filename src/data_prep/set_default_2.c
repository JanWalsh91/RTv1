/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:29:34 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:33:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Functions for setting default values for
** - position (pos)
** - color (col)
** - intensity
** - radius
*/

void	set_default_pos(t_scene *scene, int type, void *obj, t_vec3 *pos)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj),
			"Providing default position.");
	else if (type == T_PLANE || type == T_DISK || type == T_SPHERE ||
		type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default position.");
	else if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj),
			"Providing default position.");
	*pos = v_new(DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z);
}

void	set_default_col(t_scene *scene, int type, void *obj, t_vec3 *col)
{
	if (type == T_LIGHT)
		data_warning(scene, type, ((t_light *)obj),
			"Providing default color.");
	else if (type == T_PLANE || type == T_DISK || type == T_SPHERE ||
			type == T_CONE || type == T_CYLINDER)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default color.");
	else if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj),
			"Providing default color.");
	*col = v_new(DEFAULT_COL_R, DEFAULT_COL_G, DEFAULT_COL_B);
}

void	set_default_intensity(t_scene *scene, int type,
		void *obj, double *intensity)
{
	data_warning(scene, type, ((t_light *)obj),
		"Providing default intensity.");
	*intensity = DEFAULT_INTENSITY;
}

void	set_default_radius(t_scene *scene, int type, void *obj, double *radius)
{
	if (type == T_CONE || type == T_CYLINDER || type == T_SPHERE)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default radius.");
	*radius = DEFAULT_RADIUS;
}
