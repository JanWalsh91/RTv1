/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 15:58:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_color		cast_primary_ray(t_raytracing_tools *r, t_ray *ray)
{
	t_color		color;
	t_object	*obj;
	t_light		*light;
	t_ray		shadow_ray;

	// check intersections with all objects
	//	set max distance to inf;
	r->t = INFINITY;
	// set color to black
	color = v_new(0, 0, 0);
	obj = r->scenes->objects;
	while (obj)
	{
		// keep the closest one and calulate distance, point of intersection and normal at intersection.
		if (intersects(r, ray, obj) && r->t > ray->t)
			r->t = ray->t; //update closest distance
		obj = obj->next;
	}
	if (r->t == INFINITY)
		return (r->scenes->background_color);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, r->t));
	get_normal(r, ray, ray->hit_obj);
	light = r->scenes->lights;
	while (light)
	{
		if (!in_shadow(r, ray, &shadow_ray, light))
		{
			color = v_add(color, get_diffuse(r, ray, &shadow_ray, light));
		}
		// else
		// 	color = v_add(color, v_scale(obj->col, 0.1));
		light = light->next;
	}
	// color = v_add(color, get_diffuse())
	//color = ray->hit_obj->col;
	// get color at closest intersection point
	return (color);
}

/*

get color: 
determine the effect of each light on the hit point.
for each light:
	if in shade: return black
	else
		color += get_diffuse
		color += get_specular
return (color)

intersection functions:
	return true or false if an there is an intersection
	if the ray type == R_PRIMARY (or reflection/refraction), updates intersection point, and normal at intersection



*/

