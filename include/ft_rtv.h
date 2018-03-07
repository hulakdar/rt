/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:34:52 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:34:55 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RT_H
# define FT_RT_H

# include <fcntl.h>
# include </usr/local/include/mlx.h>
# include <math.h>
# include <errno.h>
# include <stdlib.h>
# include <pthread.h>

# include <stdio.h>
# include "cl_wrap.h"
# include "mac_key.h"

# define MES1 "Usage : ./RTv1 scene_number(1-8)"
# define MES2 "File opening failed"
# define MES3 "Reading failure"
# define MES4 "Memory allocation failure"
# define MES5 "Invalid scene file"
# define WIN_W 800
# define WIN_H 800
# define PI 3.14159265359

enum		e_light {
	ambient,
	point,
	end_light
};

enum 		e_obj_type {
	end_obj,
	kek,
	plane,
	sphere,
	cylinder,
	cone
};

typedef struct		s_dpoint
{
	cl_double			x;
	cl_double			y;
	cl_double			z;
}					t_dpoint;

typedef	cl_double3    t_vec;

typedef struct		s_camera
{
	t_vec			origin;
	t_vec			dir;
	t_vec			screen;
	cl_double		vport_dist;
}					t_camera;


typedef struct		s_obj
{
	short			type;
	cl_double		rad;
	t_vec			rot;
	t_vec			pos;
	cl_uchar4		col;
	cl_double		alpha;
}					t_obj;

typedef struct		s_li
{
	cl_char			type;
	t_vec			pos;
	cl_double		inten;
	cl_uchar4		col;
}					t_li;
typedef struct		s_cam
{
	t_camera		cam_mod;
	t_vec			angles;
	cl_uint 		win_h;
	cl_uint 		win_w;
}					t_cam;

typedef struct		s_gra
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*addr;
	t_cl_info 		*cl;
	t_kernel		*kernel;
	size_t	 		size;
	cl_mem			cam_mem;
	cl_mem			buf;
	int				bpp;
	int				sizeline;
	int				endian;
	t_camera		cam_def;
	t_camera		cam_mod;
	t_cam			*cam;
	int				objs;
	t_obj			*obj;
	short			ligs;
	t_li			*lights;
	cl_double		env_li;
	cl_double		step;
	float			an_x;
	float			an_y;
	float			an_z;
	cl_double		alp;
	cl_double		bet;
	cl_double		gam;
}					t_gra;

int					ft_exit_x(void);
void				ft_draw(t_gra *o);
void				ft_error(char *s);
int					key_hook(int keycode, t_gra *o);
t_gra				*key_hook_rot(t_gra *o, int keycode);
t_gra				*key_hook_def(t_gra *o);

void				ft_scene_init(t_gra *o);
void				ft_cr_sphere(t_obj *s, cl_uchar4 col,
									t_vec pos, cl_double rad);
void				ft_cr_plane(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);
void				ft_cr_cyl(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);
void				ft_cr_cone(t_obj *s, cl_uchar4 col,
								t_vec pos, t_vec rot);
void				ft_scene1(t_gra *o);
void				ft_scene2(t_gra *o);
void				ft_scene3(t_gra *o);
void				ft_scene4(t_gra *o);
void				ft_scene5(t_gra *o);
void				ft_scene50(t_gra *o);
void				ft_scene6(t_gra *o);
void				ft_scene7(t_gra *o);
void				ft_scene8(t_gra *o);
#endif
