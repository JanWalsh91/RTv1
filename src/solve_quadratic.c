/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 13:25:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/11 15:37:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Solves a quadratic equation. Returns 0 if there is no solution. 
** Returns 1 if there is a solution.
** Modifies the float passed by address to the smallest solution,
** if it exists.
*/

int	solve_quadratic(t_vec3 q, double *t, t_ray *ray)
{
	double	root1;
	double	root2;
	double	d;

(void)ray;
	d = q.y * q.y - 4 * q.x * q.z;
	if (d == 0)
	{
		*t = -q.y / (2 * q.x);
		return (1);
	}
	if (d > 0)
	{
		root1 = (-q.y + sqrtf(d)) / (2 * q.x);
		root2 = (-q.y - sqrtf(d)) / (2 * q.x);
		*t = (root1 < root2) ? root1 : root2;
		return (1);
	}
	return (0);
}