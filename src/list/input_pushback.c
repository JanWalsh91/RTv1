/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:02:03 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 16:30:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Adds an elements to the end of a list.
*/

#include "../../inc/rtv1.h"

void	input_pushback(t_input **input, t_input *n)
{
	t_input	*ptr;

	printf("input pushback\n");
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