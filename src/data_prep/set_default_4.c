/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_default_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:29:58 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:35:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Functions for setting default values for
** - field of view (fov)
** - specular coefficient (ks)
** - diffuse coefficient (kd)
** - specular exponent (specular_exp)
*/

void	set_default_fov(t_scene *scene, int type, void *obj, double *fov)
{
	if (type == T_CAMERA)
		data_warning(scene, type, ((t_camera *)obj),
			"Providing default fov.");
	*fov = DEFAULT_FOV;
}

void	set_default_ks(t_scene *scene, int type, void *obj, double *ks)
{
	if (type == T_CONE || type == T_CYLINDER ||
		type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default specular coefficient.");
	*ks = DEFAULT_KS;
}

void	set_default_kd(t_scene *scene, int type, void *obj, double *kd)
{
	if (type == T_CONE || type == T_CYLINDER ||
		type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default diffuse coefficient.");
	*kd = DEFAULT_KD;
}

void	set_default_specular_exp(t_scene *scene, int type,
		void *obj, double *specular_exp)
{
	if (type == T_CONE || type == T_CYLINDER ||
		type == T_SPHERE || type == T_PLANE)
		data_warning(scene, type, ((t_object *)obj),
			"Providing default specular exponent.");
	*specular_exp = DEFAULT_SPECULAR_EXP;
}
