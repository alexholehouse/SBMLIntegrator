# @file    TestRateRule.rb
# @brief   RateRule unit tests
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  Ben Bornstein 
#
# $Id: TestRateRule.rb 11522 2010-07-22 00:32:10Z mhucka $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/ruby/test/sbml/TestRateRule.rb $
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/sbml/test/TestRateRule.c
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

class TestRateRule < Test::Unit::TestCase

  def setup
    @@rr = LibSBML::RateRule.new(1,2)
    if (@@rr == nil)
    end
  end

  def teardown
    @@rr = nil
  end

  def test_RateRule_create
    assert( @@rr.getTypeCode() == LibSBML::SBML_RATE_RULE )
    assert( @@rr.getMetaId() == "" )
    assert( @@rr.getNotes() == nil )
    assert( @@rr.getAnnotation() == nil )
    assert( @@rr.getFormula() == "" )
    assert( @@rr.getMath() == nil )
    assert( @@rr.getVariable() == "" )
    assert( @@rr.getType() == LibSBML::RULE_TYPE_RATE )
  end

  def test_RateRule_createWithNS
    xmlns = LibSBML::XMLNamespaces.new()
    xmlns.add( "http://www.sbml.org", "testsbml")
    sbmlns = LibSBML::SBMLNamespaces.new(2,1)
    sbmlns.addNamespaces(xmlns)
    object = LibSBML::RateRule.new(sbmlns)
    assert( object.getTypeCode() == LibSBML::SBML_RATE_RULE )
    assert( object.getMetaId() == "" )
    assert( object.getNotes() == nil )
    assert( object.getAnnotation() == nil )
    assert( object.getLevel() == 2 )
    assert( object.getVersion() == 1 )
    assert( object.getNamespaces() != nil )
    assert( object.getNamespaces().getLength() == 2 )
    object = nil
  end

  def test_RateRule_free_NULL
  end

  def test_RateRule_setVariable
    variable =  "x";
    @@rr.setVariable(variable)
    assert (( variable == @@rr.getVariable() ))
    assert_equal true, @@rr.isSetVariable()
    if (@@rr.getVariable() == variable)
    end
    @@rr.setVariable(@@rr.getVariable())
    assert (( variable == @@rr.getVariable() ))
    @@rr.setVariable("")
    assert_equal false, @@rr.isSetVariable()
    if (@@rr.getVariable() != nil)
    end
  end

end
