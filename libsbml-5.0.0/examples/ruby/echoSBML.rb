#!/usr/bin/env ruby
#
# @file    echoSBML.rb
# @brief   Echos (and pretty prints) an SBML model.
# @author  Alex Gutteridge (Ruby conversion of examples/c/echoSBML.c)
# @author  Ben Bornstein
#
# $Id: echoSBML.rb 13595 2011-04-11 01:34:30Z mhucka $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/ruby/echoSBML.rb $
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.

require 'libSBML'

if ARGV.size != 2
  puts "Usage: echoSBML input-filename output-filename"
  exit(2)
end

LibSBML::writeSBML(LibSBML::readSBML(ARGV[0]),ARGV[1])
