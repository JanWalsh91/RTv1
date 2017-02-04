/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 14:34:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int	main(int ac, char **av)
{
	t_list	*input;
	t_scene	*scenes;
	t_env	env;
	int		i;


	printf("main\n");
	input = NULL;
	scenes = NULL;
	ac < 2 ? ft_display_usage_exit("usage") : 0;
	i = 0;
	while (++i < ac)
		if (!get_file(av[i], &input) || !parse_input(&scenes, &input))
			return (0);
	print_scenes(scenes);
	//calculate color(raytrace)
	init_sdl(scenes, &env);
	//update_image();
	SDL_SetRenderDrawColor(env.ren, 0xff, 0xff, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env.ren);
	int	y = 0;
	while (y < scenes->res.y)
	{
		int x = 0;
		while (x < scenes->res.x)
		{
			SDL_RenderDrawPoint(env.ren, y, x);
			++x;
		}
		++y;
	}

	SDL_RenderPresent(env.ren);
	handle_sdl_events(scenes, &env);
	SDL_DestroyWindow(env.win);
	SDL_Quit();
	return (0);
}