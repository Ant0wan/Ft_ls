/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:45:25 by abarthel          #+#    #+#             */
/*   Updated: 2019/05/24 14:38:08 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	output_ls_of_each_argument(int argc, char **argv, int i)
{
	(void)argc;
	while (argv[i]) // && i < argc)
	{
		ft_printf("r-d-r-- %s\n", argv[i]);
		++i;
	}
}
