/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:01:06 by abarthel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/29 19:59:58 by abarthel         ###   ########.fr       */
=======
/*   Updated: 2019/06/30 12:34:14 by abarthel         ###   ########.fr       */
>>>>>>> ab4bd53fd7f9ff2971b2c565ddbb71b7bc11abed
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv)
{
	t_options	options;

	options = (t_options){.l = 0, .upr = 0, .a = 0, .r = 0, .t = 0, .u = 0,
<<<<<<< HEAD
		.upa = 0, .b = 0};
=======
		.upa = 0, .b = 0, .c = 0};
>>>>>>> ab4bd53fd7f9ff2971b2c565ddbb71b7bc11abed
	return (parser(argc, argv, &options));
}
