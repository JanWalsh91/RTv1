/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/15 13:24:12 by jwalsh           ###   ########.fr       */
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
# define DEFAULT_RES_W 500
# define DEFAULT_RES_H 700
# define DEFAULT_RAY_DEPTH 5
# define DEFAULT_AMBIENT_LIGHT_COEF 0.1
# define DEFAULT_AMBIENT_LIGHT_COLOR_R 255
# define DEFAULT_AMBIENT_LIGHT_COLOR_G 255
# define DEFAULT_AMBIENT_LIGHT_COLOR_B 255
# define DEFAULT_POS_X 0
# define DEFAULT_POS_Y 0
# define DEFAULT_POS_Z 0
# define DEFAULT_DIR_X 0
# define DEFAULT_DIR_Y 1
# define DEFAULT_DIR_Z 0
# define DEFAULT_COL_R 0xFF
# define DEFAULT_COL_G 0xFF
# define DEFAULT_COL_B 0xFF
# define DEFAULT_CAM_DIR_X 0
# define DEFAULT_CAM_DIR_Y 0
# define DEFAULT_CAM_DIR_Z 1
# define DEFAULT_FOV 45
# define DEFAULT_INTENSITY 10
# define DEFAULT_RADIUS 1
# define DEFAULT_HEIGHT 1
# define DEFAULT_KS 0.1
# define DEFAULT_KD 1
# define DEFAULT_SPECULAR_EXP 200
# define CAM_IMG_PANE_DIST 1
# define BIAS 0.01
# define COLORS_PATH "res/colors.txt"

/*
** Instructions
*/

# define INSTRUCTIONS_H 512
# define INSTRUCTIONS_W 600
# define LINE_0 "RTv1 instructions:"

typedef enum		e_token
{
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET,
	T_EMPTY_LINE,
	//scene
	T_SCENE,
	//objects
	T_CAMERA,
	T_LIGHT,
	T_PLANE,
	T_DISK,
	T_SPHERE,
	T_CYLINDER,
	T_CONE,
	// T_TORUS,
	// T_CUBE, 
	//scene attributes
	T_RESOLUTION,
	T_RAY_DEPTH,
	T_BACKGROUND_COLOR,
	T_AMBIENT_LIGHT_COEF,
	T_AMBIENT_LIGHT_COLOR,
	//object attributes
	T_POSITION,
	T_DIRECTION,
	T_ROTATION,
	T_LOOK_AT,
	T_COLOR,
	T_RADIUS,
	T_HEIGHT,
	T_DIFFUSE_COEF,
	T_REFRACTION, //angle of refraction
	T_REFLECTION, //0 does not reflect, 1 perfectly reflects. Reflection for objects
	T_SPECULAR_EXPONENT, //specular exponent
	T_SPECULAR_COEF, 
	T_TRANSPARENCY,
	//acamera attributes
	T_FOV,
	//light attribtues
	T_INTENSITY,
	//io
	T_IMPORT_RT_FILE,
	T_READ_RT_FILE,
	T_READ_OBJ_FILE, 
	T_READ_TEXTURE_FILE,
	T_READ_MATERIAL_FILE,
	T_HASHTAG,
	T_INVALID_TOKEN,
	T_COUNT
}					t_token;

# define TOKENS (const char *[T_COUNT]){"{","}","","scene","camera","light","plane",\
"disk","sphere","cylinder","cone","resolution","ray depth","background color","ambient light coefficient","ambient light color","position",\
"direction","rotation","look at","color","radius","height","kd","refraction","reflection",\
"specular exponent","ks","transparency","fov","intensity","import","read rt file","read obj file",\
"read texture file","read material file","invalid token"}

// structure for each link conainting into about the input file(s)
typedef	struct		s_input
{
	int				token;
	char			*value;
	char			*file_name;
	size_t			line_number;
	struct s_input	*next;
}					t_input;

typedef t_vec3			t_color;

typedef struct			s_color_list
{
	t_color				value;
	char				*name;
	struct s_color_list	*next;
}						t_color_list;

