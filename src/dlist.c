/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:55:09 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/23 14:29:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "dlist.h"

t_dlist	*create_node(t_dlist *previous, t_dlist *next, void *data)
{
	t_dlist	*new;

	if ((new = malloc_a_node()))
	{
		new->next = next;
		new->previous = previous;
		new->data = data;
		return (new);
	}
	else
	{
		free_entire_dlist(previous);
		return (NULL);
	}
}

t_dlist	*malloc_a_node(void)
{
	t_dlist	*new;

	if ((new = (t_dlist*)malloc(sizeof(t_dlist))))
		return (new);
	else
		return (NULL);
}

/*
** should free what is inside the structure (to be defined later)
*/

void	free_entire_dlist(t_dlist *somewhere_in_dlist)
{
	t_dlist	*tmp;

	tmp = NULL;
	while (somewhere_in_dlist->next)
		somewhere_in_dlist = somewhere_in_dlist->next;
	while (somewhere_in_dlist)
	{
		tmp = somewhere_in_dlist;
		ft_memdel((void**)&somewhere_in_dlist);
		somewhere_in_dlist = somewhere_in_dlist->previous;
	}
}
