/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:22:26 by avinas            #+#    #+#             */
/*   Updated: 2018/07/24 15:40:28 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_vertex	get_normal_sphere(t_vertex vec, t_ray ray)
{
	vec.x = (ray.obj->ori.x + vec.x) / ray.obj->size;
	vec.y = (ray.obj->ori.y + vec.y) / ray.obj->size;
	vec.z = (ray.obj->ori.z + vec.z) / ray.obj->size;
	return (vec);
}

t_vertex	get_inter(t_ray ray)
{
	//ray.ori.x = ray.dir.x * ray.dir.z;
	//ray.ori.x = ray.dir.y * ray.dir.z;
	//ray.ori.z = ray.dir.z;
	ray.inter.x = ray.ori.x + ray.dir.x * ray.t;
	ray.inter.y = ray.ori.y + ray.dir.y * ray.t;
	ray.inter.z = ray.ori.z + ray.dir.z * ray.t;
	return (ray.inter);
}

t_vertex	init_quadratic(t_obj *obj, t_ray *ray)
{
	t_vertex	v1;
	t_vertex	q;

	q.x = 0;
	if(ft_strcmp(obj->name, "SPHERE") == 0)
	{
		v1 = v_sub(obj->ori, ray->ori);
		q.x = v_dot(ray->dir, ray->dir);
		q.y = 2 * v_dot(v1, ray->dir);
		q.z = v_dot(v1, v1) - pow(obj->size, 2);
	}
	return (q);
}

int			hit_it(t_obj *obj, t_ray *ray)
{
	t_vertex	q;
	double		r1;
	double		r2;
	int			res;

	r1 = -1;
	r2 = -1;
	if (ft_strcmp(obj->name, "PLAN") == 0)
	{
		//printf("%s = red: %d green: %d blue: %d |||\n", obj->name, obj->color.red, obj->color.green, obj->color.blue);
		q = v_sub(ray->dir, obj->ori);
		r1 = v_dot(q, obj->rota) / v_dot(ray->dir, obj->rota);
		if (r1 > 0.01 && r1 < 2)
			res = 1;
		else
			res = 0;
	}
	else
	{
		q = init_quadratic(obj, ray);
		res = solve_quadratic(q, &r1, &r2);
	}
	if (res)
	{
		if (r1 > r2)
			r1 = r2;
		if (ray->hit)
		{
			if (r1 < ray->t)
			{
				ray->obj = obj;
				ray->t = r1;
			}
		}
		else
		{
			ray->obj = obj;
			ray->t = r1;
		}

		return (1);
	}
	return (0);
}

int			hit_obj(t_list list, t_ray *ray)
{
	t_obj *tmpobj;

	ray->obj = NULL;
	ray->hit = 0;
	while (list.next != NULL)
	{
		tmpobj = list.content;
		if (hit_it(tmpobj, ray))
		{	
			ray->hit = 1;
			break;
		}
		list = *list.next;
	}
	tmpobj = list.content;
	if (hit_it(tmpobj, ray))
	{
		ray->hit = 1;
	}

	return (ray->hit);
}
