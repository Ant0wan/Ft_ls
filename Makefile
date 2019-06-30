# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:03:51 by abarthel          #+#    #+#              #
#    Updated: 2019/06/30 13:31:50 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include link.mk

SANITIZE := -fsanitize=address

#OPTIMIZATION := -O2 -fno-builtin
OPTIMIZATION := 

DEBUGGING := -g

WARNING := -Wall -Wextra -Werror

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME)	: $(OBJECTS)
	@make lib -j -C $(PATH_LIB)
	@$(CC) $(WARNING) $(CFLAGS) $(OPTIMIZATION) $^ -o $@ $(LIB)
	@printf "\n\e[38;5;196m%4s [\e[1m$(NAME) built]\n\n\e[0m"

clean:
	@$(RM) $(OBJECTS) $(DEPENDS)
	@make clean -C $(PATH_LIB)

fclean:
	@$(RM) $(OBJECTS) $(DEPENDS) $(NAME)
	@make fclean -C $(PATH_LIB)

re: fclean $(NAME)

test : $(NAME)
	@$(TEST_TOOL) $(TEST_INPUT)

-include $(DEPENDS)

%.o: %.c Makefile
	@$(CC) $(WARNING) $(CFLAGS) $(OPTIMIZATION) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "\e[38;5;21m%-20s \e[38;5;37mobject built\n\e[0m" $(notdir $(basename $@))
