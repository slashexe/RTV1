/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_visu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:21:48 by avinas            #+#    #+#             */
/*   Updated: 2018/07/21 19:08:08 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/rtv1.h"
#include "./SDL/SDL.h"

void	dont_panic(t_env env)
{
	if(NULL != env.renderer)
		SDL_DestroyRenderer(env.renderer);
	if(NULL != env.window)
		SDL_DestroyWindow(env.window);
	SDL_Quit();
	exit (0);
}

t_env	window_init(t_env env)
{
	env.window = NULL;
	env.renderer = NULL;
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		dont_panic (env);
	}
	if(0 != SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &env.window, &env.renderer))
	{
		ft_putstr("ERREUR: initialistion SDL\n");
		dont_panic (env);
	}	
	return (env);
}
void	draw_cam(t_env env)
{
	SDL_SetRenderDrawColor(env.renderer, 255, 255, 0, 0);
	SDL_RenderDrawPoint(env.renderer, env.cam.origine.x + WIDTH / 2, env.cam.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.cam.origine.x + 1 + WIDTH / 2, env.cam.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.cam.origine.x - 1 + WIDTH / 2, env.cam.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.cam.origine.x + WIDTH / 2, env.cam.origine.y + 1 + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.cam.origine.x + WIDTH / 2, env.cam.origine.y - 1 + HEIGHT / 2);
	SDL_SetRenderDrawColor(env.renderer, 0, 0, 255, 0);
	SDL_RenderDrawPoint(env.renderer, env.lum.origine.x + WIDTH / 2, env.lum.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.lum.origine.x + 1 + WIDTH / 2, env.lum.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.lum.origine.x - 1 + WIDTH / 2, env.lum.origine.y + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.lum.origine.x + WIDTH / 2, env.lum.origine.y + 1 + HEIGHT / 2);
	SDL_RenderDrawPoint(env.renderer, env.lum.origine.x + WIDTH / 2, env.lum.origine.y - 1 + HEIGHT / 2);
	SDL_RenderPresent(env.renderer);
}

int		main()
{	
	int			statut = EXIT_FAILURE;
	SDL_Color	orange = {255, 127, 40, 255};
	SDL_Event	event;
	SDL_bool	quit = SDL_FALSE;
	t_env		env;

	env = read_conf("./conf");
	env = window_init(env);
	draw_cam(env);
	while(!quit)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
	}
	statut = EXIT_SUCCESS;
}
