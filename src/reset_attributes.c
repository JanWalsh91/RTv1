/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:50:57 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/12 15:13:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Resets the attributes.
*/

int	reset_attributes(t_attributes *att)
{
	printf("RESET_ATTRIBUTES\n");
	(*att).res.x = INT_MAX;
	(*att).res.y = INT_MAX;
	(*att).ray_depth = INT_MAX;
	(*att).pos.x = NAN;
	(*att).pos.y = NAN;
	(*att).pos.z = NAN;
	(*att).dir.x = NAN;
	(*att).dir.y = NAN;
	(*att).dir.z = NAN;
	(*att).col.r = INT_MAX;
	(*att).col.g = INT_MAX;
	(*att).col.b = INT_MAX;
	(*att).rad = NAN;
	(*att).angle = NAN;
	(*att).height = NAN;
	print_attributes(*att);
	return(1);
}
