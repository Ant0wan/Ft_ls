/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/06 14:52:29 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "error.h"
#include "parser.h"
#include "libft.h"
#include "dlist.h"

int	display_list_content(t_dlist *list, t_options *options)
{
	(void)options;
	if (!list)
		return (SERIOUS);
	else
	{
		while (list)
		{
			if (ft_printf("%s\n", list->s_dir.d_name) < 0)
			{
				free_entire_dlist(list);
				return (print_error(NULL, NULL));
			}
			list = list->next;
		}
		return (OK);
	}
}
