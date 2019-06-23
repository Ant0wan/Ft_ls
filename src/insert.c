/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/11 19:16:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include "compare.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"

static inline _Bool	insert_beg(t_dlist *restrict new,
		struct s_ins *restrict arg)
{
	new = create_node(NULL, arg->voyager, arg->ret_readdir);
	if (!new)
		return (1);
	else
	{
		arg->voyager->previous = new;
		arg->voyager = arg->voyager->previous;
		arg->beg_list = arg->voyager;
		return (0);
	}
}

static inline _Bool	insert_end(t_dlist *restrict new,
		struct s_ins *restrict arg)
{
	new = create_node(arg->voyager, NULL, arg->ret_readdir);
	if (!new)
		return (1);
	else
	{
		arg->voyager->next = new;
		arg->voyager = arg->voyager->next;
		return (0);
	}
}

static inline _Bool	insert_inbetween(t_dlist *restrict new,
		struct s_ins *restrict arg)
{
	new = create_node(arg->voyager->previous, arg->voyager,
			arg->ret_readdir);
	if (!new)
		return (1);
	else
	{
		arg->voyager->previous->next = new;
		arg->voyager->previous = new;
		arg->voyager = new;
		return (0);
	}
}

static inline void	insert_sort(struct s_ins *restrict arg)
{
	t_dlist		*restrict new;

	new = NULL;
	while (arg->voyager->previous && compare(arg) < 0)
		arg->voyager = arg->voyager->previous;
	while (arg->voyager->next && compare(arg) >= 0)
		arg->voyager = arg->voyager->next;
	if (!arg->voyager->previous && compare(arg) < 0)
	{
		if (insert_beg(new, arg))
			return ;
	}
	else if (!arg->voyager->next && compare(arg) >= 0)
	{
		if (insert_end(new, arg))
			return ;
	}
	else
	{
		if (insert_inbetween(new, arg))
			return ;
	}
}

t_dlist				*insert(t_dlist *restrict beg_list,
		struct dirent *restrict ret_readdir, t_options options,
		struct stat *restrict statbuf)
{
	static struct s_ins	arg;

	arg = (struct s_ins){ret_readdir, statbuf, beg_list, arg.voyager, options};
	if (!arg.beg_list)
	{
		arg.voyager = create_node(NULL, NULL, ret_readdir);
		arg.voyager->statbuf = *statbuf;
		return (arg.voyager);
	}
	else if (!arg.options.a && *arg.ret_readdir->d_name == '.')
		return (arg.beg_list);
	else
	{
		insert_sort(&arg);
		if (!arg.beg_list)
		{
			free_entire_dlist(arg.voyager);
			return (NULL);
		}
		else
		{
			arg.voyager->statbuf = *statbuf;
			while (arg.beg_list->previous != NULL)
				arg.beg_list = arg.beg_list->previous;
			return (arg.beg_list);
		}
	}
}
