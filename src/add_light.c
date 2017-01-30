/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 12:09:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new light to the list t_lights.
*/

#include "../inc/rtv1.h"

void	add_light(t_light **lights, t_light *new_light)
{
	if (new_light)
	{
		if (!*lights)
			*lights = new_light;
		else
		{
			while ((*lights)->next)
				*lights = (*lights)->next;
			(*lights)->next = new_light;
		}
	}
}