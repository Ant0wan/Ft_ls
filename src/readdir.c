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
#include "insert_sort.h"

static t_dlist	*create_dir_list(DIR *ret_opendir, t_options *options)
{
	struct dirent	*ret_readdir;
	t_dlist		*list;

	list = NULL;
	while ((ret_readdir = readdir(ret_opendir)))
		list = insert_sort(list, ret_readdir, options);
	return (list);
}

static int	subdir_select(char *prog_name, char *path, t_options *options, t_dlist *list)
{
	int	ret_value;
	char	*full_path;

	ret_value = 0;
	while (list)
	{
		if (list->s_dir->d_type != DT_DIR || ft_strcmp(".", list->s_dir->d_name) || ft_strcmp("..", list->s_dir->d_name))
			list = list->next;
//		ret_value = 
		(void)prog_name;
		(void)path;
		(void)options;
		(void)full_path;
	}
	return (ret_value);
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
			return (print_error(prog_name, path));
	}
	dir_list = create_dir_list(ret_opendir, options);
	ret_value = display_list_content(dir_list, options);
	if (options->upr)
		ret_value = subdir_select(prog_name, path, options, dir_list);
	return (ret_value);
}

int	feed_readdir_with_each_argument(int argc, char **argv, int i, t_options *options)
{
	int	ret_value;

	ret_value = 0;
	if (i == 0)
		ret_value = store_readdir_output(*argv, ".", options);
	else
		while (i < argc)
		{
			ret_value = store_readdir_output(*argv, argv[i], options);
			++i;
		}
	return (ret_value);
}
