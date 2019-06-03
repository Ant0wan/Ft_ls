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
#include "error.h"
#include "dlist.h"
#include "parser.h"
#include "libft.h"

t_dlist	*create_dir_list(DIR *ret_opendir, t_options *options)
{
	struct dirent	*ret_readdir;
	t_dlist		*next;
	t_dlist		*previous;
	t_dlist		*beg_list;
	t_dlist		*end_list; // for the case -r

	next = NULL;
	previous = NULL;
	beg_list = NULL;
	//beg_list = end_list;
	(void)options;
	while ((ret_readdir = readdir(ret_opendir)))
	{
		// introduire ici le ascii sort en fonction de ret_readdir->d_name
		end_list = create_node(previous, next, ret_readdir);
		ft_printf("%s\n", end_list->s_dir->d_name); // debugging
		// create a list with what is in the dir
	}
	if (!ret_readdir)
		return (NULL);
//	else if (options->r) // sort done within sort function so no need to give other pointer
//		return (end_list);
	else
		return (beg_list);
}

int	store_readdir_output(char *prog_name, char *path, t_options *options)
{
	DIR		*ret_opendir;
	t_dlist		*dir_list;
	int		ret_value;

	ret_value = 0;
	ret_opendir = opendir(path);
	if (!ret_opendir)
	{
		print_error(prog_name, path);
		return (SERIOUS);
	}
	dir_list = create_dir_list(ret_opendir, options);
	if (!dir_list)
		print_error(prog_name, path); // and free all lists for no leaks
	return (ret_value);
}

int	feed_readdir_with_each_argument(int argc, char **argv, int i, t_options *options)
{
	int	ret_value;

	ret_value = 0;
	if (i == 0)
		ret_value = store_readdir_output(*argv, ".", options);
	else
	{
		while (i < argc)
		{
			ret_value = store_readdir_output(*argv, argv[i], options);
			++i;
		}
	}
	return (ret_value);
}
