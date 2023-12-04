# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 07:33:08 by mcutura           #+#    #+#              #
#    Updated: 2023/12/04 07:33:08 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := engine

# --- Directories ---
SRCDIR := src/
OBJDIR := build/
HDRDIR := include/

# --- Sources ---
SRC := main.cpp
SRCS := $(addprefix $(SRCDIR), $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)%.o)

# --- Headers ---
HDR := 
HDRS := $(addprefix $(HDRDIR), $(HDR))

# --- Compilers ---
CC := cc
CXX := c++

# --- Flags ---
CFLAGS := -Wall -Wextra -Wpedantic -Werror -O3
CXXFLAGS := -std=c++98 -Wall -Wextra -Wpedantic -Werror -O3
INCLUDES := -I$(HDRDIR)
debug: CFLAGS += -ggdb3 -Og
debug: CXXFLAGS += -ggdb3 -Og

# --- Utils --
RM := rm -fr
MKDIR := mkdir -pm 775

# --- Rules ---
all: $(NAME)

$(NAME): $(HDRS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

debug: all

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean debug fclean re
