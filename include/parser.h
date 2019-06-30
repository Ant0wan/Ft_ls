/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:34:05 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/30 13:20:37 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_options
{
	_Bool	l:1;
	_Bool	upr:1;
	_Bool	a:1;
	_Bool	r:1;
	_Bool	t:1;
	_Bool	u:1;
	_Bool	upa:1;
	_Bool	b:1;
	_Bool	c:1;
	_Bool	f:1;
	_Bool	upt:1;
}				t_options;

int				parser(int argc, char **argv, t_options *options);

#endif
