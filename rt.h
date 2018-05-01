/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:26 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/30 21:28:11 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIN_LEN 640
# define WIN_HEIGHT 480
# define PLN_DST 100
# define EPS 0.0001
# define ANTIALIA 10
# define MAX 9999
# define AMB 0.2

# define DOWN SDL_MOUSEBUTTONDOWN
# define UP SDL_MOUSEBUTTONUP
# define MOTION SDL_MOUSEMOTION

# define SPH 1
# define PLN 2
# define CON 3
# define CYL 4
# define CUB 5
# define ELL 6
# define TOR 7
# define PAR 8
# define HYP 9

# include "libft/includes/libft.h"
# include "frameworks/SDL2.framework/Headers/SDL.h"
# include "frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include <math.h>
# include <complex.h>
# include <pthread.h>

# define B 0x100
# define BM 0xff
# define N 0x1000

typedef	struct			s_material
{
	double				r;
	double				g;
	double				b;
}						t_material;

typedef	struct			s_coo
{
	double				x;
	double				y;
	double				z;
}						t_coo;

typedef	struct			s_texture
{
	int						type;
	t_coo					offset;
	t_coo					scale;
	char					*path;
	SDL_Surface				*surface;
}						t_texture;

typedef	struct			s_data
{
	unsigned int		*image_int;
	unsigned int		*image_base;
	SDL_Window			*sdl_window;
	SDL_Renderer		*sdl_renderer;
	SDL_Texture			*sdl_texture;
	SDL_Window			*info_window;
	SDL_Surface			*info_surface;
	TTF_Font			*font;
}						t_data;

/*
** Object Structs
*/

typedef	struct			s_plane
{
	t_material			*color;
	t_coo				norm;
	t_coo				o;
	double				supp;
	int					id;
	int					cut;
	t_texture			*texture;
	double				reflex;
	struct s_plane		*next;
}						t_plane;

typedef struct			s_cylinder
{
	t_coo				o;
	t_coo				rot;
	t_coo				dir;
	t_plane				*pln;
	double				radius;
	double				shine;
	t_material			*color;
	int					id;
	t_texture			*texture;
	double				reflex;
	struct s_cylinder	*next;
}						t_cylinder;

typedef	struct			s_cone
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	t_plane				*pln;
	double				angle;
	double				shine;
	int					id;
	t_texture			*texture;
	t_material			*color;
	double				reflex;
	struct s_cone		*next;
}						t_cone;

typedef	struct			s_sphere
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	double				radius;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	int					id;
	t_texture			*texture;
	double				reflex;
	struct s_sphere		*next;
}						t_sphere;

typedef	struct			s_ellipse
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	t_coo				rad1;
	t_coo				rad2;
	t_coo				rad3;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	int					id;
	t_texture			*texture;
	struct s_ellipse	*next;
}						t_ellipse;

typedef	struct			s_cube
{
	t_material			*color;
	double				radius;
	t_coo				dir;
	t_coo				o;
	t_coo				a;
	t_coo				u;
	t_coo				v;
	double				shine;
	t_coo				rot;
	int					id;
	struct s_cube		*next;
}						t_cube;

typedef	struct			s_tore
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	double				radiusa;
	double				radiusb;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	int					id;
	struct s_tore		*next;
}						t_tore;

typedef	struct			s_parabol
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	double				rad1;
	double				rad2;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	int					id;
	struct s_parabol	*next;
}						t_parabol;

typedef struct			s_light
{
	t_coo				o;
	t_material			*color;
	t_coo				dir;
	t_coo				norm;
	double				angle;
	double				power;
	double				shine;
	double				amb;
	int					id;
	struct s_light		*next;
}						t_light;

typedef	struct			s_ray
{
	t_coo				o;
	t_coo				dir;
	t_coo				obj;
}						t_ray;

typedef	struct			s_cam
{
	t_coo				pos;
	t_coo				forw;
	t_coo				up;
	t_coo				right;
	t_coo				rot;
}						t_cam;

/*
** Equations structs
*/

