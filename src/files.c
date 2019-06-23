/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/23 10:14:51 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "display.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "libft.h"

int			file_info(char *prog_name, char *path, t_options options, int first)
{
	static unsigned leaks;
	struct stat	statbuf;
	int			ret_value;
	t_dlist		*var_tmp;

	ret_value = 0;
	if (lstat(path, &statbuf))
		return (print_error(prog_name, path));
	else
	{
		(void)leaks;
		var_tmp = malloc(sizeof(t_dlist));

		*var_tmp = (t_dlist){.statbuf = statbuf, .previous = NULL, .next = NULL,
						.d_name = path, .d_type = 0};
		display_list_content(var_tmp, options, path, first);
	//	ft_printf("ALLO\n");
		ft_strdel(&var_tmp->gr_name);
		ft_strdel(&var_tmp->usr_name);
		free(var_tmp);
	//	free_entire_dlist(var_tmp);
		return (0);
	}
/*	else
	{
		leaks += 20;
		ft_printf("Exit file_info function && leaks should be of %u\n", leaks);
		return (display_list_content(&((t_dlist)
						{.statbuf = statbuf, .previous = NULL, .next = NULL,
						.d_name = path, .d_type = 0}), options, path, first));
	}*/
}
