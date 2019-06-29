/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:21:23 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 15:26:56 by abarthel         ###   ########.fr       */
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

t_dlist				*create_dir_list(DIR *ret_opendir, t_options options,
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

static inline int	check_symlink(char *path, t_options options)
{
	struct stat	sb;
	t_dlist		tmp;

	if (!options.l)
		return (1);
	if (lstat(path, &sb))
		return (1);
	if (ft_get_file_type(&sb) == 'l')
	{
		ft_check_symlink(&tmp, path);
		if (tmp.linkname[0] == '\0')
			return (1);
		return (0);
	}
	return (1);
}

static inline _Bool	print_path(int first, char *path)
{
	if (first == 1)
	{
		if (ft_printf("\n%s:\n", path) < 0)
			return (1);
	}
	else if (first == 2)
	{
		if (ft_printf("%s:\n", path) < 0)
			return (1);
	}
	return (0);
}

int				store_readdir_output(char *prog_name, char *path,
		t_options options, int first)
{
	DIR		*ret_opendir;
	t_dlist	*dir_list;
	int		ret_value;

	ret_value = 0;
	if (!(ret_opendir = opendir(path)))
		return (failed_opendir(prog_name, path, options, first));
	if ((path[0] != '.' || path[1] != '\0') && !check_symlink(path, options)
			&& path[ft_strlen(path) - 1] != '/')
		return (!closedir(ret_opendir)
				&& file_info(prog_name, path, options, first));
	else
		dir_list = create_dir_list(ret_opendir, options, path);
	if (print_path(first, path))
		return (return_free(dir_list, print_error(NULL, NULL)));
	ret_value = display_list_content(dir_list, options, path, first);
	if (ret_value == 2)
		return (return_free(dir_list, ret_value));
	if (options.upr)
		ret_value = subdir_select(prog_name, path, options, dir_list);
	free_entire_dlist(dir_list);
	closedir(ret_opendir);
	return (ret_value);
}
