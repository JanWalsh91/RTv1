/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 13:13:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:06:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Throws a shadow ray for each light in the scene.
** Returns true if there is an intersection between a light and the origin of
** the ray, else returns false.
*/

bool	in_shadow(t_raytracing_tools *r, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light)
{
	t_object	*obj;
	double		max;

	r->t = INFINITY;
	shadow_ray->type = R_SHADOW;
	shadow_ray->origin = v_add(primary_ray->hit,
		v_scale(primary_ray->nhit, BIAS * primary_ray->n_dir));
	if (!v_isnan(light->pos))
		max = v_length(v_sub(light->pos, shadow_ray->origin));
	else
		max = INFINITY;
	if (!v_isnan(light->pos))
		shadow_ray->dir = v_sub(light->pos, shadow_ray->origin);
	else
		shadow_ray->dir = v_scale(light->dir, -1);
	shadow_ray->dir = v_norm(shadow_ray->dir);
	obj = r->scenes->objects;
	while (obj)
	{
		if (intersects(r, shadow_ray, obj) &&
			shadow_ray->t < max && shadow_ray->t > 0)
			return (true);
		obj = obj->next;
	}
	return (false);
}