typedef	struct			s_perlin
{
	int					b_tmp[3][2];
	double				r[3][2];
	double				tab_2[3];
	int					*p;
	int					**b;
	double				*tab;
}						t_perlin;

typedef struct			s_equa
{
	double				ini[5];
	double				a[5];
	_Complex double		x[4];
	_Complex double		u[3];
	_Complex double		v[3];
	double				min;
}						t_equa;

typedef struct			s_equa_2
{
	double				p;
	double				q;
	double				delta;
	int					k;
	_Complex double		j;
	_Complex double		j2;
}						t_equa_2;

typedef struct			s_equa_3
{
	double				p;
	double				q;
	double				r;
	double				y;
	_Complex double		a0;
	double				b0;
}						t_equa_3;

typedef	struct			s_view
{
	double				screen_ratio;
	double				height;
	double				length;
	t_coo				up_left;
}						t_view;

typedef	struct			s_inter
{
	double				dst;
	t_material			*mat;
	t_material			*col;
	t_material			*lgh;
	t_ray				*angle;
	t_coo				point;
	int					obj;
	int					num;
	int					light;
	double				reflex;
}						t_inter;

typedef	struct			s_start
{
	t_sphere			*sph;
	t_plane				*pln;
	t_cone				*con;
	t_cylinder			*cyl;
	t_cube				*cub;
	t_ellipse			*ell;
	t_light				*lgh;
	t_tore				*tor;
	t_parabol			*par;
}						t_start;

typedef	struct			s_options
{
	int					sepia;
	int					blwh;
	int					maintain;
	int					obj;
	int					id;
	int					cam_move;
	int					max_depth;
}						t_options;

typedef	struct			s_rt
{
	t_data				*data;
	t_ray				*ray;
	t_cam				*cam;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cone				*cone;
	t_cylinder			*cylinder;
	t_cube				*cube;
	t_ellipse			*ellipse;
	t_parabol			*parabol;
	t_tore				*tore;
	t_view				*view;
	t_ray				*light_ray;
	t_inter				*inter;
	t_start				*start;
	t_options			*op;
	double				amb;
	t_equa				*equa;
	t_coo				tmp;
	int					lock;
	int					depth;
	int					maxdepth;
	double				reflex;
}						t_rt;

/*
** Errors
*/

void					ft_malloc_error(void);
void					ft_bad_arg(int i);
void					ft_exit(void);
void					ttf_exit(void);

/*
** Initialisation
*/

void					ft_ini(t_rt *rt);
void					ft_ini_cam(t_rt *rt);
void					ft_create(t_rt *rt);
void					parser(t_rt *rt, char *file);
int						ft_check_obj(char *str, int fd, t_rt *rt);
void					check_forms(t_rt *rt, int type);
void					ft_reset(t_rt *rt);

/*
** Parser Datas
*/

t_material				*check_color(t_material *color, char **str);
int						tab_len(char **str);
t_coo					get_coo(char **str, int err);
t_material				*get_color(char **str);
double					get_radius(char **str);
void					free_parser(t_rt *rt);

/*
** Event
*/

int						my_key_press(t_rt *rt, SDL_Keysym key);
int						ft_exit_cross(t_rt *rt);

/*
** Core
*/

void					ft_raytracing(t_rt *rt);
void					ft_check_object(t_rt *rt);

void					put_pxl(t_data *data, int x, int y, t_material *color);
void					put_pxl_base(t_data *data, int x, int y,
						t_material *color);

/*
** Vectors
*/

t_coo					ft_new_vect(float x, float y, float z);
t_coo					ft_add_vect(t_coo vect1, t_coo vect2);
t_coo					ft_div_vect(double i, t_coo vect);
t_coo					ft_mult_vect(double i, t_coo vect);
t_coo					ft_sub_vect(t_coo vect1, t_coo vect2);

double					sqrt3(double a);
double					scal(t_coo vect1, t_coo vect2);
double					ft_dst(t_coo point1, t_coo point2);
double					ft_norme(t_coo vect);
t_coo					ft_normalize(t_coo vect);
double					disc_eq(double t1, double t2);

