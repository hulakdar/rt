/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:04:22 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/12 13:04:25 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void			ft_scene8(t_gra *o)
{
	o->objs = 1;
	o->ligs = 3;
	ft_scene_init(o);
	o->obj[0].type = 5;
	o->obj[0].col = (cl_uchar4){{48, 14, 20, 0}};
	o->obj[0].pos = (t_vec){{30, 29, 100}};
	o->obj[0].rot = (t_vec){{1, 0, 0}};
	o->obj[0].rad = 5;
	o->obj[0].alpha = 40;
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){{255, 255, 255, 0}};
	o->lights[0].pos = (t_vec){{200, 200, 30}};
	o->lights[0].inten = 0.6;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){{255, 255, 255, 0}};
	o->lights[1].pos = (t_vec){{80, 200, 0}};
	o->lights[1].inten = 0.6;
	o->lights[2].type = ambient;
	o->lights[2].col = (cl_uchar4){{255, 255, 255, 0}};
	o->lights[2].pos = (t_vec){{0, 40, -50}};
	o->lights[2].inten = 0.6;
    o->lights[3].type = end_light;
}


void			ft_scene50(t_gra *o)
{
	ft_cr_sphere(&o->obj[7], (cl_uchar4){48, 14, 20, 0},
		(t_vec){20, 25, 70}, 10);
	ft_cr_sphere(&o->obj[8], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-20, 25, 70}, 10);
	ft_cr_sphere(&o->obj[9], (cl_uchar4){48, 14, 20, 0},
		(t_vec){40, 25, 230}, 10);
	ft_cr_sphere(&o->obj[10], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-40, 25, 230}, 10);
	ft_cr_cyl(&o->obj[11], (cl_uchar4){48, 14, 20, 0},
		(t_vec){20, 0, 70}, (t_vec){0, 1, 0});
	ft_cr_cyl(&o->obj[12], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-20, 0, 70}, (t_vec){0, 1, 0});
	ft_cr_cyl(&o->obj[13], (cl_uchar4){48, 14, 20, 0},
		(t_vec){40, 310, 230}, (t_vec){0, 1, 0});
	ft_cr_cyl(&o->obj[14], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-40, 310, 230}, (t_vec){0, 1, 0});
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){40, 18, -50};
	o->lights[0].inten = 0.6;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){-40, 18, -50};
	o->lights[1].inten = 0.6;
    o->lights[2].type = end_light;
}

void			ft_scene5(t_gra *o)
{
	o->objs = 16;
	o->ligs = 2;
	ft_scene_init(o);
	ft_cr_sphere(&o->obj[0], (cl_uchar4){48, 14, 20, 0},
		(t_vec){20, -20, 70}, 10);
	ft_cr_sphere(&o->obj[1], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-20, -20, 70}, 10);
	ft_cr_sphere(&o->obj[2], (cl_uchar4){48, 14, 20, 0},
		(t_vec){40, -20, 230}, 10);
	ft_cr_sphere(&o->obj[3], (cl_uchar4){48, 14, 20, 0},
		(t_vec){-40, -20, 230}, 10);
	ft_cr_plane(&o->obj[4], (cl_uchar4){248, 14, 20, 0},
		(t_vec){0, -20, 0}, (t_vec){0, 1, 0});
	ft_cr_plane(&o->obj[5], (cl_uchar4){248, 14, 20, 0},
		(t_vec){0, 25, 0}, (t_vec){0, -1, 0});
	ft_cr_plane(&o->obj[6], (cl_uchar4){248, 14, 20, 0},
		(t_vec){0, 0, 300}, (t_vec){0, 0, 1});
	ft_cr_sphere(&o->obj[15], (cl_uchar4){24, 54, 50, 0},
		(t_vec){0, -13, 90}, 5);
	ft_scene50(o);
}

void			ft_scene6(t_gra *o)
{
	o->objs = 3;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_sphere(&o->obj[0], (cl_uchar4){48, 214, 200, 0},
		(t_vec){17, 0, 101}, 5);
	ft_cr_plane(&o->obj[1], (cl_uchar4){48, 214, 200, 0},
		(t_vec){0, -10, 0}, (t_vec){0, 1, 0});
//	ft_cr_plane(&o->obj[2], (cl_uchar4){48, 214, 200, 0},
//				(t_vec){0, 30, 0}, (t_vec){0, -1, 0});
//	ft_cr_cyl(&o->obj[3], (cl_uchar4){218, 254, 250, 0},
//		(t_vec){-10, 0, 90}, (t_vec){0, 1, 0});
	ft_cr_cone(&o->obj[2], (cl_uchar4){48, 14, 20, 0},
		(t_vec){30, 29, 100}, (t_vec){0, 1, 0});
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){60, 10, -60};
	o->lights[0].inten = 0.2;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){-60, 25, 60};
	o->lights[1].inten = 0.2;
	o->lights[2].type = ambient;
	o->lights[2].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[2].pos = (t_vec){10, 10, 0};
	o->lights[2].inten = 0.4;
    o->lights[3].type = end_light;
}

void			ft_scene7(t_gra *o)
{
	o->objs = 7;
	o->ligs = 2;
	ft_scene_init(o);
	ft_cr_sphere(&o->obj[0], (cl_uchar4){85, 5, 5, 0},
		(t_vec){45, 10, 190}, 20);
	ft_cr_sphere(&o->obj[1], (cl_uchar4){185, 155, 5, 0},
		(t_vec){5, -20, 150}, 25);
	ft_cr_plane(&o->obj[2], (cl_uchar4){48, 214, 200, 0},
	(t_vec){0, -80, 0}, (t_vec){0, 1, 0});
	ft_cr_plane(&o->obj[3], (cl_uchar4){48, 214, 200, 0},
	(t_vec){0, 270, 0}, (t_vec){0, -1, 0});
	ft_cr_plane(&o->obj[4], (cl_uchar4){48, 214, 200, 0},
	(t_vec){160, 0, 150}, (t_vec){-1, 0, 0});
	ft_cr_plane(&o->obj[5], (cl_uchar4){48, 214, 200, 0},
	(t_vec){-160, 0, 150}, (t_vec){1, 0, 0});
	ft_cr_plane(&o->obj[6], (cl_uchar4){48, 214, 200, 0},
	(t_vec){0, 0, 600}, (t_vec){0, 0, -1});
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){120, 210, 260};
	o->lights[0].inten = 0.5;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){-90, 212, -70};
	o->lights[1].inten = 0.6;
    o->lights[2].type = end_light;
}
