#ifndef CL_WRAP_H
# define CL_WRAP_H
# define HEIGHT 800
# define WIDTH 800
# define MAX_SOURCE_SIZE (0x100000)
# include <pthread.h>
# include <math.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef unsigned char	t_byte;
typedef struct	s_cl_info
{
	cl_uint				num_devices;
	cl_uint				num_platforms;
	cl_device_id		device_id;
	cl_command_queue	command_queue;
	cl_context			context;
	cl_program			program;
	cl_platform_id		platform;
}				t_cl_info;
typedef union	u_color
{
	int			color;
	t_byte		channel[4];
}				t_color;

/*
 * Funcion to initialize the struct, getting the platform, devices,
 * context and command queue.
 */
void	rt_cl_init(t_cl_info *info);

/* Creating read-only buffer.
 */
cl_mem	rt_cl_malloc_read(t_cl_info *info, size_t size);

/* Creating write-only buffer.
 */
cl_mem	rt_cl_malloc_write(t_cl_info *info, size_t size);

/* Writing data to devices' memory.
 */
cl_int	rt_cl_host_to_device(
							t_cl_info *info,
							cl_mem obj,
							void *src,
							size_t size);

/* Reading data from devices' memory.
 */
cl_int	rt_cl_device_to_host(
							t_cl_info *info,
							cl_mem obj,
							void *dest,
							size_t size);

/* Compiling the program from source.
 */
cl_int	rt_cl_compile(t_cl_info *info, char *path);

/* Waiting for every task in queue to complete.
 */
void	rt_cl_join(t_cl_info *info);

/* Destruction of program, command_queue and context.
 */
void	rt_cl_free(t_cl_info *info);
#endif
