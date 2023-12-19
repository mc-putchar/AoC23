# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 06:08:09 by mcutura           #+#    #+#              #
#    Updated: 2023/12/19 06:08:09 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := aplenty

# --- Directories ---
HDRDIR := include
SRCDIR := src
OBJDIR := build

# --- Headers ---
HDR := head.hpp Workflow.hpp
HDRS := $(addprefix $(HDRDIR)/, $(HDR))

# --- Sources ---
SRC := main.cpp Workflow.cpp sorting_parts.cpp turbo_mode.cpp
SRCS := $(addprefix $(SRCDIR)/, $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)/%.o)

# --- Compilers ---
CXX := c++

# --- Flags ---
# Switched to c++11 for 64-bit integer support
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror -O3
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
