/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:02:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:43:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds a t_input n to the end of t_input input.
*/

#include "../../inc/rtv1.h"

void	input_pushback(t_input **input, t_input *n)
{
	t_input	*ptr;

	if (n)
	{
		if (!(*input))
			*input = n;
		else
		{
			ptr = *input;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = n;
		}
		n->next = NULL;
	}
}
