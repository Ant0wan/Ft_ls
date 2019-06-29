/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:50:35 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/29 11:09:57 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "dlist.h"
#include "parser.h"
#include "error.h"

static inline int	ft_print_date(t_dlist *list)
{
	char	*str;

	if (!(str = ctime(&list->statbuf.st_mtime)))
		return (1);
	if (!(ft_file_time(list->statbuf.st_mtime)))
	{
		if (ft_printf("%.12s ", &str[4]) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	else
	{
		if (ft_printf("%.7s%5.4s ", &str[4], &str[20]) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	return (OK);
}

static inline int	ft_print_symlink(t_dlist *list)
{
	if (list->linkname[0])
	{
		if (ft_printf(" -> %s\n", list->linkname) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	else
	{
		if (ft_printf("\n") < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	return (OK);
}

static inline int	ft_print_maj_min(t_dlist *list)
{
	unsigned int minor;
	unsigned int major;

	minor = 0xFFFF & list->statbuf.st_rdev;
	major = 0xFF & (list->statbuf.st_rdev >> 24);
	if (ft_printf("%3u,%4u ", major, minor) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (OK);
}

static inline int	print_list_l_option2(t_dlist *list, t_cplinfos *infos)
{
	if (ft_printf("%-11s %*u %-*s  %-*s  ", list->rights, infos->file_pad,
				list->statbuf.st_nlink, infos->usr_pad, list->usr_name,
				infos->grp_pad, list->gr_name) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (OK);
}

int					print_list_l_option(t_dlist *list, t_cplinfos *infos)
{
	if (print_list_l_option2(list, infos) != OK)
		return (SERIOUS);
	if (list->rights[0] == 'c' || list->rights[0] == 'b')
	{
		if (ft_print_maj_min(list) == SERIOUS)
			return (SERIOUS);
	}
	else
	{
		if (ft_printf("%*lld ", infos->size_pad, list->statbuf.st_size) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	if (ft_print_date(list))
		return (ft_print_date(list));
	if (ft_printf("%s", list->d_name) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (ft_print_symlink(list));
}
