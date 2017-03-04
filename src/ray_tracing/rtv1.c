/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:39:56 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 15:25:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** There is a way of simplifying calculations by calculate one vector before hand
** and using it for each pixel (multiplied by more stuff).
*/

/*
** 
*/

int rtv1(t_raytracing_tools *r)
{
	t_env	env;
	t_color	col;
	t_pt2	i;

	printf("RTV1\n");
	render(r);
	init_sdl(r->scenes, &env);
	SDL_RenderClear(env.ren);
	i.y = -1;
	while (++i.y < (r->scenes)->res.y)
	{
		i.x = -1;
		while (++i.x < (r->scenes)->res.x)
		{
			col = (r->scenes)->cameras->pixel_map[i.y][i.x];
			SDL_SetRenderDrawColor(env.ren, col.x, col.y, col.z, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(env.ren, i.x, i.y);
		}
	}
	SDL_RenderPresent(env.ren);
	handle_sdl_events(r->scenes, &env);
	SDL_DestroyWindow(env.win);
	SDL_Quit();
    return(1);
}