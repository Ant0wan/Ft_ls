/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:45:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/24 18:25:12 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>

#include "libft.h"


_Bool	get_what_is_in_the_dir(char *av)
{
	DIR				*ret_opendir;
	struct dirent	*ret_readdir;

	(void)av;
	if ((ret_opendir = opendir(av)) == NULL)
		return (EXIT_FAILURE);
	while ((ret_readdir = readdir(ret_opendir)) != NULL)
		ft_printf("%s\n", ret_readdir->d_name);
	return (EXIT_SUCCESS);
}

void	output_ls_of_each_argument(int argc, char **argv, int i)
{
	while (i < argc)
	{
		if (get_what_is_in_the_dir(argv[i]))
			return ;
		++i;
	}
}
