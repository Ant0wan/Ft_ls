/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/25 09:28:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "parser.h"
#include "formatting.h"

#define FT_LS_USAGE "ft_ls: illegal option -- %c\n"\
	"usage: ls [-lRart] [file ...]\n"

_Bool	parser(int argc, char **argv, t_options *options)
{
	int	i;

	i = 1;
	while (!parse_options(argv[i], options) && i < argc)
		++i;
	if (argv[i] && *argv[i] == '-' && *++argv[i] == '-')
		++i;
	if (i == argc)
	{
		if (get_what_is_in_the_dir(".", options))
			return (EXIT_FAILURE);
	}
	else
	{
		if (output_ls_of_each_argument(argc, argv, i, options))
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

_Bool	parse_options(char *argv, t_options *options)
{
	if (argv)
	{
		if (*argv != '-')
			return (EXIT_FAILURE);
		if (++argv && (*argv == '-' || *argv == '\0'))
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
