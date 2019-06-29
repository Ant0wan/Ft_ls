/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 17:05:24 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "libft.h"

static inline int	display_l2(t_dlist *list, t_options options,
								t_cplinfos *infos, int first)
{
	while (list)
	{
		if ((*(list->d_name) == '.' && !options.a) && first != 4)
		{
			list = list->next;
			continue;
		}
		if ((print_list_l_option(list, infos, options) < 0))
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		list = list->next;
	}
	return (OK);
}

static inline _Bool	check_is_empty(t_dlist *tmp, _Bool a)
{
	_Bool	is_empty;

	is_empty = 1;
	while (tmp && !a)
	{
		if (*tmp->d_name != '.')
			break ;
		tmp = tmp->next;
		if (!tmp)
			is_empty = 0;
	}
	return (is_empty);
}

int					display_l1(t_dlist *list, t_options options,
								char *path, int first)
{
	t_cplinfos	infos;

	if (ft_get_l_infos(list, path) == SERIOUS)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	ft_get_cplinfos(list, &infos, options, first);
	if (((first == 1 && list->rights[0] == 'd') || first != 4)
			&& check_is_empty(list, options.a))
	{
		if (ft_printf("total %u\n", infos.total_blocks) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	return (display_l2(list, options, &infos, first));
}
