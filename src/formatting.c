/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:45:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/24 18:46:56 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>

#include "libft.h"

#define NOSUCHFILE "ls: %s: No such file or directory\n"

_Bool	get_what_is_in_the_dir(char *av)
{
	DIR				*ret_opendir;
	struct dirent	*ret_readdir;

	(void)av;
	if ((ret_opendir = opendir(av)) == NULL) // attention il faut tester si ce n'est pas un fichier cr dans ce cas il ny a pas de essage derreur a afficher
	{
		ft_printf(NOSUCHFILE, av);
		return (EXIT_SUCCESS);
	}
	while ((ret_readdir = readdir(ret_opendir)) != NULL)
		ft_printf("%s\n", ret_readdir->d_name);
	return (EXIT_SUCCESS);
}

_Bool	output_ls_of_each_argument(int argc, char **argv, int i)
{
	while (i < argc)
	{
		if (get_what_is_in_the_dir(argv[i]))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
