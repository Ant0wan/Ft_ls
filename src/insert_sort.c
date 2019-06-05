/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort.c                                      :+:      :+:    :+:   */
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

static int	ft_lscmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (ft_tolower((int)s1[i]) == ft_tolower((int)s2[i]) && s1[i] && s2[i])
	{
		++i;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_dlist	*insert_sort(t_dlist *list, struct dirent *ret_readdir, t_options *options)
{
	static t_dlist	*beg_list;
	static t_dlist	*voyager;
	t_dlist		*new;

	if (!list)
	{
		list = create_node(NULL, NULL, ret_readdir);
		ft_printf("FILE:%s\n", ret_readdir->d_name); //DEBUGG
		beg_list = list;
		voyager = list;
	}
	else // What if a malloc fail ?
	{
		(void)options;
		while (voyager->previous && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name) < 0)
		{
			voyager = voyager->previous;
		}
		while (voyager->next && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name) > 0)
		{
			voyager = voyager->next;
		}
		if (!voyager->previous)
		{
			voyager->previous = create_node(NULL, voyager, ret_readdir);
			voyager = voyager->previous;
			beg_list = voyager;
		}
		else
		{
			new = create_node(voyager->previous, voyager, ret_readdir);
			voyager->previous->next = new;
			voyager->previous = new;
		}
	}
	if (beg_list->previous != NULL)
	{
		beg_list = beg_list->previous;
	}
	return (beg_list);
}
