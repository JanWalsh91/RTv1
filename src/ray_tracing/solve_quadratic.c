/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 13:25:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 14:49:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Solves a quadratic equation. Returns 0 if there is no solution, returns 1 if
** there is a solution.
** Modifies the floats passed by address to solutions found, if they exist.
*/

int	solve_quadratic(t_vec3 q, double *r1, double *r2)
{
	double	d;

	*r1 = -1;
	*r2 = -1;
	d = q.y * q.y - 4 * q.x * q.z;
	if (d == 0)
	{
		*r1 = -q.y / (2 * q.x);
		return (1);
	}
	if (d > 0)
	{
		*r1 = (-q.y + sqrtf(d)) / (2 * q.x);
		*r2 = (-q.y - sqrtf(d)) / (2 * q.x);
		return (1);
	}
	return (0);
}