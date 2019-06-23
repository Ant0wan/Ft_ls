/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/17 15:13:42 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compare.h"
#include "parser.h"
#include "libft.h"

static inline int	time_cmp(struct s_ins *restrict arg)
{
	if (arg->voyager->statbuf.st_mtime > arg->statbuf->st_mtime)
		return (1);
	else if (arg->voyager->statbuf.st_mtime < arg->statbuf->st_mtime)
		return (-1);
	else
		return (0);
}

#ifndef __unix__

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

#else

extern inline int	compare(struct s_ins *restrict arg)
{
	size_t	len1;
	size_t	len2;
	int		r;
	int		ret_time_cmp;
	_Bool	low_equal;

	len1 = ft_strlen(arg->ret_readdir->d_name);
	len2 = ft_strlen(arg->voyager->d_name);
	r = arg->options.r ? -1 : 1;
	low_equal = ft_strcasecmp(arg->ret_readdir->d_name,
								arg->voyager->d_name) ? 0 : 1;
	if (arg->options.t && (ret_time_cmp = time_cmp(arg)))
		return (ret_time_cmp * r);
	if (low_equal)
	{
		if (len1 != len2)
			return (len1 > len2 ? r : -r);
		else
			return (-r * ft_strcmp(arg->ret_readdir->d_name,
									arg->voyager->d_name));
	}
	else
		return (ft_strcasecmp(arg->ret_readdir->d_name,
								arg->voyager->d_name) * r);
}

#endif
