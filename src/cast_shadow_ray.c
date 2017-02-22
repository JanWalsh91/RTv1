/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:22:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/22 17:47:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	cast_shadow_ray(t_ray *cam_ray, t_object *hitobj, t_scene *scene)
{
	t_object	*light;
	t_object	*obj;
	double		t;
	t_ray		ray;
	t_color		new_col;

	light = scene->lights;
	while (light)
	{
		ray.dir = v_norm(v_sub(cam_ray->hit, light->pos));
		ray.origin = v_add(cam_ray->hit, v_scale(cam_ray->nhit, BIAS));
		t = v_length(v_sub(light->pos, cam_ray->hit));
		obj = scene->objects;
		while (obj)
		{
			if (get_intersection(&ray, obj))
			{
				if (0 > ray.t || ray.t > t)
					break ;
			}
			obj = obj->next; 
		}
		double r2 = powf(v_length(v_sub(cam_ray->hit, light->pos)), 2);
		new_col = v_scale(v_mult(light->col, v_scale(hitobj->col, light->intensity / (255 * 4 * M_PI * r2))), ft_clampd(v_dot(v_scale(ray.dir, -1), cam_ray->nhit), 0, 1));
		new_col = v_clamp(new_col, 0, 255);
		cam_ray->col = v_clamp(v_add(cam_ray->col, new_col), 0, 255);
		// cam_ray->col = v_new(50, 50, 50);
		light = light->next;
	}
}

// hitobj->col

// v_mult(hitobj->col, v_scale(light->col, 1 / 255))
// diffuse color

// spherical light distance

// phong