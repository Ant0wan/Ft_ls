/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/06 17:21:39 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "libft.h"

static inline int	display_l2(t_dlist *list, t_options options,
		t_cplinfos *infos, void **vars)
{
	while (list)
	{
		if ((!ft_strcmp(list->d_name, ".") || !ft_strcmp(list->d_name, ".."))
				&& options.upa && *(int*)vars[0] != 4)
		{
			list = list->next;
			continue;
		}
		if (*(list->d_name) == '.' && !options.a && *(int*)vars[0] != 4)
		{
			list = list->next;
			continue;
		}
		if ((print_list_l_option(list, infos, options) < 0))
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		if (list->rights[10] == '@' && options.at)
			ft_print_acl(list, (char*)vars[1]);
		if ((list->rights[10] == '@' || list->rights[10] == '+') && options.e)
			ft_get_extended_rights(list, (char*)vars[1]);
		list = list->next;
	}
	return (OK);
}

static inline _Bool	check_is_empty(t_dlist *tmp, t_options options)
{
	_Bool	is_empty;

	is_empty = 1;
	while (tmp && options.a
			&& (!ft_strcmp(tmp->d_name, ".") || !ft_strcmp(tmp->d_name, "..")))
		tmp = tmp->next;
	if (!tmp && options.b)
		return (0);
	while (tmp)
	{
		if (tmp && *(tmp->d_name) == '.'
			&& *(tmp->d_name + 1) != '\0' && *(tmp->d_name + 1) != '.')
			break ;
		if (tmp && *tmp->d_name != '.')
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
	void		*vars[2];

	if (ft_get_l_infos(list, path) == SERIOUS)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}
	ft_get_cplinfos(list, &infos, options, first);
	if (((first == 1 && list->rights[0] == 'd') || first != 4)
		&& check_is_empty(list, options))
	{
		if (ft_printf("total %u\n", infos.total_blocks) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	vars[0] = &first;
	vars[1] = path;
	return (display_l2(list, options, &infos, vars));
}
