/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loption.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:56:48 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/22 21:29:58 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include "dlist.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

char		ft_get_file_type(struct stat *statbuf)
{
	if ((statbuf->st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((statbuf->st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((statbuf->st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((statbuf->st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((statbuf->st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((statbuf->st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((statbuf->st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('-');
}

char		ft_get_acl(char *path)
{
	ssize_t		xattr;
	acl_t		acl;
	acl_entry_t	tmp;
	char		c;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
		acl_free(acl);
	if ((xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		c = '@';
	else if (acl != NULL)
		c = '+';
	else
		c = '\0';
	acl_free(acl);
	return (c);
}

//static void	ft_get_file_rights(struct stat *sb, char str[12])
static void	ft_get_file_rights(t_dlist *tmp, char *path)
{
	tmp->rights[0] = ft_get_file_type(&tmp->statbuf);
	tmp->rights[1] = tmp->statbuf.st_mode & S_IRUSR ? 'r' : '-';
	tmp->rights[2] = tmp->statbuf.st_mode & S_IWUSR ? 'w' : '-';
	tmp->rights[3] = tmp->statbuf.st_mode & S_IXUSR ? 'x' : '-';
	tmp->rights[4] = tmp->statbuf.st_mode & S_IRGRP ? 'r' : '-';
	tmp->rights[5] = tmp->statbuf.st_mode & S_IWGRP ? 'w' : '-';
	tmp->rights[6] = tmp->statbuf.st_mode & S_IXGRP ? 'x' : '-';
	tmp->rights[7] = tmp->statbuf.st_mode & S_IROTH ? 'r' : '-';
	tmp->rights[8] = tmp->statbuf.st_mode & S_IWOTH ? 'w' : '-';
	tmp->rights[9] = tmp->statbuf.st_mode & S_IXOTH ? 'x' : '-';
	if (tmp->statbuf.st_mode & S_ISUID)
		tmp->rights[4] = (tmp->statbuf.st_mode & S_IXUSR) ? 's' : 'S';
	if (tmp->statbuf.st_mode & S_ISGID)
		tmp->rights[7] = (tmp->statbuf.st_mode & S_IXGRP) ? 's' : 'S';
	if (tmp->statbuf.st_mode & S_ISVTX)
		tmp->rights[9] = tmp->rights[9] == '-' ? 'T' : 't';
	tmp->rights[10] = ft_get_acl(path);
	tmp->rights[11] = '\0';
}

int		ft_file_time(time_t date)
{
	long int	current_time;

	current_time = time(0);
	if (date < current_time - 15552000) // file modified more than 6 monthes ago
		return (1);
	else if (date > current_time) // file modified in the future
		return (1);
	else
		return (0);
}

int		ft_check_symlink(t_dlist *tmp, char *path)
{
	ssize_t	read_link;

	if ((read_link = readlink(path, tmp->linkname, 1024)) == -1)
	{
		perror("lstat");
		return (MINOR);
	}
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

int			ft_get_l_infos(t_dlist *tmp, char *pathtmp)
{
	char	*path;

//	ft_printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while (tmp)
	{
//		ft_printf("pathtmp = %s\n", pathtmp);
		if (!ft_strstr(tmp->d_name, pathtmp))
			path = concat_path(pathtmp, tmp->d_name);
		else
			path = pathtmp;
//		ft_printf("path = %s\n", path);
		//lstat(path, &tmp->statbuf);
		ft_get_file_rights(tmp, path);
		if (ft_get_gr_usr_name(tmp) == SERIOUS)
			return (SERIOUS);
		if (tmp->rights[0] == 'l')
			if (ft_check_symlink(tmp, path))
				return (SERIOUS);
		tmp = tmp->next;
		if (path != pathtmp)
			ft_strdel(&path);
	}
//	ft_printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	return (OK);
}
