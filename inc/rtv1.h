/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/24 16:22:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include "/Users/jwalsh/.brew/include/SDL2/SDL.h"
# include "../Libft/inc/libft.h"
# include "../Libft/inc/ft_printf.h"  //?
# include "../Libmathft/inc/libmathft.h"
# include "keycode_mac.h"
# include "colors.h"

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
# define DEFAULT_DIR_X 0
# define DEFAULT_DIR_Y 0
# define DEFAULT_DIR_Z 1
# define DEFAULT_COL_R 0xAA
# define DEFAULT_COL_G 0xAA
# define DEFAULT_COL_B 0xFF
# define DEFAULT_dir_X 0
# define DEFAULT_dir_Y 1
# define DEFAULT_dir_Z 0
# define DEFAULT_FOV 45
# define DEFAULT_
# define CAM_IMG_PANE_DIST 1
# define BIAS 0.01

/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

# define TYPES "{,},scene,camera,light,plane,sphere,cylinder,cone,resolution,\
ray depth,background color,position,direction,rotation,look_at,color,radius,\
height,refraction,reflection,specular,transparency,fov,intensity,import,read"
typedef enum		e_token
{
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET,
	//scene
	T_SCENE,
	//objects
	T_CAMERA,
	T_LIGHT,
	T_PLANE,
	T_SPHERE,
	T_CYLINDER,
	T_CONE,
	// T_TORUS,
	// T_CUBE, 
	//attributes scene
	T_RESOLUTION,
	T_RAY_DEPTH,
	T_BACKGROUND_COLOR,
	//attributes objects
	T_POSITION,
	T_DIRECTION,
	T_ROTATION,
	T_LOOK_AT,
	T_COLOR,
	T_RADIUS,
	T_HEIGHT,
	T_REFRACTION, //angle of refraction
	T_REFLECTION, //0 does not reflect, 1 perfectly reflects. Reflection for objects
	T_SPECULAR, //reflection for lights. 0 - 1
	T_TRANSPARENCY,
	//attribtues camera
	T_FOV,
	//attribtues light
	T_INTENSITY,
	//io
	T_IMPORT_RT_FILE,
	T_READ_RT_FILE,
	T_READ_OBJ_FILE, 
	T_READ_TEXTURE_FILE,
	T_READ_MATERIAL_FILE,
	T_COUNT
}					t_token;


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

typedef t_vec3			t_color;

typedef	struct		s_ray
{
	t_vec3		origin; //point of origin
	t_vec3		dir; //must be normalized
	double		root1;
	double		root2;
	// t_vec3		origin2;
	// t_vec3		dir2;
	double		t; // closest valid intersection
	t_vec3		hit; // interection points in World View
	t_type		hit_type;
	t_vec3		nhit; //normal at intersection point
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
	t_vec3		dir;
	t_vec3		look_at;
	t_color		col;
	t_shading	shading;// ???
	double		fov;
	double		rad;
	double		angle;
	double		height;
	double		intensity;
}					t_attributes;



typedef struct	s_object
{
	t_type			type;
    char			*name;
	double			rad; //radius for sphere, or cylinder, or cone.
	double			angle; //angle of cone.
	double			height; //height of cone/cylinder
    void			*t;
    t_vec3			pos;
    t_vec3			dir;
	t_vec3			look_at;
    t_color			col;
	double			intensity;
    t_shading		shading;
	t_color			**pixel_map;
	t_matrix		ctw; //camera to world matrix (only for cameras)
	// t_matrix		mtw; //model to world matrix (only for objects in scene)
	// t_matrix		wtm; //world to model matrix (only for objects in scene)
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

typedef	struct		s_input
{
	int				token;
	char			*value;
	char			*file_name;
	size_t			line_number;
	struct s_input	*next;
}					t_input;

typedef struct		s_parse_tools
{
	bool			in_scene;
	bool			in_object;
	t_list			**input;
	int				fd;
	char			*file_name;
	t_attributes 	**att;
	char 			*key;
	char			*value;
	char			*types;
	char			*objects;

}					t_parse_tools;

typedef struct		s_incr
{
	int				c_1;
	int				c_2;
	float			r;
	float			g;
	float			b;
}					t_incr;

typedef struct		s_intersection_tools
{
	t_vec3			q; //quadratic equation components
	double			r1;
	double			r2; // quadratic equation solutions (roots)
	double			t; // final solution (closest intersection point)
	t_vec3			p; //tmp point.
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			v3; //extra tmp vectors.
	double			d1;
	double			d2; //extra tmp doubles.
}					t_intersection_tools;

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

// int			get_file(char *file_name, t_list **input);
int			get_file(char *file_name, t_input **input);
int			get_token(char *key);
int			set_line_count(t_list **input);
int			parse_input(t_scene **scenes, t_list **input);
int			init_attributes(t_attributes **att);
int			parse_resolution(t_pt2 *res, char *s, size_t line);
int			parse_ray_depth(int *ray_dpeth, char *s, size_t line);
int			parse_position(t_vec3 *pos, char *s, size_t line);
int			parse_direction(t_vec3 *dir, char *s, size_t line);
int			parse_look_at(t_vec3 *dir, char *s, size_t line);
int			parse_color(t_color *col, char *s, size_t line);
int			parse_radius(double *rad, char *s, size_t line);
int			parse_angle(double *angle, char *s, size_t line);
int			parse_height(double *height, char *s, size_t line);
int			parse_intensity(double *intensity, char *s, size_t line);
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
void		update_ray(t_ray *ray, t_object *obj, double *t);
t_vec3		get_normal(t_ray *ray, t_object *obj);
void		cast_shadow_ray(t_ray *cam_ray, t_object *obj, t_scene *scene);

/*
** SDL2 Functions
*/

int			init_sdl(t_scene *scene, t_env *env);
int			handle_sdl_events(t_scene *scenes, t_env *env);

/*
** Intersection functions.
*/

int			get_intersection(t_ray *ray, t_object *obj);
int			get_sphere_intersection(t_ray *ray, t_object *obj);
int			get_plane_intersection(t_ray *ray, t_object *obj);
int			get_cylinder_intersection(t_ray *ray, t_object *obj);
int			get_finite_cylinder_intersection(t_ray *ray, t_object *obj, t_intersection_tools *i);
int			get_cyclinder_caps_intersection(t_ray *ray, t_object *obj, t_intersection_tools *i);
int			get_cone_intersection(t_ray *ray, t_object *obj);
int			get_caps_intersection(t_ray *ray, t_object *obj, double *t);
int			get_disc_intersection(t_ray *ray, t_object *disc);
int			solve_quadratic(t_vec3 q, double *r1, double *r2);

/*
** Free Functions
*/

/*
** List management Functions
*/

void		input_pushback(t_input **input, t_input *n);
t_input		*input_new(char *line, char *file_name, int fd, t_input **input);

/*
** Error Functions
*/

void	error_line_exit(const char *msg, size_t line);

/*
** Debug functions
*/

# define C(...) ft_printf("check%i\n", __VA_ARGS__);
# define P(x) ft_printf(x);
void	print_scenes(t_scene *scenes_head);
void	print_input(t_list **list_head);
void	print_attributes(t_attributes att);
void	print_vec(t_vec3 vec);
void	print_matrix(t_matrix m);

#endif
