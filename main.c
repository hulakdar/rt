/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:27:52 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/02 19:03:22 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"
#include <stdio.h>
#include <mlx.h>
#include "../include/ft_rtv.h"


void		ft_get_scene(int i, t_gra *o)
{
	if (i == 1)
		ft_scene1(o);
	else if (i == 2)
		ft_scene2(o);
	else if (i == 3)
		ft_scene3(o);
	else if (i == 4)
		ft_scene4(o);
	else if (i == 5)
		ft_scene5(o);
	else if (i == 6)
		ft_scene6(o);
	else if (i == 7)
		ft_scene7(o);
	else if (i == 8)
		ft_scene8(o);
}

static void		ft_init(t_gra *o, t_cl_info *info)
{
	int			dummy;

	o->cam_def.origin = (t_vec){{0, 0, 0}};
	o->cam_def.dir = (t_vec){{0, 0, 1}};
	o->cam_mod.origin = o->cam_def.origin;
	o->cam_mod.dir = o->cam_def.dir;
	o->cam_mod.screen.z = o->cam_mod.vport_dist;
	o->env_li = 0.3;
	o->an_x = 0;
	o->an_y = 0;
	o->an_z = 0;
	o->step = 0.1;
	cl_mem buf = rt_cl_malloc_read(info, o->size * sizeof(int));
	cl_mem objects = rt_cl_malloc_write(info, (o->objs + 1) * sizeof(t_obj), o->obj);
	cl_mem lights = rt_cl_malloc_write(info, (o->ligs + 1) * sizeof(t_li), o->lights);
	cl_mem camera = rt_cl_malloc_write(info, sizeof(t_cam), o->cam);
	rt_cl_push_arg(o->kernel, &objects, sizeof(cl_mem));
	rt_cl_push_arg(o->kernel, &lights, sizeof(cl_mem));
	rt_cl_push_arg(o->kernel, &buf, sizeof(cl_mem));
	rt_cl_push_arg(o->kernel, &camera, sizeof(cl_mem));
	clEnqueueNDRangeKernel(info->command_queue,
						   o->kernel->kernel, 1,
						   NULL, &o->size, NULL, 0, NULL, NULL);
	o->mlx = mlx_init();
	o->win = mlx_new_window(o->mlx, o->cam->win_w, o->cam->win_h, "IT WORKED?!");
	o->img = mlx_new_image(o->mlx, o->cam->win_w, o->cam->win_h);
	o->addr = (int *)mlx_get_data_addr(o->img, &dummy, &dummy, &dummy);
	o->cam_mem = camera;
	o->buf = buf;
	rt_cl_device_to_host(info, buf, o->addr, o->size * sizeof(int));
	mlx_hook(o->win, 17, 1L << 17, ft_exit_x, 0);
	mlx_key_hook(o->win, key_hook, o);
    rt_cl_join(info);
	mlx_put_image_to_window(o->mlx, o->win, o->img, 0, 0);
}

void		ft_error(char *s)
{
	//ft_putendl_fd(s, 2);
    write(2, s, 2);
	exit(0);
}

int			ft_exit_x(void)
{
	exit(0);
}

int	main(void)
{
    t_gra		o;
	t_cl_info	info;
	t_kernel 	kernel;
	t_cam		cam;

	o.cl = &info;
    rt_cl_init(&info);
    rt_cl_compile(&info, "../kernel.cl");
	kernel = rt_cl_create_kernel(&info, "ft_tracer");
	o.kernel = &kernel;
	cam.cam_mod = o.cam_mod;
	cam.angles = (t_vec){{0, 0, 0}};
	cam.win_w = 1300;
	cam.win_h = 1300;
	o.cam = &cam;
	o.size = cam.win_h * cam.win_w;
	ft_get_scene(2, &o);
    ft_init(&o, &info);
    mlx_loop(o.mlx);
}
