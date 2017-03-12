/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diffuse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:18:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/12 16:44:07 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Gets the diffuse value of the color at hitpoint.
*/

t_color	get_diffuse(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	double	r2;
	(void)r;

	if (!v_isnan(light->pos))
		r2 = powf(v_length(v_sub(shadow_ray->origin, light->pos)), 2.0);
	else
		r2 = 1 / (4 * M_PI);
	new_col = v_scale(v_mult(light->col, v_scale(primary_ray->hit_obj->col, light->intensity /
		(4 * M_PI * r2))), ft_clampd(v_dot(shadow_ray->dir, v_scale(primary_ray->nhit, primary_ray->n_dir)), 0, 1));
	new_col = v_scale(new_col, primary_ray->hit_obj->kd);
	new_col = v_clamp(new_col, 0, 255);
	return (new_col);
}