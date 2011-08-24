/**
 * \file    TestSBMLConvertStrict.c
 * \brief   SBMLConvert unit tests for strict conversion
 * \author  Sarah Keating
 *
 * $Id: TestSBMLConvert.c 9087 2009-02-17 01:41:43Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-4/src/sbml/test/TestSBMLConvert.c $
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
#include <sbml/SBMLDocument.h>
#include <sbml/SBMLTypes.h>

#include <check.h>



#include <sbml/common/extern.h>

BEGIN_C_DECLS

START_TEST (test_SBMLConvertStrict_convertNonStrictUnits)
{
  SBMLDocument_t *d = SBMLDocument_createWithLevelAndVersion(2, 4);
  Model_t * m = SBMLDocument_createModel(d);
  
  /* create a compartment */
  Compartment_t * c = Model_createCompartment(m);
  Compartment_setId(c, "c");
  Compartment_setConstant(c, 0);

  /* create  a parameter with units mole */
  Parameter_t * p = Model_createParameter(m);
  Parameter_setId(p, "p");
  Parameter_setUnits(p, "mole");

  /* create a math element */
  ASTNode_t *math = SBML_parseFormula("p");

  /* create an assignment rule */
  Rule_t *ar = Model_createAssignmentRule(m);
  Rule_setVariable(ar, "c");
  Rule_setMath(ar, math);

  /* these should all fail since the model has bad units */

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 1) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );
  
  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 2) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 3) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );
  
  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 1, 2) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );

  SBMLDocument_free(d);
}
END_TEST


START_TEST (test_SBMLConvertStrict_convertNonStrictSBO)
{
  SBMLDocument_t *d = SBMLDocument_createWithLevelAndVersion(2, 4);
  Model_t * m = SBMLDocument_createModel(d);
  
  /* create a compartment with SBO */
  Compartment_t * c = Model_createCompartment(m);
  Compartment_setId(c, "c");
  Compartment_setConstant(c, 0);
  SBase_setSBOTerm((SBase_t *) (c), 64);

  /* conversion to L2V3 and L2V2 should fail due to bad SBO
   * but to L2V1 and L1 should pass as sbo terms not applicable
   */

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 3) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 2) == 0 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 4, NULL );

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 1) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 1, NULL );

  /* check that sbo term has been removed */
  Compartment_t *c1 = Model_getCompartment(SBMLDocument_getModel(d), 0);

  fail_unless (SBase_getSBOTerm((SBase_t *) (c1)) == -1, NULL );

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 1, 2) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 1, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 2, NULL );
  
  /* check that sbo term has been removed */
  Compartment_t *c2 = Model_getCompartment(SBMLDocument_getModel(d), 0);

  fail_unless (SBase_getSBOTerm((SBase_t *) (c2)) == -1, NULL );

  SBMLDocument_free(d);
}
END_TEST


START_TEST (test_SBMLConvertStrict_convertToL1)
{
  SBMLDocument_t *d = SBMLDocument_createWithLevelAndVersion(2, 4);
  
  /* create model with metaid */
  Model_t * m = SBMLDocument_createModel(d);
  SBase_setMetaId((SBase_t *) (m), "_m");
  
  /* create a compartment with sbo*/
  Compartment_t * c = Model_createCompartment(m);
  Compartment_setId(c, "c");
  SBase_setSBOTerm((SBase_t *) (c), 240);

  /* create a species with hasOnlySubstanceUnits = true*/
  Species_t *s = Model_createSpecies(m);
  Species_setId(s, "s");
  Species_setCompartment(s, "c");
  Species_setHasOnlySubstanceUnits(s, 1);

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 1, 2) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 1, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 2, NULL );

  ///* check that attributes that are no longer valid have been removed */
  Model_t * m1 = SBMLDocument_getModel(d);

  fail_unless (SBase_getMetaId((SBase_t *) (m1)) == NULL);

  Compartment_t *c1 = Model_getCompartment(m1, 0);

  fail_unless (SBase_getSBOTerm((SBase_t *) (c1)) == -1, NULL );

  Species_t *s1 = Model_getSpecies(m1, 0);

  fail_unless (Species_getHasOnlySubstanceUnits(s1) == 0);

  SBMLDocument_free(d);
}
END_TEST


START_TEST (test_SBMLConvertStrict_convertSBO)
{
  SBMLDocument_t *d = SBMLDocument_createWithLevelAndVersion(2, 4);
  Model_t * m = SBMLDocument_createModel(d);
  
  /* create a compartment with SBO */
  Compartment_t * c = Model_createCompartment(m);
  Compartment_setId(c, "c");
  SBase_setSBOTerm((SBase_t *) (c), 240);

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 3) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 3, NULL );
  
  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 2) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 2, NULL );

  /* check that sbo term has been removed */
  Compartment_t *c1 = Model_getCompartment(SBMLDocument_getModel(d), 0);

  fail_unless (SBase_getSBOTerm((SBase_t *) (c1)) == -1, NULL );

  SBMLDocument_free(d);
}
END_TEST


START_TEST (test_SBMLConvertStrict_convertL1ParamRule)
{
  SBMLDocument_t *d = SBMLDocument_createWithLevelAndVersion(1, 2);
  Model_t * m = SBMLDocument_createModel(d);
  
  /* create a compartment */
  Compartment_t * c = Model_createCompartment(m);
  Compartment_setId(c, "c");

  /* create  a parameter */
  Parameter_t * p = Model_createParameter(m);
  Parameter_setId(p, "p");
  Parameter_t * p1 = Model_createParameter(m);
  Parameter_setId(p1, "p1");

  /* create a math element */
  ASTNode_t *math = SBML_parseFormula("p");

  /* create an assignment rule */
  Rule_t *ar = Model_createAssignmentRule(m);
  Rule_setVariable(ar, "p1");
  Rule_setMath(ar, math);
  Rule_setUnits(ar, "mole");

  fail_unless( SBMLDocument_setLevelAndVersionStrict(d, 2, 1) == 1 );
  fail_unless( SBMLDocument_getLevel  (d) == 2, NULL );
  fail_unless( SBMLDocument_getVersion(d) == 1, NULL );

  Rule_t * r1 = Model_getRule(SBMLDocument_getModel(d), 0);

  fail_unless (Rule_getUnits(r1) == NULL );

  SBMLDocument_free(d);
}
END_TEST


Suite *
create_suite_SBMLConvertStrict (void) 
{ 
  Suite *suite = suite_create("SBMLConvertStrict");
  TCase *tcase = tcase_create("SBMLConvertStrict");


  tcase_add_test( tcase, test_SBMLConvertStrict_convertNonStrictUnits       );
  tcase_add_test( tcase, test_SBMLConvertStrict_convertNonStrictSBO         );
  tcase_add_test( tcase, test_SBMLConvertStrict_convertToL1                 );
  tcase_add_test( tcase, test_SBMLConvertStrict_convertSBO                  );
  tcase_add_test( tcase, test_SBMLConvertStrict_convertL1ParamRule          );

  suite_add_tcase(suite, tcase);

  return suite;
}

END_C_DECLS

