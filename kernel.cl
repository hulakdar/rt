typedef double3 t_vec;

typedef struct		s_camera
{
	double3			origin;
	double3			dir;
	double3	    	screen;
	double			vport_w;
	double			vport_h;
	double			vport_dist;
}					t_camera;
typedef struct		s_cam
{
	t_camera		cam_mod;
	double3			angles;
	unsigned 		win_h;
	unsigned 		win_w;
}					t_cam;
typedef struct		s_obj
{
	short			type;
	double			rad;
	double3			rot;
    double3			pos;
	uchar4          col;
	double			alpha;
}					t_obj;
typedef struct		s_li
{
	short			type;
	t_vec			pos;
	double			inten;
	uchar4	        col;
}					t_li;

#define syntax

static void ft_roots(double2 *t, double a, double b, double c)
{
	double	deskr;

	deskr = b * b - 4 * a * c;
	if (deskr >= 0 && a != 0)
	{
		if (deskr == 0)
		{
			t->x = -0.5 * b / a;
			t->y = t->x;
		}
		else
		{
			t->x = (-b + sqrt(deskr)) / (2 * a);
			t->y = (-b - sqrt(deskr)) / (2 * a);
		}
	}
	else
	{
		t->x = -1;
		t->y = -1;
	}
}

static void  ft_sphere(global t_obj *obj, double3 *ray, double2 *t)
{
	double	a;
	double	b;
	double	c;
	double3	oc;

	oc = ray[0] - obj->pos;
	a = dot(ray[1], ray[1]);
	b = 2 * dot(ray[1], oc);
	c = dot(oc, oc) - (obj->rad * obj->rad);
	ft_roots(t, a, b, c);
}

static void		ft_plane(global t_obj *obj, double3 *ray, double2 *t)
{
	double	a;
	double	b;
	t_vec	oc;

	oc = ray[0] - obj->pos;
	a = -dot(oc, obj->rot);
	b = dot(ray[1], obj->rot);
	t->x = b != 0 ? a / b : -1;
	if (t->x < 0.0001)
		t->x = -1;
	t->y = t->x;
}

static void		ft_cylinder(global t_obj *obj, double3 *ray, double2 *t)
{
	double	a;
	double	b;
	double	c;
	t_vec	oc;

	a = (double)(dot(ray[1], ray[1]) -
			(dot(ray[1], obj->rot) *
			dot(ray[1], obj->rot)));
	oc = ray[0] - obj->pos;
	b = 2 * (double)(dot(ray[1], oc) - dot(ray[1], obj->rot) * dot(oc, obj->rot));
	c = (double)(dot(oc, oc) - dot(oc, obj->rot) * dot(oc, obj->rot) -
	            (obj->rad * obj->rad));
	ft_roots(t, a, b, c);
}

