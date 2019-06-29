/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:24:30 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 15:33:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "dlist.h"
#include "error.h"
#include "files.h"
#include "readdir.h"

extern inline int	return_free(t_dlist *list, int ret_value)
{
	free_entire_dlist(list);
	return (ret_value);
}

extern inline int	failed_opendir(char *prog_name, char *path,
		t_options options, int first)
{
	if (errno == ENOTDIR)
		return (file_info(prog_name, path, options, first));
	return (print_error(prog_name, path));
}
