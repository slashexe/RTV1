/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 13:30:37 by avinas            #+#    #+#             */
/*   Updated: 2018/07/24 15:25:21 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

double		v_dot(t_vertex vec1, t_vertex vec2)
{
	return (vec1.x * vec2.x
			+ vec1.y * vec2.y
			+ vec1.z * vec2.z);
}

t_vertex	v_sub(t_vertex vec1, t_vertex vec2)
{
	t_vertex	vec;

	vec.x = vec1.x - vec2.x;
	vec.y = vec1.y - vec2.y;
	vec.z = vec1.z - vec2.z;
	return (vec);
}

t_vertex	v_norm(t_vertex vec)
{
	t_vertex	vecnorm;

	
	vecnorm.x = vec.x / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vecnorm.y = vec.y / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vecnorm.z = vec.z / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (vecnorm);
}

double			solve_quadratic(t_vertex q, double *r1, double *r2)
{
	double	d;

	*r1 = -1;
	*r2 = -1;
	d = q.y * q.y - 4 * q.x * q.z;
	/*if (d == 0)
	{
		*r1 = -q.y / (2 * q.x);
		return (1);
	}*/
	if (d >= 0)
	{
		/*
		rslt = ((-q.y - sqrt(d)) / (2 * q.x)) > 0 ?
				(-q.y + sqrtf(d)) / (2 * q.x) :
				(-q.y - sqrtf(d)) / (2 * q.x)
		*/
		*r1 = (-q.y + sqrtf(d)) / (2 * q.x);
		*r2 = (-q.y - sqrtf(d)) / (2 * q.x);
		return (2);
	}
	/*else
		rslt = 0;
	return (rslt);*/
	return (0);
}

int			is_closer(t_vertex vec1, t_vertex vec2, t_ray *ray)
{
	double	dist1;
	double	dist2;	

	dist1 = sqrtf(pow(ray->ori.x - vec1.x, 2)
			+ pow(ray->ori.y - vec1.y, 2)
			+ pow(ray->ori.z - vec1.z, 2));
	dist2 = sqrtf(pow(ray->ori.x - vec2.x, 2)
			+ pow(ray->ori.y - vec2.y, 2)
			+ pow(ray->ori.z - vec2.z, 2));
	if (dist1 > dist2)
		return (1);
	return (0);
}
