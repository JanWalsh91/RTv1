/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 14:04:10 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 14:55:30 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Calculates and returns the ambient value of the color.
*/

t_color	get_ambient(t_raytracing_tools *r)
{
	return (v_clamp(v_scale(r->scenes->ambient_light_color,
	r->scenes->ambient_light_coef), 0, 255));
}