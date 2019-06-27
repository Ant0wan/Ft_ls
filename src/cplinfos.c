/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cplinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:35:25 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/27 14:11:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "dlist.h"
#include "libft.h"

void	ft_get_cplinfos(t_dlist *list, t_cplinfos *infos,
			t_options *options, int first)
{
	int i;

	i = 0;
	init_cplinfos(infos);
	while (list)
	{
		if ((*(list->d_name) == '.' && !options->a) && first != 4)
		{
			list = list->next;
			continue ;
		}
		if ((list->rights[0] == 'c' || list->rights[0] == 'b') && !i)
		{
			i = 1;
			infos->size_pad += 10;
		}
		ft_upd_cplinfos(list, infos);
		list = list->next;
	}
}

void	init_cplinfos(t_cplinfos *infos)
{
	infos->total_blocks = 0;
	infos->file_pad = 0;
	infos->usr_pad = 0;
	infos->grp_pad = 0;
	infos->size_pad = 0;
}

void	ft_upd_cplinfos(t_dlist *tmp, t_cplinfos *infos)
{
	unsigned int	len;

	infos->total_blocks += tmp->statbuf.st_blocks;
	if ((len = ft_numlen(tmp->statbuf.st_nlink)) > infos->file_pad)
		infos->file_pad = len;
	if ((len = ft_strlen(tmp->usr_name)) > infos->usr_pad)
		infos->usr_pad = len;
	if ((len = ft_strlen(tmp->gr_name)) > infos->grp_pad)
		infos->grp_pad = len;
	if ((len = ft_numlen(tmp->statbuf.st_size)) > infos->size_pad)
		infos->size_pad = len;
}
