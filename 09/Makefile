# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 05:54:42 by mcutura           #+#    #+#              #
#    Updated: 2023/12/09 05:54:42 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := OASIS

# --- Directories ---
HDRDIR := include/
SRCDIR := src/
OBJDIR := build/

# --- Headers ---
HDR := head.hpp Utils.hpp
HDRS := $(addprefix $(HDRDIR), $(HDR))

# --- Sources ---
SRC := main.cpp
SRC += Utils.cpp
SRCS := $(addprefix $(SRCDIR), $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)%.o)

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
