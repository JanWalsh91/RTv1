/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/14 14:48:26 by jwalsh           ###   ########.fr       */
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
	t_vec3 pix;

	cam = scene->cameras; //fix to find current camera (not first in list)
	//compute cam_dir in Screen Space/Camera Space
	pix.x = (2 * (i.x + 0.5) / (float)scene->res.x - 1) * scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (i.y + 0.5) / (float)scene->res.y) * cam->scale;
	pix.z = CAM_IMG_PANE_DIST; //distance of image screen from camera origin.
	cam_ray.dir = vec3_normalize(pix);
	// if (i.x == 0 && i.y == 0)
	// {
	// 	printf("pix vec: ");
	// 	print_vec(pix);
	// }
	//set cam_ray origin in world space.
	cam_ray.origin = cam->pos;
	//transform the ray.dir to world space (a common space where all object are).
	cam_ray.dir = vec3_matrix4_product(cam_ray.dir, cam->ctw);
	cam_ray.dir = vec3_normalize(cam_ray.dir);
	if (i.x == 0 && i.y == 0)
	{
		printf("cam origin: ");
		print_vec(cam_ray.origin);
		printf("cam dir: ");
		print_vec(cam_ray.dir);
	}

	return (cam_ray);
}