/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 16:48:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Initializes a camera ray to be used in shooting primary/camera rays.
*/

t_ray	init_camera_ray(t_pt2 i, t_scene *scene)
{
	t_ray	cam_ray;
	t_object 	*cam;

	cam = scene->cameras; //fix to find current camera (not first in list)
	t_vec3 pix;
	//convert pixel coords to Camera Sapce
	pix.x = (2 * i.x - 1) * scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * i.y) * cam->scale;
	pix.z = 1; //distance of image screen from camera origin.
	//set camera origin.
	cam_ray.origin = cam->pos;
	//apply ctw matrix on cam_origin
	cam_ray.dir = vec3_normalize(vec3_subtract(pix, cam_ray.origin));
	
	//t_matrix4 ctw = get_ctw_matrix(scene->cam);
	//apply ctw matrix on pix.
	//
	return (cam_ray);
}