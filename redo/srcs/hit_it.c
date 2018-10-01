#include "../../include/rtv1.h"

int		ray_hit(t_ray ray, t_hitable *hitable, t_v2 limit, t_hit_record *rec)
{
	if (hitable->name == SPHERE)
		return (hit_sphere((t_sphere *)hitable, ray, limit, rec));
	if (hitable->name == PLANE)
		return (hit_plane((t_plane *)hitable, ray, limit, rec));
	/*if (hitable->name == CYLINDER)
		return (ray_hit_cylinder((t_cylinder *)hitable, ray, limit, rec));
	if (hitable->name == CONE)
		return (ray_hit_cone((t_cone *)hitable, ray, limit, rec));
	*/
	return (0);
}

int		hit_obj_list(t_list list, t_ray *ray, t_v2 limit, t_hit_rec *rec)
{
	t_obj		*tmpobj;
	t_hit_rec	tmprec;
	int			hit;

	hit = 0;
	tmpobj = list;
	rec->item_hit = NULL;
	while (tmpobj)
	{
		if (ray_hit(ray, (t_hitable *)tmpobj->content, limit, &tmprec))
		{
			hit = 1;
			limit.y = tmprec.r1;
			tmprec.item_hit = tmpobj;
			ft_memcpy(rec, &tmprec, sizeof(t_hit_rec));
		}
		tmpobj = tmpobj->next;
	}
	return (hit);
}

double			solve_quadratic(t_v3 q, limit, ret)
{
	float	d;
	float	r1;

	d = q.y * q.y - 4 * q.x * q.z;
	if (d < 0)
		return (0);
	r1 = (-q.y - sqrtf(d)) / (2 * q.x);
	if (r1 < limit.x || r1 > limit.y)
		r1 = (-q.y + sqrtf(d)) / (2 * q.x);
	if (r1 < limit.x || r1 > limit.y)
		return (0);
	*ret = r1;
	return (1);
}