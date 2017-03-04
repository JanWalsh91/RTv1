/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raytracing_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 14:16:37 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 14:20:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Sets all options on. 
*/

void	init_raytracing_tools(t_raytracing_tools *r)
{
	r->options.shadows = 1;
	r->options.diffuse = 1;
	r->options.specular = 1;
	r->options.reflection = 1;
	r->options.refraction = 1;
	r->options.ambient = 1;
	r->options.antialiasing = 1;
	r->options.textures = 1;
	r->options.bump_mapping = 1;
	r->options.normal_mapping = 1;
	r->options.filters = 1;
}