/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:57:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/03 17:29:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int	main(int ac, char **av)
{
	t_scene	*scenes;
	int		i;
	t_list	*input;

	printf("main\n");
	ac < 2 ? ft_display_usage_exit("usage") : 0;
	i = 0;
	while (++i < ac)
		if (!get_file(av[i], &input) || !parse_input(&scenes, &input))
			return (0);
	print_scenes(scenes);
	
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("BIG ERROR");
		return (0);
	}
	SDL_Window *win = SDL_CreateWindow("TEST", 100, 100, 640, 640, SDL_WINDOW_SHOWN);
	if (!win)
	{
		printf("SDL window ceartion error");
		SDL_Quit();
		return (0);
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!ren)
	{
		printf("SDL window ceartion error");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (1);
	}
	SDL_SetRenderDrawColor(ren, 0xff, 0, 0, 0);
	int	y = 0;
	while (y < 640)
	{
		int x = 0;
		while (x < 640)
		{
			SDL_RenderDrawPoint(ren, y, x);
			++x;
		}
		++y;
	}
	SDL_Event e;
	int quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT){
				quit = 1;
			}
			if (e.type == SDL_KEYDOWN){
				quit = 1;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quit = 1;
			}
		}
			SDL_RenderClear(ren);
			SDL_RenderPresent(ren);
	}


	//send info to raytracer(scenes)
	return (0);
}