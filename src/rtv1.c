/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:39:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 15:34:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** There is a way of simplifying calculations by calculate one vector before hand
** and using it for each pixel (multiplied by more sstuff).
*/

/*
** 
*/

int rtv1(t_scene **scenes)
{
	t_env	env;

	draw_image(*scenes);
	init_sdl(*scenes, &env);
	SDL_SetRenderDrawColor(env.ren, 0xff, 0xff, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env.ren);
	int	y = 0;
	while (y < (*scenes)->res.y)
	{
		int x = 0;
		while (x < (*scenes)->res.x)
		{
			SDL_RenderDrawPoint(env.ren, y, x);
			++x;
		}
		++y;
	}
	
	SDL_RenderPresent(env.ren);
	handle_sdl_events(*scenes, &env);
	SDL_DestroyWindow(env.win);
	SDL_Quit();


	t_pt2	i;

	i.y = -1;
	(void)scenes;

    return(1);
}