/**
 * \file    TestXMLNamespaces.c
 * \brief   XMLNamespaces unit tests
 * \author  Michael Hucka <mhucka@caltech.edu>
 *
 * $Id: TestXMLNamespaces.c 13523 2011-04-08 13:09:22Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/xml/test/TestXMLNamespaces.c $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <sbml/common/common.h>
#include <sbml/xml/XMLNamespaces.h>

#include <check.h>

#if __cplusplus
CK_CPPSTART
#endif

static XMLNamespaces_t *NS;

void
XMLNamespacesTest_setup (void)
{
  NS = XMLNamespaces_create();

  if (NS == NULL)
  {
    fail("XMLNamespacesTest_setup() failed to create a XMLNamespaces object.");
  }
}

void
XMLNamespacesTest_teardown (void)
{
  XMLNamespaces_free(NS);
}


START_TEST (test_XMLNamespaces_baseline)
{
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 1 );
}
END_TEST


START_TEST (test_XMLNamespaces_add)
{
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 1 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1");
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 0 );

  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 0 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1a");
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 0 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1a");
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 0 );


  fail_if( XMLNamespaces_getIndex(NS, "http://test1.org/") == -1);
}
END_TEST


START_TEST (test_XMLNamespaces_add1)
{
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 1 );

  int i = XMLNamespaces_add(NS, "http://test1.org/", "test1");

  fail_unless( i == LIBSBML_OPERATION_SUCCESS);
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  fail_unless( XMLNamespaces_isEmpty(NS) == 0 );
}
END_TEST


START_TEST (test_XMLNamespaces_get)
{
  XMLNamespaces_add(NS, "http://test1.org/", "test1");    /* index 0 */
  XMLNamespaces_add(NS, "http://test2.org/", "test2");    /* index 1 */
  XMLNamespaces_add(NS, "http://test3.org/", "test3");    /* index 2 */
  XMLNamespaces_add(NS, "http://test4.org/", "test4");    /* index 3 */
  XMLNamespaces_add(NS, "http://test5.org/", "test5");    /* index 4 */
  XMLNamespaces_add(NS, "http://test6.org/", "test6");    /* index 5 */
  XMLNamespaces_add(NS, "http://test7.org/", "test7");    /* index 6 */
  XMLNamespaces_add(NS, "http://test8.org/", "test8");    /* index 7 */
  XMLNamespaces_add(NS, "http://test9.org/", "test9");    /* index 8 */

  fail_unless( XMLNamespaces_getLength(NS) == 9 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 9 );

  fail_unless( XMLNamespaces_getIndex(NS, "http://test1.org/") == 0 );
  fail_unless( strcmp(XMLNamespaces_getPrefix(NS, 1), "test2") == 0 );
  fail_unless( strcmp(XMLNamespaces_getPrefixByURI(NS, "http://test1.org/"),
		      "test1") == 0 );
  fail_unless( strcmp(XMLNamespaces_getURI(NS, 1), "http://test2.org/") == 0 );
  fail_unless( strcmp(XMLNamespaces_getURIByPrefix(NS, "test2"),
		      "http://test2.org/") == 0 );

  fail_unless( XMLNamespaces_getIndex(NS, "http://test1.org/") ==  0 );
  fail_unless( XMLNamespaces_getIndex(NS, "http://test2.org/") ==  1 );
  fail_unless( XMLNamespaces_getIndex(NS, "http://test5.org/") ==  4 );
  fail_unless( XMLNamespaces_getIndex(NS, "http://test9.org/") ==  8 );
  fail_unless( XMLNamespaces_getIndex(NS, "http://testX.org/") == -1 );

  fail_unless( XMLNamespaces_hasURI(NS, "http://test1.org/") !=  0 );
  fail_unless( XMLNamespaces_hasURI(NS, "http://test2.org/") !=  0 );
  fail_unless( XMLNamespaces_hasURI(NS, "http://test5.org/") !=  0 );
  fail_unless( XMLNamespaces_hasURI(NS, "http://test9.org/") !=  0 );
  fail_unless( XMLNamespaces_hasURI(NS, "http://testX.org/") ==  0 );

  fail_unless( XMLNamespaces_getIndexByPrefix(NS, "test1") ==  0 );
  fail_unless( XMLNamespaces_getIndexByPrefix(NS, "test5") ==  4 );
  fail_unless( XMLNamespaces_getIndexByPrefix(NS, "test9") ==  8 );
  fail_unless( XMLNamespaces_getIndexByPrefix(NS, "testX") == -1 );

  fail_unless( XMLNamespaces_hasPrefix(NS, "test1") !=  0 );
  fail_unless( XMLNamespaces_hasPrefix(NS, "test5") !=  0 );
  fail_unless( XMLNamespaces_hasPrefix(NS, "test9") !=  0 );
  fail_unless( XMLNamespaces_hasPrefix(NS, "testX") ==  0 );

  fail_unless( XMLNamespaces_hasNS(NS, "http://test1.org/", "test1") !=  0 );
  fail_unless( XMLNamespaces_hasNS(NS, "http://test5.org/", "test5") !=  0 );
  fail_unless( XMLNamespaces_hasNS(NS, "http://test9.org/", "test9") !=  0 );
  fail_unless( XMLNamespaces_hasNS(NS, "http://testX.org/", "testX") ==  0 );
}
END_TEST


