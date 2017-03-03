/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 14:13:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new scene.
*/

t_scene	*get_new_scene(char *name)
{
	// printf("GET_NEW_SCENE\n");
	t_scene		*new_scene;
	static int	i = 0;

	new_scene = NULL;
	if (!(new_scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		ft_error_exit("Malloc error");
	new_scene->next = NULL;
	//printf("---new_scene->name#:		[%p]---\n", &(new_scene->name));
	if (!name)
		new_scene->name = ft_strdup(ft_strjoin("Scene ", ft_itoa(++i)));
	else
		new_scene->name = ft_strdup(name);
	new_scene->objects = NULL;
	new_scene->cameras = NULL;
	new_scene->lights = NULL;
	// printf("new scene name: [%s]\n", new_scene->name);
	// printf("\n");
	return (new_scene);
}