# @file    TestReadFromFile4.rb
# @brief   Reads tests/l1v1-minimal.xml into memory and tests it.
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  Ben Bornstein 
#
# $Id: TestReadFromFile4.rb 11522 2010-07-22 00:32:10Z mhucka $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/ruby/test/sbml/TestReadFromFile4.rb $
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/sbml/test/TestReadFromFile4.c
# using the conversion program dev/utilities/translateTests/translateTests.pl.
# Any changes made here will be lost the next time the file is regenerated.
#
# -----------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2010 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
# -----------------------------------------------------------------------------
require 'test/unit'
require 'libSBML'

class TestReadFromFile4 < Test::Unit::TestCase

  def test_read_l1v1_minimal
    filename = "../../sbml/test/test-data/l1v1-minimal.xml"
    d = LibSBML::readSBML(filename)
    if (d == nil)
    end
    assert( d.getLevel() == 1 )
    assert( d.getVersion() == 1 )
    m = d.getModel()
    assert( m.getNumCompartments() == 1 )
    c = m.getCompartment(0)
    assert ((  "x" == c.getName() ))
    assert( m.getNumSpecies() == 1 )
    s = m.getSpecies(0)
    assert ((  "y"  == s.getName() ))
    assert ((  "x"  == s.getCompartment() ))
    assert( s.getInitialAmount() == 1 )
    assert( s.getBoundaryCondition() == false )
    assert( m.getNumReactions() == 1 )
    r = m.getReaction(0)
    assert ((  "r" == r.getName() ))
    assert( r.getReversible() != false )
    assert( r.getFast() == false )
    assert( r.getNumReactants() == 1 )
    assert( r.getNumProducts() == 1 )
    sr = r.getReactant(0)
    assert ((  "y" == sr.getSpecies() ))
    assert( sr.getStoichiometry() == 1 )
    assert( sr.getDenominator() == 1 )
    sr = r.getProduct(0)
    assert ((  "y" == sr.getSpecies() ))
    assert( sr.getStoichiometry() == 1 )
    assert( sr.getDenominator() == 1 )
    d = nil
  end

end