START_TEST (test_XMLNamespaces_remove)
{
  XMLNamespaces_add(NS, "http://test1.org/", "test1"); 
  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  XMLNamespaces_add(NS, "http://test3.org/", "test3"); 
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 5 );
  XMLNamespaces_remove(NS, 4);
  fail_unless( XMLNamespaces_getLength(NS) == 4 );
  XMLNamespaces_remove(NS, 3);
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  XMLNamespaces_remove(NS, 2);
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  XMLNamespaces_remove(NS, 1);
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 0 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1");
  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  XMLNamespaces_add(NS, "http://test3.org/", "test3");
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 5 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 4 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 2 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  XMLNamespaces_remove(NS, 0);
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
  fail_unless( XMLNamespaces_getNumNamespaces(NS) == 0 );

}
END_TEST


START_TEST (test_XMLNamespaces_remove_by_prefix)
{
  XMLNamespaces_add(NS, "http://test1.org/", "test1"); 
  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  XMLNamespaces_add(NS, "http://test3.org/", "test3"); 
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );
  XMLNamespaces_removeByPrefix(NS, "test1");
  fail_unless( XMLNamespaces_getLength(NS) == 4 );
  XMLNamespaces_removeByPrefix(NS, "test2");
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  XMLNamespaces_removeByPrefix(NS, "test3");
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  XMLNamespaces_removeByPrefix(NS, "test4");
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  XMLNamespaces_removeByPrefix(NS, "test5");
  fail_unless( XMLNamespaces_getLength(NS) == 0 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1");
  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  XMLNamespaces_add(NS, "http://test3.org/", "test3");
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );
  XMLNamespaces_removeByPrefix(NS, "test5");
  fail_unless( XMLNamespaces_getLength(NS) == 4 );
  XMLNamespaces_removeByPrefix(NS, "test4");
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  XMLNamespaces_removeByPrefix(NS, "test3");
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  XMLNamespaces_removeByPrefix(NS, "test2");
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  XMLNamespaces_removeByPrefix(NS, "test1");
  fail_unless( XMLNamespaces_getLength(NS) == 0 );

  XMLNamespaces_add(NS, "http://test1.org/", "test1"); 
  XMLNamespaces_add(NS, "http://test2.org/", "test2"); 
  XMLNamespaces_add(NS, "http://test3.org/", "test3");
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );
  XMLNamespaces_removeByPrefix(NS, "test3");
  fail_unless( XMLNamespaces_getLength(NS) == 4 );
  XMLNamespaces_removeByPrefix(NS, "test1");
  fail_unless( XMLNamespaces_getLength(NS) == 3 );
  XMLNamespaces_removeByPrefix(NS, "test4");
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  XMLNamespaces_removeByPrefix(NS, "test5");
  fail_unless( XMLNamespaces_getLength(NS) == 1 );
  XMLNamespaces_removeByPrefix(NS, "test2");
  fail_unless( XMLNamespaces_getLength(NS) == 0 );

}
END_TEST


