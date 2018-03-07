/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:42:54 by lberezyn          #+#    #+#             */
/*   Updated: 2018/01/22 11:42:59 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include "../include/ft_rtv.h"

static cl_double3			ft_rot_matrix(double alpha, double beta, double gamma, cl_double3 r)
{
	double		mat[3][3];
	cl_double3	ret;

	mat[0][0] = cos(beta) * cos(gamma);
	mat[1][0] = cos(gamma) * sin(alpha) * sin(beta) - cos(alpha) * sin(gamma);
	mat[2][0] = cos(alpha) * cos(gamma) * sin(beta) + sin(alpha) * sin(gamma);
	mat[0][1] = cos(beta) * sin(gamma);
	mat[1][1] = cos(alpha) * cos(gamma) + sin(alpha) * sin(beta) * sin(gamma);
	mat[2][1] = -cos(gamma) * sin(alpha) + cos(alpha) * sin(beta) * sin(gamma);
	mat[0][2] = -sin(beta);
	mat[1][2] = cos(beta) * sin(alpha);
	mat[2][2] = cos(alpha) * cos(beta);
	ret.x = (mat[0][0] * r.x) + (mat[1][0] * r.y) +
			(mat[2][0] * r.z);
	ret.y = (mat[0][1] * r.x) + (mat[1][1] * r.y) +
			(mat[2][1] * r.z);
	ret.z = (mat[0][2] * r.x) + (mat[1][2] * r.y) +
			(mat[2][2] * r.z);
	return (ret);
}

void	ft_draw(t_gra *o)
{
	rt_cl_host_to_device(o->cl, o->cam_mem, o->cam, sizeof(t_cam));
	clEnqueueNDRangeKernel(o->cl->command_queue,
						   o->kernel->kernel, 1,
						   NULL, &o->size, NULL, 0, NULL, NULL);
	rt_cl_device_to_host(o->cl, o->buf, o->addr, o->size * sizeof(int));
	rt_cl_join(o->cl);
	mlx_put_image_to_window(o->mlx, o->win, o->img, 0, 0);
}

t_gra			*key_hook_cam(t_gra *o, int keycode)
{
	if (keycode == 2)
		o->cam->angles.y += o->step;
	else if (keycode == 0)
		o->cam->angles.y -= o->step;
	else if (keycode == 1)
		o->cam->angles.x += o->step;
	else if (keycode == 13)
		o->cam->angles.x -= o->step;
	else if (keycode == ARROW_DOWN)
	{
		o->cam->cam_mod.origin.s0 -= o->cam->cam_mod.dir.s0;
		o->cam->cam_mod.origin.s1 -= o->cam->cam_mod.dir.s1;
		o->cam->cam_mod.origin.s2 -= o->cam->cam_mod.dir.s2;
	}
	else if (keycode == ARROW_UP)
	{
		o->cam->cam_mod.origin.s0 += o->cam->cam_mod.dir.s0;
		o->cam->cam_mod.origin.s1 += o->cam->cam_mod.dir.s1;
		o->cam->cam_mod.origin.s2 += o->cam->cam_mod.dir.s2;
	}
    if (keycode >= 0 && keycode <= 13)
        o->cam->cam_mod.dir = ft_rot_matrix(o->cam->angles.x, o->cam->angles.y, o->cam->angles.z, o->cam_def.dir);
	return (o);
}

t_gra			*key_hook_def(t_gra *o)
{
	o->cam->cam_mod.origin.s0 = o->cam_def.origin.s0;
	o->cam->cam_mod.origin.s1 = o->cam_def.origin.s1;
	o->cam->cam_mod.origin.s2 = o->cam_def.origin.s2;
	o->cam->cam_mod.dir = o->cam_def.dir;
	o->cam->angles.s0 = 0;
	o->cam->angles.s1 = 0;
	o->cam->angles.s2 = 0;
	return (o);
}

int				key_hook(int keycode, t_gra *o)
{
	if (keycode == 53)
	{
		mlx_destroy_image(o->mlx, o->img);
		mlx_destroy_window(o->mlx, o->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 82)
		o = key_hook_def(o);
	else if (keycode >= 123 && keycode <= 126)
		o = key_hook_cam(o, keycode);
	else if (keycode >= 0 && keycode <= 13)
		o = key_hook_cam(o, keycode);
	mlx_clear_window(o->mlx, o->win);
	ft_draw(o);
	return (0);
}

