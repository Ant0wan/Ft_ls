/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/17 15:16:22 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readdir.h"
#include "parser.h"
#include "error.h"
#include "libft.h"

/*
** LINUX (GNU COREUTILS) TYPE PARSER
*/

#ifdef __unix__
# define HELP "--help"

static void		set_booleans_of_t_options(char *prog_name, char *arg,
		char c, t_options *options)
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
	else if (c == '-')
	{
		if (!ft_strcmp(HELP, arg))
			exit(print_help(prog_name));
		else
			exit(print_unrec_opt(prog_name, arg));
	}
	else
	{
		print_usage(prog_name, c);
		exit(SERIOUS);
	}
}

static int		parse_options(char **argv, int i, t_options *options)
{
	int a;

	a = 0;
	if (argv[i])
	{
		if (argv[i][a] == '-')
		{
			if (!ft_strcmp("-", argv[i]))
				return (2);
			if (!ft_strcmp("--", argv[i]))
				return (1);
			else
			{
				while (argv[i][++a])
					set_booleans_of_t_options(*argv, argv[i], argv[i][a],
							options);
			}
			return (0);
		}
	}
	return (2);
}

int				parser(int argc, char **argv, t_options *options)
{
	int	i;
	int	nb_arg;
	int	ret_value;

	i = 1;
	nb_arg = 0;
	ret_value = 0;
	while (i < argc && (!ret_value || ret_value == 2))
	{
		ret_value = parse_options(argv, i, options);
		++i;
		if (ret_value == 2)
			++nb_arg;
	}
	if (!(argc - i + nb_arg))
		ret_value = feed_readdir_with_each_argument(argc, argv, 0, *options);
	else
		ret_value = feed_readdir_with_each_argument(argc, argv, 1, *options);
	return (ret_value);
}

#endif
