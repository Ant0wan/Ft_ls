/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:50:35 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/18 11:02:57 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "dlist.h"
#include "parser.h"
#include "error.h"

unsigned int	ft_nb_len(unsigned int nb);

static void	init_cplinfos(t_cplinfos *ptr)
{
	ptr->total_blocks = 0;
	ptr->file_pad = 0;
	ptr->usr_pad = 0;
	ptr->grp_pad = 0;
	ptr->size_pad = 0;
}

static void	ft_get_cpl_infos(t_dlist *list, t_cplinfos *ptr)
{
	t_dlist			*tmp;
	unsigned int	len;

	init_cplinfos(ptr);
	tmp = list;	
	while (tmp)
	{
		ptr->total_blocks += tmp->l_infos.nb_blocks;
		if ((len = ft_nb_len(tmp->l_infos.nlink)) > ptr->file_pad)
			ptr->file_pad = len;
		if ((len = ft_strlen(tmp->l_infos.usr_name)) > ptr->usr_pad)
			ptr->usr_pad = len;
		if ((len = ft_strlen(tmp->l_infos.gr_name)) > ptr->grp_pad)
			ptr->grp_pad = len;
		if ((len = ft_nb_len(tmp->l_infos.st_size)) > ptr->size_pad)
			ptr->size_pad = len;
		tmp = tmp->next;
	}
}

static void	free_strings(t_dlist *tmp, char i)
{
		if (i == 0 || i == 2)
		{
			ft_strdel(&tmp->l_infos.usr_name);
			ft_strdel(&tmp->l_infos.gr_name);
			ft_strdel(&tmp->l_infos.file_modif);
		}
		if (i == 1 || i == 2)
			ft_strdel(&tmp->l_infos.linkname);
}

int			print_list_l_option(t_dlist *list, t_options *options)
{
	t_cplinfos	ptr;
	t_dlist		*tmp;

	(void)options;
	ft_get_cpl_infos(list, &ptr);
	tmp = list;
	if (ft_printf("total %li\n", ptr.total_blocks) < 0)
	{
		free_strings(tmp, 2);
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	while (tmp)
	{
		if (ft_printf("%c%s  %*u %*s  %*s  %*u %.12s %s",
			tmp->l_infos.file_type, tmp->l_infos.rights, ptr.file_pad,
			tmp->l_infos.nlink, ptr.usr_pad, tmp->l_infos.usr_name,
		   	ptr.grp_pad, tmp->l_infos.gr_name, ptr.size_pad,
			tmp->l_infos.st_size, &tmp->l_infos.file_modif[4],
		   	tmp->d_name) < 0)
		{
			free_strings(tmp, 2);	
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		free_strings(tmp, 0);
		if (tmp->l_infos.linkname)
		{
			if (ft_printf(" -> %s\n", tmp->l_infos.linkname) < 0)
			{
				free_strings(tmp, 1);
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
		ft_strdel(&tmp->l_infos.linkname);
		tmp = tmp->next;
	}
	return (OK);
}
