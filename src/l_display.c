/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_display.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:50:35 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/29 22:26:19 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "dlist.h"
#include "parser.h"
#include "error.h"
#include "display.h"

int	print_list_l_option(t_dlist *list, t_cplinfos *infos, t_options options)
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
	if (ft_print_date(list, options))
		return (ft_print_date(list, options));
	if (ft_printf("%s", list->d_name) < 0)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	return (ft_print_symlink(list));
}
