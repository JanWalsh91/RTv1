/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 15:47:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	get_sphere_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
static void	get_plane_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
// static void	get_cylinder_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);

void	get_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	if (ray->hit_type == T_SPHERE)
		get_sphere_normal(r, ray, obj);
	if (ray->hit_type == T_PLANE)
		get_plane_normal(r, ray, obj);
	// if (obj->type == T_CYLINDER)
	// 	get_cylinder_normal(r, ray, obj);
	// if (obj->type == T_CONE)
	// 	get_cone_normal(r, ray, obj);
}

static void	get_sphere_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	(void)r;
	ray->nhit = v_scale(v_sub(ray->hit, obj->pos), ray->n_dir);
	ray->nhit = v_norm(ray->nhit);
}

static void	get_plane_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	(void)r;
	ray->nhit = v_scale(v_norm(obj->dir), ray->n_dir);
}

// static void	get_cylinder_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
// {
// 	(void)ray;
// 	(void)obj;
// 	(void)n;
// 	return (*n);	
// }

// static void	get_cone_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
// {
// 	(void)ray;
// 	(void)obj;
// 	(void)n;
// 	return (*n);	
// }