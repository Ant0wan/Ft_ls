/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/30 18:12:52 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "error.h"
#include "libft.h"

void	print_error(char *prog_name, char *av)
{
	char	*vas_ret;

	ft_asprintf(&vas_ret, "%s: %s", prog_name, av);
	perror(vas_ret);
	if (!vas_ret)
	{
		ft_memdel((void**)vas_ret);
	}
}

void	print_usage(char *prog_name, char c)
{
	if (!ft_dprintf(STDERR_FILENO, "%s: illegal option -- %c\n"\
			"usage: %s [-lRart] [file ...]\n", prog_name, c, prog_name))
	{
		perror(NULL);
	}
}
