/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:01:06 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/06 16:10:17 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <dirent.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	t_options	options;
	ft_printf("%zu\n", sizeof(struct dirent));
	options = (t_options){.l = 0, .upr = 0, .a = 0, .r = 0, .t = 0};
	return (parser(argc, argv, &options));
}
