/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:28:48 by avinas            #+#    #+#             */
/*   Updated: 2018/07/23 18:26:19 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

 void    dont_panic(t_env env)
{
	if(NULL != env.renderer)
		SDL_DestroyRenderer(env.renderer);
	if(NULL != env.window)
		SDL_DestroyWindow(env.window);
	SDL_Quit();
	exit (0);
}

t_env	*init_view(t_env *env)
{
	env->window = NULL;
	env->renderer = NULL;
	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		dont_panic (*env);
	}
	if(0 != SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &env->window, &env->renderer))
	{
		ft_putstr("ERREUR: initialistion SDL\n");
		dont_panic (*env);
	}
	return (env);
}

void	draw(t_env *env, int x, int y, t_color color)
{
	//printf("x : %d  y : %d\n", x, y);
	//if (x - WIDTH / 2 == -398 && y - HEIGHT / 2 == -382)
	//	printf("red: %d green: %d blue: %d |||\n", color.red, color.green, color.blue);
	SDL_SetRenderDrawColor(env->renderer, color.red, color.green, color.blue, 0);
	SDL_RenderDrawPoint(env->renderer, x, y);
}

void	disp_all(SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
}
