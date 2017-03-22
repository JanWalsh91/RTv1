/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:07:26 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:25:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initializes the SDL, window and renderer.
*/

static int	init_window(t_scene *scene, t_env *env);
static int	init_rederer(t_scene *scene, t_env *env);

int			init_sdl(t_scene *scene, t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("BIG ERROR");
		return (0);
	}
	init_window(scene, env);
	init_rederer(scene, env);
	return (1);
}

static int	init_window(t_scene *scene, t_env *env)
{
	env->win = SDL_CreateWindow(scene->name, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, scene->res.x, scene->res.y, SDL_WINDOW_SHOWN);
	if (!env->win)
	{
		printf("SDL window creation error");
		SDL_Quit();
		return (0);
	}
	return (1);
}

static int	init_rederer(t_scene *scene, t_env *env)
{
	(void)scene;
	env->ren = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->ren)
	{
		printf("SDL render creation error");
		SDL_DestroyWindow(env->win);
		SDL_Quit();
		return (1);
	}
	return (1);
}
