/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/23 15:39:33 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include "display.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "libft.h"

int			display_path(char *path)
{
	if (!path)
		return (print_error(NULL, NULL));
	else
	{
		ft_printf("\n%s:\n", path);
		return (OK);
	}
}

static int	display_a(t_dlist *list)
{
	while (list)
	{
		if (ft_printf("%s\n", list->d_name) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		list = list->next;
	}
	return (OK);
}

static int	display_l(t_dlist *list, t_options *options, char *path, int first)
{
	t_cplinfos	infos;

	if (ft_get_l_infos(list, path) == SERIOUS)
	{
		free_entire_dlist(list);
		return (print_error(NULL, NULL));
	}	
	ft_get_cplinfos(list, &infos, options, first);
	if ((first != 1 && list->rights[0] != 'd')
		   	|| (first ==  1 && list->rights[0] == 'd'))
		if (ft_printf("total %u\n", infos.total_blocks) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	while (list)
	{
		if ((*(list->d_name) == '.' && !options->a) && first != 4)
		{
			list = list->next;
			continue;
		}
		if ((print_list_l_option(list, &infos) < 0))
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		list = list->next;
	}
	return (OK);
}

static int	classic_display(t_dlist *list)
{
	while (list)
	{
		if (*(list->d_name) == '.')
		{
			list = list->next;
			continue;
		}
		else if (ft_printf("%s\n", list->d_name) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		list = list->next;
	}
	return (OK);
}

int			display_list_content(t_dlist *list, t_options options, char *path,
									int first)
{
	if (!list)
		return (print_error(NULL, NULL));
	else if (options.l)
		return (display_l(list, &options, path, first));
	else if (options.a)
		return (display_a(list));
	else
		return (classic_display(list));
}
