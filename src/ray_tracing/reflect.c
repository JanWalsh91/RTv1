/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:21:02 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:22:36 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Given a ray direction and normal at hit point, returns the direction of the
** reflected ray.
*/

t_vec3	reflect(t_vec3 ray_dir, t_vec3 nhit)
{
	return (v_sub(ray_dir, v_scale(nhit, 2 * v_dot(ray_dir, nhit))));
}
