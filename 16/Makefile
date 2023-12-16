# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/16 06:04:38 by mcutura           #+#    #+#              #
#    Updated: 2023/12/16 06:04:38 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := energizer

# --- Directories ---
HDRDIR := include
SRCDIR := src
OBJDIR := build

# --- Headers ---
HDR := head.hpp
HDRS := $(addprefix $(HDRDIR)/, $(HDR))

# --- Sources ---
SRC := main.cpp
SRCS := $(addprefix $(SRCDIR)/, $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)/%.o)

# --- Compilers ---
CXX := c++

# --- Flags ---
CXXFLAGS := -std=c++98 -Wall -Wextra -Wpedantic -Werror -O3
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
