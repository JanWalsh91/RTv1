/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:39:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/07 15:23:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** There is a way of simplifying calculations by calculate one vector before hand
** and using it for each pixel (multiplied by more stuff).
*/

/*
** 
*/

int rtv1(t_scene **scenes)
{
	t_env	env;
	t_color	col;

	printf("RTV1\n");
	draw_image(*scenes);
	init_sdl(*scenes, &env);
	SDL_RenderClear(env.ren);
	int	y = 0;
	while (y < (*scenes)->res.y)
	{
		int x = 0;
		while (x < (*scenes)->res.x)
		{
			col = (*scenes)->cameras->pixel_map[y][x];
			SDL_SetRenderDrawColor(env.ren, col.r, col.g, col.b, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(env.ren, x, y);
			++x;
		}
		++y;
	}
	SDL_RenderPresent(env.ren);
	handle_sdl_events(*scenes, &env);
	SDL_DestroyWindow(env.win);
	SDL_Quit();
    return(1);
}