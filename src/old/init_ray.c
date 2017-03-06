/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 14:39:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 15:04:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_ray	init_ray(t_raytracing_tools *r, t_ray_type ray_type)
{
	t_ray	ray;

	ray.type = ray_type;
	if (ray_type == R_CAMERA)
		return (init_camera_ray());
	else if (ray_type == R_SHADOW)
		return (init_shadow_ray());
	else if (ray_type == R_DIFFUSE)
		return (init_diffuse_ray());
	else if (ray_type == R_SPECULAR)
		return (init_specular_ray());
	// else if (ray_type == R_DIFFUSE)
	// 	return (init_relfection_ray());
	// else if (ray_type == R_DIFFUSE)
	// 	return (init_refraction_ray());
	// else if (ray_type == R_DIFFUSE)
	// 	return (init_ambient_ray());	
}