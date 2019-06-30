/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/30 12:33:30 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "compare.h"
#include "error.h"
#include "libft.h"

int	print_error(char *restrict prog_name, char *restrict av)
{
	char	*vas_ret;

	if (av)
	{
		ft_asprintf(&vas_ret, "%s: %s", prog_name, av);
		perror(vas_ret);
		if (vas_ret != NULL)
			free(vas_ret);
	}
	else
		perror(NULL);
	return (SERIOUS);
}

int	print_usage(char *restrict prog_name, char c)
{
	if (!ft_dprintf(STDERR_FILENO, "%1$s: illegal option -- %2$c\n"\
					"usage: %1$s [-ARaclrtu] [file ...]\n", prog_name, c))
		perror(NULL);
	return (SERIOUS);
}
