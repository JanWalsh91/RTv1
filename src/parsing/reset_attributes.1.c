/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_attributes.1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 15:41:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/02 16:08:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Resets the attributes.
*/

int	reset_attributes(t_attributes *att)
{
	// printf("RESET_ATTRIBUTES\n");
	//scene
	att->res.x = -1;
	att->res.y = -1;
	att->ray_depth = -1;
	//light
	att->intensity = NAN;
	//camera
	att->fov = NAN;
	//objects
	att->pos = v_new(NAN, NAN, NAN);
	att->dir = v_new(NAN, NAN, NAN);
	att->rot = v_new(NAN, NAN, NAN);
	att->look_at = v_new(NAN, NAN, NAN);
	att->col = v_new(NAN, NAN, NAN);
	att->rad = NAN;
	att->height = NAN;
	att->refraction = NAN;
	att->reflection = NAN;
	att->specular = NAN;
	att->transparency = NAN;
	// print_attributes(*att);
	return(1);
}
