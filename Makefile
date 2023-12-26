# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/26 10:51:10 by mcutura           #+#    #+#              #
#    Updated: 2023/12/26 10:51:10 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

X := \x1b[0m
M := \x1b[35m
A := \x1b[36m
S := \x1b[1;36m
CALENDAR := $(wildcard */)

INPUTS := $(CALENDAR:%=%input.txt)
SOLUTIONS := $(shell awk 'BEGIN {FS=":= "} /NAME :=*/ { \
	printf "%.3s%s\n", FILENAME, $$2; nextfile}' */Makefile)

.PHONY: all re clean fclean help run NOMNOM

help:	# Print help on Makefile
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\t$(S)make $(M)<target>$(X)\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "$(M)%-16s$(A)%s$(X)\n", $$1, $$2 } ' Makefile

all: $(CALENDAR)	# Compile all targets
	$(info Compiled 2023 Advent of code)

run: $(SOLUTIONS) | $(INPUTS)	# Run all solutions
	$(info Running solutions)
	@for sol in $(SOLUTIONS); do \
		day=$$(dirname $$sol); \
		printf "Day %s\n" $$day; \
		./$$sol $$day/input.txt; \
	done

NOMNOM:	# to download inputs, export your aoc session COOKIE=<...>
	@test $${COOKIE?Please provide COOKIE to retrieve inputs. Env var will do}
	@echo NOMNOM

clean: $(CALENDAR)	# Clean compiled build objects
fclean: $(CALENDAR)	# Clean all generated files
re: fclean all	# Re-compile all targets

$(SOLUTIONS):
	@$(MAKE) all --no-print-directory

$(CALENDAR)::
	$(info Make $(MAKECMDGOALS) day $@)
	@$(MAKE) -s --no-print-directory -C $@ $(MAKECMDGOALS)

$(INPUTS): | NOMNOM
	$(foreach DAY, $(CALENDAR), $(shell day=$(DAY); \
	URL="https://adventofcode.com/2023/day/$${day##0}input"; \
	curl -z $(DAY)input.txt -o $(DAY)input.txt \
	--cookie "session=$(COOKIE)" $$URL))
	$(info Inputs ready)
