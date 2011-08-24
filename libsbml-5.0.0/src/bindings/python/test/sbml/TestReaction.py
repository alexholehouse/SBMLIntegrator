#
# @file    TestReaction.py
# @brief   SBML Reaction unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Ben Bornstein 
#
# $Id$
# $HeadURL$
#
# ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
#
# DO NOT EDIT THIS FILE.
#
# This file was generated automatically by converting the file located at
# src/sbml/test/TestReaction.c
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


class TestReaction(unittest.TestCase):

  global R
  R = None

  def setUp(self):
    self.R = libsbml.Reaction(2,4)
    if (self.R == None):
      pass    
    pass  

  def tearDown(self):
    _dummyList = [ self.R ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addProduct(self):
    sr = libsbml.SpeciesReference(2,4)
    sr.setSpecies( "s")
    self.R.addProduct(sr)
    self.assert_( self.R.getNumReactants() == 0 )
    self.assert_( self.R.getNumProducts() == 1 )
    self.assert_( self.R.getNumModifiers() == 0 )
    _dummyList = [ sr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_addReactant(self):
    sr = libsbml.SpeciesReference(2,4)
    sr.setSpecies( "s")
    self.R.addReactant(sr)
    self.assert_( self.R.getNumReactants() == 1 )
    self.assert_( self.R.getNumProducts() == 0 )
    self.assert_( self.R.getNumModifiers() == 0 )
    _dummyList = [ sr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_create(self):
    self.assert_( self.R.getTypeCode() == libsbml.SBML_REACTION )
    self.assert_( self.R.getMetaId() == "" )
    self.assert_( self.R.getNotes() == None )
    self.assert_( self.R.getAnnotation() == None )
    self.assert_( self.R.getId() == "" )
    self.assert_( self.R.getName() == "" )
    self.assert_( self.R.getKineticLaw() == None )
    self.assert_( self.R.getReversible() != False )
    self.assert_( self.R.getFast() == False )
    self.assertEqual( False, self.R.isSetId() )
    self.assertEqual( False, self.R.isSetName() )
    self.assertEqual( False, self.R.isSetKineticLaw() )
    self.assertEqual( False, self.R.isSetFast() )
    self.assertEqual( True, self.R.isSetReversible() )
    self.assert_( self.R.getNumReactants() == 0 )
    self.assert_( self.R.getNumProducts() == 0 )
    self.assert_( self.R.getNumModifiers() == 0 )
    pass  

  def test_Reaction_createWithNS(self):
    xmlns = libsbml.XMLNamespaces()
    xmlns.add( "http://www.sbml.org", "testsbml")
    sbmlns = libsbml.SBMLNamespaces(2,1)
    sbmlns.addNamespaces(xmlns)
    object = libsbml.Reaction(sbmlns)
    self.assert_( object.getTypeCode() == libsbml.SBML_REACTION )
    self.assert_( object.getMetaId() == "" )
    self.assert_( object.getNotes() == None )
    self.assert_( object.getAnnotation() == None )
    self.assert_( object.getLevel() == 2 )
    self.assert_( object.getVersion() == 1 )
    self.assert_( object.getNamespaces() != None )
    self.assert_( object.getNamespaces().getLength() == 2 )
    _dummyList = [ object ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_free_NULL(self):
    _dummyList = [ None ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_getProduct(self):
    sr1 = libsbml.SpeciesReference(2,4)
    sr2 = libsbml.SpeciesReference(2,4)
    sr1.setSpecies( "P1")
    sr2.setSpecies( "P2")
    self.R.addProduct(sr1)
    self.R.addProduct(sr2)
    _dummyList = [ sr1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ sr2 ]; _dummyList[:] = []; del _dummyList
    self.assert_( self.R.getNumReactants() == 0 )
    self.assert_( self.R.getNumProducts() == 2 )
    self.assert_( self.R.getNumModifiers() == 0 )
    sr1 = self.R.getProduct(0)
    sr2 = self.R.getProduct(1)
    self.assert_((  "P1" == sr1.getSpecies() ))
    self.assert_((  "P2" == sr2.getSpecies() ))
    pass  

  def test_Reaction_getProductById(self):
    sr1 = libsbml.SpeciesReference(2,4)
    sr1.setSpecies( "P1")
    sr2 = libsbml.SpeciesReference(2,4)
    sr2.setSpecies( "P1")
    self.R.addProduct(sr1)
    self.R.addProduct(sr2)
    self.assert_( self.R.getNumReactants() == 0 )
    self.assert_( self.R.getNumProducts() == 2 )
    self.assert_( self.R.getNumModifiers() == 0 )
    self.assert_( self.R.getProduct( "P1") != sr1 )
    self.assert_( self.R.getProduct( "P2") != sr2 )
    self.assert_( self.R.getProduct( "P3") == None )
    _dummyList = [ sr1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ sr2 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_getReactant(self):
    sr1 = libsbml.SpeciesReference(2,4)
    sr2 = libsbml.SpeciesReference(2,4)
    sr1.setSpecies( "R1")
    sr2.setSpecies( "R2")
    self.R.addReactant(sr1)
    self.R.addReactant(sr2)
    _dummyList = [ sr1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ sr2 ]; _dummyList[:] = []; del _dummyList
    self.assert_( self.R.getNumReactants() == 2 )
    self.assert_( self.R.getNumProducts() == 0 )
    self.assert_( self.R.getNumModifiers() == 0 )
    sr1 = self.R.getReactant(0)
    sr2 = self.R.getReactant(1)
    self.assert_((  "R1" == sr1.getSpecies() ))
    self.assert_((  "R2" == sr2.getSpecies() ))
    pass  

  def test_Reaction_getReactantById(self):
    sr1 = libsbml.SpeciesReference(2,4)
    sr1.setSpecies( "R1")
    sr2 = libsbml.SpeciesReference(2,4)
    sr2.setSpecies( "R2")
    self.R.addReactant(sr1)
    self.R.addReactant(sr2)
    self.assert_( self.R.getNumReactants() == 2 )
    self.assert_( self.R.getNumProducts() == 0 )
    self.assert_( self.R.getNumModifiers() == 0 )
    self.assert_( self.R.getReactant( "R1") != sr1 )
    self.assert_( self.R.getReactant( "R2") != sr2 )
    self.assert_( self.R.getReactant( "R3") == None )
    _dummyList = [ sr1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ sr2 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_removeProduct(self):
    o1 = self.R.createProduct()
    o2 = self.R.createProduct()
    o3 = self.R.createProduct()
    o3.setSpecies("test")
    self.assert_( self.R.removeProduct(0) == o1 )
    self.assert_( self.R.getNumProducts() == 2 )
    self.assert_( self.R.removeProduct(0) == o2 )
    self.assert_( self.R.getNumProducts() == 1 )
    self.assert_( self.R.removeProduct("test") == o3 )
    self.assert_( self.R.getNumProducts() == 0 )
    _dummyList = [ o1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ o2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ o3 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_removeReactant(self):
    o1 = self.R.createReactant()
    o2 = self.R.createReactant()
    o3 = self.R.createReactant()
    o3.setSpecies("test")
    self.assert_( self.R.removeReactant(0) == o1 )
    self.assert_( self.R.getNumReactants() == 2 )
    self.assert_( self.R.removeReactant(0) == o2 )
    self.assert_( self.R.getNumReactants() == 1 )
    self.assert_( self.R.removeReactant("test") == o3 )
    self.assert_( self.R.getNumReactants() == 0 )
    _dummyList = [ o1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ o2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ o3 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_Reaction_setId(self):
    id =  "J1";
    self.R.setId(id)
    self.assert_(( id == self.R.getId() ))
    self.assertEqual( True, self.R.isSetId() )
    if (self.R.getId() == id):
      pass    
    self.R.setId(self.R.getId())
    self.assert_(( id == self.R.getId() ))
    self.R.setId("")
    self.assertEqual( False, self.R.isSetId() )
    if (self.R.getId() != None):
      pass    
    pass  

  def test_Reaction_setName(self):
    name =  "MapK_Cascade";
    self.R.setName(name)
    self.assert_(( name == self.R.getName() ))
    self.assertEqual( True, self.R.isSetName() )
    if (self.R.getName() == name):
      pass    
    self.R.setName(self.R.getName())
    self.assert_(( name == self.R.getName() ))
    self.R.setName("")
    self.assertEqual( False, self.R.isSetName() )
    if (self.R.getName() != None):
      pass    
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestReaction))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
