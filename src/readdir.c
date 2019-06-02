/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/31 18:13:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include "dlist.h"
#include "parser.h"


t_dlist	*create_dir_list(DIR *ret_opendir)
{
	struct dirent	*ret_readdir;

	while ((ret_readdir = readdir(ret_opendir)))
	{
		// create a list with what is in the dir
	}
	if (!ret_readdir)
		return (NULL);
	else
		return (ret_readdir);
}

int	store_readdir_output(char *prog_name, char *path, t_options *options)
{
	DIR		*ret_opendir;
	t_dlist		*dir_list;

	ret_opendir = opendir(path);
	if (!ret_opendir)
	{
		print_error(prog_name, path);
		return (ERROR);
	}
	dir_list = create_dir_list(ret_opendir);
	if (!dir_list)
		print_error(); // and free all lists for no leaks
}
