/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/23 20:47:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "libft.h"

#define FT_LS_USAGE "ft_ls: illegal option -- %c\n"\
	"usage: ls [-lRart] [file ...]\n"

_Bool	parser(int argc, char **argv, t_options *options)
{
	int	i;

	i = 1;
	while (!parse_options(argv[i], options) && i < argc)
		++i;
	// pour le reste du parsing, ici il s'arrete une fois plus d'options
	ft_printf("stop at: %s\n", argv[i]);
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

void	set_booleans_of_t_options(char c, t_options *options)
{
	if (c == 'l')
	   options->l = 1;
	else if (c == 'R')
	   options->upr = 1;
	else if (c == 'a')
		options->a = 1;
	else if (c == 'r')
		options->r = 1;
	else if (c == 't')
		options->t = 1;
	else
	{
		ft_printf(FT_LS_USAGE, c);
		exit (EXIT_FAILURE);
	}
}
