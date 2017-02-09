/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:18:22 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/09 12:08:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Prints an error to the screen and exits the program.
*/

void	error_line_exit(char *msg, size_t line)
{
	// char *test = ft_strdup("mytest");
	(void)msg;
	(void)line;
	ft_printf("%s\n", "a;lsdkfj ;alksdjf ;alksdfj ");
	ft_printf("ERROR at line: %s\n", (char *)msg);
	exit(0);
}