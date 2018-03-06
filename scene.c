/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:35:32 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:35:34 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void			ft_scene_init(t_gra *o)
{
	if (!(o->obj = (t_obj*)malloc(sizeof(t_obj) * (o->objs + 1))))
		ft_error(MES4);
	if (!(o->lights = (t_li*)malloc(sizeof(t_li) * (o->ligs + 1))))
		ft_error(MES4);
}

void			ft_scene1(t_gra *o)
{
	o->objs = 1;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_sphere(&o->obj[0], (cl_uchar4){0, 255, 255, 0}, (t_vec){0, 0, 90}, 25);
	o->obj[1].type = end_obj;
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){200, 200, 30};
	o->lights[0].inten = 0.6;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){80, 200, 0};
	o->lights[1].inten = 0.6;
	o->lights[2].type = ambient;
	o->lights[2].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[2].pos = (t_vec){0, 40, -50};
	o->lights[2].inten = 0.6;
    o->lights[3].type = end_light;
}

void			ft_scene2(t_gra *o)
{
	o->objs = 3;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_sphere(&o->obj[0], (cl_uchar4){48, 214, 200, 0},
		(t_vec){0, 0, 150}, 25);
	ft_cr_plane(&o->obj[1], (cl_uchar4){28, 114, 100, 0},
		(t_vec){10, -30, 0}, (t_vec){0, 1, 0});
	ft_cr_sphere(&o->obj[2], (cl_uchar4){85, 5, 5, 0},
		(t_vec){30, 10, 150}, 25);
	o->obj[3].type = end_obj;
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){160, 200, -60};
	o->lights[0].inten = 0.8;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){50, 150, 160};
	o->lights[1].inten = 0.6;
	o->lights[2].type = ambient;
	o->lights[2].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[2].pos = (t_vec){0, 100, 0};
	o->lights[2].inten = 0.3;
	o->lights[3].type = end_light;
}

void			ft_scene3(t_gra *o)
{
	o->objs = 1;
	o->ligs = 2;
	ft_scene_init(o);
	ft_cr_cone(&o->obj[0], (cl_uchar4){255, 255, 255, 0},
		(t_vec){0, 0, 0}, (t_vec){0, 1, 0});
	o->obj[1].type = end_obj;
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){0, 200, -130};
	o->lights[0].inten = 0.6;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){-80, 200, 0};
	o->lights[1].inten = 0.6;
	o->lights[2].type = end_light;
}

void			ft_scene4(t_gra *o)
{
	o->objs = 1;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_cyl(&o->obj[0], (cl_uchar4){255, 235, 135, 0},
		(t_vec){0, 0, 0}, (t_vec){0, 1, 0});
	o->obj[1].type = end_obj;
	o->lights[0].type = ambient;
	o->lights[0].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[0].pos = (t_vec){160, 200, -60};
	o->lights[0].inten = 0.2;
	o->lights[1].type = ambient;
	o->lights[1].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[1].pos = (t_vec){50, 200, 60};
	o->lights[1].inten = 0.2;
	o->lights[2].type = ambient;
	o->lights[2].col = (cl_uchar4){255, 255, 255, 0};
	o->lights[2].pos = (t_vec){0, -50, 0};
	o->lights[2].inten = 0.4;
	o->lights[3].type = end_light;
}
