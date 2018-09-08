/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avinas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:59:23 by avinas            #+#    #+#             */
/*   Updated: 2018/07/23 18:31:31 by avinas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"
#include "stdio.h"

t_cam	get_cam(int *fd, char **line)
{
	char	**tab;
	t_cam	ret;

	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.ori.x = ft_atoi(tab[0]);
	ret.ori.y = ft_atoi(tab[1]);
	ret.ori.z = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.rota.x = ft_atoi(tab[0]);
	ret.rota.y = ft_atoi(tab[1]);
	ret.rota.z = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	ret.focal = ft_atoi(*line);
	printf("CAM : \nori= %f|%f|%f\nrota= %f|%f|%f\nfocal= %f\n", ret.ori.x, ret.ori.y, ret.ori.z, ret.rota.x, ret.rota.y, ret.rota.z, ret.focal);
	get_next_line(*fd, line);
	get_next_line(*fd, line);
	return (ret);
}

t_lum	get_lum(int *fd, char **line)
{
	char	**tab;
	t_lum	ret;

	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.ori.x = ft_atoi(tab[0]);
	ret.ori.y = ft_atoi(tab[1]);
	ret.ori.z = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	ret.intens = ft_atoi(*line);
	get_next_line(*fd, line);
	get_next_line(*fd, line);
	printf("LUM : \nori= %f|%f|%f\nintens= %f\n", ret.ori.x, ret.ori.y, ret.ori.z, ret.intens);
	return (ret);
}

t_obj	get_obj(int *fd, char **line, int cpt)
{
	char	**tab;
	t_obj	ret;

	ret.name = *line;
	ret.id = cpt;
	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.ori.x = ft_atoi(tab[0]);
	ret.ori.y = ft_atoi(tab[1]);
	ret.ori.z = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.rota.x = ft_atoi(tab[0]);
	ret.rota.y = ft_atoi(tab[1]);
	ret.rota.z = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	tab = ft_strsplit(*line, ':');
	ret.color.red = ft_atoi(tab[0]);
	ret.color.green = ft_atoi(tab[1]);
	ret.color.blue = ft_atoi(tab[2]);
	get_next_line(*fd, line);
	ret.size = ft_atoi(*line);
	get_next_line(*fd, line);
	get_next_line(*fd, line);
	printf("\nOBJET : \n%s\nori= %f|%f|%f\nrota= %f|%f|%f\ncolor= %d|%d|%d\nsize= %f\nID= %d\n", ret.name, ret.ori.x, ret.ori.y, ret.ori.z, ret.rota.x, ret.rota.y, ret.rota.z, ret.color.red, ret.color.green, ret.color.blue, ret.size, ret.id);
	return (ret);
}

int			read_file(int fd, t_env *env, char *line)
{
	int		cpt;
	t_obj	tmpobj;

	cpt = -1;
	while (++cpt < 6 && get_next_line(fd, &line) == 1)
		;
	if (ft_strcmp(line, "CAM:") != 0)
		return(0);
	env->cam = get_cam(&fd, &line);
	if (ft_strcmp(line, "LUM:") != 0)
		return(0);
	env->lum = get_lum(&fd, &line);
	cpt = 0;
	while (ft_strcmp(line, "OBJET:") == 0 && get_next_line(fd, &line) == 1)
	{
		tmpobj = get_obj(&fd, &line, ++cpt);
		ft_lstadd(&env->list, ft_lstnew(&tmpobj, sizeof(tmpobj)));
	}
	close(fd);
	return (1);
}

int			open_file(t_env *env, char *file)
{
	int		fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	return (read_file(fd, env, ""));
}