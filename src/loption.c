/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loption.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:56:48 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/23 15:25:19 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include "dlist.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

int		ft_check_symlink(t_dlist *tmp, char *path)
{
	ssize_t	read_link;

	if ((read_link = readlink(path, tmp->linkname, 1024)) == -1)
		return (MINOR);
	tmp->linkname[read_link] = '\0';
	return (OK);
}

int		ft_get_gr_usr_name(t_dlist *tmp)
{
	struct passwd	*pwd;
	struct group	*grp;

	if ((pwd = getpwuid(tmp->statbuf.st_uid)) && pwd->pw_name)
	{
		if (!(tmp->usr_name = ft_strdup(pwd->pw_name)))
			return (SERIOUS);
	}
	else if (!(tmp->usr_name = ft_itoa(tmp->statbuf.st_uid)))
		return (SERIOUS);
	if ((grp = getgrgid(tmp->statbuf.st_gid)) && grp->gr_name)
	{
		if (!(tmp->gr_name = ft_strdup(grp->gr_name)))
			return (SERIOUS);
	}
	else if (!(tmp->gr_name = ft_itoa(tmp->statbuf.st_gid)))
		return (SERIOUS);
	return (OK);
}

int		ft_get_l_infos(t_dlist *tmp, char *pathtmp)
{
	char	*path;
	int		i;

	i = 0;
	while (tmp)
	{
		if (!ft_strstr(tmp->d_name, pathtmp))
			path = concat_path(pathtmp, tmp->d_name);
		else
			path = pathtmp;
		ft_get_file_rights(tmp, path, &i);
		if (ft_get_gr_usr_name(tmp) == SERIOUS)
			return (SERIOUS);
		if (tmp->rights[0] == 'l')
			if (ft_check_symlink(tmp, path))
				return (SERIOUS);
		tmp = tmp->next;
		if (path != pathtmp)
			ft_strdel(&path);
	}
	return (OK);
}
