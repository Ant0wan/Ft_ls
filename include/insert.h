/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:46:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/15 16:46:18 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_H
# define INSERT_H
# include <sys/stat.h>
# include "parser.h"
# include "dlist.h"

t_dlist *insert(t_dlist *restrict list, struct dirent *restrict ret_readdir,
		t_options options, struct stat *restrict statbuf);

#endif