typedef struct		s_attributes
{
	//scene
	t_pt2		res;
	int			ray_depth;
	t_color		ambient_light_color;
	double		ambient_light_coef;
	//light
	double		intensity;
	//camera
	double		fov;
	//objects
	t_vec3		pos;
	t_vec3		dir; //not sphere
	t_vec3		rot; //not sphere
	t_vec3		look_at; //not sphere
	t_color		col; 
	double		rad; //cone, cylinder, sphere
	double		height; //cone, cylinder
	double		ks;
	double		kd;
	double		refraction; //not light, cam
	double		reflection; //not light, cam
	double		specular_exp; // ""
	double		transparency; // ""
}					t_attributes;


//Keep in same order.
// # define OBJECTS "camera,light,plane,sphere,cylinder,cone"
// # define OBJECT_COUNT 6
// typedef enum		e_type
// {
// 	CAMERA = 1,
// 	LIGHT = 2,
// 	PLANE = 3,
// 	SPHERE = 4,
// 	CYLINDER = 5,
// 	CONE = 6
// }					t_type;

typedef enum		e_ray_type
{
	R_PRIMARY,
	R_SHADOW,
	R_DIFFUSE,
	R_SPECULAR,
	R_REFLECTION,
	R_REFRACTION,
	R_AMBIENT
}					t_ray_type;

typedef	struct		s_ray
{
	t_ray_type	type; //ray type
	t_vec3		origin; // ray origin
	t_vec3		dir; // ray direction: must be normalized
	double		root1;
	double		root2;
	double		t; // distance of intersection
	struct s_object	*hit_obj; //pointer to object hit at intersection point
	t_vec3		hit; // intersection point in World View
	t_token		hit_type; // type of object hit
	int			n_dir; //direction of normal at intersetion point
	t_vec3		nhit; //normal at hit point
	t_color		col; // color found
}					t_ray;


typedef struct	s_object
{
	t_token			type;
    char			*name;
    void			*t;
    t_vec3			pos;
    t_vec3			dir;
	t_vec3			rot;
	t_vec3			look_at;
    t_color			col;
	double			rad; //radius for sphere, or cylinder, or cone.
	double			height; //height of cone/cylinder
	double 			angle;
	double			kd; //diffuse coefficient
	double			ks; //specular coefficient
	double			refraction;
	double			reflection;
	double			specular_exp; //
	double			transparency;
	struct s_object	*next;
}				t_object;

typedef struct	s_light
{
    char			*name;
    void			*t;
    t_vec3			pos;
    t_vec3			dir;
	t_vec3			rot;
	t_vec3			look_at;
    t_color			col;
	double			intensity;
	struct s_light	*next;
}				t_light;

typedef struct	s_camera
{
    char			*name;
    void			*t;
    t_vec3			pos;
    t_vec3			dir;
	t_vec3			rot;
	t_vec3			look_at;
	t_color			**pixel_map;
	t_matrix		ctw; //camera to world matrix (only for cameras)
	double			scale;
	double			fov;
	struct s_camera	*prev;
	struct s_camera	*next;
}				t_camera;

typedef struct	s_scene
{
    t_pt2			res;
    char			*name;
    int				ray_depth;
	t_color			background_color;
	t_color			ambient_light_color;
	double			ambient_light_coef;
	double			image_aspect_ratio;
    t_camera		*cameras;
    t_light			*lights;
    t_object		*objects;
	struct s_scene	*prev;
    struct s_scene	*next;
}				t_scene;

typedef struct		s_parse_tools
{
	bool			in_scene;
	bool			in_object;
	t_input			*input; //pointer to current link
	t_input			*input_head; //pointer to input. // used?
	t_scene			*scenes;
	t_scene			*current_scene;
	t_object		*current_object;
	t_camera		*current_camera;
	t_light			*current_light;
	t_token			current_type;
	int				fd;  // ?
	char			*file_name;  // ?
	t_attributes 	*global_attributes;
	t_attributes	*scene_attributes;
	t_attributes	*object_attributes;
	t_color_list	*colors;
	void			(**parse)(struct s_parse_tools *); //list of funtion ptrs for each token
}					t_parse_tools;

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
	int				n_dir;
}					t_intersection_tools;

typedef struct		s_options
{
	bool			shadows;
	bool			diffuse;
	bool			specular;
	bool			reflection;
	bool			refraction;
	bool			ambient;
	bool			antialiasing;
	bool			textures;
	bool			bump_mapping;
	bool			normal_mapping;
	bool			filters;
}					t_options;

