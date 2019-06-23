/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:55:09 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/22 21:32:15 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "dlist.h"

static inline t_dlist	*malloc_a_node(void)
{
	t_dlist	*new;

	if ((new = (t_dlist*)malloc(sizeof(t_dlist))))
		return (new);
	else
		return (NULL);
}

t_dlist					*create_node(t_dlist *restrict previous,
		t_dlist *restrict next, struct dirent *restrict s_dir)
{
	t_dlist	*new;

	if ((new = malloc_a_node()))
	{
		new->next = next;
		new->previous = previous;
		new->d_name = ft_strdup(s_dir->d_name);
	//	new->linkname =  NULL;
		new->linkname[0] = '\0';
		new->gr_name = NULL;
		new->usr_name = NULL;
		if (!new->d_name)
		{
			free_entire_dlist(previous);
			return (NULL);
		}
		new->d_type = s_dir->d_type;
		return (new);
	}
	else
	{
		free_entire_dlist(previous);
		return (NULL);
	}
}

void					free_entire_dlist(t_dlist *restrict somewhere_in_dlist)
{
	t_dlist	*tmp;

	tmp = NULL;
	while (somewhere_in_dlist && somewhere_in_dlist->next)
		somewhere_in_dlist = somewhere_in_dlist->next;
	while (somewhere_in_dlist)
	{
		tmp = somewhere_in_dlist->previous;
//		ft_printf("Starting the memdels\n");
		ft_memdel((void**)&somewhere_in_dlist->d_name);
//		ft_printf("d_name freed\n");
		ft_memdel((void**)&somewhere_in_dlist->gr_name);
//		ft_printf("gr_name freed\n");
		ft_memdel((void**)&somewhere_in_dlist->usr_name);
//		ft_printf("usr_name freed\n");
	//	ft_memdel((void**)&somewhere_in_dlist->linkname);
		free(somewhere_in_dlist);
		somewhere_in_dlist = tmp;
	}
}
