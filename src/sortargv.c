/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortargv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:00:09 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/17 22:53:38 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "error.h"
#include "libft.h"

static inline int	compare_arg(char *arg1, char *arg2)
{
	struct stat binbuf;
	struct stat binbuf2;

	binbuf = (struct stat){.st_mode = 0};
	binbuf2 = (struct stat){.st_mode = 0};
	lstat(arg1, &binbuf);
	lstat(arg2, &binbuf2);
	if ((binbuf.st_mode && !(binbuf2.st_mode))
			|| ((binbuf.st_mode & S_IFMT) == S_IFDIR
				&& (binbuf2.st_mode & S_IFMT) != S_IFDIR))
		return (0);
	else if ((!(binbuf.st_mode) && binbuf2.st_mode)
			|| ((binbuf.st_mode & S_IFMT) != S_IFDIR
				&& (binbuf2.st_mode & S_IFMT) == S_IFDIR))
		return (1);
	else
		return (ft_strcmp(arg1, arg2) > 0 ? 0 : 1);
}

static inline void	selection_sort(char **array, int start, int argc)
{
	int		i;
	char	*ptr;

	--start;
	while (++start < argc)
	{
		i = start;
		while (i < argc - 1)
			if (compare_arg(array[++i], array[start]))
			{
				ptr = array[i];
				array[i] = array[start];
				array[start] = ptr;
			}
	}
}

extern inline int	sort_argv(int argc, char **argv, int i)
{
	selection_sort(argv, i, argc);
	return (i);
}
