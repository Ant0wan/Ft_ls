/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:46:15 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/29 22:28:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include "parser.h"
# include "dlist.h"

int		display_path(char *path);
int		display_list_content(t_dlist *list, t_options options,
		char *path, int f);
int		print_list_l_option(t_dlist *list, t_cplinfos *infos,
		t_options options);
void	ft_get_cplinfos(t_dlist *list, t_cplinfos *infos,
		t_options options, int first);
int		display_l1(t_dlist *list, t_options options, char *path,
		int first);
int		ft_print_date(t_dlist *list, t_options options);
int		ft_print_access_date(t_dlist *list);
int		print_list_l_option2(t_dlist *list, t_cplinfos *infos);
int		ft_print_access_date(t_dlist *list);
int		ft_print_date(t_dlist *list, t_options options);
int		ft_print_symlink(t_dlist *list);
int		ft_print_maj_min(t_dlist *list);

#endif
