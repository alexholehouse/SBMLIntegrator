///  @file    TestSpeciesType.cs
///  @brief   SpeciesType unit tests
///  @author  Frank Bergmann (Csharp conversion)
///  @author  Akiya Jouraku (Csharp conversion)
///  @author  Sarah Keating 
/// 
///  $Id$
///  $HeadURL$
/// 
///  ====== WARNING ===== WARNING ===== WARNING ===== WARNING ===== WARNING ======
/// 
///  DO NOT EDIT THIS FILE.
/// 
///  This file was generated automatically by converting the file located at
///  src/sbml/test/TestSpeciesType.c
///  using the conversion program dev/utilities/translateTests/translateTests.pl.
///  Any changes made here will be lost the next time the file is regenerated.
/// 
///  -----------------------------------------------------------------------------
///  This file is part of libSBML.  Please visit http://sbml.org for more
///  information about SBML, and the latest version of libSBML.
/// 
///  Copyright 2005-2010 California Institute of Technology.
///  Copyright 2002-2005 California Institute of Technology and
///                      Japan Science and Technology Corporation.
///  
///  This library is free software; you can redistribute it and/or modify it
///  under the terms of the GNU Lesser General Public License as published by
///  the Free Software Foundation.  A copy of the license agreement is provided
///  in the file named "LICENSE.txt" included with this software distribution
///  and also available online as http://sbml.org/software/libsbml/license.html
///  -----------------------------------------------------------------------------


namespace LibSBMLCSTest.sbml {

  using libsbmlcs;

  using System;

  using System.IO;

  public class TestSpeciesType {
    public class AssertionError : System.Exception 
    {
      public AssertionError() : base()
      {
        
      }
    }


    static void assertTrue(bool condition)
    {
      if (condition == true)
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        return;
      }
      else if ( (a == null) || (b == null) )
      {
        throw new AssertionError();
      }
      else if (a.Equals(b))
      {
        return;
      }
  
      throw new AssertionError();
    }

    static void assertNotEquals(object a, object b)
    {
      if ( (a == null) && (b == null) )
      {
        throw new AssertionError();
      }
      else if ( (a == null) || (b == null) )
      {
        return;
      }
      else if (a.Equals(b))
      {
        throw new AssertionError();
      }
    }

    static void assertEquals(bool a, bool b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(bool a, bool b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertEquals(int a, int b)
    {
      if ( a == b )
      {
        return;
      }
      throw new AssertionError();
    }

    static void assertNotEquals(int a, int b)
    {
      if ( a != b )
      {
        return;
      }
      throw new AssertionError();
    }

    private SpeciesType CT;

    public void setUp()
    {
      CT = new  SpeciesType(2,4);
      if (CT == null);
      {
      }
    }

    public void tearDown()
    {
      CT = null;
    }

    public void test_SpeciesType_create()
    {
      assertTrue( CT.getTypeCode() == libsbml.SBML_SPECIES_TYPE );
      assertTrue( CT.getMetaId() == "" );
      assertTrue( CT.getNotes() == null );
      assertTrue( CT.getAnnotation() == null );
      assertTrue( CT.getId() == "" );
      assertTrue( CT.getName() == "" );
      assertEquals( false, CT.isSetId() );
      assertEquals( false, CT.isSetName() );
    }

    public void test_SpeciesType_createWithNS()
    {
      XMLNamespaces xmlns = new  XMLNamespaces();
      xmlns.add( "http://www.sbml.org", "testsbml");
      SBMLNamespaces sbmlns = new  SBMLNamespaces(2,2);
      sbmlns.addNamespaces(xmlns);
      SpeciesType object1 = new  SpeciesType(sbmlns);
      assertTrue( object1.getTypeCode() == libsbml.SBML_SPECIES_TYPE );
      assertTrue( object1.getMetaId() == "" );
      assertTrue( object1.getNotes() == null );
      assertTrue( object1.getAnnotation() == null );
      assertTrue( object1.getLevel() == 2 );
      assertTrue( object1.getVersion() == 2 );
      assertTrue( object1.getNamespaces() != null );
      assertTrue( object1.getNamespaces().getLength() == 2 );
      object1 = null;
    }

    public void test_SpeciesType_free_NULL()
    {
    }

    public void test_SpeciesType_setId()
    {
      string id =  "mitochondria";
      CT.setId(id);
      assertTrue(( id == CT.getId() ));
      assertEquals( true, CT.isSetId() );
      if (CT.getId() == id);
      {
      }
      CT.setId(CT.getId());
      assertTrue(( id == CT.getId() ));
      CT.setId("");
      assertEquals( false, CT.isSetId() );
      if (CT.getId() != null);
      {
      }
    }

    public void test_SpeciesType_setName()
    {
      string name =  "My_Favorite_Factory";
      CT.setName(name);
      assertTrue(( name == CT.getName() ));
      assertEquals( true, CT.isSetName() );
      if (CT.getName() == name);
      {
      }
      CT.setName(CT.getName());
      assertTrue(( name == CT.getName() ));
      CT.setName("");
      assertEquals( false, CT.isSetName() );
      if (CT.getName() != null);
      {
      }
    }

    public void test_SpeciesType_unsetName()
    {
      CT.setName( "name");
      assertTrue((  "name"      == CT.getName() ));
      assertEquals( true, CT.isSetName() );
      CT.unsetName();
      assertEquals( false, CT.isSetName() );
    }

  }
}
