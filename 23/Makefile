# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 06:02:12 by mcutura           #+#    #+#              #
#    Updated: 2023/12/23 06:02:12 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := long_walk

# --- Directories ---
HDRDIR := include
SRCDIR := src
OBJDIR := build

# --- Headers ---
HDR := head.hpp Graph.hpp
HDRS := $(addprefix $(HDRDIR)/, $(HDR))

# --- Sources ---
SRC := main.cpp part1.cpp Graph.cpp part2.cpp
SRCS := $(addprefix $(SRCDIR)/, $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)/%.o)

# --- Compilers ---
CXX := c++

# --- Flags ---
CXXFLAGS := -std=c++98 -Wall -Wextra -Wpedantic -Werror -O3 -march=native
INCLUDES := -I$(HDRDIR)
debug: CXXFLAGS += -ggdb3 -Og

# --- Utils --
RM := rm -fr
MKDIR := mkdir -pm 775

# --- Rules ---
.PHONY: all clean debug fclean re
all: $(NAME)

$(NAME): $(HDRS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@$(MKDIR) $(OBJDIR)

debug: all

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
