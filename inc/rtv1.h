/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:53:33 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/18 17:18:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include "/Users/jwalsh/.brew/include/SDL2/SDL.h"
# include "../Libft/inc/libft.h"
# include "../Libmathft/inc/libmathft.h"
# include "keycode_mac.h" //?
# include "colors.h"//?

/*
** General settings
*/

# define USAGE "usage: ./RTv1 <file.rt>"
# define DEFAULT_RES_W 500
# define DEFAULT_RES_H 700
# define DEFAULT_RAY_DEPTH 5
# define DEFAULT_KA 0.1
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
** Tokens for the parser.
*/

typedef enum		e_token
{
	T_OPEN_BRACKET,
	T_CLOSE_BRACKET,
	T_EMPTY_LINE,
	T_SCENE,
	T_CAMERA,
	T_LIGHT,
	T_PLANE,
	T_DISK,
	T_SPHERE,
	T_CYLINDER,
	T_CONE,
	T_RESOLUTION,
	T_RAY_DEPTH,
	T_BACKGROUND_COLOR,
	T_KA,
	T_AMBIENT_LIGHT_COLOR,
	T_POSITION,
	T_DIRECTION,
	T_ROTATION,
	T_LOOK_AT,
	T_COLOR,
	T_RADIUS,
	T_HEIGHT,
	T_DIFFUSE_COEF,
	T_REFRACTION,
	T_REFLECTION,
	T_SPECULAR_EXPONENT,
	T_SPECULAR_COEF, 
	T_TRANSPARENCY,
	T_FOV,
	T_INTENSITY,
	T_IMPORT_RT_FILE,
	T_READ_RT_FILE,
	T_READ_OBJ_FILE, 
	T_READ_TEXTURE_FILE,
	T_READ_MATERIAL_FILE,
	T_HASHTAG,
	T_INVALID_TOKEN,
	T_COUNT
}					t_token;

/*
** Link for chained list in which is stored info about each line parsed.
*/

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
	t_pt2		res;
	int			ray_depth;
	t_color		ambient_light_color;
	double		ka;
	double		intensity;
	double		fov;
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		rot;
	t_vec3		look_at;
	t_color		col; 
	double		rad;
	double		height;
	double		ks;
	double		kd;
	double		refraction;
	double		reflection;
	double		specular_exp;
	double		transparency;
}					t_attributes;

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

/*
**
*/

typedef	struct		s_ray
{
	t_ray_type	type; //ray type
	t_vec3		origin; // ray origin
	t_vec3		dir; // ray direction: must be normalized
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
	double			specular_exp;
	double			transparency;
	struct s_object	*next;
}				t_object;

typedef struct	s_light
{
    char			*name;
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
    t_vec3			pos;
    t_vec3			dir;
	t_vec3			rot;
	t_vec3			look_at;
	t_color			**pixel_map;
	t_matrix		ctw;
	double			scale;
	double			fov;
	struct s_camera	*prev;
	struct s_camera	*next;
}				t_camera;

/*
** Link containing info about one scene.
** res - resolution
** name - scene name
*/

typedef struct	s_scene
{
    t_pt2			res;
    char			*name;
    int				ray_depth;
	t_color			background_color;
	t_color			ambient_light_color;
	double			ka;
	double			image_aspect_ratio;
    t_camera		*cameras;
    t_light			*lights;
    t_object		*objects;
	struct s_scene	*prev;
    struct s_scene	*next;
}				t_scene;

/*
** Tools for parsing input files.
** input - chained list with info about each line
** scenes - chained list with info about all scenes
** current_* - pointers to relevant objects
** fd - current fd
** file_name - current file name
** global_attributes - attributes given outside scene declarations
** scene_attributes - attribtues given within scene declarations
**				      but outside object declarations
** object_attributes - attributes given within object declarations
** colors - chained list with color names and rgb values
** parse - list of function pointers for each token
*/

typedef struct		s_parse_tools
{
	bool			in_scene;
	bool			in_object;
	t_input			*input;
	t_input			*input_head; //pointer to input. // used?
	t_scene			*scenes;
	t_scene			*current_scene;
	t_object		*current_object;
	t_camera		*current_camera;
	t_light			*current_light;
	t_token			current_type;
	int				fd;
	char			*file_name;
	t_attributes 	*global_attributes;
	t_attributes	*scene_attributes;
	t_attributes	*object_attributes;
	t_color_list	*colors;
	char			**tokens;
	void			(**parse)(struct s_parse_tools *);
}					t_parse_tools;

