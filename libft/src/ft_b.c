/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:00:19 by abarthel          #+#    #+#             */
/*   Updated: 2019/04/08 14:14:01 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "prs_struct.h"
#include "specifiers.h"
#include "prefix.h"
#include "format.h"

#ifndef NB_BITS
# define NB_BITS 8
#endif

extern t_flags		g_flags;
extern t_modifier	g_modifier;
extern t_options	g_options;
extern t_prefix		g_prefix;

static inline size_t	ft_type_len(void)
{
	if (g_modifier.hh)
		return (sizeof(char) * NB_BITS);
	else if (g_modifier.h)
		return (sizeof(short) * NB_BITS);
	else if (g_modifier.l)
		return (sizeof(long) * NB_BITS);
	else if (g_modifier.ll)
		return (sizeof(long long) * NB_BITS);
	else if (g_modifier.j)
		return (sizeof(intmax_t) * NB_BITS);
	else if (g_modifier.t)
		return (sizeof(ptrdiff_t) * NB_BITS);
	else if (g_modifier.z)
		return (sizeof(size_t) * NB_BITS);
	else
		return (sizeof(int) * NB_BITS);
}

void					ft_b(uintmax_t nb)
{
	reset_prefix();
	g_prefix.base = 2;
	g_flags.plus = 0;
	g_flags.zero = 0;
	if (g_flags.hash)
	{
		g_prefix.size = 2;
		g_prefix.prefix = "0b";
	}
	g_options.precision = 0;
	g_prefix.len = ft_type_len();
	format(nb);
}
