# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 20:46:13 by mcutura           #+#    #+#              #
#    Updated: 2023/12/12 20:46:13 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := hot_springs

# --- Directories ---
HDRDIR := include/
SRCDIR := src/
OBJDIR := build/

# --- Headers ---
HDR := head.hpp Stopwatch.hpp Utils.hpp
HDRS := $(addprefix $(HDRDIR), $(HDR))

# --- Sources ---
SRC := main.cpp Stopwatch.cpp Utils.cpp
SRCS := $(addprefix $(SRCDIR), $(SRC))

# --- Objects ---
OBJS := $(SRC:%.cpp=$(OBJDIR)%.o)

# --- Compilers ---
CXX := c++

# --- Flags ---
CXXFLAGS := -std=c++11 -Wall -Wextra -Wpedantic -Werror -O3 -pthread
INCLUDES := -I$(HDRDIR)
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
