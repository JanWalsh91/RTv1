/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:22:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/03 16:48:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static int	intersection(t_object *obj, t_ray *cam_ray, t_ray *ray, t_light *light);

void	cast_shadow_ray(t_ray *cam_ray, t_object *hitobj, t_scene *scene)
{
	t_light		*light;
	t_ray		ray;
	t_color		new_col;
	// static int	i = 1000;

	light = scene->lights;
	ray.origin = v_add(cam_ray->hit, v_scale(cam_ray->nhit, BIAS));
	while (light)
	{
		if (!intersection(scene->objects, cam_ray, &ray, light))
		{
			double r2 = powf(v_length(v_sub(cam_ray->hit, light->pos)), 2.0);
			new_col = v_scale(v_mult(light->col, v_scale(hitobj->col, light->intensity / (255.0 * 4 * M_PI * r2))), ft_clampd(v_dot(v_scale(ray.dir, -1), cam_ray->nhit), 0, 1));
			new_col = v_clamp(new_col, 0, 255);
			cam_ray->col = v_clamp(v_add(cam_ray->col, new_col), 0, 255);
			// print_vec(cam_ray->col);
		}
		light = light->next;
	}
}

static int	intersection(t_object *obj, t_ray *cam_ray, t_ray *ray, t_light *light)
{
	double	t;

	ray->dir = v_norm(v_sub(cam_ray->hit, light->pos));
	t = v_length(v_sub(light->pos, cam_ray->hit));
	while (obj)
	{
		ray->t = INFINITY;
		if (get_intersection(ray, obj))
		{
			if (0 < ray->t && ray->t < t)
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}