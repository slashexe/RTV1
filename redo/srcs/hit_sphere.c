#include "../../include/rtv1.h"

t_v3	get_inter(t_ray ray, float r1)
{
	t_v3	ret;

	ret = (t_v3){
		.x = ray.origin.x + r1 * ray.direction.x,
		.y = ray.origin.y + r1 * ray.direction.y,
		.z = ray.origin.z + r1 * ray.direction.z
	};
	return (ret);
}

int	hit_sphere(t_sphere *sphere, t_ray ray, t_v2 limit, t_hit_rec *rec)
{
	t_v3	v1;
	t_v3	q;

	v1 = v_sub(ray.ori, sphere->center);
	q.x = v_dot(ray->dir, ray->dir);
	q.y = 2 * v_dot(v1, ray->dir)
	q.z = v_dot(v1, v1) - pow(spher->radius);
	if ((solve_quadratic(q, limit, &(rec->r1))) == 0)
		return (0);
	rec->p = get_inter(ray, rec->r1);
	rec->normal = get_normal_sphere(sphere, rec->p);
	rec->info = sphere->info;
}