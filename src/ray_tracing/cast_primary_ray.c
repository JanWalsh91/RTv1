/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_primary_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 11:10:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 14:59:32 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_color		cast_primary_ray(t_raytracing_tools *r, t_ray *ray)
{
	t_color		color;
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_ray		shadow_ray;

	r->t = INFINITY;
	color = v_new(0, 0, 0);
	o_ptr = r->scenes->objects;
	while (o_ptr)
	{
		if (intersects(r, ray, o_ptr) && r->t > ray->t)
			r->t = ray->t;
		o_ptr = o_ptr->next;
	}
	if (r->t == INFINITY)
		return (r->scenes->background_color);
	ray->hit = v_add(ray->origin, v_scale(ray->dir, r->t));
	get_normal(r, ray, ray->hit_obj);
	l_ptr = r->scenes->lights;
	while (l_ptr)
	{
		if (!in_shadow(r, ray, &shadow_ray, l_ptr))
		{
			color = v_add(color, get_diffuse(r, ray, &shadow_ray, l_ptr));
			color = v_add(color, get_specular(r, ray, &shadow_ray, l_ptr));
			// color = ray->hit_obj->col;
		}
		l_ptr = l_ptr->next;
	}
	color = v_add(color, get_ambient(r));
	return (v_clamp(color, 0, 255));
}