# @file    TestValidASTNode.rb
# @brief   Test the isWellFormedASTNode function
#
# @author  Akiya Jouraku (Ruby conversion)
# @author  Sarah Keating 
#
# $Id: TestValidASTNode.rb 11522 2010-07-22 00:32:10Z mhucka $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/bindings/ruby/test/math/TestValidASTNode.rb $
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/math/test/TestValidASTNode.cpp
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

class TestValidASTNode < Test::Unit::TestCase

  def test_ValidASTNode_Name
    n = LibSBML::parseFormula("c")
    assert_equal true, n.isWellFormedASTNode()
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal false, (n.isWellFormedASTNode())
    n = nil
  end

  def test_ValidASTNode_Number
    n = LibSBML::parseFormula("1.2")
    assert_equal true, n.isWellFormedASTNode()
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal false, (n.isWellFormedASTNode())
    n = nil
  end

  def test_ValidASTNode_binary
    n = LibSBML::ASTNode.new(LibSBML::AST_DIVIDE)
    assert_equal false, (n.isWellFormedASTNode())
    c = LibSBML::parseFormula("c")
    n.addChild(c)
    assert_equal false, (n.isWellFormedASTNode())
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal true, n.isWellFormedASTNode()
    n = nil
  end

  def test_ValidASTNode_lambda
    n = LibSBML::ASTNode.new(LibSBML::AST_LAMBDA)
    assert_equal false, (n.isWellFormedASTNode())
    c = LibSBML::parseFormula("c")
    n.addChild(c)
    assert_equal true, n.isWellFormedASTNode()
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal true, n.isWellFormedASTNode()
    e = LibSBML::parseFormula("e")
    n.addChild(e)
    assert_equal true, n.isWellFormedASTNode()
    n = nil
  end

  def test_ValidASTNode_nary
    n = LibSBML::ASTNode.new(LibSBML::AST_TIMES)
    assert_equal false, (n.isWellFormedASTNode())
    c = LibSBML::parseFormula("c")
    n.addChild(c)
    assert_equal false, (n.isWellFormedASTNode())
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal true, n.isWellFormedASTNode()
    e = LibSBML::parseFormula("e")
    n.addChild(e)
    assert_equal true, n.isWellFormedASTNode()
    n = nil
  end

  def test_ValidASTNode_root
    n = LibSBML::ASTNode.new(LibSBML::AST_FUNCTION_ROOT)
    assert_equal false, (n.isWellFormedASTNode())
    c = LibSBML::parseFormula("c")
    n.addChild(c)
    assert_equal true, n.isWellFormedASTNode()
    d = LibSBML::parseFormula("3")
    n.addChild(d)
    assert_equal true, n.isWellFormedASTNode()
    e = LibSBML::parseFormula("3")
    n.addChild(e)
    assert_equal false, (n.isWellFormedASTNode())
    n = nil
  end

  def test_ValidASTNode_setType
    n = LibSBML::ASTNode.new()
    i = n.setType(LibSBML::AST_REAL)
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert( n.getType() == LibSBML::AST_REAL )
    i = n.setType(LibSBML::AST_PLUS)
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert( n.getType() == LibSBML::AST_PLUS )
    assert( n.getCharacter() ==  '+'  )
    i = n.setType(LibSBML::AST_FUNCTION_ARCCOSH)
    assert( i == LibSBML::LIBSBML_OPERATION_SUCCESS )
    assert( n.getType() == LibSBML::AST_FUNCTION_ARCCOSH )
    i = n.setType(LibSBML::AST_UNKNOWN)
    assert( i == LibSBML::LIBSBML_INVALID_ATTRIBUTE_VALUE )
    assert( n.getType() == LibSBML::AST_UNKNOWN )
    n = nil
  end

  def test_ValidASTNode_unary
    n = LibSBML::ASTNode.new(LibSBML::AST_FUNCTION_ABS)
    assert_equal false, (n.isWellFormedASTNode())
    c = LibSBML::parseFormula("c")
    n.addChild(c)
    assert_equal true, n.isWellFormedASTNode()
    d = LibSBML::parseFormula("d")
    n.addChild(d)
    assert_equal false, (n.isWellFormedASTNode())
    n = nil
  end

end
