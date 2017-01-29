/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/29 17:52:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "/Users/jwalsh/.brew/include/SDL2/SDL.h"
# include "../Libft/libft.h"
# include "../Libmathft/libmathft.h"
# include "../Libgraphicsft/libgraphicsft.h"
# include "keycode_mac.h"
# include "colors.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <pthread.h>
# include "scene.h"
# include "object.h"
# include "sphere.h"

/*
** General settings
*/

# define THREAD_COUNT 10
# define DEFAULT_RES_H
# define DEFAULT_RES_W
//Default values if not provided by scene file.
# define DEFAULT_RAY_DEPTH 3

/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

typedef int			t_color;

typedef struct		s_shared_attributes
{
	char	*name;
	t_pt2	resolution;
	t_vec3	pos;
	t_vec3	rotation;
	t_color	color;
	long	radius;
}					t_shared_attributes;

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

int	parse_file(t_list **scenes, char *file);
int parse_shared_attributes(char *line, t_shared_attributes *att);
int parse_scene(int fd, char **line, t_shared_attributes global_att);
int parse_object(int fd, char **line, t_shared_attributes global_att, t_shared_attributes scene_att);
int update_shared_attirbutes();


/*
** MLX functions
*/



/*
** Free functions
*/



#endif
