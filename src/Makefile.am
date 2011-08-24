# what flags you want to pass to the C compiler & linker
CFLAGS -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g
LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = SBMLIntegrator
main_SOURCES = main.cpp sbml_display.h sbml_formatter.h sbml_search.h
sbml_cleanup_SOURCES = sbml_cleanup.cpp sbml_display.h sbml_search.h sbml_formatter.h sbml_cleanup.h



.
.
targetbinaryN_SOURCES = targetbinaryN.c