/*
** Tools for determining ray object intersections.
** q - quadratic equation components
** r1, r2 - quadratic equation solutions/roots
** t - distance to closest intersection
** v1, v2, v3, p - extra temporary vectors
** d1, d2, d3 - extra temporary doubles
** n_dir - direction of normal at point
*/

typedef struct		s_intersection_tools
{
	t_vec3			q;
	double			r1;
	double			r2;
	double			t;
	t_vec3			p; // used?
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			v3;
	double			d1;
	double			d2;
	int				n_dir;
}					t_intersection_tools;

/*
** Tools to help with the raytracing algorithms.
** scenes - contains info about all scenes
** pix - current pixel
** t - distance to closest intersection 
*/

typedef struct		s_raytracing_tools
{
	t_scene			*scenes;
	t_pt2			pix;
	double			t;
}					t_raytracing_tools;

/*
** Basis structure to handle SDL events.
*/

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Event		e;
}					t_env;

/*
** File Parsing Functions
*/

void			init_parse_tools(t_parse_tools *t);
void			init_tokens(t_parse_tools *t);
void			get_file(char *file_name, t_parse_tools *t);
int				get_token(t_parse_tools *t, char *key);
void			parse_input(t_parse_tools *t);
char 			**split_trim(char *s, char c);
t_scene			*get_new_scene(t_parse_tools *t);
t_object 		*get_new_object(t_parse_tools *t);
void			set_non_values(t_object *new_object);
t_light 		*get_new_light(t_parse_tools *t);
t_camera 		*get_new_camera(t_parse_tools *t);
void			push_scene(t_scene **scenes, t_scene *new_scene);
void			push_object(t_object **objects, t_object *new_object);
void			push_light(t_light **lights_head, t_light *new_light);
void			push_camera(t_camera **cameras_head, t_camera *new_camera);
void			set_attributes(t_parse_tools *t, t_attributes *a);
int				reset_attributes(t_attributes *att);
void			parse_open_bracket(t_parse_tools *t);
void			parse_close_bracket(t_parse_tools *t);
void			parse_empty_line(t_parse_tools *t);
void			parse_scene(t_parse_tools *t);
void			parse_camera(t_parse_tools *t);
void			parse_light(t_parse_tools *t);
void			parse_plane(t_parse_tools *t);
void			parse_disk(t_parse_tools *t);
void			parse_sphere(t_parse_tools *t);
void			parse_cylinder(t_parse_tools *t);
void			parse_cone(t_parse_tools *t);
void			parse_resolution(t_parse_tools *t);
void			parse_ray_depth(t_parse_tools *t);
void			parse_background_color(t_parse_tools *t);
void			parse_ambient_light_color(t_parse_tools *t);
void			parse_ka(t_parse_tools *t);
void			parse_position(t_parse_tools *t);
void			parse_direction(t_parse_tools *t);
void			parse_rotation(t_parse_tools *t);
void			parse_look_at(t_parse_tools *t);
void			parse_color(t_parse_tools *t);
void			parse_radius(t_parse_tools *t);
void			parse_height(t_parse_tools *t);
void			parse_refraction(t_parse_tools *t);
void			parse_reflection(t_parse_tools *t);
void			parse_diffuse_coef(t_parse_tools *t);
void			parse_specular_coef(t_parse_tools *t);
void			parse_specular_exponent(t_parse_tools *t);
void			parse_transparency(t_parse_tools *t);
void			parse_fov(t_parse_tools *t);
void			parse_intensity(t_parse_tools *t);
void			import_rt_file(t_parse_tools *t);
void			read_rt_file(t_parse_tools *t);
void			read_obj_file(t_parse_tools *t);
void			read_texture_file(t_parse_tools *t);
void			read_material_file(t_parse_tools *t);
void			hashtag(t_parse_tools *t);
void			invalid_token(t_parse_tools *t);
t_vec3			get_color(t_parse_tools *t, char *value);
t_vec3			parse_rgb(char *value);
t_vec3			parse_hexadecimal(char *value);
bool			valid_hex_format(char *value, int *i);
t_vec3			parse_color_name(t_parse_tools *t, char *value);
t_vec3			parse_vector(char *value);
double			parse_double(char *value);

/*
** List management Functions
*/

