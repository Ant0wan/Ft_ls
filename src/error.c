/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:28 by abarthel          #+#    #+#             */
/*   Updated: 2019/06/15 15:59:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "compare.h"
#include "error.h"
#include "libft.h"

#ifdef __unix__
# define ERROR_MSG "%s: cannot access '%s'"
# define INV_OPT "%1$s: invalid option -- '%2$c'\n"\
			"Try '%1$s --help' for more information.\n"

#else
# define ERROR_MSG "%s: %s"
# define INV_OPT "%1$s: illegal option -- %2$c\n"\
			"usage: %1$s [-lRart] [file ...]\n"

#endif

#ifdef __unix__
# define UNRECOGNIZED_OPT "%1$s: unrecognized option '%2$s'\n"\
	"Try '%1$s --help' for more information.\n"
# define HELP "Usage: %s [OPTION]... [FILE]...\n"\
	"List information about the FILEs (the current directory by default).\n"\
	"Sort entries alphabetically if -t is not specified.\n\n"\
	"Mandatory arguments to long options are mandatory for short"\
	"options too.\n"\
	"  -a, --all                  do not ignore entries starting with .\n"\
	"  -l                         use a long listing format\n"\
	"  -r, --reverse              reverse order while sorting\n"\
	"  -R, --recursive            list subdirectories recursively\n"\
	"  -t                         sort by modification time, newest first\n"\
	"      --help                 display this help and exit\n\n"\
	"Exit status:\n"\
	" 0  if OK,\n"\
	" 1  if minor problems (e.g., cannot access subdirectory),\n"\
	" 2  if serious trouble (e.g., cannot access command-line argument).\n\n"\
	"Full documentation and source code at:"\
	" <https://github.com/Ant0wan/Ft_ls.git>\n"\
	"Authors: Sabri El Ahmar and Antoine Barthelemy\n"

int	print_help(char *prog_name)
{
	ft_printf(HELP, prog_name);
	return (SERIOUS);
}

int	print_unrec_opt(char *prog_name, char *arg)
{
	ft_printf(UNRECOGNIZED_OPT, prog_name, arg);
	return (SERIOUS);
}

#endif

int	print_error(char *restrict prog_name, char *restrict av)
{
	char	*vas_ret;

	if (av)
	{
		ft_asprintf(&vas_ret, ERROR_MSG, prog_name, av);
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
	if (!ft_dprintf(STDERR_FILENO, INV_OPT, prog_name, c))
		perror(NULL);
	return (SERIOUS);
}
