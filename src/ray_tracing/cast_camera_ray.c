/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:57:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 17:09:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Returns the color of a pixel.
*/

t_color	cast_camera_ray(t_ray *cam_ray, t_scene *scene)
{
	// printf("CAST_CAMERA_RAY\n");
	t_object	*obj;
	t_object	*hitobj;
	double		t;

	hitobj = NULL;
	t = INFINITY;
	obj = scene->objects;
	// iterate over all objects and update the closest intersection.
	cam_ray->col = scene->background_color; //background color
	while (obj)
	{
		if (get_intersection(cam_ray, obj) && cam_ray->t < t)
		{
			t = cam_ray->t;
			hitobj = obj;
			update_ray(cam_ray, obj, &t);
		}
		obj = (obj)->next;
	}
	//if an intersection has been found, t is the distance to closest one.
	if (t != INFINITY)
	{
		// cam_ray->col = hitobj->col;
		cast_shadow_ray(cam_ray, hitobj, scene);
	}
	return (cam_ray->col);
}

void	update_ray(t_ray *ray, t_object *obj, double *t)
{
	*t = ray->t;
	ray->hit = v_add(ray->origin, v_scale(ray->dir, ray->t));
	ray->nhit = get_normal(ray, obj);
}
