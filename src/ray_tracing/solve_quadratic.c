/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 13:25:29 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 17:24:17 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Solves a quadratic equation.
** Updates r1 and r2 if at least a solution exists.
** Returns true if the quadratic has at least one solution.
*/

bool	solve_quadratic(t_vec3 q, double *r1, double *r2)
{
	double	d;

	*r1 = -1;
	*r2 = -1;
	d = q.y * q.y - 4 * q.x * q.z;
	if (d == 0)
	{
		*r1 = -q.y / (2 * q.x);
		return (true);
	}
	if (d > 0)
	{
		*r1 = (-q.y + sqrtf(d)) / (2 * q.x);
		*r2 = (-q.y - sqrtf(d)) / (2 * q.x);
		return (true);
	}
	return (false);
}
