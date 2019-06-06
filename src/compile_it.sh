#!/bin/sh
if [ $# -eq 0 ]
	then
		#gcc -Wall -Wextra -Werror parser.c insert_sort.c dlist.c readdir.c files.c display.c main.c error.c -I../libft/include -I../include ../libft/libft.a -o ft_ls
		gcc -g -Wall -Wextra -Werror insert_sort.c parser.c dlist.c readdir.c files.c display.c main.c error.c -I../libft/include -I../include ../libft/libft.a -o ft_ls
		#gcc -O2 -Wall -Wextra -Werror insert_sort.c parser.c dlist.c readdir.c files.c display.c main.c error.c -I../libft/include -I../include ../libft/libft.a -o ft_ls
		#gcc -g -fsanitize=address -Wall -Wextra -Werror insert_sort.c parser.c dlist.c readdir.c files.c display.c main.c error.c -I../libft/include -I../include ../libft/libft.a -o ft_ls
else
	rm -rf ft_ls.dSYM && rm -rf ft_ls
fi
