/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:50:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 14:27:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Resets the attributes.
*/

static void	set_vec_to_nan(t_vec3 *v);

int	reset_attributes(t_attributes *att)
{
	// printf("RESET_ATTRIBUTES\n");
	(*att).res.x = INT_MAX;
	(*att).res.y = INT_MAX;
	(*att).ray_depth = INT_MAX;
	set_vec_to_nan(&(*att).pos);
	set_vec_to_nan(&(*att).dir);
	set_vec_to_nan(&(*att).look_at);
	(*att).col.x = INT_MAX;
	(*att).col.y = INT_MAX;
	(*att).col.z = INT_MAX;
	(*att).rad = NAN;
	(*att).angle = NAN;
	(*att).height = NAN;
	(*att).intensity = NAN;
	// print_attributes(*att);
	return(1);
}

static void	set_vec_to_nan(t_vec3 *v)
{
	v->x = NAN;
	v->y = NAN;
	v->z = NAN;
}