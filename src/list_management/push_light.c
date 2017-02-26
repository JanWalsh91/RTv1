/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:46:09 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:46:30 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Adds a new light to the end of list t_lights.
*/

void	push_light(t_light **lights_head, t_light *new_light)
{
	t_light	*light_ptr;

	printf("push_light: [%s]\n", new_light->name);
	if (new_light)
	{
		if (!(*lights_head))
			*lights_head = new_light;
		else
		{
			light_ptr = *lights_head;
			while (light_ptr->next)
				light_ptr = light_ptr->next;
			light_ptr->next = new_light;
		}
		new_light->next = NULL;
	}
}