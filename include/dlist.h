/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:55:48 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 14:11:57 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H
# include <sys/stat.h>
# include <dirent.h>
# include "parser.h"

typedef struct	s_cplinfos
{
	unsigned		total_blocks;
	unsigned int	file_pad;
	unsigned int	usr_pad;
	unsigned int	grp_pad;
	unsigned int	size_pad;
}				t_cplinfos;

typedef struct	s_dlist
{
	struct stat		statbuf;
	struct s_dlist	*previous;
	struct s_dlist	*next;
	char			rights[12];
	char			linkname[1024];
	char			*d_name;
	char			*gr_name;
	char			*usr_name;
	unsigned char	d_type;
}				t_dlist;

void			free_entire_dlist(t_dlist *restrict somewhere_in_dlist);
t_dlist			*create_node(t_dlist *restrict previous, t_dlist *restrict next,
		struct dirent *restrict s_dir);

char			*concat_path(char *path, char *name);
int				ft_file_time(time_t date);
void			init_cplinfos(t_cplinfos *infos);
void			ft_upd_cplinfos(t_dlist *tmp, t_cplinfos *infos);
void			init_cplinfos(t_cplinfos *infos);
void			ft_upd_cplinfos(t_dlist *tmp, t_cplinfos *infos);
unsigned int	ft_nb_len(unsigned int nb);
void			ft_get_file_rights(t_dlist *tmp, char *path, int *i);
char			ft_get_file_type(struct stat *stat);
int				ft_get_l_infos(t_dlist *tmp, char *path);
int				ft_check_symlink(t_dlist *tmp, char *path);

int				subdir_select(char *prog_name, char *path, t_options options,
		t_dlist *list);

#endif
