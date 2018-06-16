/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 21:20:01 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 11:54:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	build_debug(t_cl_core *cl, t_cl_kl *kl)
{
	size_t	log_size;
	char	*log_msg;

	clGetProgramBuildInfo(kl->program, cl->device, CL_PROGRAM_BUILD_LOG, 0,
													NULL, &log_size);
	log_msg = (char *)malloc(log_size);
	clGetProgramBuildInfo(kl->program, cl->device, CL_PROGRAM_BUILD_LOG,
													log_size, log_msg, NULL);
	ft_printf("%s\n", log_msg);
	ft_memdel((void **)&log_msg);
	ft_err_handler("OpenCl", "Can't build program!", 0, 1);
}

void		cl_reinit_mem(t_cl_core *cl, cl_mem *mem, size_t size, void *ptr)
{
	mem ? clReleaseMemObject(*mem) : 0;
	if (!cl || !mem || !size)
		return ;
	if (!ptr)
		!(*mem = clCreateBuffer(cl->context, CL_MEM_READ_WRITE, size, 0, 0))
			? ft_err_handler("OpenCl", "Can't allocate memmory!", 0, 1) : 0;
	else
		!(*mem = clCreateBuffer(cl->context, CL_MEM_COPY_HOST_PTR,
			size, ptr, 0))
			? ft_err_handler("OpenCl", "Can't allocate memmory!", 0, 1) : 0;
}

void		cl_init(t_cl_core *cl, cl_device_type dev_type)
{
	cl_int			err;
	t_uint			n_o_p;
	cl_platform_id	*p_ids;
	int				i;

	err = clGetPlatformIDs(0, NULL, &n_o_p);
	err ? ft_err_handler("OpenCl", "Can't get platform id's!", 0, 1) : 0;
	p_ids = malloc(sizeof(cl_platform_id) * n_o_p);
	err = clGetPlatformIDs(n_o_p, p_ids, NULL);
	err ? ft_err_handler("OpenCl", "Can't get platform id's!", 0, 1) : 0;
	i = -1;
	while (++i < (int)n_o_p)
		if (!(err = clGetDeviceIDs(p_ids[i], dev_type, 1, &cl->device, NULL)))
			break ;
	err ? err = clGetDeviceIDs(p_ids[0], CL_DEVICE_TYPE_DEFAULT,
			1, &cl->device, NULL) : 0;
	free(p_ids);
	err ? ft_err_handler("OpenCl", "Can't get device!", 0, 1) : 0;
	cl->context = clCreateContext(0, 1, &cl->device, NULL, NULL, &err);
	err ? ft_err_handler("OpenCl", "Can't create context!", 0, 1) : 0;
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &err);
	err ? ft_err_handler("OpenCl", "Can't create queue!", 0, 1) : 0;
}

void		cl_parse_kernel(t_cl_core *cl, t_cl_kl *kl,
						const char *kernel_name, const char *func_name)
{
	static cl_program	backup;
	static char			*k_n_saved;
	static char			*obj_content;
	size_t				obj_size;
	cl_int				er;

	if (!k_n_saved || ft_strcmp(k_n_saved, kernel_name))
	{
		if (!(er = open(kernel_name, O_RDONLY))
			|| !(obj_content = malloc(MAX_KERNEL_SIZE)))
			ft_err_handler("OpenCl", "Fail!", 0, 1);
		obj_size = read(er, obj_content, MAX_KERNEL_SIZE);
		backup = clCreateProgramWithSource(cl->context, 1,
				(const char **)&obj_content, (const size_t *)&obj_size, &er);
		ft_memdel((void **)&obj_content);
		kl->program = backup;
		er ? ft_err_handler("OpenCl", "Can't create program!", 0, 1) : 0;
	}
	ft_memdel((void **)&k_n_saved);
	k_n_saved = ft_strdup(kernel_name);
	er = clBuildProgram(backup, 1, &cl->device,
		"-I ./includes -cl-fast-relaxed-math", 0, 0);
	er == CL_BUILD_PROGRAM_FAILURE ? build_debug(cl, kl) : 0;
	kl->kernel = clCreateKernel(backup, func_name, &er);
	er ? ft_err_handler("OpenCl", "Can't create kernel!", 0, 1) : 0;
}
