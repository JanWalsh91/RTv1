/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:42:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 16:08:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new camera.
*/

static void	set_non_values(t_camera *new_camera);

t_camera 	*get_new_camera(t_parse_tools *t)
{
	t_camera 	*new_camera;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	if (!(new_camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		ft_error_exit("Malloc error");
	set_non_values(new_camera);
	if (!t->input->value)
	{
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name)) //if on new scene
			i = 1;
		new_camera->name = ft_strdup(ft_strsjoin(3, TOKENS[t->input->token], " ", ft_itoa(i)));
		++i;
	}
	else
		new_camera->name = ft_strdup(t->input->value);
	return (new_camera);
}

static void	set_non_values(t_camera *new_camera)
{
	ft_bzero(new_camera, sizeof(t_camera));
	new_camera->prev = NULL;
	new_camera->next = NULL;
	new_camera->pos = v_new(NAN, NAN, NAN);
	new_camera->dir = v_new(NAN, NAN, NAN);
	new_camera->rot = v_new(NAN, NAN, NAN);
	new_camera->look_at = v_new(NAN, NAN, NAN);
	new_camera->fov = NAN;
}