/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:13:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/12 15:57:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

bool	in_shadow(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light)
{
	t_object	*obj;
	double		max;

	// printf("IN SHADOW? \n");
	r->t = INFINITY;
	shadow_ray->type = R_SHADOW;
	//move origin by the bias following the direction of the normal
	shadow_ray->origin = v_add(primary_ray->hit, v_scale(primary_ray->nhit, BIAS * primary_ray->n_dir));
	//set max distance
	if (!v_isnan(light->pos))
		max = v_length(v_sub(light->pos, shadow_ray->origin));
	else
		max = INFINITY;
	//set shadow ray direction
	if (!v_isnan(light->pos))
		shadow_ray->dir = v_sub(light->pos, shadow_ray->origin);
	else
		shadow_ray->dir = v_scale(light->dir, -1);
	shadow_ray->dir = v_norm(shadow_ray->dir);
	obj = r->scenes->objects;
	while (obj)
	{
		if (intersects(r, shadow_ray, obj) && shadow_ray->t < max && shadow_ray->t > 0)
			return (true);
		obj = obj->next;
	}
	return (false);
}