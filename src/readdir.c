/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 20:18:04 by abarthel         ###   ########.fr       */
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

char	*concat_path(char *path, char *d_name)
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
	full_path = ft_strendcpy(full_path, "/");
	full_path = ft_strendcpy(full_path, d_name);
	return (beg_path);
}

int		subdir_select(char *prog_name, char *path, t_options options,
		t_dlist *list)
{
	char		*full_path;
	int			ret_value;

	ret_value = 0;
	while (list)
	{
		while (list && ((list->d_type != DT_DIR && list->d_type != DT_UNKNOWN)
					|| !ft_strcmp(".", list->d_name)
					|| !ft_strcmp("..", list->d_name)))
			list = list->next;
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

int		feed_readdir_with_each_argument(int argc, char **argv, int i,
		t_options options)
{
	int		ret_value;
	int		ival_after_opt;

	ret_value = 0;
	ival_after_opt = i;
	if (i == 0)
		ret_value = store_readdir_output(*argv, ".", options, 0);
	else
	{
		while (i < argc)
		{
			if (i == ival_after_opt && argc == ival_after_opt + 1)
				ret_value = store_readdir_output(*argv, argv[i], options, 0);
			else if (i == ival_after_opt || ret_value == 2)
				ret_value = store_readdir_output(*argv, argv[i], options, 2);
			else
				ret_value = store_readdir_output(*argv, argv[i], options, 1);
			++i;
		}
	}
	return (ret_value);
}
