#include "../../include/rtv1.h"

int	hit_plane(t_plane *plane, t_ray, ray, t_v2 limit, t_hit_rec *rec)
{
	float	v1;
	float	q;
	float	dist;

	v1 = v_dot(plane->normal, v_sub(plane->ori, ray->ori));
	q = v_dot(plane->normal, ray.dir);
	dist = v1 / q;
	if (dist > limit.x && dist < limit.y)
	{
		rec->r1 = dist;
		rec->p = get_inter(ray, rec->r1);
		rec->normal = plane->normal;
		rec->info = plane->info;
		return (1);
	}
	return (0);
}