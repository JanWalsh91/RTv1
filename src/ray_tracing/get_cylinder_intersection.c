/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cylinder_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:27:49 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:17:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	t_object *obj, t_intersection_tools *i);

/*
** Checks for a cylinder-ray intersection.
*/

bool		get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	t_object *obj)
{
	t_intersection_tools	i;

	i.v3 = v_sub(ray->origin, obj->pos);
	i.v1 = v_sub(ray->dir, v_scale(obj->dir, v_dot(ray->dir, obj->dir)));
	i.q.x = v_dot(i.v1, i.v1);
	i.v2 = v_sub(i.v3, v_scale(obj->dir, v_dot(i.v3, obj->dir)));
	i.q.y = 2 * v_dot(i.v1, i.v2);
	i.q.z = v_dot(i.v2, i.v2) - pow(obj->rad, 2);
	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	(i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0;
	get_finite_cylinder_intersection(r, ray, obj, &i);
	(i.r1 < 0 || isnan(i.r1)) ? i.r1 = i.r2 : 0;
	if (i.r1 < 0 || isnan(i.r1))
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = obj;
		ray->hit_type = T_CYLINDER;
	}
	return (true);
}

static void	get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray,
	t_object *obj, t_intersection_tools *i)
{
	if (i->r1 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r1));
		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos,
			v_scale(obj->dir, obj->height)))) > 0)
			i->r1 = NAN;
	}
	if (i->r2 > 0)
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos,
			v_scale(obj->dir, obj->height)))) > 0)
			i->r2 = NAN;
	}
}
