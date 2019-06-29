/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 17:05:27 by sel-ahma         ###   ########.fr       */
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
		return (display_l1(list, options, path, first));
	else if (options.a)
		return (display_a(list));
	else
		return (classic_display(list));
}
