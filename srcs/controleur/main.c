/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:32:29 by avinas            #+#    #+#             */
/*   Updated: 2018/07/24 15:44:47 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"



void	print_list(t_list *elem)
{
	t_obj	*tmpobj;

	tmpobj = elem->content;
	ft_putstr("\norigine:x = ");
	ft_putnbr(tmpobj->ori.x);
	ft_putstr(" y = ");
	ft_putnbr(tmpobj->ori.y);
	ft_putstr(" z = ");
	ft_putnbr(tmpobj->ori.z);
	ft_putstr("\n");
	ft_putstr("\ncolor:red = ");
	ft_putnbr(tmpobj->color.red);
	ft_putstr(" green = ");
	ft_putnbr(tmpobj->color.green);
	ft_putstr(" blue = ");
	ft_putnbr(tmpobj->color.blue);
	ft_putstr("\n");
}

void	print_vec(t_vertex vec)
{
	printf("x = %f | y = %f | z = %f\n", vec.x, vec.y, vec.z);
}

void	canon(t_env *env)
{
	t_ray		ray;
	t_vertex	l;
	t_vertex	n;
	t_color		finalcolor;
	double		dt;
	//double		length;
	int			x;
	int			y;

	x = -1;
	env->cam.focal = WIDTH / (2 * tan(FOV / 2));
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			ray.ori = env->cam.ori;
			ray.dir.x = (x - WIDTH / 2);
			ray.dir.y = (y - HEIGHT / 2);
			ray.dir.z = -10000.0f;

			/*length = 1.0 / sqrt( ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z );
			ray.dir.x *= length;
			ray.dir.y *= length;
			ray.dir.z *= length;
			*/
			//fisheye();
			if (hit_obj(*env->list, &ray))
			{
				if (ray.obj != NULL)
				{
					/*ray.dir = env->lum.ori;
					ray.ori = ray.inter;
					ray.ori.x = ray.ori.x + ray.dir.x * 0.1;
					ray.ori.y = ray.ori.y + ray.dir.y * 0.1;
					ray.ori.z = ray.ori.z + ray.dir.z * 0.1;
					*/
					/*if (hit_obj(*env->list, &ray))
					{*/
						ray.inter = get_inter(ray);
						l.x = env->lum.ori.x - ray.inter.x;
						l.y = env->lum.ori.y - ray.inter.y;
						l.z = env->lum.ori.z - ray.inter.z;

						if(ft_strcmp(ray.obj->name, "SPHERE") == 0)
							n = get_normal_sphere(ray.inter, ray);
						else if(ft_strcmp(ray.obj->name, "PLAN") == 0)
							n = ray.obj->rota;
						dt = v_dot(v_norm(n), v_norm(l));
						if (x - WIDTH / 2 == -400 && y - HEIGHT / 2 == 37)
							printf("%s = red: %d green: %d blue: %d dt: %f |||\n", ray.obj->name, ray.obj->color.red, ray.obj->color.green, ray.obj->color.blue, dt);
						if (dt < 0)
						{
							if (ft_strcmp(ray.obj->name, "PLAN") == 0)
								dt = 1;
							else
								dt = 0;
						}
						finalcolor.red = (ray.obj->color.red) * dt; 
						finalcolor.green = (ray.obj->color.green) * dt; 
						finalcolor.blue = (ray.obj->color.blue) * dt;
						draw(env, x, y, finalcolor);
					//}
				}
				/*
				if (hit_plane(*env->list, &ray))
				{
					printf("toto = plan\n");
				}
				*/
			}
		}
	}
	if (x % 100 == 0)
	{
		ft_putnbr(x);
		ft_putstr("\n");
	}

disp_all(env->renderer);
}

void    get_out(int a)
{
	if (a == 2)
	{
		exit(1);
	}
	else
		ft_putendl("Controls:\nENTER YOUR KEYS\n");
}

int     main(int argc, char **argv)
{
	t_env       *env;
	int         statut = EXIT_FAILURE;
	SDL_Event   event;
	SDL_bool    quit = SDL_FALSE;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (0);
	if (argc > 2)
	{
		ft_putendl("error: Too much Arguments");
		get_out(2);
	}
	if (argc < 2)
	{
		if (open_file(env, "./conf") == 0)
		{
			ft_putendl("Error Scene");
			get_out(2);
		}
	}
	else if (open_file(env, argv[1]) == 0)
	{
		ft_putendl("Error Scene");
		get_out(2);
	}

	get_out(1);


	int X;
	int Y;
	ft_lstiter(env->list, &(print_list));
	env = init_view(env);
	canon(env);
	while(!quit)
	{
		SDL_WaitEvent(&event);
		//printf("%d\n", event.type);
		if (event.type == 1025)
		//if(SDL_PollEvent(&event))
 		{
    		X = event.button.x  - WIDTH / 2;
    		Y = event.button.y  - HEIGHT / 2;
 			printf("x=%d y=%d\n", X,Y);
 		}
		if (event.type == SDL_QUIT)
			quit = SDL_TRUE;
	}
	statut = EXIT_SUCCESS;
	return (0);
}
