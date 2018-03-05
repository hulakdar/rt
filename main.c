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

void		ft_init(t_gra *o)
{
	o->cam_def.origin = (t_dpoint){0, 0, -100};
	o->cam_def.dir = (t_dpoint){0, 0, 1};
	o->cam_mod.origin = o->cam_def.origin;
	o->cam_mod.dir = o->cam_def.dir;
	o->cam_mod.screen.z = o->cam_mod.vport_dist;
	o->env_li = 0.3;
	o->an_x = 0;
	o->an_y = 0;
	o->an_z = 0;
	o->step = 10;
	o->i = 0;
}

void		ft_error(char *s)
{
	//ft_putendl_fd(s, 2);
    write(2, s, 2);
	exit(0);
}

int			ft_exit_x(void)
{
	exit(1);
}

// __kernel void	ft_tracer(t_obj *obj, t_li *li, global int *address, t_cam cam)
int	main(void)
{
    void		*mlx;
    void		*window;
    void		*image;
    int			*data;
    int			dummy;
    size_t		size;
    t_cam		cam;
    t_cl_info	info;
    t_gra		o;

    rt_cl_init(&info);
    rt_cl_compile(&info, "../kernel.cl");
    t_kernel kernel = rt_cl_create_kernel(&info, "ft_tracer");
	cl_mem buf = rt_cl_malloc_write(&info, 400 * 400 * sizeof(int));
	cl_mem objects = rt_cl_malloc_read(&info, o.objs * sizeof(t_obj));
	cl_mem lights = rt_cl_malloc_read(&info, o.ligs * sizeof(t_li));
    mlx = mlx_init();
    window = mlx_new_window(mlx, 400, 400, "IT WORKED?!");
    image = mlx_new_image(mlx, 400, 400);
    data = (int *)mlx_get_data_addr(image, &dummy, &dummy, &dummy);
    dummy = 400;
    size = 400;
    ft_get_scene(1, &o);
    ft_init(&o);
	cam.cam_mod = o.cam_mod;
	cam.angles = (t_dpoint){0, 0, 0};
    rt_cl_push_arg(&kernel, &objects, sizeof(cl_mem));
	rt_cl_push_arg(&kernel, &lights, sizeof(cl_mem));
	rt_cl_push_arg(&kernel, &buf, sizeof(cl_mem));
	rt_cl_push_arg(&kernel, &cam, sizeof(t_cam));
    clEnqueueNDRangeKernel(info.command_queue,
                           kernel.kernel, 2,
                           NULL, &size, NULL, 0, NULL, NULL);
    rt_cl_device_to_host(&info, buf, data, 400 * 400 * sizeof(int));
    rt_cl_join(&info);
    rt_cl_free(&info);
    rt_cl_free_kernel(&kernel);
	mlx_hook(window, 17, 1L << 17, ft_exit_x, 0);
	mlx_loop(mlx);
    mlx_put_image_to_window(mlx, window, image, 0, 0);
    mlx_loop(mlx);
}
