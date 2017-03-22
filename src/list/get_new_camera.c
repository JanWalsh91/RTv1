/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:42:55 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 12:46:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new camera.
*/

static void	set_cam_non_values(t_camera *new_camera);

t_camera	*get_new_camera(t_parse_tools *t)
{
	t_camera	*new_camera;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	if (!(new_camera = (t_camera *)ft_memalloc(sizeof(t_camera))))
		ft_errno_exit();
	set_cam_non_values(new_camera);
	if (!t->input->value || !*t->input->value)
	{
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name))
			i = 1;
		new_camera->name = ft_strjoin(t->tokens[t->input->token], " ");
		new_camera->name = ft_strjoinfree(new_camera->name, ft_itoa(i), 'b');
		++i;
	}
	else
		new_camera->name = ft_strdup(t->input->value);
	return (new_camera);
}

static void	set_cam_non_values(t_camera *new_camera)
{
	new_camera->prev = NULL;
	new_camera->next = NULL;
	new_camera->pos = v_new(NAN, NAN, NAN);
	new_camera->dir = v_new(NAN, NAN, NAN);
	new_camera->rot = v_new(NAN, NAN, NAN);
	new_camera->look_at = v_new(NAN, NAN, NAN);
	new_camera->fov = NAN;
	new_camera->name = NULL;
}
