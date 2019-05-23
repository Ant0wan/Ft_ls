/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:43:53 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/23 16:06:02 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

_Bool	parse_options(char *argv)
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
			//	go parse les options till wrong
				while (argv && *argv)
				{
					printf("option:%c\n", *argv);
					++argv;
				}
				return (EXIT_SUCCESS);
			}
		}
	}
	else
		return (EXIT_SUCCESS);
}

_Bool	parser(int argc, char **argv)
{
	int	i;

	i = 0;
	while (!parse_options(argv[++i]) && i < argc)
	{
		printf("i:%d, arg:%s\n", i, argv[i]);
	}
	return (EXIT_FAILURE);
}
