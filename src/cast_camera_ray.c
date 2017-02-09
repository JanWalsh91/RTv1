/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:57:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/07 16:24:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Returns the color of a pixel.
*/

t_color	cast_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	t_color		col;
	float		t;

	t = INFINITY;
	//printf("CAST_CAMERA_RAY\n");
	t_object *current_object;
	
	current_object = scene->objects;
	while (current_object)
	{
		//printf("intersection with: [%s]\n", (*current_object)->name);
		if (get_intersection(cam_ray, current_object))
		{
			if (cam_ray->t < t)
			{
				t = cam_ray->t;
				col = (current_object)->col;
			}
		} 
		current_object = (current_object)->next;
	}
	(t == INFINITY) ? col.r = 0x0F, col.g = 0x0F, col.b = 0x0F : 0;
	return (col);
}
