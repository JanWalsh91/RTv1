/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_plane_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:25:30 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 15:25:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Checks if t_ray ray intersects plane obj.
** If the dot product of the ray->dir and obj->dir is close to 0,
** it means the normal of the plane and the direction of the ray are
** perpendicular, which means the plane and the ray are almost parallel.
** Thus, there is no intersection.
**
** We also check if that dot product is negative, in which case the normal
** is facing in the wrong direction. We inverse the normal and check again.
*/

bool	get_plane_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	t_intersection_tools	i;

	i.n_dir = 1;
	if (v_dot(obj->dir, ray->dir) > 0)
		i.n_dir = -1;
	i.d1 = v_dot(v_scale(obj->dir, i.n_dir), ray->dir);
	if (i.d1 > -1e-6)
		return (false);
	i.v1 = v_sub(obj->pos, ray->origin);
	i.r1 = v_dot(i.v1, v_scale(obj->dir, i.n_dir)) / i.d1;
	if (i.r1 < 0)
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = obj;
		ray->hit_type = T_PLANE;
	}
	return (true);
}