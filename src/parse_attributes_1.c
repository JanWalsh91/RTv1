/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:41:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/09 12:09:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

int	parse_resolution(t_pt2 *res, char *s, size_t line)
{
	char **s2;

	printf("	parse_resolution: [%s]\n", s);
	if (ft_charcount(s, ',') != 1)
		error_line_exit("resolution formatting error", line);
	s2 = split_trim(s, ',');
	if (!(s2[0] && s2[1]))
		error_line_exit("resolution formatting error", line);
	res->x = ft_atoi(s2[0]);
	res->y = ft_atoi(s2[1]);
	printf("	parse_resolution end x: [%i] y: [%i]\n", res->x, res->y);
	return(1);
}

int	parse_position(t_vec3 *pos, char *s, size_t line)
{
	printf("	parse_position: [%s]\n", s);
	char **s2;
	(void)line;
	if (ft_charcount(s, ',') != 2)
		error_line_exit("position formatting error", line);
	s2 = split_trim(s, ',');
	if (!s2[0] || !s2[1] || !s2[2])
		error_line_exit("position formatting error", line);
	pos->x = (float)ft_atoi(s2[0]);
	pos->y = (float)ft_atoi(s2[1]);
	pos->z = (float)ft_atoi(s2[2]);
	printf("	parse position end: x: [%f] y: [%f] z: [%f]\n", pos->x, pos->y, pos->z);
	return(1);
}

int	parse_rotation(t_vec3 *rot, char *s, size_t line)
{
	char **s2;
(void)line;
	printf("	parse_rotation: [%s]\n", s);
	if (ft_charcount(s, ',') != 2)
		error_line_exit("rotation formatting error", line);
	s2 = split_trim(s, ',');
	if (!(s2[0] && s2[1] && s2[2]))
		error_line_exit("rotation formatting error", line);
	rot->x = ft_atoi(s2[0]);
	rot->y = ft_atoi(s2[1]);
	rot->z = ft_atoi(s2[2]);
	return(1);
}

int	parse_radius(double *rad, char *s, size_t line)
{
	(void)line;
	printf("	parse_radius: [%s]\n", s);
	if (s)
		*rad = ft_atoi(s);
	else
		error_line_exit("radius formatting error", line);
	return (1);
}

int	parse_ray_depth(int *ray_depth, char *s, size_t line)
{
	(void)line;
	printf("	parse_ray_depth: [%s]\n", s);
	if (s)
		*ray_depth = ft_atoi(s);
	else
		error_line_exit("ray depth formatting error", line);
	return (1);
}

int	parse_color(t_color *col, char *s, size_t line)
{
	(void)line;
	char **s2;

	printf("	parse_color: [%s]\n", s);
	if (ft_charcount(s, ',') != 2)
		error_line_exit("color formatting error", line);
	s2 = split_trim(s, ',');
	if (!s2[0] || !s2[1] || !s2[2])
		error_line_exit("color formatting error", line);
	col->r = ft_atoi(s2[0]);
	col->g = ft_atoi(s2[1]);
	col->b = ft_atoi(s2[2]);
	if (col->r < 0 || col->g < 0 || col->b < 0 ||
		col->r > 255 || col->g > 255 || col->b > 255)
		error_line_exit("color formatting error", line);
	printf("	parse_color end r: [%i] g: [%i] b: [%i]\n", col->r, col->g, col->b);
	return(1);
}