START_TEST (test_XMLNamespaces_remove1)
{
  XMLNamespaces_add(NS, "http://test1.org/", "test1"); 
  XMLNamespaces_add(NS, "http://test2.org/", "test2");

  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  
  int i = XMLNamespaces_remove(NS, 4);
  
  fail_unless (i == LIBSBML_INDEX_EXCEEDS_SIZE );
  fail_unless( XMLNamespaces_getLength(NS) == 2 );
  
  i = XMLNamespaces_removeByPrefix(NS, "test4");

  fail_unless (i == LIBSBML_INDEX_EXCEEDS_SIZE );
  fail_unless( XMLNamespaces_getLength(NS) == 2 );

  i = XMLNamespaces_remove(NS, 1);

  fail_unless (i == LIBSBML_OPERATION_SUCCESS );
  fail_unless( XMLNamespaces_getLength(NS) == 1 );

  i = XMLNamespaces_removeByPrefix(NS, "test1");

  fail_unless (i == LIBSBML_OPERATION_SUCCESS );
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
}
END_TEST


START_TEST (test_XMLNamespaces_clear)
{
  XMLNamespaces_add(NS, "http://test1.org/", "test1"); 
  XMLNamespaces_add(NS, "http://test2.org/", "test2");
  XMLNamespaces_add(NS, "http://test3.org/", "test3"); 
  XMLNamespaces_add(NS, "http://test4.org/", "test4");
  XMLNamespaces_add(NS, "http://test5.org/", "test5");

  fail_unless( XMLNamespaces_getLength(NS) == 5 );

  int i = XMLNamespaces_clear(NS);

  fail_unless( i == LIBSBML_OPERATION_SUCCESS);
  fail_unless( XMLNamespaces_getLength(NS) == 0 );
}
END_TEST

START_TEST (test_XMLNamespaces_accessWithNULL)
{
  fail_unless( XMLNamespaces_add(NULL, NULL, NULL) == LIBSBML_INVALID_OBJECT);
  fail_unless( XMLNamespaces_clear(NULL) == LIBSBML_OPERATION_FAILED);
  fail_unless( XMLNamespaces_clone(NULL) == NULL);

  XMLNamespaces_free(NULL);

  fail_unless( XMLNamespaces_getIndex(NULL, NULL) == -1);
  fail_unless( XMLNamespaces_getIndexByPrefix(NULL, NULL) == -1);
  fail_unless( XMLNamespaces_getLength(NULL) == 0);
  fail_unless( XMLNamespaces_getPrefix(NULL, 0) == NULL);
  fail_unless( XMLNamespaces_getPrefixByURI(NULL, NULL) == NULL);
  fail_unless( XMLNamespaces_getURI(NULL, 0) == NULL);
  fail_unless( XMLNamespaces_getURIByPrefix(NULL, NULL) == NULL);
  fail_unless( XMLNamespaces_hasNS(NULL, NULL, NULL) == 0);
  fail_unless( XMLNamespaces_hasPrefix(NULL, NULL) == 0);
  fail_unless( XMLNamespaces_hasURI(NULL, NULL) == 0);
  fail_unless( XMLNamespaces_isEmpty(NULL) == 1);
  fail_unless( XMLNamespaces_remove(NULL, 0) == LIBSBML_INVALID_OBJECT);
  fail_unless( XMLNamespaces_removeByPrefix(NULL, NULL) == LIBSBML_INVALID_OBJECT);
}
END_TEST

Suite *
create_suite_XMLNamespaces (void)
{
  Suite *suite = suite_create("XMLNamespaces");
  TCase *tcase = tcase_create("XMLNamespaces");

  tcase_add_checked_fixture( tcase,
                             XMLNamespacesTest_setup,
                             XMLNamespacesTest_teardown );

  tcase_add_test( tcase, test_XMLNamespaces_baseline         );
  tcase_add_test( tcase, test_XMLNamespaces_add              );
  tcase_add_test( tcase, test_XMLNamespaces_add1             );
  tcase_add_test( tcase, test_XMLNamespaces_get              );
  tcase_add_test( tcase, test_XMLNamespaces_remove           );
  tcase_add_test( tcase, test_XMLNamespaces_remove_by_prefix );
  tcase_add_test( tcase, test_XMLNamespaces_remove1          );
  tcase_add_test( tcase, test_XMLNamespaces_clear            );
  tcase_add_test( tcase, test_XMLNamespaces_accessWithNULL   );
  
  suite_add_tcase(suite, tcase);

  return suite;
}

#if __cplusplus
CK_CPPEND
#endif

