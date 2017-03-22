/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_specular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:13:51 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:21:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Calculates and returns the specular value of the color at hitpoint.
*/

t_color	get_specular(t_raytracing_tools *r, t_ray *primary_ray,
		t_ray *shadow_ray, t_light *light)
{
	t_color	new_col;
	double	specular_intensity;
	t_vec3	reflection;
	double	directional_light_factor;

	directional_light_factor = v_isnan(light->pos) ? 1000 : 1;
	reflection = reflect(primary_ray->dir, v_scale(primary_ray->nhit,
		primary_ray->n_dir));
	specular_intensity = pow((ft_clampd(v_dot(reflection,
		shadow_ray->dir), 0, 1)), primary_ray->hit_obj->specular_exp);
	specular_intensity *= light->intensity * primary_ray->hit_obj->ks *
		directional_light_factor;
	new_col = v_scale(light->col, specular_intensity);
	new_col = v_clamp(new_col, 0, 255);
	return (new_col);
}
