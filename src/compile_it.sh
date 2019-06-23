#!/bin/sh

FILESANDOUTPUT="ft_nb_len.c l_display.c loption.c sortargv.c compare.c parser.c parser2.c insert.c dlist.c readdir.c readdir2.c files.c display.c main.c error.c -I../libft/include -I../include ../libft/libft.a -o ft_ls"

if [ $# -eq 0 ]
	then
		#clang -Wall -Wextra -Werror $FILESANDOUTPUT
		clang -g -Wall -Wextra -Werror $FILESANDOUTPUT
		#clang -O2 -fno-builtin -Wall -Wextra -Werror $FILESANDOUTPUT
		#clang -O2 -fno-builtin $FILESANDOUTPUT
		#clang -g -fsanitize=address -Wall -Wextra -Werror $FILESANDOUTPUT
		#clang -g -fsanitize=address -Wall -Wextra -Werror -Weverything $FILESANDOUTPUT
else
	rm -rf ft_ls.dSYM && rm -rf ft_ls
fi
