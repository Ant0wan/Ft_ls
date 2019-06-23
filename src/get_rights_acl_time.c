/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loption.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ahma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:56:48 by sel-ahma          #+#    #+#             */
/*   Updated: 2019/06/23 15:23:14 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "dlist.h"
#include "error.h"

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

static char		ft_get_acl(char *path, int *i)
{
	ssize_t		xattr;
	acl_t		acl;
	acl_entry_t	tmp;
	char		c;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
		acl_free(acl);
	if ((xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW)) > 0)
	{
		c = '@';
		*i = 1;
	}
	else if (acl != NULL)
	{
		c = '+';
		*i = 1;
	}
	else
		c = !*i ? '\0' : ' ';
	acl_free(acl);
	return (c);
}

void		ft_get_file_rights(t_dlist *tmp, char *path, int *i)
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
	tmp->rights[10] = ft_get_acl(path, i);
	tmp->rights[11] = '\0';
}

int		ft_file_time(time_t date)
{
	long int	current_time;

	current_time = time(0);
	if (date < current_time - 15552000)
		return (1);
	else if (date > current_time)
		return (1);
	else
		return (0);
}
