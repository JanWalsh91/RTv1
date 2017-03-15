/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 14:22:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Returns 1 if an intersection was found. 0 if an intersection was not found.
** If there is an intersection, modifies ray->t: the distance of ray->origin
** to the intersection, in order to get the closest intersecting object.
*/

bool		intersects(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	if (obj->type == T_SPHERE)
		return (get_sphere_intersection(r, ray, obj));
	else if (obj->type == T_PLANE)
		return (get_plane_intersection(r, ray, obj));
	else if (obj->type == T_DISK)
		return (get_disk_intersection(r, ray, obj));
	else if (obj->type == T_CYLINDER)
		return (get_cylinder_intersection(r, ray, obj));
	else if (obj->type == T_CONE)
		return (get_cone_intersection(r, ray, obj));
	return (false); //error ? (should never get here)
}

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
	t_intersection_tools 	i;
	int						n_dir;

	n_dir = 1;
	if (v_dot(obj->dir, ray->dir) > 0) //check if hits back side
		n_dir = -1; //change normal direction
	i.d1 = v_dot(v_scale(obj->dir, n_dir), ray->dir);
    if (i.d1 < -1e-6)
	{ 
		i.v1 = v_sub(obj->pos, ray->origin); //switch?
		i.r1 = v_dot(i.v1, v_scale(obj->dir, n_dir)) / i.d1;
		if (i.r1 < 0)
			return (false);
		//check ray type: ONLY UPDATES INTERSECTION INFO IF APPPROPRIATE RAY
		if (r->t > i.r1) //if closer intersection, 
		{
			ray->t = i.r1; //update ray-hitpointer intersection distance
			if (ray->type == R_PRIMARY) //update more info if primary ray
			{
				ray->n_dir = n_dir; 
				ray->hit_obj = obj;
				ray->hit_type = T_PLANE;
			}
		}
		return (true);
    }
	return (false);
}

/*
** Consider doing sphere intersection with quadratic equation instead.
*/

bool		get_sphere_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	t_intersection_tools	i;
	int						n_dir;

	n_dir = 1;
	//CHECK SIDE OF INTERSECTION FOR NORMAL
	//if one of the roots is negative and the other position, the ray origin in witihin the sphere, thus, normal is inversed.
	i.v1 = v_sub(ray->origin, obj->pos);
	i.q.x = v_dot(ray->dir, ray->dir);
	i.q.y = 2 * v_dot(i.v1, ray->dir);
	i.q.z = v_dot(i.v1, i.v1) - pow(obj->rad, 2);
 	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	(i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0; //pick the smallest one.
	if (i.r1 < 0) //the smallest one is negative, thus take the other one and normal direction is inversed.
	{
		i.r1 = i.r2;
		n_dir = -1;
	} 
	if (i.r1 < 0) //both are negative (no intersection)
		return (false);
	if (r->t > i.r1) //found a closer intersection
	{
		ray->t = i.r1; //save closer itersection
		// printf("udpate ray->t: [%f]\n", ray->t);
		if (ray->type == R_PRIMARY)
		{
			ray->n_dir = n_dir;
			ray->hit_obj = obj;
			ray->hit_type = T_SPHERE;
		}
	}
	return (true);
}

// TO BE UPDATED: check when update info
bool		get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj)
{
	t_intersection_tools	i;
	int						n_dir;

	i.n_dir = 1;
	i.v3 = v_sub(ray->origin, obj->pos);
	i.v1 = v_scale(obj->dir, v_dot(ray->dir, obj->dir));
	i.v1 = v_sub(ray->dir, i.v1);
	i.q.x = v_dot(i.v1, i.v1);
	i.v2 = v_scale(obj->dir, v_dot(i.v3, obj->dir));
	i.v2 = v_sub(i.v3, i.v2);
	i.q.y = 2 * v_dot(i.v1, i.v2);
	i.q.z = v_dot(i.v2, i.v2) - powf(obj->rad, 2);
 	if (!solve_quadratic(i.q, &i.r1, &i.r2))
		return (false);
	(i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0;
	obj->height > 0 ? get_finite_cylinder_intersection(r, ray, obj, &i) : 0;
	if (i.r1 < 0 || isnan(i.r1)) //the smallest one is negative, thus take the other one and normal direction is inversed.
	{
		i.n_dir = -1;
		i.r1 = i.r2;
	} 
	if (i.r1 < 0 || isnan(i.r1))	
		return (false);
	if (r->t > i.r1)
	{
		ray->t = i.r1;
		if (ray->type == R_PRIMARY)
		{
			ray->hit_obj = obj;
			ray->hit_type = T_CYLINDER;
			ray->n_dir = i.n_dir;
		}
	}
	return (true);
}

bool		get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i)
{
	if (i->r1 > 0) //first point;
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r1));
		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0)
			i->r1 = NAN;
	}
	if (i->r2 > 0) //second point;
	{
		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0)
			i->r2 = NAN;
	}
	return (true);
}


