/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:57:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/21 12:05:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Returns the color of a pixel.
*/

t_color	cast_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	// printf("CAST_CAMERA_RAY\n");
	t_color		col;
	t_object *obj;
	double		t;

	t = INFINITY;
	obj = scene->objects;
	// iterate over all objects and update the closest intersection.
	while (obj)
	{
		// Tranform ray origin and direction to model space.
		// cam_ray->dir2 = vec3_normalize(vec3_matrix4_product(cam_ray->dir, obj->wtm));
		// cam_ray->origin2 = pvec3_matrix4_product(cam_ray->origin, obj->wtm);
		if (get_intersection(cam_ray, obj))
		{
			// Update closest interesection and assign color.
			// if (cam_ray->t < t)
			// {
			// 	//update t, 
				t = cam_ray->t;
				col = (obj)->col;
			// 	// printf(" --> t: [%f] cam_ray->t: [%f]\n", t, cam_ray->t);
			// }
		} 
		obj = (obj)->next;
	}
	// If no intersection is found, return background color. 
	(t == INFINITY) ? col.r = 0x0F, col.g = 0x0F, col.b = 0x0F : 0;
	return (col);
}
