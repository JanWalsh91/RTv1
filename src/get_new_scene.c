/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 16:03:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Creates a new scene and sets default values.
*/

t_scene	*get_new_scene(char *name)
{
	t_scene *new_scene;

	if (!(new_scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		return (0);
	new_scene->next = NULL;
	if (name)
		new_scene->name = ft_strdup(name);
	//set default values for scene.
	return (new_scene);
}