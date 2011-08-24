///  @file    TestDate_newSetters.cs
///  @brief   Date unit tests
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
///  src/sbml/test/TestDate_newSetters.c
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


namespace LibSBMLCSTest.annotation {

  using libsbmlcs;

  using System;

  using System.IO;

  public class TestDate_newSetters {
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


    public void test_Date_setDateAsString()
    {
      Date date = new  Date(2007,10,23,14,15,16,1,3,0);
      assertTrue( date != null );
      int i = date.setDateAsString( "20081-12-30T12:15:45+02:00");
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue((  
      i = date.setDateAsString( "200-12-30T12:15:45+02:00");
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue((  
      i = date.setDateAsString("");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue((  
      i = date.setDateAsString( "2008-12-30T12:15:45+02:00");
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getYear() == 2008 );
      assertTrue( date.getMonth() == 12 );
      assertTrue( date.getDay() == 30 );
      assertTrue( date.getHour() == 12 );
      assertTrue( date.getMinute() == 15 );
      assertTrue( date.getSecond() == 45 );
      assertTrue( date.getSignOffset() == 1 );
      assertTrue( date.getHoursOffset() == 2 );
      assertTrue( date.getMinutesOffset() == 0 );
      date = null;
    }

    public void test_Date_setDay()
    {
      Date date = new  Date(2005,2,12,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setDay(29);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getDay() == 1 );
      i = date.setDay(31);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getDay() == 1 );
      i = date.setDay(15);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getDay() == 15 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setHour()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setHour(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getHour() == 0 );
      i = date.setHour(12121);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getHour() == 0 );
      i = date.setHour(9);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getHour() == 9 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setHoursOffset()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setHoursOffset(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getHoursOffset() == 0 );
      i = date.setHoursOffset(11);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getHoursOffset() == 11 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setMinute()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setMinute(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMinute() == 0 );
      i = date.setMinute(12121);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMinute() == 0 );
      i = date.setMinute(32);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getMinute() == 32 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setMinutesOffset()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setMinutesOffset(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMinutesOffset() == 0 );
      i = date.setMinutesOffset(60);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMinutesOffset() == 0 );
      i = date.setMinutesOffset(45);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getMinutesOffset() == 45 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setMonth()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setMonth(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMonth() == 1 );
      i = date.setMonth(12121);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getMonth() == 1 );
      i = date.setMonth(11);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getMonth() == 11 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setSecond()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setSecond(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getSecond() == 0 );
      i = date.setSecond(12121);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getSecond() == 0 );
      i = date.setSecond(32);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getSecond() == 32 );
      assertTrue((  
      date = null;
    }

    public void test_Date_setYear()
    {
      Date date = new  Date(2005,12,30,12,15,45,1,2,0);
      assertTrue( date != null );
      int i = date.setYear(434);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getYear() == 2000 );
      i = date.setYear(12121);
      assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
      assertTrue( date.getYear() == 2000 );
      i = date.setYear(2008);
      assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
      assertTrue( date.getYear() == 2008 );
      assertTrue((  
      date = null;
    }

  }
}