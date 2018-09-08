int		hit_plane(t_list list, t_ray *ray)
{
	double r1;

	r1 = ((v_dot(&tmp->rot, &tmp->pos) -
				v_dot(&tmp->rot, &pos)) / v_dot(&tmp->rot, &ray));
	if (r1 < 0.0001)
		return (0);
	return (r1);
}