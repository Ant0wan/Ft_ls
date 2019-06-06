/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/06 08:51:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "error.h"
#include "libft.h"

int	print_error(char *prog_name, char *av)
{
	char	*vas_ret;

	if (av)
	{
		ft_asprintf(&vas_ret, "%s: %s", prog_name, av);
		perror(vas_ret);
		if (!vas_ret)
		{
			ft_memdel((void**)vas_ret);
		}
	}
	else
	{
		perror(NULL);
	}
	return (SERIOUS);
}

int	print_usage(char *prog_name, char c)
{
	if (!ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n"\
			"usage: %s [-lRart] [file ...]\n", prog_name, c, prog_name))
	{
		perror(NULL);
	}
	return (SERIOUS);
}
