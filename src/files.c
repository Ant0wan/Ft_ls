/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/25 11:41:22 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "dlist.h"
#include "display.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "libft.h"

void	ft_init_var(t_dlist *var, struct stat *statbuf, int *first,
						char *path)
{
	var->statbuf = *statbuf;
	var->previous = NULL;
	var->next = NULL;
	var->rights[0] = '\0';
	var->linkname[0] = '\0';
	var->d_name = path;
	var->gr_name = NULL;
	var->usr_name = NULL;
	if (ft_get_file_type(statbuf) != 'd')
		*first = 4;
}

int		file_info(char *prog_name, char *path, t_options options, int first)
{
	struct stat		statbuf;
	int				ret_value;
	t_dlist			var_tmp;

	ret_value = 0;
	if (lstat(path, &statbuf))
		return (print_error(prog_name, path));
	else
	{
		ft_init_var(&var_tmp, &statbuf, &first, path);
//		ft_printf("IN FILE INFO path = %s | first = %i\n", path, first);
		display_list_content(&var_tmp, options, path, first);
		ft_strdel(&var_tmp.gr_name);
		ft_strdel(&var_tmp.usr_name);
		return (0);
	}
}
