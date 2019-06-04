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
#include "error.h"
#include "dlist.h"
#include "parser.h"
#include "libft.h"
#include "files.h"
#include "display.h"

static t_dlist	*insert_sort(t_dlist *list, struct dirent *ret_readdir, t_options *options)
{
	static t_dlist	*beg_list;
	static t_dlist	*voyager;

	if (!list)
	{
		list = create_node(NULL, NULL, ret_readdir);
		beg_list = list;
		voyager = list;
	}
	else
	{
		(void)options;
		// FAUX ici car concevoir le tri a l'insertion
		voyager->next = create_node(list, NULL, ret_readdir);
		voyager = voyager->next;
	}
	return (beg_list);
}

static t_dlist	*create_dir_list(DIR *ret_opendir, t_options *options)
{
	struct dirent	*ret_readdir;
	t_dlist		*list;

	list = NULL;
	while ((ret_readdir = readdir(ret_opendir)))
	{
		list = insert_sort(list, ret_readdir, options);
	}
	if (!list)
		return (NULL);
	else
		return (list);
}

static int	store_readdir_output(char *prog_name, char *path, t_options *options)
{
	DIR		*ret_opendir;
	t_dlist		*dir_list;
	int		ret_value;

	ret_value = 0;
	ret_opendir = opendir(path);
	if (!ret_opendir)
	{
		if (errno == ENOTDIR)
			return (file_info(prog_name, path, options));
		else
		{
			print_error(prog_name, path);
			return (SERIOUS);
			//return (MINOR);
		}
	}
	dir_list = create_dir_list(ret_opendir, options);
	display_list_content(dir_list, options);
//	if (!dir_list) la recurssion se fera par ici avec un dir_list null pour signaler un dossier vide
//		print_error(prog_name, path); // and free all lists for no leaks
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
