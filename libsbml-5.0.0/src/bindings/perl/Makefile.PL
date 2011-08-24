## src/bindings/perl/Makefile.PL.  Generated from Makefile.PL.in by configure.
##
## \file    Makefile.PL
## \brief   Perl-specific SWIG directives for wrapping libSBML API
## \author  TBI {xtof,raim}@tbi.univie.ac.at
##
## $Id: Makefile.PL.in 10145 2009-08-30 04:30:15Z ajouraku $
## $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/perl/Makefile.PL.in $

##
## Copyright 2004 TBI
##
## This library is free software; you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation; either version 2.1 of the License, or
## any later version.
##
## This library is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
## MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
## documentation provided hereunder is on an "as is" basis, and the
## California Institute of Technology and Japan Science and Technology
## Corporation have no obligations to provide maintenance, support,
## updates, enhancements or modifications.  In no event shall the
## California Institute of Technology or the Japan Science and Technology
## Corporation be liable to any party for direct, indirect, special,
## incidental or consequential damages, including lost profits, arising
## out of the use of this software and its documentation, even if the
## California Institute of Technology and/or Japan Science and Technology
## Corporation have been advised of the possibility of such damage.  See
## the GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library; if not, write to the Free Software Foundation,
## Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
##
## The original code contained here was initially developed by:
##
##     Christoph Flamm and Rainer Machne
##     Institut fuer Theoretische Chemie
##     Universitaet Wien
##     Waehringerstrasse 17/3/308
##     A-1090 Wien, Austria


use ExtUtils::MakeMaker;
use Config;

$lddlfags = " ";
if ("linux-gnu" eq "cygwin")
{
  $lddlflags .= "-shared";
}
else
{
  $lddlflags .= "$Config{lddlflags}";
}

WriteMakefile(
              NAME        => "LibSBML",
	      PREFIX      => "/home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml",
              MAKEFILE    => 'Makefile-perl',
              INSTALLDIRS => "site",
              LIBS        => "     -lxml2 -lz -lbz2 -lm  -lm",
              LDDLFLAGS   => $lddlflags,
              CC          => "g++",
	      CCFLAGS     => " ",
              INC         => "-I../swig -I../../sbml -I../.. -I../../../include",
              MYEXTLIB    => "../../libsbml.la",
              macro       => {USE_SWIG => q[]},
              OBJECT      => "LibSBML_wrap.o",
	      MAN1PODS    => {},
	      MAN3PODS    => {},
              AUTHOR      => "Christoph Flamm <xtof@tbi.univie.ac.at>",
              VERSION     => "5.0.0",
);

package MY;
sub postamble {
	return <<'MAKE_FRAG';

extra_sources  = \
  LibSBML.i \
  local.cpp \
  local.i \
  list_get_fix.i \
  list_of_fix.i

swig_sources =      \
  $(extra_sources)  \
  ../swig/libsbml.h \
  ../swig/libsbml.i

PACKAGE_ARGS=

ifeq ("", "1")
	PACKAGE_ARGS += -DUSE_LAYOUT
endif


main_sources = \
  $(shell grep '%include sbml' ../swig/libsbml.i | grep -v 'libsbml-version.h' \
    | cut -f2- -d'/' | sed -e 's,^,../../sbml/,g')

LibSBML.pm: LibSBML_wrap.cxx

LibSBML_wrap.cxx: LibSBML.pod $(swig_sources)
	../../../config/chk_swig_version.sh || exit
	swig  -c++ -perl5 -proxy $(PACKAGE_ARGS) -I../../../include -I../.. LibSBML.i 

LibSBML.pod: $(main_sources) ../swig/libsbml.i ../swig/swigdoc.py
	../swig/swigdoc.py perl -I../.. -D../../../docs/src ../swig/libsbml.i LibSBML.pod

MYPACKLIST = $(DESTINSTALLSITEARCH)/auto/$(FULLEXT)/.packlist
#MYPERLLOCAL = $(INSTALLARCHLIB)/perllocal.pod
myuninstall:
	$(NOECHO) dirs=`cat $(MYPACKLIST) | xargs -n 1 dirname`; \
	$(PERLRUN) -MExtUtils::Install -e \
	  'uninstall('\''$(MYPACKLIST)'\',1,0')'; \
	for d in $$dirs; do \
          if test -d $$d && test -n "`find $$d -maxdepth 0 -empty`"; then \
	    echo rmdir $$d; \
	    rmdir $$d; \
          fi; \
        done; 
MAKE_FRAG
}
# End of file
