/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/30 12:49:36 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare.h"
#include "parser.h"
#include "libft.h"

static inline int	time_cmp(struct s_ins *restrict arg)
{
	if (arg->options.u)
	{
		if (arg->voyager->statbuf.st_atime > arg->statbuf->st_atime)
			return (1);
		else if (arg->voyager->statbuf.st_atime < arg->statbuf->st_atime)
			return (-1);
		else
			return (0);
	}
	else if (arg->options.c)
	{
		if (arg->voyager->statbuf.st_ctime > arg->statbuf->st_ctime)
			return (1);
		else if (arg->voyager->statbuf.st_ctime < arg->statbuf->st_ctime)
			return (-1);
		else
			return (0);
	}
	if (arg->voyager->statbuf.st_mtime > arg->statbuf->st_mtime)
		return (1);
	else if (arg->voyager->statbuf.st_mtime < arg->statbuf->st_mtime)
		return (-1);
	else
		return (0);
}

extern inline int	compare(struct s_ins *restrict arg)
{
	int	ret_time_cmp;
	int	r;

	if (arg->options.t && (ret_time_cmp = time_cmp(arg)))
	{
		r = arg->options.r ? -1 : 1;
		return (ret_time_cmp * r);
	}
	if (arg->options.r)
		return (ft_strcmp(arg->voyager->d_name, arg->ret_readdir->d_name));
	else
		return (ft_strcmp(arg->ret_readdir->d_name, arg->voyager->d_name));
}
