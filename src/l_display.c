/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:50:35 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/22 18:50:12 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "dlist.h"
#include "parser.h"
#include "error.h"

unsigned int	ft_nb_len(unsigned int nb);

void			init_cplinfos(t_cplinfos *infos)
{
	infos->total_blocks = 0;
	infos->file_pad = 0;
	infos->usr_pad = 0;
	infos->grp_pad = 0;
	infos->size_pad = 0;
}

void			ft_upd_cplinfos(t_dlist *tmp, t_cplinfos *infos)
{
	unsigned int	len;

	infos->total_blocks += tmp->statbuf.st_blocks;
	if ((len = ft_nb_len(tmp->statbuf.st_nlink)) > infos->file_pad)
		infos->file_pad = len;
	if ((len = ft_strlen(tmp->usr_name)) > infos->usr_pad)
		infos->usr_pad = len;
	if ((len = ft_strlen(tmp->gr_name)) > infos->grp_pad)
		infos->grp_pad = len;
	if ((len = ft_nb_len(tmp->statbuf.st_size)) > infos->size_pad)
		infos->size_pad = len;
}

int			ft_print_date(t_dlist *list)
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

int			ft_print_symlink(t_dlist *list)
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

int			ft_print_maj_min(t_dlist *list, t_cplinfos *infos)
{
	unsigned int minor;
	unsigned int major;

	(void)infos;
	//infos->size_pad += 6;
	minor = 0xFFFF & list->statbuf.st_rdev;
	major = 0xFF & (list->statbuf.st_rdev >> 24);
	if (ft_printf("  %3u,%4u ", major, minor) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (OK);
}

int			print_list_l_option(t_dlist *list, t_cplinfos *infos)
{
	//print_rights_nlink :
	if (ft_printf("%s  %*u ", list->rights, infos->file_pad,
				list->statbuf.st_nlink) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	//	print_gr_usr_name :
	if (ft_printf("%-*s  %-*s  ", infos->usr_pad, list->usr_name,
			   	infos->grp_pad, list->gr_name) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	//print_size or major/minor :
	if (list->rights[0] == 'c' || list->rights[0] == 'b')
	{
		if (ft_print_maj_min(list, infos) == SERIOUS)
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
	//print_date :
	if (ft_print_date(list))
		return (ft_print_date(list)); //error
	//print_name :
	if (ft_printf("%s", list->d_name) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (ft_print_symlink(list));	
}