double					ft_min(t_rt *rt, t_equa *equa);
void					ft_equa2(t_equa *equa, double a0, double a1, double a2);
void					ft_equa3(t_rt *rt, double a0, t_coo data);
void					ft_equa4(t_rt *rt);
double					ft_real(t_equa *equa);

/*
** Sphere
*/

double					ft_check_sphere(t_sphere *sphere, t_ray *ray);
void					check_sphere_inter(t_rt *rt, int type);
void					ft_ini_sphere(t_rt *rt);
int						ft_add_sphere(int fd, t_rt *rt, int id);
void					ft_sphere_info(t_sphere *sphere);
void					free_sphere(t_rt *rt);
void					move_sphere(t_rt *rt, SDL_Event ev);
void					inter_plane_sphere(t_sphere *sphere, char **datas);

/*
** Plane
*/

void					check_plane_inter(t_rt *rt, int type);
double					ft_check_plane(t_plane *plane, t_ray *ray);
void					ft_ini_plane(t_rt *rt);
int						ft_add_plane(int fd, t_rt *rt, int id);
void					move_plane(t_rt *rt, SDL_Event ev);
void					ft_plane_info(t_plane *plane);

/*
** Cone
*/

void					check_cone_inter(t_rt *rt, int type);
double					ft_check_cone(t_cone *cone, t_ray *ray);
int						ft_add_cone(int fd, t_rt *rt, int id);
void					ft_cone_info(t_cone *cone);
void					free_cone(t_rt *rt);
void					move_cone(t_rt *rt, SDL_Event ev);
void					get_norm_cone(t_rt *rt);
void					inter_plane_cone(t_cone *cone, char **datas);

/*
** Cylinder
*/

int						ft_add_cylinder(int fd, t_rt *rt, int id);
void					check_cylinder_inter(t_rt *rt, int type);
void					free_cylinder(t_rt *rt);
void					move_cyl(t_rt *rt, SDL_Event ev);
void					norm_cylinder(t_rt *rt);
void					inter_plane_cylinder(t_cylinder *cylinder,
char **datas);

/*
** Parabol
*/

void					check_parabol_inter(t_rt *rt, int type);
int						ft_add_parabol(int fd, t_rt *rt, int id);
void					ft_parabol_info(t_parabol *parabol);
void					free_parabol(t_rt *rt);

/*
** Tore
*/

int						ft_add_tore(int fd, t_rt *rt, int id);
void					check_tore_inter(t_rt *rt, int type);
double					ft_check_tore(t_rt *rt, t_ray *ray);
void					ft_tore_info(t_tore *tore);
void					free_tore(t_rt *rt);

/*
** Cam and Lights
*/

int						ft_add_light(int fd, t_rt *rt, int id);

int						light_amb(t_rt *rt, int fd);

int						ft_add_cam(int fd, t_rt *rt);

void					ft_get_point(t_rt *rt);
void					ft_apply_light(t_rt *rt);
void					ft_light_diffspec(t_rt *rt);
void					ft_get_light(t_rt *rt);

/*
** Rotation
*/

t_coo					ft_rotation(t_coo vect, t_coo rot);
void					make_rot(t_rt *rt);

void					tore_para_rot(t_rt *rt);
void					cyl_cone_rot(t_rt *rt);
void					sphere_ellipse_rot(t_rt *rt);

/*
** Cube Functions
*/

t_coo					ft_det_vect(t_coo vect1, t_coo vect2);
void					check_cube_inter(t_rt *rt, int type);
int						ft_add_cube(int fd, t_rt *rt, int id);
void					ft_angle_cube(t_cube *cube, int i);
void					ft_face_cube(t_cube *cube, int i);
void					ft_norm_cube(t_rt *rt, int i);

/*
** Antialiasing
*/

void					aliasing(t_rt *rt);
void					ft_ray(t_rt *rt, int x, int y, int type);
void					ft_ini_ray(t_rt *rt, double x, double y);

/*
** Cut plane Functions
*/

double					ft_inter_plane_ini(t_ray *ray, t_plane *pln,
double t1, double t2);

/*
** Ellipse Functions
*/

