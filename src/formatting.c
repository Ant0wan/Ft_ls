/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:45:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/25 11:05:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "formatting.h"
#include "libft.h"
#include "parser.h"
#include "dlist.h"
#define NOSUCHFILE "ls: %s: No such file or directory\n"

void	select_output_format(t_dlist *node, t_options *options)
{
	if (options->l == 0)
		ft_printf("%s\n", node->s_dir->d_name);
	else
		ft_printf("r-d-r-d type:%d, %s\n", node->s_dir->d_type,
				node->s_dir->d_name);
}

_Bool	output_ls_of_each_argument(int argc, char **argv, int i,
		t_options *options)
{
	while (i < argc)
	{
		if (get_what_is_in_the_dir(argv[i], options))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	printf_list_element(t_dlist *ptr_list_beg, t_dlist *ptr_list_end,
		t_options *options)
{
	if (options->r == 1)
	{
		while (ptr_list_end->s_dir)
		{
			select_output_format(ptr_list_end, options);
			ptr_list_end = ptr_list_end->previous;
			if (!ptr_list_end)
				break ;
		}
	}
	else
	{
		while (ptr_list_beg->s_dir)
		{
			select_output_format(ptr_list_beg, options);
			ptr_list_beg = ptr_list_beg->next;
			if (!ptr_list_beg)
				break ;
		}
	}
}

_Bool	get_what_is_in_the_dir(char *av, t_options *options)
{
	DIR				*ret_opendir;
	struct dirent	*ret_readdir;
	t_dlist			*ptr_list_end;
	t_dlist			*ptr_list_beg;

	if ((ret_opendir = opendir(av)) == NULL) // attention il faut tester
		//si ce n'est pas un fichier cr dans ce cas il ny a pas de essage derreur a afficher
	{
		ft_printf(NOSUCHFILE, av);
		return (EXIT_SUCCESS);
	}
	ptr_list_end = create_node(NULL, NULL, NULL);
	ptr_list_beg = ptr_list_end;
	while ((ret_readdir = readdir(ret_opendir)) != NULL)
	{
		if (options->a == 0 && *(ret_readdir->d_name) == '.')
			continue ;
		if (!(ptr_list_end->s_dir))
			ptr_list_end->s_dir = ret_readdir;
		else
		{
			ptr_list_end->next = create_node(ptr_list_end, NULL, ret_readdir);
			ptr_list_end = ptr_list_end->next;
		}
	}
	printf_list_element(ptr_list_beg, ptr_list_end, options);
	(void)closedir(ret_opendir);
	free_entire_dlist(ptr_list_end);
	return (EXIT_SUCCESS);
}
