/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diffuse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:18:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 16:18:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"



t_color	get_diffuse(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	double	r2;
	(void)r;


	r2 = powf(v_length(v_sub(shadow_ray->origin, light->pos)), 2.0);
	new_col = v_scale(v_mult(light->col, v_scale(primary_ray->hit_obj->col, light->intensity /
		(255.0 * 4 * M_PI * r2))), ft_clampd(v_dot(v_scale(shadow_ray->dir, 1), v_scale(primary_ray->nhit, primary_ray->n_dir)), 0, 1));
	new_col = v_clamp(new_col, 0, 255);
	if (primary_ray->hit_type == T_SPHERE && new_col.x < 10)
	{
		
	}
	return (new_col);
}