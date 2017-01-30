/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 16:37:48 by jwalsh           ###   ########.fr       */
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
# include "camera.h"
# include "light.h"
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

typedef struct		s_attributes
{
	char	*name;
	t_pt2	res;
	t_vec3	pos;
	t_vec3	rot;
	t_color	col;
	long	radius;
}					t_attributes;

typedef enum		e_names
{
}					t_names;

typedef enum		e_type
{
	CAMERA = 1,
	LIGHT = 2,
	PLANE = 3,
	SPHERE = 4,
	CYLINDER = 5,
	CONE = 6
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

/*
** File Parsing Functions
*/

int			get_file(char *file_name, t_list **input);
int			parse_input(t_scene **scenes, t_list **input);
int			init_attributes(t_attributes *att);
int			parse_resolution(t_pt2 *res, char *s);
int			parse_position(t_vec3 *pos, char *s);
int			parse_rotation(t_vec3 *res, char *s);
int			parse_color(t_color *col, char *s);
char 		**split_trim(char *s);
t_scene		*get_new_scene(char *name);
t_object	*get_new_object(char *name, char *type);
void		add_scene(t_scene **scenes, t_scene *new_scene);
void		add_object(t_object **objects, t_object *new_object);

/*
** Ray Tracing Functions
*/

int rtv1(t_scene **scene);
int draw_image(t_scene *scene);
int	trace_camera_ray(t_pt2 p, t_scene *scene);

/*
** SDL2 Functions
*/

/*
** List Managment Functions
*/


/*
** Free Functions
*/


#endif
