# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    link.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:45:47 by abarthel          #+#    #+#              #
#    Updated: 2019/07/06 15:31:41 by sel-ahma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SOURCES_PATH := ./src/

SOURCES :=	acl.c \
			compare.c \
			cplinfos.c \
			display.c \
			dlist.c \
			error.c \
			files.c \
			get_rights_acl_time.c \
			insert.c \
			l_display.c \
			l_display_utils.c \
			l_display_utils2.c \
			l_display_beg.c \
			loption.c \
			main.c \
			parser.c \
			readdir.c \
			sortargv.c \
			store_readdir.c \
			store_utils.c \

OBJECTS := $(patsubst %.c,%.o,$(addprefix $(SOURCES_PATH), $(SOURCES)))

INCLUDES := -I./include/ -I./libft/include/

PATH_LIB = ./libft/

LIB = $(PATH_LIB)libft.a

DEPENDS := $(patsubst %.c,%.d,$(addprefix $(SOURCES_PATH), $(SOURCES)))

TEST_PATH := ./tools/

TEST_TOOL := perl $(addprefix $(TEST_PATH),test-ls.pl)

TEST_INPUT := $(addprefix $(TEST_PATH),input-ls)
