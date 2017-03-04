/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 17:06:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static t_vec3	get_sphere_normal(t_ray *ray, t_object *obj, t_vec3 *n);
static t_vec3	get_plane_normal(t_ray *ray, t_object *obj, t_vec3 *n);
static t_vec3	get_cylinder_normal(t_ray *ray, t_object *obj, t_vec3 *n);
static t_vec3	get_cone_normal(t_ray *ray, t_object *obj, t_vec3 *n);

t_vec3	get_normal(t_ray *ray, t_object *obj)
{
	t_vec3	n;

	n.x = 0;
	n.y = 0;
	n.z = 0;
	if (ray->hit_type == T_SPHERE)
		return (get_sphere_normal(ray, obj, &n));
	if (ray->hit_type == T_PLANE)
		return (get_plane_normal(ray, obj, &n));
	if (obj->type == T_CYLINDER)
		return (get_cylinder_normal(ray, obj, &n));
	if (obj->type == T_CONE)
		return (get_cone_normal(ray, obj, &n));
	return (n);
}

static t_vec3	get_sphere_normal(t_ray *ray, t_object *obj, t_vec3 *n)
{
	(void)ray;
	(void)obj;
	(void)n;
	*n = v_sub(ray->hit, obj->pos);
	*n = v_norm(*n);
	return (*n);
}

static t_vec3	get_plane_normal(t_ray *ray, t_object *obj, t_vec3 *n)
{
	(void)ray;
	(void)obj;
	(void)n;
	*n = v_scale(v_norm(obj->dir), -1);
	return (*n);	
}

static t_vec3	get_cylinder_normal(t_ray *ray, t_object *obj, t_vec3 *n)
{
	(void)ray;
	(void)obj;
	(void)n;
	return (*n);	
}

static t_vec3	get_cone_normal(t_ray *ray, t_object *obj, t_vec3 *n)
{
	(void)ray;
	(void)obj;
	(void)n;
	return (*n);	
}