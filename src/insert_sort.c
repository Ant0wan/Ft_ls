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

static int	ft_lscmp(const char *s1, const char *s2, t_options *options)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	a = ft_tolower((int)s1[i]);
	b = ft_tolower((int)s2[i]);
	while (a == b && s1[i] && s2[i])
	{
		++i;
		a = ft_tolower((int)s1[i]);
		b = ft_tolower((int)s2[i]);
	}
	if (options->r)
		return ((unsigned char)b - (unsigned char)a);
	else
		return ((unsigned char)a - (unsigned char)b);
}

t_dlist	*insert_sort(t_dlist *list, struct dirent *ret_readdir, t_options *options)
{
	static t_dlist	*beg_list;
	static t_dlist	*voyager;
	t_dlist		*new;

	if (!list)
	{
		list = create_node(NULL, NULL, ret_readdir);
		beg_list = list;
		voyager = list;
	}
	else // What if a malloc fail ?
	{
		while (voyager->previous && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name, options) < 0)
			voyager = voyager->previous;
		while (voyager->next && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name, options) > 0)
			voyager = voyager->next;
		if (!voyager->previous && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name, options) <= 0)
		{
			voyager->previous = create_node(NULL, voyager, ret_readdir);
			voyager = voyager->previous;
			beg_list = voyager;
		}
		else if (!voyager->next && ft_lscmp(ret_readdir->d_name, voyager->s_dir->d_name, options) >= 0)
		{
			voyager->next = create_node(voyager, NULL, ret_readdir);
			voyager = voyager->next;
		}
		else
		{
			new = create_node(voyager->previous, voyager, ret_readdir);
			voyager->previous->next = new;
			voyager->previous = new;
			voyager = new;
		}
	}
	while (beg_list->previous != NULL)
		beg_list = beg_list->previous;
	return (beg_list);
}
