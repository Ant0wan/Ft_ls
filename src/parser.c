/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/23 18:44:55 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "libft.h"
#include <stdio.h>

#define FT_LS_USAGE "ft_ls: illegal option -- %c\n"\
	"usage: ls [-lRart] [file ...]\n"

_Bool	parser(int argc, char **argv, t_options *options)
{
	int	i;

	i = 0;
	while (!parse_options(argv[++i], options) && i < argc)
	{
		// pour le reste du parsing, ici il s'arrete une fois plus d'options
		(void)i; // to debugg, it is useless of course
	}
	return (EXIT_FAILURE);
}

_Bool	parse_options(char *argv, t_options *options)
{
	if (argv)
	{
		if (*argv != '-')
			return (EXIT_FAILURE);
		else
		{
			if (++argv && (*argv == '-' || *argv == 0))
				return (EXIT_FAILURE);
			else
			{
				while (argv && *argv)
				{
					set_booleans_of_t_options(*argv, options);
					++argv;
				}
				return (EXIT_SUCCESS);
			}
		}
	}
	else
		return (EXIT_SUCCESS);
}

_Bool	set_booleans_of_t_options(char c, t_options *options)
{
	if (c == 'l' && (options->l |= (1 << 0)))
		return (EXIT_SUCCESS);
	else if (c == 'R' && (options->upr |= (1 << 0)))
		return (EXIT_SUCCESS);
	else if (c == 'a' && (options->a |= (1 << 0)))
		return (EXIT_SUCCESS);
	else if (c == 'r' && (options->r |= (1 << 0)))
		return (EXIT_SUCCESS);
	else if (c == 't' && (options->t |= (1 << 0)))
		return (EXIT_SUCCESS);
	else
	{
		print_option_usage(c);
		return (EXIT_FAILURE);
	}
}

void	print_option_usage(char c)
{
	ft_printf(FT_LS_USAGE, c);
}
