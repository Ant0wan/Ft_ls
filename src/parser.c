/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/30 15:59:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "formatting.h"
#include "error.h"

void	set_booleans_of_t_options(char *prog_name, char c, t_options *options)
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
		print_usage(prog_name, c);
		exit (EXIT_FAILURE);
	}
}

int	parse_options(char **argv, char *av, t_options *options)
{
	if (av)
	{
		if (*av != '-')
			return (EXIT_FAILURE);
		if (++av && (*av == '-' || *av == '\0'))
			return (EXIT_FAILURE);
		else
		{
			while (av && *av)
			{
				set_booleans_of_t_options(*argv, *av, options);
				++av;
			}
			return (EXIT_SUCCESS);
		}
	}
	else
		return (EXIT_SUCCESS);
}

int	parser(int argc, char **argv, t_options *options)
{
	int	i;

	i = 1;
	while (!parse_options(argv, argv[i], options) && i < argc)
		++i;
	if (argv[i] && *argv[i] == '-' && *++argv[i] == '-')
		++i;
	if (i == argc)
	{
		if (get_what_is_in_the_dir(*argv, ".", options) == OK)
			return (OK);
	}
	else
	{
		if (output_ls_of_each_argument(argc, argv, i, options) == OK)
			return (OK);
	}
	return (SERIOUS);
}
