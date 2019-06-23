/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:05:26 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/17 15:16:46 by abarthel         ###   ########.fr       */
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

#ifdef __unix__

int				feed_readdir_with_each_argument(int argc, char **argv, int i,
		t_options options)
{
	int		ret_value;
	_Bool	no_more_opt;

	ret_value = 0;
	no_more_opt = 0;
	if (i == 0)
		ret_value = store_readdir_output(*argv, ".", options);
	else
	{
		while (i < argc)
		{
			if (((*argv[i] != '-' || !ft_strcmp("-", argv[i]))
				&& no_more_opt == 0) || no_more_opt)
				ret_value = store_readdir_output(*argv, argv[i], options);
			if (!ft_strcmp("--", argv[i]))
				no_more_opt = 1;
			++i;
		}
	}
	return (ret_value);
}

#endif
