/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/22 21:07:16 by sel-ahma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sortargv.h"
#include "readdir.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

/*
** MACOS TYPE PARSER
*/

#ifndef __unix__

static void		set_booleans_of_t_options(char *prog_name, char c,
		t_options *options)
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
		exit(SERIOUS);
	}
}

static _Bool	parse_options(char **argv, char *av, t_options *options)
{
	if (av)
	{
		if (*av != '-')
			return (1);
		if (!ft_strcmp("-", av))
			return (1);
		else if (!ft_strcmp("--", av))
			return (1);
		else
		{
			++av;
			while (av && *av)
			{
				set_booleans_of_t_options(*argv, *av, options);
				++av;
			}
			return (0);
		}
	}
	else
		return (0);
}

int				parser(int argc, char **argv, t_options *options)
{
	int	i;
	int	ret_value;

	i = 1;
	ret_value = 0;
	while (!parse_options(argv, argv[i], options) && i < argc)
		++i;
	if (argv[i] && !ft_strcmp(argv[i], "--"))
		++i;
	sort_argv(argc, argv, i); // here for sorting arg
	if (i == argc)
		ret_value = feed_readdir_with_each_argument(argc, argv, 0, *options);
	else
		ret_value = feed_readdir_with_each_argument(argc, argv, i, *options);
	return (ret_value);
}

#endif
