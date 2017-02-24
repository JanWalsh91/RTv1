/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_line_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:25:15 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 10:59:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Sets line count in input linked list.
*/

int	set_line_count(t_list **input)
{
	// P("SET_LINE_COUNT\n")
	static int	i = 0;
	t_list *ptr;

	ptr = *input;
	while (ptr)
	{
		ptr->content_size = ++i;
		ptr= ptr->next;
	}
	return(1);
}