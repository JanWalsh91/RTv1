/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:15:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:25:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Handles SDL user events.
*/

int	handle_sdl_events(t_scene *scenes, t_env *env)
{
	int quit;

	quit = 0;
	(void)scenes;
	while (!quit)
	{
		SDL_WaitEvent(&env->e);
		if (env->e.window.event == SDL_WINDOWEVENT_CLOSE ||
			(env->e.key.type == SDL_KEYDOWN &&
			env->e.key.keysym.sym == SDLK_ESCAPE))
			quit = 1;
	}
	return (1);
}
