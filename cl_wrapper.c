/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:37:46 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/02 18:06:00 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"

void		rt_cl_init(t_cl_info *info)
{
	cl_int		status;

	clGetPlatformIDs(
			1,
			&info->platform,
			&info->num_platforms);
	clGetDeviceIDs(
			info->platform,
			CL_DEVICE_TYPE_GPU,
			1,
			&info->device_id,
			&info->num_devices);
	info->context = clCreateContext(
			NULL,
			1,
			&info->device_id,
			NULL,
			NULL,
			&status);
	info->command_queue = clCreateCommandQueue(
			info->context,
			info->device_id,
			0,
			&status);
}

cl_mem		rt_cl_malloc_read(t_cl_info *info, size_t size)
{
	return (clCreateBuffer(
			info->context,
			CL_MEM_READ_ONLY,
			size,
			NULL,
			NULL));
}

cl_mem		rt_cl_malloc_write(t_cl_info *info, size_t size)
{
	return (clCreateBuffer(
			info->context,
			CL_MEM_WRITE_ONLY,
			size,
			NULL,
			NULL));
}

cl_int		rt_cl_host_to_device(
							t_cl_info *info,
							cl_mem obj,
							void *src,
							size_t size)
{
	return (clEnqueueWriteBuffer(
				info->command_queue,
				obj,
				CL_TRUE,
				0,
				size,
				src,
				0,
				NULL,
				NULL));
}

cl_int		rt_cl_device_to_host(
							t_cl_info *info,
							cl_mem obj,
							void *dest,
							size_t size)
{
	return (clEnqueueReadBuffer(
				info->command_queue,
				obj,
				CL_TRUE,
				0,
				size,
				dest,
				0,
				NULL,
				NULL));
}

cl_int		rt_cl_compile(t_cl_info *info, char *path)
{
	int		fd;
	char	src[MAX_SOURCE_SIZE];
	size_t	size;
	char	*seeker;

	if ((fd = open(path, O_RDONLY)) != -1)
	{
		size = read(fd, src, MAX_SOURCE_SIZE);
		seeker = &src[0];
		info->program = clCreateProgramWithSource(
				info->context,
				1,
				(const char **)&seeker,
				(const size_t *)&size,
				NULL);
		clBuildProgram(info->program, 1, &info->device_id, NULL, NULL, NULL);
		close(fd);
	}
	else
		return (CL_BUILD_PROGRAM_FAILURE);
	return (CL_SUCCESS);
}

void		rt_cl_join(t_cl_info *info)
{
	clFlush(info->command_queue);
	clFinish(info->command_queue);
}

void		rt_cl_free(t_cl_info *info)
{
	clReleaseProgram(info->program);
	clReleaseCommandQueue(info->command_queue);
	clReleaseContext(info->context);
}

void		rt_cl_free_kernel(t_kernel *kernel)
{
	clReleaseKernel(kernel->kernel);
}

t_kernel	rt_cl_create_kernel(t_cl_info *info, char *name)
{
	t_kernel	kernel;

	kernel.kernel = clCreateKernel(info->program, name, NULL);
	kernel.args = 0;
	kernel.info = info;
	return (kernel);
}

void		rt_cl_push_arg(t_kernel *kernel, void *src, size_t size)
{
	clSetKernelArg(kernel->kernel, kernel->args++, size, src);
}

void		rt_cl_drop_arg(t_kernel *kernel)
{
	kernel->args = 0;
}

void		rt_cl_push_task(t_kernel *kernel, size_t size)
{
    clEnqueueNDRangeKernel(kernel->info->command_queue, kernel->kernel, 1,
			NULL, &size, NULL, 0, NULL, NULL);
}