typedef struct		s_raytracing_tools
{
	t_scene			*scenes;
	t_options		options;
	t_pt2			pix;
	double			t; //closets intersection distance
}					t_raytracing_tools;

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		e;
	int				h;
	int				w;
}					t_env;

/*
** Main
*/

void	init_raytracing_tools(t_raytracing_tools *r);

/*
** File Parsing Functions
*/

void		set_options(char *arg, t_options *options);
void		get_file(char *file_name, t_input **input);
int			get_token(char *key);
void		parse_input(t_parse_tools *t);
char 		**split_trim(char *s, char c);
t_scene		*get_new_scene(t_parse_tools *t);
t_object 	*get_new_object(t_parse_tools *t);
void		set_non_values(t_object *new_object);
t_light 	*get_new_light(t_parse_tools *t);
t_camera 	*get_new_camera(t_parse_tools *t);
void		push_scene(t_scene **scenes, t_scene *new_scene);
void		push_object(t_object **objects, t_object *new_object);
void		push_light(t_light **lights_head, t_light *new_light);
void		push_camera(t_camera **cameras_head, t_camera *new_camera);
void		set_attributes(t_parse_tools *t, t_attributes *a);
int			reset_attributes(t_attributes *att);

void	init_parse_tools(t_parse_tools *t);
void	parse_open_bracket(t_parse_tools *t);
void	parse_close_bracket(t_parse_tools *t);
void	parse_empty_line(t_parse_tools *t);
void	parse_scene(t_parse_tools *t);
void	parse_camera(t_parse_tools *t);
void	parse_light(t_parse_tools *t);
void	parse_plane(t_parse_tools *t);
void	parse_disk(t_parse_tools *t);
void	parse_sphere(t_parse_tools *t);
void	parse_cylinder(t_parse_tools *t);
void	parse_cone(t_parse_tools *t);
void	parse_resolution(t_parse_tools *t);
void	parse_ray_depth(t_parse_tools *t);
void	parse_background_color(t_parse_tools *t);
void	parse_ambient_light_color(t_parse_tools *t);
void	parse_ambient_light_coef(t_parse_tools *t);
void	parse_position(t_parse_tools *t);
void	parse_direction(t_parse_tools *t);
void	parse_rotation(t_parse_tools *t);
void	parse_look_at(t_parse_tools *t);
void	parse_color(t_parse_tools *t);
void	parse_radius(t_parse_tools *t);
void	parse_height(t_parse_tools *t);
void	parse_refraction(t_parse_tools *t);
void	parse_reflection(t_parse_tools *t);
void	parse_diffuse_coef(t_parse_tools *t);
void	parse_specular_coef(t_parse_tools *t);
void	parse_specular_exponent(t_parse_tools *t);
void	parse_transparency(t_parse_tools *t);
void	parse_fov(t_parse_tools *t);
void	parse_intensity(t_parse_tools *t);
void	import_rt_file(t_parse_tools *t);
void	read_rt_file(t_parse_tools *t);
void	read_obj_file(t_parse_tools *t);
void	read_texture_file(t_parse_tools *t);
void	read_material_file(t_parse_tools *t);
void	hashtag(t_parse_tools *t);
void	invalid_token(t_parse_tools *t);
t_vec3	get_color(t_parse_tools *t, char *value);
t_vec3	parse_rgb(char *value);
t_vec3	parse_hexadecimal(char *value);
t_vec3	parse_color_name(t_parse_tools *t, char *value);
t_vec3	parse_vector(char *value);
double	parse_double(char *value);

/*
** Data Checking Functions
*/

