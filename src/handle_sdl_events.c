/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sdl_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:15:05 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 14:22:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Handles SDL user events.
*/

int	handle_sdl_events(t_scene *scenes, t_env *env)
{
	(void)scenes;
	int quit = 0;
	while (!quit)
	{
		SDL_WaitEvent(&env->e);
		if (env->e.window.type == SDL_WINDOWEVENT_CLOSE){
			quit = 1;
		}
		if (env->e.window.type == SDL_KEYDOWN){
			quit = 1;
		}
		if (env->e.window.type == SDL_MOUSEBUTTONDOWN){
			quit = 1;
		}
	}
	return (1);
}