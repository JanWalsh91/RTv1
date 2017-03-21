/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 14:12:41 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 16:02:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	free_cameras(t_camera *cams, t_pt2 res);
static void	free_lights(t_light *lights);
static void	free_objects(t_object *objs);
static void	free_matrix(t_matrix *m);

/*
** Frees the t_scenes linked list and all substructures.
*/

void		free_scenes(t_scene *scenes)
{
	t_scene *tmp;

	while (scenes->prev)
		scenes = scenes->prev;
	while (scenes)
	{
		tmp = scenes;
		free(scenes->name);
		free_cameras(scenes->cameras, scenes->res);
		scenes->cameras = NULL;
		free_lights(scenes->lights);
		scenes->lights = NULL;
		free_objects(scenes->objects);
		scenes->objects = NULL;
		scenes = scenes->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_cameras(t_camera *cams, t_pt2 res)
{
	t_camera	*tmp;
	int			i;

	while (cams->prev)
		cams = cams->prev;
	while (cams)
	{
		tmp = cams;
		if (cams->name)
			free(cams->name);
		if (cams->ctw)
			free_matrix(&cams->ctw);
		i = -1;
		while (++i < res.y)
			free(cams->pixel_map[i]);
		free(cams->pixel_map);
		cams->pixel_map = NULL;
		cams = cams->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights;
		if (lights->name)
			free(lights->name);
		lights = lights->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_objects(t_object *objs)
{
	t_object	*tmp;

	while (objs)
	{
		tmp = objs;
		if (objs->name)
			free(objs->name);
		objs = objs->next;
		free(tmp);
		tmp = NULL;
	}
}

static void	free_matrix(t_matrix *m)
{
	int	y;

	y = -1;
	while (++y < 4)
		free((*m)[y]);
	free(*m);
	*m = NULL;
}
