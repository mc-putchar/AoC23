# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 11:02:50 by mcutura           #+#    #+#              #
#    Updated: 2023/12/26 11:02:50 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := calibrator

# --- Sources ---
SRC := calibrator.c

# --- Flags ---
CC := cc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -O3
debug: CFLAGS += -ggdb3 -Og

# --- Utils --
RM := rm -fr

# --- Rules ---
.PHONY: all clean debug fclean re
all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
fclean: clean
	$(RM) $(NAME)

re: fclean all
debug: all
