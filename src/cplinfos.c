/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cplinfos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:35:25 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/23 15:36:37 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "dlist.h"

void	ft_get_cplinfos(t_dlist *list, t_cplinfos *infos,
						t_options *options, int first)
{
	int i = 0;

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
