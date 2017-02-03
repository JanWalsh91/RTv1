/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:41:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/03 15:57:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int	parse_resolution(t_pt2 *res, char *s)
{
	char **s2;

	printf("parse_resolution: [%s]\n", s);
	s2 = split_trim(s, ',');
	//if (!(s2[0] && s2[1]))
	//	return (0); //ERROR INVALID RESOLUTION FORMAT
	res->x = ft_atoi(s2[0]);
	res->y = ft_atoi(s2[1]);
	printf("parse_resolution end x: [%i] y: [%i]\n", res->x, res->y);
	return(1);
}

int	parse_position(t_vec3 *pos, char *s)
{
	printf("parse_position: [%s]\n", s);
	char **s2;

	s2 = split_trim(s, ',');
	if (!s2[0] || !s2[1] || !s2[2])
		return (0);
	pos->x = (float)ft_atoi(s2[0]);
	pos->y = (float)ft_atoi(s2[1]);
	pos->z = (float)ft_atoi(s2[2]);
	printf("parse position end: x: [%f] y: [%f] z: [%f]\n", pos->x, pos->y, pos->z);
	return(1);
}

int	parse_rotation(t_vec3 *rot, char *s)
{
	char **s2;

	s2 = split_trim(s, ',');
	if (!(s2[0] && s2[1] && s2[2]))
		return (0); //ERROR INVALID ROTATION FORMAT
	rot->x = ft_atoi(s2[0]);
	rot->y = ft_atoi(s2[1]);
	rot->z = ft_atoi(s2[2]);
	return(1);
}

int	parse_dimension(int	*x, char *s)
{
	(void)s;
	(void)x;
	return(1);
}

int	parse_ray_depth(int *ray_depth, char *s)
{
	if (s)
		*ray_depth = ft_atoi(s);
	return (1);
}