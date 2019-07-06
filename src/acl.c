/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:20:56 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/07/06 17:18:44 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <stdlib.h>
#include "display.h"
#include "libft.h"
#include "error.h"

static inline void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}

static inline int	ft_print_extended_rights(char *name)
{
	char	**extrights;
	char	**tab;
	int		i;

	if (!(extrights = ft_strsplit(name, '\n')))
		return (SERIOUS);
	i = 1;
	while (extrights[i])
	{
		if (!(tab = ft_strsplit(extrights[i], ':')))
		{
			ft_free_tab(extrights);
			return (SERIOUS);
		}
		ft_printf(" %i: %s:%s %s %s\n",
				i - 1, tab[0], tab[2], tab[4], tab[5]);
		ft_free_tab(tab);
		i++;
	}
	ft_free_tab(extrights);
	return (OK);
}

extern inline int	ft_get_extended_rights(t_dlist *list, char *path)
{
	acl_t	acl;
	char	*name;
	ssize_t	len;
	char	*fullpath;

	if (ft_strcmp(path, list->d_name) == 0)
		fullpath = path;
	else
		fullpath = concat_path(path, list->d_name);
	acl = acl_get_link_np(fullpath, ACL_TYPE_EXTENDED);
	name = acl_to_text(acl, &len);
	if (ft_print_extended_rights(name))
	{
		acl_free(name);
		acl_free(acl);
		fullpath != path ? ft_strdel(&fullpath) : 0;
		return (SERIOUS);
	}
	acl_free(name);
	acl_free(acl);
	fullpath != path ? ft_strdel(&fullpath) : 0;
	return (OK);
}

static inline int	ft_print_acl2(char *buf, ssize_t xattr, char *fullpath,
									t_dlist *list)
{
	char	*name;
	ssize_t	size;

	name = buf;
	while (name < buf + xattr)
	{
		size = getxattr(fullpath, name, 0, 0, 0, XATTR_NOFOLLOW);
		if (ft_printf("\t%s\t %li\n", name, size) < 0)
		{
			free_entire_dlist(list);
			return (print_error(NULL, NULL));
		}
		name += ft_strlen(name) + 1;
	}
	return (OK);
}

extern inline int	ft_print_acl(t_dlist *list, char *path)
{
	char	*buf;
	ssize_t	xattr;
	char	*fullpath;

	if (ft_strcmp(path, list->d_name) == 0)
		fullpath = path;
	else
		fullpath = concat_path(path, list->d_name);
	if ((xattr = listxattr(fullpath, NULL, 0, XATTR_NOFOLLOW)) < 0)
		return (OK);
	if (!(buf = malloc(sizeof(char) * xattr)))
		return (SERIOUS);
	if (listxattr(fullpath, buf, xattr, XATTR_NOFOLLOW) > 0)
	{
		if (ft_print_acl2(buf, xattr, fullpath, list))
			return (SERIOUS);
	}
	ft_strdel(&buf);
	fullpath != path ? ft_strdel(&fullpath) : 0;
	return (OK);
}
