/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_disk_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:29:23 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:11:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Checks for a ray-disk intersection.
*/

bool	get_disk_intersection(t_raytracing_tools *r, t_ray *ray, t_object *disk)
{
	t_intersection_tools	i;
	t_vec3					hitpoint;

	i.n_dir = 1;
	if (v_dot(disk->dir, ray->dir) > 0)
		i.n_dir = -1;
	i.d1 = v_dot(v_scale(disk->dir, i.n_dir), ray->dir);
	if (i.d1 > -1e-6)
		return (false);
	i.v1 = v_sub(disk->pos, ray->origin);
	i.r1 = v_dot(i.v1, v_scale(disk->dir, i.n_dir)) / i.d1;
	if (i.r1 < 0)
		return (false);
	hitpoint = v_add(ray->origin, v_scale(ray->dir, i.r1));
	if (v_length(v_sub(hitpoint, disk->pos)) > disk->rad)
		return (false);
	r->t > i.r1 ? ray->t = i.r1 : 0;
	if (ray->type == R_PRIMARY && r->t > i.r1)
	{
		ray->hit_obj = disk;
		ray->hit_type = T_DISK;
	}
	return (true);
}