static void		ft_cone(global t_obj *obj, double3 *ray, double2 *t)
{
	double2	dots;
	double3	abc;
	t_vec	oc;

	oc = ray[0] - obj->pos;
	dots = (double2)(dot(ray[1], obj->rot),  dot(oc, obj->rot));
	abc = (double3)(dot(ray[1], ray[1]) - (1 + obj->aplpha * obj->aplpha) * dots.x * dots.x,
	2 * (dot(ray[1], oc) - (1 + obj->aplpha * obj->aplpha) * dots.x * dots.y),
	dot(oc, oc) - (1 + obj->aplpha * obj->aplpha) * dots.y * dots.y;
	ft_roots(t, abc.x, abc.y, abc.z);
}

static double				ft_shadow(global t_obj *me, global t_obj *obj, double3 *ray)
{
	int				i;
	double			root;
	double			ret;
	double2         t;

	i = -1;
	root = length(ray[1]);
	ret = 0.0;
	ray[1] = normalize(ray[1]);
	while (obj->type)
	{
		if (me != obj)
        {
            t = (double2)(0, 0);
            if (obj->type == 3)
                ft_sphere(obj, ray, &t);
            else if (obj->type == 2)
            	ft_plane(obj, ray, &t);
            else if (obj->type == 4)
            	ft_cylinder(obj, ray, &t);
            else if (obj->type == 5)
                ft_cone(obj, ray, &t);
            if (t.x > 0.000000000001 && t.x < root)
                ret += t.x;
        }
		obj++;
	}
	return (ret);
}

static double3				ft_normal(double3 *ray, global t_obj *obj, double3 p, double t)
{
    double3			n;
	double3			oc;
	double			m;

	if (obj->type == 4 || obj->type == 5)
	{
		oc = ray[0] - obj->pos;
		m = dot(ray[1], obj->rot) * t + dot(oc, obj->rot);
		n = p - obj->pos - obj->rot * m;
		if (obj->type == 5)
			n = n - obj->rot * m * obj->alpha * obj->alpha;
	}
	else if (obj->type == 2)
		n = obj->rot;
	else if (obj->type == 3)
		n = p - obj->pos;
	n = normalize(n);
	return (n);
}

static double3			ft_rot_matrix(double alpha, double beta, double gamma, double3 r)
{
	double3		mat[3];

	mat[0] = (double3)(cos(beta) * cos(gamma), cos(beta) * sin(gamma), -sin(beta));
	mat[1] = (double3)(cos(gamma) * sin(alpha) * sin(beta) - cos(alpha) * sin(gamma),
		cos(alpha) * cos(gamma) + sin(alpha) * sin(beta) * sin(gamma),
		cos(beta) * sin(alpha));
	mat[2] = (double3)(cos(alpha) * cos(gamma) * sin(beta) + sin(alpha) * sin(gamma),
		-cos(gamma) * sin(alpha) + cos(alpha) * sin(beta) * sin(gamma),
		cos(alpha) * cos(beta));
	return (mat[0] * r.x + mat[1] * r.y + mat[2] * r.z);
	// ????? mat * r ?????
}

static double3	ft_rotation(double3 dir, double3 angles)
{
	return (ft_rot_matrix(angles.x, angles.y, angles.z,
		normalize(dir)));
}

static void		ft_get_ray(t_cam cam, int x, int y, double3 *ray)
{
	ray[0] = cam.cam_mod.origin;
	ray[1] = (double3)((((x + 0.5) / cam.win_w) * 2 - 1) * cam.win_w / cam.win_h,
			   1 - 2 * ((y + 0.5) / cam.win_h),
			   1.0);
	ray[1] = ft_rotation(ray[1], cam.angles);
}

__kernel void		ft_tracer(global t_obj *obj, global t_li *li,global int *address, global t_cam *cam_p)
{
    t_cam 			cam = *cam_p;
	global t_obj	*start = obj;
	global t_obj	*current = 0;
    int         	x = get_global_id(0) % cam.win_w;
    int			y = get_global_id(0) / cam.win_w;
    uchar4      	clo_col = (uchar4){0,0,0,0};
    double3     	ray[2] = {(double3)(0,0,0),(double3)(0,0,0)};
    double2     	t = (double2)(-1,-1);
    double      	clo = INFINITY;
    double      	light = 0.2;
    double      	blik = 0.0;
    double			cosi;
    double3			h;
    double3			l;
    double3     	lp[2];

    ft_get_ray(cam, x, y, &ray[0]);
    /*
    if (x == 200 && y == 200)
        printf("Ray: %f %f %f %d %f %x\n", obj->pos.x, obj->pos.y, obj->pos.z, obj->type, obj->rad, obj->col);
    t_obj object = {3, 2.0, {0,0,0},{0,0,40},(uchar4)(214,48,255,0),0.0};
    t_obj *obj = &object;
    t_li lili = {1,(t_vec)(0,10,10),1.0,(uchar4)(255,255,255,0)};
    t_li *li = &lili;
     */
    while (obj->type != 0)
    {
        if (obj->type == 3)
            ft_sphere(obj, ray, &t);
        else if (obj->type == 2)
            ft_plane(obj, ray, &t);
        else if (obj->type == 4)
            ft_cylinder(obj, ray, &t);
        else if (obj->type == 5)
            ft_cone(obj, ray, &t);
        if (t.x < 0 && t.y < 0)
            ;
        else
        {
            if (t.x < 0)
                t.x = t.y;
            else if (t.y < 0)
                ;
            else
                t.x = (t.x < t.y) ? t.x : t.y;
            if (clo > t.x)
            {
                if (t.x > 0.0 || t.y > 0.0)
                {
                    clo = t.x;
                    clo_col = obj->col;
					current = obj;

                }
            }
        }
        obj++;
    }
    if (current)
    {
        double3 p = ray[1] * clo + cam.cam_mod.origin;
        lp[0] = p;
        uchar4 blik_col = {0, 0, 0, 0};
        double3 pc = ft_normal(&ray[0], current, p, clo);
        double3 v = cam.cam_mod.origin - p;
        v = normalize(v);
        while (li->type != 2)
        {
            lp[1] = li->pos - p;
            if ((ft_shadow(current, start, lp)) == 0)
            {
                l = normalize(lp[1]);
                h = l + v;
                h = normalize(h);
                cosi = dot(pc, l);
                cosi = cosi < 0 ? 0 : cosi;
                light += cosi * li->inten;
                double dotsq = dot(h, pc) * dot(h, pc);
                blik = exp(-250 * (1.0 - dotsq) / dotsq);
                blik_col.x = (blik_col.x + li->col.x * blik * li->inten > 255) ? 255 :
                             blik_col.x + li->col.x * blik * li->inten;
                blik_col.y = (blik_col.y + li->col.y * blik * li->inten > 255) ? 255 :
                             blik_col.y + li->col.y * blik * li->inten;
                blik_col.z = (blik_col.z + li->col.z * blik * li->inten > 255) ? 255 :
                             blik_col.z + li->col.z * blik * li->inten;
            }
        	li++;
        }
        clo_col.x = ((clo_col.x * light +
                      blik_col.x) > 255) ? 255 :
                    clo_col.x * light + blik_col.x;
        clo_col.y = ((clo_col.y * light +
                      blik_col.y) > 255) ? 255 :
                    clo_col.y * light + blik_col.y;
        clo_col.z = ((clo_col.z * light +
                      blik_col.z) > 255) ? 255 :
                    clo_col.z * light + blik_col.z;

    }
    address[x + y * cam.win_w] = upsample(upsample(clo_col.w,clo_col.x), upsample(clo_col.y,clo_col.z));
}

