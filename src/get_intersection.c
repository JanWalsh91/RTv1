/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:11:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/14 14:19:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Returns 1 if an intersection was found. 0 if an intersection was not found.
** If there is an intersection, modifies ray->t: the distance of ray->origin
** to the intersection, in order to get the closest intersecting object.
*/

int		get_intersection(t_ray *ray, t_object *obj)
{
	if (obj->type == SPHERE)
		return (get_sphere_intersection(ray, obj));
	else if (obj->type == PLANE)
		return (get_plane_intersection(ray, obj));
	else if (obj->type == CYLINDER)
		return (get_cylinder_intersection(ray, obj));
	else if (obj->type == CONE)
		return (get_cone_intersection(ray, obj));
	return (0); //error ? (should never get here)
}

/*
** Consider doing sphere intersection with quadratic equation instead.
*/

int		get_sphere_intersection(t_ray *ray, t_object *obj)
{
	t_vec2 t;
	t_vec2 th;
	float	d2;
	float	tmp;

	t_vec3 p = vec3_subtract(obj->pos, ray->origin);
	th.x = vec3_dot(p, ray->dir);
	if (th.x < 0)
		return (0); 
	d2 = vec3_dot(p, p) - th.x * th.x; 
	if (d2 > obj->rad * obj->rad)
		return (0); 
	th.y = sqrt(obj->rad * obj->rad - d2); 
	t.x = th.x - th.y; 
	t.y = th.x + th.y;
	if (t.x > t.y)
	{
		tmp = t.x;
		t.x = t.y;
		t.y = tmp;		
	}
	if (t.x < 0)
	{ 
		t.x = t.y; // if t0 is negative, let's use t.y instead 
		if (t.x < 0)
			return (0); // both t0 and t.y are negative 
	}
	ray->t = t.x;
	printf("INTERSECTION! : t : [%f]\n", ray->t);
	return (1);
}

/*
** Checks if t_ray ray intersects plane obj.
** If the dot product of the ray->dir and obj->dir is close to 0, 
** it means the normal of the plane and the direction of the ray are
** perpendicular, which means the plane and the ray are almost parallel.
** Thus, there is no intersection. 
**
** We also check if that dot product is negative, in which case the norma;
** is facing in the wrong direction. We inverse the normal and check again.
*/

int	get_plane_intersection(t_ray *ray, t_object *obj)
{
    float denom;
	t_vec3 p;

	denom = vec3_dot(obj->dir, ray->dir);
	if (denom < 0) //only for double-sided polygons.
	{
		obj->dir = vec3_product(obj->dir, -1);
		denom = vec3_dot(obj->dir, ray->dir);
	}
    if (denom > 1e-6)
	{ 
		p = vec3_subtract(obj->pos, ray->origin); // switch ??
		ray->t = vec3_dot(p, obj->dir) / denom;
        return (ray->t >= 0); 
    }
	return (0);
}

//add height to cylinders and check for cap intersection. 

int		get_cylinder_intersection(t_ray *ray, t_object *obj)
{
	t_vec3	q;
	t_vec3 	ray_tmp;
	t_vec3	obj_tmp;
	t_vec3	x;
	double	t;

	ray->dir = vec3_normalize(ray->dir);
	ray_tmp = ray->dir;
	ray_tmp.y = 0;
	obj_tmp = obj->dir;
	obj_tmp.y = 0;

	x = vec3_subtract(ray->origin, obj->pos);
	q.x = vec3_dot(ray_tmp, ray_tmp) - pow(vec3_dot(ray_tmp, obj_tmp), 2); 
	q.y = 2 * (vec3_dot(ray_tmp, x) - vec3_dot(ray_tmp, obj_tmp) * vec3_dot(x, obj_tmp));
	q.z = vec3_dot(x, x) - pow(vec3_dot(x, obj_tmp), 2) - obj->rad * obj->rad;
	if (solve_quadratic(q, &t, ray))
	{
		ray->t = t;
		//check height for BOTH results of quadratic
		//t_vec3 pos = vec3_product(ray->dir, t); //position of intersecting point.
		// printf("INTERSECTION! : t : [%f]\n", ray->t);
		return (1);
	}		
	else
		return (0);
	//get_cap_intersection
	return (0);
}

int		get_cone_intersection(t_ray *ray, t_object *obj)
{
	t_vec3	q;
	double	t;
	double	k;
	t_vec3	x;

	k = pow(obj->rad / obj->height, 2);
	x = vec3_subtract(ray->origin, obj->pos);
	q.x = vec3_dot(ray->dir, ray->dir) - (1 + k) * powf(vec3_dot(ray->dir, obj->dir), 2);
	q.y = 2 * (vec3_dot(ray->dir, x) - (1 + k) * vec3_dot(ray->dir, obj->dir) * vec3_dot(x, obj->dir));
	q.z = vec3_dot(x, x) - (1 + k) * powf(vec3_dot(x, obj->dir), 2);
 	if (solve_quadratic(q, &t, ray))
	{
		ray->t = t;
		return (1);
	}		
	else
		return (0);
	return (0);
}