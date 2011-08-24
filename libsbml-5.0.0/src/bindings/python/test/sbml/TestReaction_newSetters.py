#
# @file    TestReaction_newSetters.py
# @brief   Reaction unit tests for new set function API
#
# @author  Akiya Jouraku (Python conversion)
# @author  Sarah Keating 
#
# $Id$
# $HeadURL$
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/sbml/test/TestReaction_newSetters.c
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

import sys
import unittest
import libsbml


class TestReaction_newSetters(unittest.TestCase):

  global R
  R = None

  def setUp(self):
    self.R = libsbml.Reaction(1,2)
    if (self.R == None):
      pass    
    pass  

  def tearDown(self):
    _dummyList = [ self.R ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addProduct1(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(2,2)
    p1 = libsbml.SpeciesReference(2,2)
    p1.setSpecies( "k")
    p1.setId( "k1")
    i = m.addProduct(p)
    self.assert_( i == libsbml.LIBSBML_INVALID_OBJECT )
    p.setSpecies( "k")
    p.setId( "k1")
    i = m.addProduct(p)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( m.getNumProducts() == 1 )
    i = m.addProduct(p1)
    self.assert_( i == libsbml.LIBSBML_DUPLICATE_OBJECT_ID )
    self.assert_( m.getNumProducts() == 1 )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ p1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addProduct2(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(2,1)
    p.setSpecies( "k")
    i = m.addProduct(p)
    self.assert_( i == libsbml.LIBSBML_VERSION_MISMATCH )
    self.assert_( m.getNumProducts() == 0 )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addProduct3(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(1,2)
    p.setSpecies( "k")
    i = m.addProduct(p)
    self.assert_( i == libsbml.LIBSBML_LEVEL_MISMATCH )
    self.assert_( m.getNumProducts() == 0 )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addProduct4(self):
    m = libsbml.Reaction(2,2)
    p = None
    i = m.addProduct(p)
    self.assert_( i == libsbml.LIBSBML_OPERATION_FAILED )
    self.assert_( m.getNumProducts() == 0 )
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addReactant1(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(2,2)
    p1 = libsbml.SpeciesReference(2,2)
    p1.setSpecies( "k")
    p1.setId( "k1")
    i = m.addReactant(p)
    self.assert_( i == libsbml.LIBSBML_INVALID_OBJECT )
    p.setSpecies( "k")
    p.setId( "k1")
    i = m.addReactant(p)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( m.getNumReactants() == 1 )
    i = m.addReactant(p1)
    self.assert_( i == libsbml.LIBSBML_DUPLICATE_OBJECT_ID )
    self.assert_( m.getNumReactants() == 1 )
    _dummyList = [ p1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addReactant2(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(2,1)
    p.setSpecies( "k")
    i = m.addReactant(p)
    self.assert_( i == libsbml.LIBSBML_VERSION_MISMATCH )
    self.assert_( m.getNumReactants() == 0 )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addReactant3(self):
    m = libsbml.Reaction(2,2)
    p = libsbml.SpeciesReference(1,2)
    p.setSpecies( "k")
    i = m.addReactant(p)
    self.assert_( i == libsbml.LIBSBML_LEVEL_MISMATCH )
    self.assert_( m.getNumReactants() == 0 )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addReactant4(self):
    m = libsbml.Reaction(2,2)
    p = None
    i = m.addReactant(p)
    self.assert_( i == libsbml.LIBSBML_OPERATION_FAILED )
    self.assert_( m.getNumReactants() == 0 )
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_createKineticLaw(self):
    r = libsbml.Reaction(2,2)
    kl = r.createKineticLaw()
    self.assert_( r.isSetKineticLaw() == True )
    self.assert_( (kl).getLevel() == 2 )
    self.assert_( (kl).getVersion() == 2 )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_createProduct(self):
    m = libsbml.Reaction(2,2)
    p = m.createProduct()
    self.assert_( m.getNumProducts() == 1 )
    self.assert_( (p).getLevel() == 2 )
    self.assert_( (p).getVersion() == 2 )
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_createReactant(self):
    m = libsbml.Reaction(2,2)
    p = m.createReactant()
    self.assert_( m.getNumReactants() == 1 )
    self.assert_( (p).getLevel() == 2 )
    self.assert_( (p).getVersion() == 2 )
    _dummyList = [ m ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setFast1(self):
    i = self.R.setFast(True)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( self.R.getFast() == True )
    self.assertEqual( True, self.R.isSetFast() )
    i = self.R.setFast(False)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( self.R.getFast() == False )
    self.assertEqual( True, self.R.isSetFast() )
    i = self.R.unsetFast()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( self.R.getFast() == False )
    self.assertEqual( False, self.R.isSetFast() )
    pass  

  def test_Reaction_setFast2(self):
    R1 = libsbml.Reaction(2,4)
    i = R1.unsetFast()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( R1.getFast() == False )
    self.assertEqual( False, R1.isSetFast() )
    pass  

  def test_Reaction_setId1(self):
    i = self.R.setId( "1cell")
    self.assert_( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE )
    self.assertEqual( False, self.R.isSetId() )
    pass  

  def test_Reaction_setId2(self):
    i = self.R.setId( "cell")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, self.R.isSetId() )
    self.assert_((  "cell"  == self.R.getId() ))
    i = self.R.setId("")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetId() )
    pass  

  def test_Reaction_setKineticLaw1(self):
    kl = libsbml.KineticLaw(2,1)
    i = self.R.setKineticLaw(kl)
    self.assert_( i == libsbml.LIBSBML_LEVEL_MISMATCH )
    self.assertEqual( False, self.R.isSetKineticLaw() )
    _dummyList = [ kl ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setKineticLaw2(self):
    kl = libsbml.KineticLaw(1,1)
    i = self.R.setKineticLaw(kl)
    self.assert_( i == libsbml.LIBSBML_VERSION_MISMATCH )
    self.assertEqual( False, self.R.isSetKineticLaw() )
    _dummyList = [ kl ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setKineticLaw3(self):
    kl = libsbml.KineticLaw(1,2)
    i = self.R.setKineticLaw(kl)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, self.R.isSetKineticLaw() )
    _dummyList = [ kl ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setKineticLaw4(self):
    i = self.R.setKineticLaw(None)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetKineticLaw() )
    i = self.R.unsetKineticLaw()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetKineticLaw() )
    pass  

  def test_Reaction_setName1(self):
    i = self.R.setName( "cell")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, self.R.isSetName() )
    i = self.R.unsetName()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, self.R.isSetName() )
    pass  

  def test_Reaction_setName2(self):
    p = libsbml.Reaction(2,2)
    i = p.setName( "1cell")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( True, p.isSetName() )
    i = p.unsetName()
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, p.isSetName() )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setName3(self):
    p = libsbml.Reaction(2,2)
    i = p.setName("")
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assertEqual( False, p.isSetName() )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setReversible1(self):
    i = self.R.setReversible(True)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( self.R.getReversible() == True )
    i = self.R.setReversible(False)
    self.assert_( i == libsbml.LIBSBML_OPERATION_SUCCESS )
    self.assert_( self.R.getReversible() == False )
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestReaction_newSetters))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
