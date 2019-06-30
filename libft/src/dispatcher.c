/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:51:32 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/18 14:12:53 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "struct_disp.h"
#include "specifiers.h"

#ifndef T_
# define T_ (void*)
#endif

#ifndef NB_PTR
# define NB_PTR 26
#endif

static const t_specifier	g_specifier[] =
{
	{ 'c', T_ & ft_chr},
	{ 'd', T_ & ft_nbr},
	{ 'e', T_ & ft_nbr},
	{ 'f', T_ & ft_double},
	{ 'i', T_ & ft_nbr},
	{ 'o', T_ & ft_octal},
	{ 's', T_ & ft_str},
	{ 'u', T_ & ft_unbr},
	{ 'x', T_ & ft_lhexa},
	{ 'X', T_ & ft_uhexa},
	{ 'C', T_ & ft_wchr},
	{ 'p', T_ & ft_p},
	{ 'n', T_ & ft_n},
	{ 'D', T_ & ft_upnbr},
	{ 'O', T_ & ft_upoc},
	{ 'U', T_ & ft_upunbr},
	{ 'E', T_ & ft_nbr},
	{ 'F', T_ & ft_double},
	{ 'g', T_ & ft_nbr},
	{ 'G', T_ & ft_nbr},
	{ 'a', T_ & ft_nbr},
	{ 'A', T_ & ft_nbr},
	{ 'S', T_ & ft_wstr},
	{ 'r', T_ & ft_nbr},
	{ 'b', T_ & ft_b},
	{ 'y', T_ & ft_y}
};

void	*dispatcher(char c)
{
	int	i;

	i = 0;
	while (i < NB_PTR && g_specifier[i].type ^ c)
		++i;
	if (i == NB_PTR)
		return (NULL);
	else
		return (g_specifier[i].f);
}
