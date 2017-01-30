/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 12:03:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a new scene to the list t_scene.
*/

#include "../inc/rtv1.h"

void	add_scene(t_scene **scenes, t_scene *new_scene)
{
	if (new_scene)
	{
		if (!*scenes)
			*scenes = new_scene;
		else
		{
			while ((*scenes)->next)
				*scenes = (*scenes)->next;
			(*scenes)->next = new_scene;
		}
	}
}