/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/10 14:15:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Initializes a camera ray to be used in shooting primary/camera rays.
*/

t_ray	init_camera_ray(t_pt2 i, t_scene *scene)
{
	t_ray		cam_ray;
	t_object 	*cam;

	cam = scene->cameras; //fix to find current camera (not first in list)
	t_vec3 pix;
	pix.x = (2 * (i.x + 0.5) / (float)scene->res.x - 1) * scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (i.y + 0.5) / (float)scene->res.y) * cam->scale;
	pix.z = 1; //distance of image screen from camera origin.
	if (i.x == 0 && i.y == 0)
	{
		printf("pix vec: ");
		print_vec(pix);
	}
	//set camera origin.
	cam_ray.origin = cam->pos;
	// set the direction of the camera based on pix.
	// rotation is not taken into account yet.
	// insead of simple assignement, calc ctw matrix and apply its result on pix to dir.
	cam_ray.dir = vec3_normalize(pix);
	// cam_ray.dir = vec3_matrix4_product(cam_ray.dir, cam->ctw);
	// cam_ray.dir = vec3_normalgit subize(cam_ray.dir);
	if (i.x == 0 && i.y == 0)
	{
		printf("cam origin: ");
		print_vec(cam_ray.origin);
		printf("cam dir: ");
		print_vec(cam_ray.dir);
	}

	return (cam_ray);
}