/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_display_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:50:35 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/30 15:43:49 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "libft.h"
#include "dlist.h"
#include "parser.h"
#include "error.h"

static inline int	ft_print_str(char *str, t_dlist *list, t_options options)
{
	if (!options.upt)
	{
		if (ft_printf("%.12s ", &str[4]) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	else
	{
		if (ft_printf("%.15s %.4s ", &str[4], &str[20]) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
	}
	return (OK);
}

static inline int	ft_print_access_date(t_dlist *list, t_options options)
{
	char *str;

	if (!(str = ctime(&list->statbuf.st_atime)))
		return (1);
	if (!(ft_file_time(list->statbuf.st_atime)) || options.upt)
	{
		if (ft_print_str(str, list, options))
			return (SERIOUS);
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

static inline int	ft_print_status_date(t_dlist *list, t_options options)
{
	char *str;

	if (!(str = ctime(&list->statbuf.st_ctime)))
		return (1);
	if (!(ft_file_time(list->statbuf.st_ctime)) || options.upt)
	{
		if (ft_print_str(str, list, options))
			return (SERIOUS);
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

extern inline int	ft_print_date(t_dlist *list, t_options options)
{
	char	*str;

	if (options.u)
		return (ft_print_access_date(list, options));
	if (options.c)
		return (ft_print_status_date(list, options));
	if (!(str = ctime(&list->statbuf.st_mtime)))
		return (1);
	if (!(ft_file_time(list->statbuf.st_mtime)) || options.upt)
	{
		if (ft_print_str(str, list, options))
			return (SERIOUS);
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
