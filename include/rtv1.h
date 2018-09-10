/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 15:14:28 by avinas            #+#    #+#             */
/*   Updated: 2018/07/24 15:36:19 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../SDL/SDL.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# define HEIGHT 1000
# define WIDTH 1000
# define FOV -10000.0f
# include "stdio.h"

typedef struct	s_vertex
{
	double		x;
	double		y;
	double		z;
}				t_vertex;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_lum
{
	t_vertex	ori;
	double      intens;
}				t_lum;

typedef struct	s_cam
{
	t_vertex	ori;
	t_vertex	rota;
	double		focal;
}				t_cam;

typedef struct  s_obj
{
	t_vertex    ori;
	t_vertex    rota;
	t_color     color;
	double      size;
	int         id;
	char        *name;
}               t_obj;

typedef struct  s_env
{
	SDL_Window	*window;
	SDL_Renderer	*renderer;
	t_cam       cam;
	t_lum       lum;
	t_list      *list;
}               t_env;

typedef struct s_ray
{
	t_vertex	ori;
	t_vertex	dir;
	t_vertex	inter;
	t_obj		*obj;
	double		t;
	int			hit;
}				t_ray;

t_env		read_conf(char *path);
int			hit_obj(t_list list, t_ray *ray);
t_vertex	get_inter(t_ray ray);
t_env		*init_view(t_env *env);
void		draw(t_env *env, int x, int y, t_color color);
void		disp_all(SDL_Renderer *renderer);

double		v_dot(t_vertex vec1, t_vertex vec2);
t_vertex	v_sub(t_vertex vec1, t_vertex vec2);
t_vertex	v_norm(t_vertex vec);

double		solve_quadratic(t_vertex q, double *r1, double *r2);
t_vertex	get_normal_sphere(t_vertex vec, t_ray ray);
int			is_closer(t_vertex vec1, t_vertex vec2, t_ray *ray);

void        get_out(int a);
int         open_file(t_env *env, char *file);
#endif