int		check_data(t_scene *scenes);
void	set_default_resolution(t_scene *scene);
void	set_default_ray_depth(t_scene *scene);
void	set_default_ambient_light_coef(t_scene *scene);
void	set_default_ambient_light_color(t_scene *scene);
void	check_cameras(t_scene *scene, t_camera *cameras);
void	check_lights(t_scene *scene, t_light *lights);
void	check_objects(t_scene *scene, t_object *objects);
void	set_default_pos(t_scene *scene, int type, void *obj, t_vec3 *pos);
void	set_default_col(t_scene *scene, int type, void *obj, t_vec3 *col);
void	set_default_intensity(t_scene *scene, int type, void *obj, double *intensity);
void	set_default_radius(t_scene *scene, int type, void *obj, double *radius);
void	set_default_height(t_scene *scene, int type, void *obj, double *height);
void	set_default_cam_dir(t_scene *scene, int type, void *cam, t_vec3 *dir);
void	set_default_obj_dir(t_scene *scene, int type, void *obj, t_vec3 *dir);
void	set_default_light_dir(t_scene *scene, int type, void *obj, t_vec3 *dir);
void	set_default_fov(t_scene *scene, int type, void *obj, double *fov);
void	set_default_ks(t_scene *scene, int type, void *obj, double *ks);
void	set_default_kd(t_scene *scene, int type, void *obj, double *kd);
void	set_default_specular_exp(t_scene *scene, int type, void *obj, double *specular_exp);
void	get_obj_direction(t_scene *scene, t_object *obj);
void	get_cam_direction(t_scene *scene, t_camera *cam);
void	get_light_direction(t_scene *scene, t_light *light);
void	init_camera(t_scene *scene, t_camera *cam);
void	update_camera_scale(t_camera *camera);
void	update_camera_ctw(t_camera *camera);

/*
** Ray Tracing Functions
*/

int 		rtv1(t_raytracing_tools *r);
void	 	render(t_raytracing_tools *r);
t_ray		init_camera_ray(t_pt2 i, t_scene *scene);
t_color		cast_primary_ray(t_raytracing_tools *r, t_ray *ray);
// t_color		cast_camera_ray(t_ray *cam_ray, t_scene *scene);
void		update_ray(t_ray *ray, t_object *obj, double *t);
// t_vec3		get_normal(t_ray *ray, t_object *obj);
void		get_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
// void		cast_shadow_ray(t_ray *cam_ray, t_object *obj, t_scene *scene);
bool	in_shadow(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color	get_diffuse(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color	get_specular(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color	get_ambient(t_raytracing_tools *r);
t_vec3	reflect(t_vec3 ray_dir, t_vec3 nhit);

/*
** SDL2 Functions
*/

int			init_sdl(t_scene *scene, t_env *env);
int			handle_sdl_events(t_scene *scenes, t_env *env);

/*
** Intersection functions.
*/

// int			get_intersection(t_ray *ray, t_object *obj);
// int			get_sphere_intersection(t_ray *ray, t_object *obj);
// int			get_plane_intersection(t_ray *ray, t_object *obj);
// int			get_cylinder_intersection(t_ray *ray, t_object *obj);
// int			get_finite_cylinder_intersection(t_ray *ray, t_object *obj, t_intersection_tools *i);
// int			get_cyclinder_caps_intersection(t_ray *ray, t_object *obj, t_intersection_tools *i);
// int			get_cone_intersection(t_ray *ray, t_object *obj);
// int			get_caps_intersection(t_ray *ray, t_object *obj, double *t);
// int			get_disk_intersection(t_ray *ray, t_object *disk);
bool		intersects(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool		get_plane_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool		get_sphere_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool		get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool		get_finite_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i);
bool		get_finite_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i);
bool		lower_than_min(double r, t_intersection_tools *i, t_object *obj, t_ray *ray);
bool		higher_than_max(double r, t_intersection_tools *i, t_object *obj, t_ray *ray);
bool		get_cyclinder_caps_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj, t_intersection_tools *i);
bool		get_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *cone);
bool		get_disk_intersection(t_raytracing_tools *r, t_ray *ray, t_object *disk);
int			solve_quadratic(t_vec3 q, double *r1, double *r2);

/*
** Free Functions
*/

void		free_matrix(t_matrix *m);

/*
** List management Functions
*/

void			input_pushback(t_input **input, t_input *n);
t_input			*input_new(char *line, char *file_name, int fd, t_input **input);
int				init_color_list(t_color_list **colors);
void			color_pushback(t_color_list **colors, t_color_list *new_color);
t_color_list	*color_new(char *next_line);
bool			find_color_value(t_color_list *colors, char *value, t_vec3 *new_col);
int				get_hex_value(char c);
/*
** Error Functions
*/

void	error_line_exit(const char *msg, size_t line);
void	rt_file_error_exit(t_parse_tools *t, char *msg);
void	rt_file_warning(t_parse_tools *t, char *msg);
void	data_error_exit(t_scene *scene, int type, void *object, char *msg);
void	data_warning(t_scene *scene, int type, void *object, char *msg);

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
