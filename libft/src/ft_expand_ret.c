/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:49:12 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/17 13:45:05 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <stdlib.h>

#include "prs_struct.h"
#include "libft.h"

#ifndef BUFF
# define BUFF 1024
#endif

#ifndef G_ERROR
# define G_ERROR 1
#endif

extern t_ret		g_ret;
extern _Bool		g_error;

extern inline void	ft_expand_ret(int size)
{
	void *restrict	new_ret;

	g_ret.max += size < BUFF ? BUFF : size;
	if (!(new_ret = (char*)ft_memalloc(sizeof(char) * g_ret.max + 1)))
	{
		g_error = G_ERROR;
		return ;
	}
	else
	{
		if (g_ret.i > -1)
			ft_memcpy(new_ret, g_ret.ret, g_ret.i + 1);
		ft_memdel((void**)&g_ret.ret);
		g_ret.ret = (char*)new_ret;
	}
}