void					check_ellipse_inter(t_rt *rt, int type);
int						ft_add_ellipse(int fd, t_rt *rt, int id);
void					ft_ellipse_info(t_ellipse *ellipse);

/*
** Color Functions
*/

t_material				hex_rgb(int col);
unsigned int			col_hexa(int r, int g, int b);
void					ft_check_expose(t_material *mat, double max);

/*
** Color Filters
*/

void					sepia(t_rt *rt);
void					bl_wh(t_rt *rt);
void					cpy_image(unsigned int *tab1, unsigned int *tab2);

/*
** Direct movement of objects
*/

void					move_object(t_rt *rt, SDL_Event ev);
void					get_obj(t_rt *rt, int x, int y);
void					move_camera(t_rt *rt, SDL_Event ev);
t_coo					ft_inv_rot(t_coo vect, t_coo rot);
void					move_color(t_material *c, double r, double g, double b);

void					rt_infos(t_rt *rt);

/*
** Textures
*/

int						ft_texture_all(t_rt *rt, t_coo hit, t_texture *texture);
int						ft_texture_checker(double l, t_coo hit);
int						ft_texture_stripe(double width, t_coo hit, int x_or_y);
int						ft_texture_woodgrain(t_coo hit);
int						ft_texture_color_rainbow(double x);
double					ft_texture_waves(t_coo hit);
double					ft_texture_perlin(t_coo hit);
double					ft_texture_marble(t_coo hit);
double					ft_texture_wood(t_coo hit);
int						ft_texture_square(t_coo hit, t_rt *rt);
int						ft_texture_sparkle(void);
t_material				*ft_mult_color(int n, t_material *color);

t_coo					ft_mapping_all(t_coo hit, t_rt *rt);
t_coo					ft_mapping_sphere(t_coo hit);
t_coo					ft_mapping_cylinder(t_coo hit);
t_coo					ft_mapping_cone(t_coo hit);
t_coo					ft_mapping_plane(t_coo hit, t_coo origin_plane,
t_coo dir_plane);

t_coo					ft_local_coo(t_coo hit, t_coo origin, t_coo rot);
t_coo					ft_new_coo(double u, double v, t_texture *t,
SDL_Surface *s);
t_coo					ft_texel(double u, double v, SDL_Surface *surface);
t_coo					ft_uv(t_coo point_2d, int obj, SDL_Surface *surface);
t_coo					ft_shift_texture(SDL_Surface *s, t_coo p, double a,
double b);
t_coo					ft_scale_texture(SDL_Surface *s, t_coo p, double a,
double b);

t_material				ft_getpixelcolor(SDL_Surface *surface,
double i, double j);

SDL_Surface				*ft_upload_texture(char *path);
int						ft_check_textures_uploaded(t_data *data,
SDL_Surface *surface);
int						ft_check_img_path(char *img_path);

int						ft_save_img(t_rt *rt);

void					ft_ini_texture(t_texture *texture);

int						get_texture_type(char **str);
t_coo					get_scale(char **str, int err);
t_coo					get_offset(char **str, int err);
char					*get_path(char **str);

t_coo					ft_local_coo(t_coo hit, t_coo origin, t_coo rot);

int						tab_len(char **str);
char					*get_path(char **str);
t_coo					get_scale(char **str, int err);
t_coo					get_offset(char **str, int err);
int						get_texture_type(char **str);

double					ft_noise(double vec[3]);
double					s_curve(double t);
double					at3(double rx, double ry, double rz, double *q);
double					lerp(double t, double a, double b);
t_perlin				*ft_setup(t_perlin *l, double *vec);
void					ft_free_bl(t_perlin *l, int **b);
double					ft_lerp(double s1, double *tab);
t_perlin				*ft_rndm(t_perlin *l, double g3[B + B + 2][3], int i);
int						*ft_init_p(t_perlin *l, int i, int j, int k);

/*
** Threads Functions
*/

void					*thread_render_1(void *rt);
void					*thread_render_2(void *rt);
void					*thread_render_3(void *rt);
void					*thread_render_4(void *rt);

void					ft_reflexion_ray(t_rt *rt);

#endif
