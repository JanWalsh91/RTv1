/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 17:10:36 by jwalsh           ###   ########.fr       */
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
# include <limits.h>

/*
** General settings
*/

# define THREAD_COUNT 10
//Default values if not provided by scene file.
# define DEFAULT_RES_H 500
# define DEFAULT_RES_W 700
# define DEFAULT_RAY_DEPTH 5
# define DEFAULT_POS_X 1
# define DEFAULT_POS_Y 1
# define DEFAULT_POS_Z 1
# define DEFAULT_COL WHITE
# define DEFAULT_ROT_X 0
# define DEFAULT_ROT_Y 0
# define DEFAULT_ROT_Z 0
# define DEFAULT_FOV 50
# define DEFAULT_


/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

typedef int			t_color;

typedef	struct		s_ray
{
	t_vec3		origin; //point of origin
	t_vec3		dir; //must be normalized
	t_color		col; // color found
}					t_ray;

typedef	struct		s_shading
{
}					t_shading;

typedef struct		s_attributes
{
//	char		*name;
	t_pt2		res;
	int			ray_depth;
	t_vec3		pos;
	t_vec3		rot;
	t_color		col;
	t_shading	shading;
	double		fov;
	long		radius;
}					t_attributes;


//Keep in same order.
# define OBJECTS "camera,light,plane,sphere,cylinder,cone"
typedef enum		e_type
{
	CAMERA = 1,
	LIGHT = 2,
	PLANE = 3,
	SPHERE = 4,
	CYLINDER = 5,
	CONE = 6
}					t_type;

typedef struct	s_camera
{
    char			*name;
    t_vec3			pos;
    t_vec3			rotation;
	double			fov;
	double			scale;
	t_color			**pixel_map;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_light
{
    char			*name;
    t_vec3			pos;
    t_vec3			rotation;
    t_color			color;
    struct s_light	*next;
}				t_light;

typedef struct	s_object
{
	t_type			type;
    char			*name;
	int				rad;
    void			*t;
    t_vec3			pos;
    t_vec3			rot;
    t_color			col;
    t_shading		shading;
	struct s_object	*next;
}				t_object;

typedef struct	s_scene
{
    t_pt2			res;
    char			*name;
    int				ray_depth;
    t_camera		*cameras;
    t_light			*lights;
    t_object		*objects;
	double			image_aspect_ratio;

    struct s_scene	*next;
}				t_scene;

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
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		e;
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
int			init_attributes(t_attributes **att);
int			parse_resolution(t_pt2 *res, char *s);
int			parse_ray_depth(int *ray_dpeth, char *s);
int			parse_position(t_vec3 *pos, char *s);
int			parse_rotation(t_vec3 *rot, char *s);
int			parse_color(t_color *col, char *s);
char 		**split_trim(char *s, char c);
t_scene		*get_new_scene(char *name);
t_object	*get_new_object(char *scene_name, char *name, char *type);
void		push_scene(t_scene **scenes, t_scene *new_scene);
void		push_object(t_object **objects, t_object *new_object);
int			set_attributes_scene(t_attributes *att, t_scene *scene);
int			extract_cameras(t_scene *scene);
void		push_camera(t_camera **cameras_head, t_camera *new_camera);
int			extract_lights(t_scene *scene);
void		push_light(t_light **lights_head, t_light *new_light);
int			set_attributes_object(t_attributes *att, t_object *object);
int			reset_attributes(t_attributes *att);


/*
** Ray Tracing Functions
*/

int			rtv1(t_scene *scene);
int		 	draw_image(t_scene *scene);
int			trace_camera_ray(t_pt2 p, t_scene *scene);

/*
** SDL2 Functions
*/

int			init_sdl(t_scene *scene, t_env *env);
int			handle_sdl_events(t_scene *scenes, t_env *env);

/*
** List Managment Functions
*/

/*
** Free Functions
*/

/*
** Debug functions
*/

void	print_scenes(t_scene *scenes_head);
void	print_input(t_list **list_head);
void	print_attributes(t_attributes att);


#endif
