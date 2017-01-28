/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/28 17:15:35 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "SDL.h"
# include "../Libft/libft.h"
# include "../Libmathft/libmathft.h"
# include "keycode_mac.h"
# include "colors.h"
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>

/*
** General settings
*/

# define THREAD_COUNT 10
# define WIN_H
# define WIN_W
//Default values if not provided by scene file.
# define MAX_RAY_DEPTH 3

/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

typedef int			t_color;

typedef enum		e_names
{
}					t_names;

typedef enum		e_type
{
	SPHERE = 1,
	PLANE = 2
}					t_type;

typedef struct		s_incr
{
	int				c_1;
	int				c_2;
	float			r;
	float			g;
	float			b;
}					t_incr;

typedef struct		s_camera
{
	t_vec3			position;
	t_vec3			direction;
}					t_camera;

typedef struct		s_light
{
	t_vec3			position;
}					t_light;

typedef struct		s_obejct
{
	t_vec3			position;
	t_vec3			orientation;
	t_type			type;
	t_color			color;
}					t_object;

typedef struct		s_draw_tools
{
	int				bpp;
	int				size_line;
	int				endian;
	char			*image;
}					t_draw_tools;

typedef struct		s_env
{
	t_draw_tools	draw;
	void			*mlx;
	void			*win_mlx;
	void			*img_mlx;
	int				h;
	int				w;
}					t_env;

typedef struct		s_r
{
	t_env			e;
	char			*title;
}					t_r;

typedef struct		s_th
{
	t_r				*f;
	int				i;
}					t_th;

/*
** Main
*/





/*
** MLX functions
*/



/*
** Free functions
*/



#endif