void			input_pushback(t_input **input, t_input *n);
t_input			*input_new(char *line, char *file_name, int fd, t_parse_tools *t);
int				init_color_list(t_color_list **colors);
void			color_pushback(t_color_list **colors, t_color_list *new_color);
t_color_list	*color_new(char *next_line);
bool			find_color_value(t_color_list *colors, char *value, t_vec3 *new_col);
int				get_hex_value(char c);

/*
** Data Checking Functions
*/

void			check_data(t_scene *scenes);
void			check_cameras(t_scene *scene, t_camera *cameras);
void			check_lights(t_scene *scene, t_light *lights);
void			check_objects(t_scene *scene, t_object *objects);
void			get_obj_direction(t_scene *scene, t_object *obj);
void			get_cam_direction(t_scene *scene, t_camera *cam);
void			get_light_direction(t_scene *scene, t_light *light);
void			init_camera(t_scene *scene, t_camera *cam);
void			update_camera_scale(t_camera *camera);
void			update_camera_ctw(t_camera *camera);

/*
** Set Default Functions
*/

void			set_default_resolution(t_scene *scene);
void			set_default_ray_depth(t_scene *scene);
void			set_default_ka(t_scene *scene);
void			set_default_ambient_light_color(t_scene *scene);
void			set_default_pos(t_scene *scene, int type, void *obj, t_vec3 *pos);
void			set_default_col(t_scene *scene, int type, void *obj, t_vec3 *col);
void			set_default_intensity(t_scene *scene, int type, void *obj, double *intensity);
void			set_default_radius(t_scene *scene, int type, void *obj, double *radius);
void			set_default_height(t_scene *scene, int type, void *obj, double *height);
void			set_default_cam_dir(t_scene *scene, int type, void *cam, t_vec3 *dir);
void			set_default_obj_dir(t_scene *scene, int type, void *obj, t_vec3 *dir);
void			set_default_light_dir(t_scene *scene, int type, void *obj, t_vec3 *dir);
void			set_default_fov(t_scene *scene, int type, void *obj, double *fov);
void			set_default_ks(t_scene *scene, int type, void *obj, double *ks);
void			set_default_kd(t_scene *scene, int type, void *obj, double *kd);
void			set_default_specular_exp(t_scene *scene, int type, void *obj, double *specular_exp);

/*
** Ray Tracing Functions
*/

int 			rtv1(t_raytracing_tools *r);
void	 		render(t_raytracing_tools *r);
t_ray			init_camera_ray(t_pt2 i, t_scene *scene);
t_color			cast_primary_ray(t_raytracing_tools *r, t_ray *ray);
void			update_ray(t_ray *ray, t_object *obj, double *t);
void			get_normal(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool			in_shadow(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color			get_diffuse(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color			get_specular(t_raytracing_tools *r, t_ray *primary_ray, t_ray *shadow_ray, t_light *light);
t_color			get_ambient(t_raytracing_tools *r);
t_vec3			reflect(t_vec3 ray_dir, t_vec3 nhit);


/*
** Intersection functions.
*/

bool			intersects(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool			get_plane_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool			get_sphere_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool			get_cylinder_intersection(t_raytracing_tools *r, t_ray *ray, t_object *obj);
bool			get_cone_intersection(t_raytracing_tools *r, t_ray *ray, t_object *cone);
bool			get_disk_intersection(t_raytracing_tools *r, t_ray *ray, t_object *disk);
bool			solve_quadratic(t_vec3 q, double *r1, double *r2);

/*
** SDL2 Functions
*/

int				init_sdl(t_scene *scene, t_env *env);
int				handle_sdl_events(t_scene *scenes, t_env *env);

/*
** Free Functions
*/

void			free_matrix(t_matrix *m);

/*
** Error Functions
*/

void			error_line_exit(const char *msg, size_t line);
void			rt_file_error_exit(t_parse_tools *t, char *msg);
void			rt_file_warning(t_parse_tools *t, char *msg);
void			data_error_exit(t_scene *scene, int type, void *object, char *msg);
void			data_warning(t_scene *scene, int type, void *object, char *msg);

/*
** Debug functions
*/

# define C(...) ft_printf("check%i\n", __VA_ARGS__);
# define P(x) ft_printf(x);
void			print_scenes(t_scene *scenes_head);
void			print_input(t_list **list_head);
void			print_attributes(t_attributes att);
void			print_vec(t_vec3 vec);
void			print_matrix(t_matrix m);

#endif