bool		get_disk_intersection(t_raytracing_tools *r, t_ray *ray, t_object *disk)
{
	t_intersection_tools	i;
	int						n_dir;

	n_dir = 1;
	if (v_dot(disk->dir, ray->dir) > 0)
		n_dir = -1;
	i.d1 = v_dot(v_scale(disk->dir, n_dir), ray->dir);
    if (i.d1 < -1e-6)
	{ 
		i.v1 = v_sub(disk->pos, ray->origin); //switch?
		i.r1 = v_dot(i.v1, v_scale(disk->dir, n_dir)) / i.d1;
		if (i.r1 < 0)
			return (false);
		t_vec3 hitpoint = v_add(ray->origin, v_scale(ray->dir, i.r1));
		if (v_length(v_sub(hitpoint, disk->pos)) > disk->rad)
			return (false);
		if (r->t > i.r1)
		{
			ray->t = i.r1;
			if (ray->type == R_PRIMARY)
			{
				ray->hit_obj = disk;
				ray->hit_type = T_DISK;
				ray->n_dir = n_dir;
			}
		}
		return (true);
    }
	return (false);
}

bool		get_cyclinder_caps_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i)
{
	t_object	disk;
	t_ray		ray2;
	
	ray2 = *ray;
	disk.rad = obj->rad;
	disk.pos = obj->pos;
	disk.dir = obj->dir;
	if (get_disk_intersection(r, &ray2, &disk))
		ray2.t < i->r1 || i->r1 == -1 ? i->r1 = ray2.t : 0;
	disk.pos = v_add(disk.pos, v_scale(obj->dir, obj->height));
	if (get_disk_intersection(r, &ray2, &disk))
		ray2.t < i->r1 || i->r1 == -1 ? i->r1 = ray2.t : 0;
	return (true);
}

bool		get_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *cone)
{
	t_intersection_tools i;
    t_vec3    ori_cen;
    double    k;

	k = tan(cone->angle);
    ori_cen = v_sub(ray->origin, cone->pos);
    i.q.x = v_dot(ray->dir, ray->dir) - (1.0 + k * k) * powf(v_dot(ray->dir, cone->dir), 2.0);
    i.q.y = 2 * (v_dot(ray->dir, ori_cen) - (1.0 + k * k) * v_dot(ray->dir, cone->dir)
                * v_dot(ori_cen, cone->dir));
    i.q.z = v_dot(ori_cen, ori_cen) - (1.0 + k * k) * powf(v_dot(ori_cen,
                cone->dir), 2.0);
    if (!solve_quadratic(i.q, &i.r1, &i.r2) || (i.r1 < 0 && i.r2 < 0))
        return (0);
    (i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0;
	cone->height > 0 ? get_finite_cone_intersection(r, ray, cone, &i) : 0;
	if (i.r1 < 0 || isnan(i.r1)) //the smallest one is negative, thus take the other one
		i.r1 = i.r2;
	if (i.r1 < 0 || isnan(i.r1))	
		return (false);
	if (r->t > i.r1)
	{
		ray->t = i.r1;
		if (ray->type == R_PRIMARY)
		{
			ray->hit_obj = cone;
			ray->hit_type = T_CONE;
		}
	}
	return (true);
}

bool		get_finite_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i)
{
	bool	r1_too_low;
	bool	r1_too_high;
	bool	r2_too_low;
	bool	r2_too_high;

	r1_too_low = lower_than_min(i->r1, i, obj, ray) || i->r1 == -1;
	r1_too_high = higher_than_max(i->r1, i, obj, ray) || i->r1 == -1;
	r2_too_low = lower_than_min(i->r2, i, obj, ray) || i->r2 == -1;
	r2_too_high = higher_than_max(i->r2, i, obj, ray) || i->r2 == -1;
	if (r1_too_low || r1_too_high)
	{
		i->r1 = NAN;
		if (r2_too_low || r2_too_high)
			i->r2 = NAN;
	}
	else if (!r1_too_low && !r1_too_high)
		i->r2 = NAN;
	return (true);
}

bool		lower_than_min(double r, t_intersection_tools *i, t_object *obj, t_ray *ray)
{
	if (r > 0)
	{
		if (v_dot(obj->dir, v_sub(v_add(ray->origin, v_scale(ray->dir, r)), obj->pos)) < 0.0)
			return (true);		
	}
	else
		return (true);
	return (false);
}
bool		higher_than_max(double r, t_intersection_tools *i, t_object *obj, t_ray *ray)
{
	if (r > 0)
	{
		if (v_dot(obj->dir, v_sub(v_add(ray->origin, v_scale(ray->dir, r)),
			v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0.0)
			return (true);		
	}
	else
		return (true);
	return (false);
}