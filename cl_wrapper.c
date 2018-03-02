/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 14:37:46 by skamoza           #+#    #+#             */
/*   Updated: 2018/03/02 14:43:50 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_wrap.h"

void	rt_cl_init(t_cl_info *info)
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

cl_mem	rt_cl_malloc_read(t_cl_info *info, size_t size)
{
	return (clCreateBuffer(
			info->context,
			CL_MEM_READ_ONLY,
			size,
			NULL,
			NULL));
}

cl_mem	rt_cl_malloc_write(t_cl_info *info, size_t size)
{
	return (clCreateBuffer(
			info->context,
			CL_MEM_WRITE_ONLY,
			size,
			NULL,
			NULL));
}

cl_int	rt_cl_host_to_device(
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

cl_int	rt_cl_device_to_host(
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

cl_int	rt_cl_compile(t_cl_info *info, char *path)
{
	int		fd;
	char	src[MAX_SOURCE_SIZE];
	size_t	size;
	cl_int	ret;

	if ((fd = open(path, O_RDONLY)) != -1)
	{
		size = read(fd, src, MAX_SOURCE_SIZE);
		info->program = clCreateProgramWithSource(
				info->context,
				1,
				(const char **)&src,
				(const size_t *)&size,
				&ret);
	}
	else
		ret = CL_BUILD_PROGRAM_FAILURE;
	return (ret);
}

void	rt_cl_join(t_cl_info *info)
{
	clFlush(info->command_queue);
	clFinish(info->command_queue);
}

void	rt_cl_free(t_cl_info *info)
{
	clReleaseProgram(info->program);
	clReleaseCommandQueue(info->command_queue);
	clReleaseContext(info->context);
}
