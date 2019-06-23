/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/23 15:26:42 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include "display.h"
#include "readdir.h"
#include "insert.h"
#include "parser.h"
#include "dlist.h"
#include "error.h"
#include "files.h"
#include "libft.h"

static t_dlist	*create_dir_list(DIR *ret_opendir, t_options options,
		char *path)
{
	struct stat		statbuf;
	struct dirent	*ret_readdir;
	t_dlist			*beg_list;
	char			*pathname;

	beg_list = NULL;
	if (options.t || options.l)
	{
		while ((ret_readdir = readdir(ret_opendir)))
		{
			pathname = concat_path(path, ret_readdir->d_name);
			if (lstat(pathname, &statbuf))
			{
				ft_memdel((void**)&pathname);
				return (NULL);
			}
			beg_list = insert(beg_list, ret_readdir, options, &statbuf);
			ft_memdel((void**)&pathname);
			if (!beg_list)
				return (NULL);
		}
	}
	else
	{
		while ((ret_readdir = readdir(ret_opendir)))
		{
			beg_list = insert(beg_list, ret_readdir, options, &statbuf);
			if (!beg_list)
				return (NULL);
		}
	}
	return (beg_list);
}

char			*concat_path(char *path, char *d_name)
{
	char	*full_path;
	char	*beg_path;

	if (path && d_name)
	{
		full_path = (char*)malloc(sizeof(*full_path) * (ft_strlen(path) + 1
					+ ft_strlen(d_name)) + 1);
		if (!full_path)
			return (NULL);
	}
	else
		return (NULL);
	beg_path = full_path;
	full_path = ft_strendcpy(full_path, path);
	if (full_path[-1] != '/')
		full_path = ft_strendcpy(full_path, "/");
	full_path = ft_strendcpy(full_path, d_name);
	return (beg_path);
}

static int		subdir_select(char *prog_name, char *path, t_options options,
		t_dlist *list)
{
	char		*full_path;
	int			ret_value;
	struct stat test;
	char		*tmp;

	ret_value = 0;
	while (list)
	{
		lstat((tmp = ft_strjoin(path, list->d_name)), &test);
		while (list && ((list->d_type != DT_DIR && ((test.st_mode & S_IFMT) == S_IFDIR))
					|| !ft_strcmp(".", list->d_name)
					|| !ft_strcmp("..", list->d_name)))
			list = list->next;
		ft_strdel(&tmp);
		if (list)
		{
			full_path = concat_path(path, list->d_name);
			if (display_path(full_path))
				return (SERIOUS);
			ret_value = store_readdir_output(prog_name, full_path, options, 0)
				? 1 : ret_value;
			ft_memdel((void**)&full_path);
			list = list->next;
		}
	}
	return (ret_value);
}

int				store_readdir_output(char *prog_name, char *path,
		t_options options, int first)
{
	DIR		*ret_opendir;
	t_dlist	*dir_list;
	int		ret_value;

	ret_value = 0;
	ret_opendir = opendir(path);
	if (!ret_opendir)
	{
		if (errno == ENOTDIR)
		{
		//	ft_printf("exit store readir because !ret_opendir && errno = ENOTDIR\n");
			return (file_info(prog_name, path, options, first));
		}
		else
			return (print_error(prog_name, path));
	}
	dir_list = create_dir_list(ret_opendir, options, path);
	if (first == 1)
		ft_printf("\n%s:\n", path);
	else if (first == 2)
		ft_printf("%s:\n", path);
	ret_value = display_list_content(dir_list, options, path, first);
	if (ret_value == 2)
	{
	//	ft_printf("exit store readir with ret_value = 2\n");
		free_entire_dlist(dir_list);
		return (ret_value);
	}
	if (options.upr)
		ret_value = subdir_select(prog_name, path, options, dir_list);
	free_entire_dlist(dir_list);
	closedir(ret_opendir);
	//ft_printf("exit store readir with ret_value = 0\n");
	return (ret_value);
}

#ifndef __unix__

int				feed_readdir_with_each_argument(int argc, char **argv, int i,
		t_options options)
{
	int		ret_value;

	ret_value = 0;
	if (i == 0)
		ret_value = store_readdir_output(*argv, ".", options, 0);
	else
	{
		while (i < argc)
		{
			if (i == 1 && argc == 2)
				ret_value = store_readdir_output(*argv, argv[i], options, 0);
			else if (i == 1)
				ret_value = store_readdir_output(*argv, argv[i], options, 2);
			else
				ret_value = store_readdir_output(*argv, argv[i], options, 1);
			++i;
		}
	}
	return (ret_value);
}

#endif
