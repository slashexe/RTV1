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

typedef struct e_form
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}				t_form;

typedef struct	s_v2
{
	float		x;
	float		y;
}				t_v2;

typedef struct	s_v3
{
	float		x;
	float		y;
	float		z;
}				t_v3;

typedef struct s_info
{
	t_v3	color;
	float	ambiant;
	float	diffuse;
	float	specular;
}				t_info;

typedef struct s_sphere
{
	t_form		name;
	t_info		info;
	t_v3		center;
	float		radius;
}				t_sphere;

typedef struct s_cylinder
{
	t_form		name;
	t_info		info;
	t_v3		ori;
	t_v3		dir;
	float		radius;
}				t_cylinder;

typedef struct s_cone
{
	t_form		name;
	t_info		info;
	t_v3		ori;
	t_v3		dir;
	float		alpha;
}				t_cone;

typedef struct	s_plane
{
	t_form		name;
	t_v3		ori;
	t_v3		normal;
}				t_plane;

typedef struct s_ray
{
	t_v3		ori;
	t_v3		dir;
}				t_ray;

typedef struct s_hit_rec
{
	float		t;
	t_v3		p;
	t_v3		normal;
	t_info		info;
	t_list		*list;
}				t_hit_rec;

typedef struct	s_cam
{
	t_v3		ori;
	t_v3		rota;
	float		focal;
}				t_cam;







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
