/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:46:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/17 15:19:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_H
# define COMPARE_H
# include <sys/stat.h>
# include <dirent.h>
# include "compare.h"
# include "parser.h"
# include "dlist.h"

struct				s_ins
{
	struct dirent	*ret_readdir;
	struct stat		*statbuf;
	t_dlist			*beg_list;
	t_dlist			*voyager;
	t_options		options;
};

int					compare(struct s_ins *restrict arg);

#endif
