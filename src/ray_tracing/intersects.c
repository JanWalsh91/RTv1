/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 15:54:30 by jwalsh           ###   ########.fr       */
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
	obj->dir = v_norm(obj->dir); //should already be done before. Just checking...
	if (obj->type == T_SPHERE)
		return (get_sphere_intersection(r, ray, obj));
	else if (obj->type == T_PLANE)
		return (get_plane_intersection(r, ray, obj));
	// else if (obj->type == T_CYLINDER)
	// 	return (get_cylinder_intersection(r, ray, obj));
	// else if (obj->type == T_CONE)
	// 	return (get_cone_intersection(r, ray, obj));
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
	i.d1 = v_dot(obj->dir, ray->dir);
	if (i.d1 < 0) //only for double-sided polygons. //update
	{
		n_dir = -1;
		i.d1 = v_dot(v_scale(obj->dir, n_dir), ray->dir);
	}
    if (i.d1 > 1e-6)
	{ 
		i.v1 = v_sub(obj->pos, ray->origin); //switch?
		i.r1 = v_dot(i.v1, v_scale(obj->dir, n_dir)) / i.d1;
		if (i.r1 < 0)
			return (false);
		//check ray type: ONLY UPDATES INTERSECTION INFO IF APPPROPRIATE RAY
		if (r->t > i.r1)
		{
			ray->t = i.r1;
			if (ray->type == R_PRIMARY)
			{
				ray->hit_obj = obj;
				ray->hit_type = T_PLANE;
				ray->n_dir = n_dir;
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
			ray->hit_obj = obj;
			ray->hit_type = T_SPHERE;
			ray->n_dir = n_dir;
		}
	}
	return (true);
}

//TO BE UPDATED: check when update info
// bool		get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj)
// {
// 	t_intersection_tools	i;

// 	i.v3 = v_sub(ray->origin, obj->pos);
// 	i.v1 = v_scale(obj->dir, v_dot(ray->dir, obj->dir));
// 	i.v1 = v_sub(ray->dir, i.v1);
// 	i.q.x = v_dot(i.v1, i.v1);
// 	i.v2 = v_scale(obj->dir, v_dot(i.v3, obj->dir));
// 	i.v2 = v_sub(i.v3, i.v2);
// 	i.q.y = 2 * v_dot(i.v1, i.v2);
// 	i.q.z = v_dot(i.v2, i.v2) - powf(obj->rad, 2);
//  	if (!solve_quadratic(i.q, &i.r1, &i.r2))
// 		return (false);
// 	obj->height > 0 ? get_finite_cylinder_intersection(ray, obj, &i) : 0;
// 	(i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0;
// 	obj->height > 0 ? get_cyclinder_caps_intersection(ray, obj, &i) : 0;
// 	(i.r1 < 0) ? i.r1 = i.r2 : 0;
// 	if (i.r1 < 0)
// 		return (false);
// 	ray->t = i.r1;
// 	return (true);
// }

// bool		get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i)
// {
// 	//chek for validity of roots. 
// 	//set to -1 those which are not on finite cylinder body.
// 	//check first point: distance r1
// 	if (i->r1 > 0) //first point;
// 	{
// 		i->p = v_add(ray->origin, v_scale(ray->dir, i->r1));
// 		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
// 			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0)
// 			i->r1 = -1;
// 	}
// 	if (i->r2 > 0) //second point;
// 	{
// 		i->p = v_add(ray->origin, v_scale(ray->dir, i->r2));
// 		if (v_dot(obj->dir, v_sub(i->p, obj->pos)) < 0 ||
// 			v_dot(obj->dir, v_sub(i->p, v_add(obj->pos, v_scale(obj->dir, obj->height)))) > 0)
// 			i->r2 = -1;
// 	}
// 	return (true);
// }

// bool		get_disc_intersection(t_raytracing_tools *r, t_ray *ray, t_object *disc)
// {
// 	double	denom;
// 	t_vec3	tmp;
// 	t_vec3	p;

// 	tmp = disc->dir;
// 	denom = v_dot(tmp, tmp);
// 	if (denom < 0) //only for double-sided polygons.
// 	{
// 		tmp = v_scale(disc->dir, -1);
// 		denom = v_dot(tmp, ray->dir);
// 	}
//     if (denom > 1e-6)
// 	{ 
// 		p = v_sub(disc->pos, ray->origin); // switch ??
// 		ray->t = v_dot(p, tmp) / denom; //distance of intersection to ray origin.
// 		p = v_add(ray->origin, v_scale(ray->dir, ray->t)); //point of intersection
// 		if (v_dot(v_sub(p, disc->pos), v_sub(p, disc->pos)) < powf(disc->rad, 2))
// 			return (ray->t >= 0); 
// 	}
// 	return (false);
// }

// bool		get_cyclinder_caps_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i)
// {
// 	t_object	disc;
// 	t_ray		ray2;
	
// 	ray2 = *ray;
// 	disc.rad = obj->rad;
// 	disc.pos = obj->pos;
// 	disc.dir = obj->dir;
// 	if (get_disc_intersection(&ray2, &disc))
// 		ray2.t < i->r1 || i->r1 == -1 ? i->r1 = ray2.t : 0;
// 	disc.pos = v_add(disc.pos, v_scale(obj->dir, obj->height));
// 	if (get_disc_intersection(&ray2, &disc))
// 		ray2.t < i->r1 || i->r1 == -1 ? i->r1 = ray2.t : 0;
// 	return (true);
// }


// //not yet quite working. 
// bool		get_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj)
// {
// 	t_intersection_tools	i;

// 	i.d1 = pow(obj->rad / obj->height, 2.);
// 	i.v1 = v_sub(ray->origin, obj->pos);
// 	i.q.x = v_dot(ray->dir, ray->dir) - (1 + i.d1) * powf(v_dot(ray->dir, obj->dir), 2);
// 	i.q.y = 2 * (v_dot(ray->dir, i.v1) - (1 + i.d1) * v_dot(ray->dir, obj->dir) * v_dot(i.v1, obj->dir));
// 	i.q.z = v_dot(i.v1, i.v1) - (1 + i.d1) * powf(v_dot(i.v1, obj->dir), 2);
//  	if (!solve_quadratic(i.q, &i.r1, &i.r2))
// 	 	return (false);
// 	(i.r2 < i.r1) ? ft_swapd(&i.r1, &i.r2) : 0;
// 	(i.r1 < 0) ? i.r1 = i.r2 : 0;
// 	if (i.r1 < 0)
// 		return (false);
// 	ray->t = i.r1;	
// 	return (true);
// }