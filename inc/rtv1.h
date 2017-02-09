/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/09 11:57:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "/Users/jwalsh/.brew/include/SDL2/SDL.h"
# include "../Libft/inc/libft.h"
# include "../Libft/inc/ft_printf.h"
# include "../Libmathft/libmathft.h"
//# include "../Libgraphicsft/libgraphicsft.h"
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
# define DEFAULT_COL_R 0xAA
# define DEFAULT_COL_G 0xAA
# define DEFAULT_COL_B 0xFF
# define DEFAULT_ROT_X 0
# define DEFAULT_ROT_Y 0
# define DEFAULT_ROT_Z 0
# define DEFAULT_FOV 90
# define DEFAULT_


/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

typedef struct			s_color
{
	int			r;
	int			g;
	int			b;
}						t_color;

typedef	struct		s_ray
{
	t_vec3		origin; //point of origin
	t_vec3		dir; //must be normalized
	float		t; // closest valid intersection
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
	double		rad;
}					t_attributes;


//Keep in same order.
# define OBJECTS "camera,light,plane,sphere,cylinder,cone"
# define OBJECT_COUNT 6
typedef enum		e_type
{
	CAMERA = 1,
	LIGHT = 2,
	PLANE = 3,
	SPHERE = 4,
	CYLINDER = 5,
	CONE = 6
}					t_type;

typedef struct	s_object
{
	t_type			type;
    char			*name;
	double			rad;
    void			*t;
    t_vec3			pos;
    t_vec3			rot;
    t_color			col;
    t_shading		shading;
	t_color			**pixel_map;
	t_matrix4		ctw;
	float			scale;
	float			fov;
	struct s_object	*next;
}				t_object;

typedef struct	s_scene
{
    t_pt2			res;
    char			*name;
    int				ray_depth;
    t_object		*cameras;
    t_object		*lights;
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
int			set_line_count(t_list **input);
int			parse_input(t_scene **scenes, t_list **input);
int			init_attributes(t_attributes **att);
int			parse_resolution(t_pt2 *res, char *s, size_t line);
int			parse_ray_depth(int *ray_dpeth, char *s, size_t line);
int			parse_position(t_vec3 *pos, char *s, size_t line);
int			parse_rotation(t_vec3 *rot, char *s, size_t line);
int			parse_color(t_color *col, char *s, size_t line);
int			parse_radius(double *rad, char *s, size_t line);
char 		**split_trim(char *s, char c);
t_scene		*get_new_scene(char *name);
t_object	*get_new_object(char *scene_name, char *name, char *type);
void		push_scene(t_scene **scenes, t_scene *new_scene);
void		push_object(t_object **objects, t_object *new_object);
int			set_attributes_scene(t_attributes *att, t_scene *scene);
int			set_attributes_object(t_attributes *att, t_object *object);
int			reset_attributes(t_attributes *att);
int			extract_cameras_lights(t_scene *scene);
int			init_cameras(t_scene *scene);
int			update_camera_scale(t_object *camers);
int			update_camera_ctw(t_object *camers);

/*
** Ray Tracing Functions
*/

int			rtv1(t_scene **scenes);
int		 	draw_image(t_scene *scene);
t_ray		init_camera_ray(t_pt2 i, t_scene *scene);
t_color		cast_camera_ray(t_ray *cam_ray, t_scene *scene);
int			get_intersection(t_ray *ray, t_object *obj);
int			get_sphere_intersection(t_ray *ray, t_object *obj);

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
** Error Functions
*/

void	error_line_exit(char *msg, size_t line);

/*
** Debug functions
*/

# define C(...) ft_printf("check%i\n", __VA_ARGS__);
# define P(x) ft_printf(x);
void	print_scenes(t_scene *scenes_head);
void	print_input(t_list **list_head);
void	print_attributes(t_attributes att);
void	print_vec(t_vec3 vec);


#endif
