/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/12 13:54:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new scene.
*/

t_scene		*get_new_scene(t_parse_tools *t)
{
	// printf("GET_NEW_SCENE\n");
	t_scene		*new_scene;
	static int	i = 0;

	new_scene = NULL;
	if (!(new_scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		ft_error_exit("Malloc error");
	new_scene->next = NULL;
	new_scene->prev = NULL;
	new_scene->name = (!t->input->value) ?
		ft_strdup(ft_strjoin("Scene ", ft_itoa(++i))) :
		ft_strdup(t->input->value);
	new_scene->res.x = -1;
	new_scene->res.y = -1;
	new_scene->ray_depth = -1;
	new_scene->objects = NULL;
	new_scene->cameras = NULL;
	new_scene->lights = NULL;
	new_scene->background_color = v_new(NAN, NAN, NAN);
	new_scene->ambient_light_color = v_new(NAN, NAN, NAN);
	new_scene->ambient_light_coef = NAN;
	new_scene->image_aspect_ratio = NAN;
	return (new_scene);
}