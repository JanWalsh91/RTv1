/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/10 16:32:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** 
*/

int		get_intersection(t_ray *ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (get_sphere_intersection(ray, obj));
	else if (obj->type == PLANE)
		return (get_plane_intersection(ray, obj));
	return (1);
}

int		get_sphere_intersection(t_ray *ray, t_object *obj)
{
	t_vec2 t;
	t_vec2 th;
	float	d2;
	float	tmp;

	t_vec3 p = vec3_subtract(obj->pos, ray->origin);
	th.x = vec3_dot(p, ray->dir);
	if (th.x < 0)
		return (0); 
	d2 = vec3_dot(p, p) - th.x * th.x; 
	if (d2 > obj->rad * obj->rad)
		return (0); 
	th.y = sqrt(obj->rad * obj->rad - d2); 
	t.x = th.x - th.y; 
	t.y = th.x + th.y;
	if (t.x > t.y)
	{
		tmp = t.x;
		t.x = t.y;
		t.y = tmp;		
	}
	if (t.x < 0)
	{ 
		t.x = t.y; // if t0 is negative, let's use t.y instead 
		if (t.x < 0)
			return (0); // both t0 and t.y are negative 
	}
	ray->t = t.x;
	//ft_printf("INTERSECTION!");
	return (1);
}

int	get_plane_intersection(t_ray *ray, t_object *obj)
{
    float denom;
	t_vec3 p;

	denom = vec3_dot(obj->rot, ray->dir);
	if (denom < 0) //only for double-sided polygons.
	{
		obj->rot = vec3_product(obj->rot, -1);
		denom = vec3_dot(obj->rot, ray->dir);
	}
    if (denom > 1e-6)
	{ 
		p = vec3_subtract(obj->pos, ray->origin);
		ray->t = vec3_dot(p, obj->rot) / denom;
        return (ray->t >= 0); 
    }
	// printf("\n");
	return (0); 
}