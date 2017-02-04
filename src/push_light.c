/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 17:10:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new light to the list t_lights.
*/

#include "../inc/rtv1.h"

void	push_light(t_light **lights_head, t_light *new_light)
{
	t_light	*light_ptr;

	if (new_light)
	{
		if (!*lights_head)
			*lights_head = new_light;
		else
		{
			light_ptr = *lights_head;
			while (light_ptr->next)
				light_ptr = light_ptr->next;
			light_ptr->next = new_light;
		}
	}
}