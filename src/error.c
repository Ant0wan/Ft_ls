/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/30 15:42:51 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	print_error(char *prog_name, char *av)
{
	char	*vas_ret;

	if (ft_asprintf(&vas_ret, "%s: %s", prog_name, av))
	{
		perror(vas_ret);
		if (!vas_ret)
		{
			ft_memdel((void**)vas_ret);
		}
	}
}
