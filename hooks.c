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

#include "../include/ft_rtv.h"

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
	else if (keycode == 123)
		o->cam->cam_mod.origin.s0 += 0.1;
	else if (keycode == 124)
		o->cam->cam_mod.origin.s0 -= 0.1;
	else if (keycode == 126)
		o->cam->cam_mod.origin.s2 += 10;
	else if (keycode == 125)
		o->cam->cam_mod.origin.s2 -= 10;
	return (o);
}

t_gra			*key_hook_def(t_gra *o)
{
	o->cam->cam_mod.origin.s0 = o->cam_def.origin.s0;
	o->cam->cam_mod.origin.s1 = o->cam_def.origin.s1;
	o->cam->cam_mod.origin.s2 = o->cam_def.origin.s2;
	o->cam->cam_mod.dir = o->cam_def.dir;
	o->an_x = 0;
	o->an_y = 0;
	o->an_z = 0;
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

