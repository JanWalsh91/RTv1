/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:39 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 13:32:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	get_sphere_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
static void	get_plane_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
static void	get_cylinder_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
static void	get_cone_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);

void	get_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	if (ray->hit_type == T_SPHERE)
		get_sphere_normal(r, ray, obj);
	if (ray->hit_type == T_PLANE || ray->hit_type == T_DISK)
		get_plane_normal(r, ray, obj);
	if (ray->hit_type == T_CYLINDER)
		get_cylinder_normal(r, ray, obj);
	if (obj->type == T_CONE)
		get_cone_normal(r, ray, obj);
}

static void	get_sphere_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	(void)r;
	ray->nhit = (v_sub(ray->hit, obj->pos));
	// ray->nhit = v_scale(v_sub(ray->hit, obj->pos), ray->n_dir);
	ray->nhit = v_norm(ray->nhit);
}

static void	get_plane_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	if (ray->hit_type == T_DISK)
	{
		
	}
	(void)r;
	ray->nhit = v_norm(obj->dir);
}

static void	get_cylinder_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	t_vec3	x;
	double	m;

	(void)r;
	
	x = v_sub(ray->origin, obj->pos);
	m = v_dot(ray->dir, v_scale(obj->dir, ray->t)) + v_dot(x, obj->dir);
	x = v_add(obj->pos, v_scale(obj->dir, m));
	ray->nhit = v_norm(v_sub(ray->hit, x));
}

static void	get_cone_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	t_vec3	x;
	// double	m;

	// x = v_sub(ray->origin, obj->pos);
	// m = v_dot(ray->dir, v_scale(obj->dir, ray->t)) + v_dot(x, obj->dir);
	// double a = m * tan(obj->angle) * tan(obj->angle);
	// t_vec3 A = v_scale(obj->dir, a);
	// ray->nhit = v_norm(v_sub(ray->hit, A));

    // ray->nhit.x = (ray->hit.x - obj->pos.x) * (obj->height / obj->rad);
    // ray->nhit.y = obj->rad / obj->height;
    // ray->nhit.z = (ray->hit.z - obj->pos.z) * (obj->height / obj->rad);
    // ray->nhit = v_norm(ray->nhit);


	// ray->nhit = (P - V) - (|(P - V)| \ cos(a)) * A;
	x = v_sub(ray->hit, obj->pos);
	ray->nhit = v_sub(x, v_scale(obj->dir, (v_length(x) / cos(obj->angle))));
	ray->nhit = v_norm(ray->nhit);
	ray->n_dir = v_dot(ray->nhit, ray->dir) < 0 ? 1 : -1;
}