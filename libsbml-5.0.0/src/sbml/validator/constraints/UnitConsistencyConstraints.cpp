/**
 * @cond doxygen-libsbml-internal
 *
 * @file    UnitConsistencyConstraints.cpp
 * @brief   UnitConsistency check constraints.  See SBML Wiki
 * @author  Ben Bornstein
 *
 * $Id: UnitConsistencyConstraints.cpp 13010 2011-02-22 13:43:02Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/validator/constraints/UnitConsistencyConstraints.cpp $
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

#ifndef AddingConstraintsToValidator

//#include <string>

#include <sbml/SBMLTypes.h>
#include <sbml/SBMLTypeCodes.h>
#include <sbml/SBO.h>
#include <sbml/validator/VConstraint.h>
#include <sbml/units/UnitFormulaFormatter.h>
#include <sbml/units/FormulaUnitsData.h>

#include <sbml/util/List.h>
#include <sbml/util/memory.h>

#include "CompartmentOutsideCycles.h"
#include "FunctionDefinitionVars.h"

#include "UniqueIdsForUnitDefinitions.h"
#include "UniqueIdsInKineticLaw.h"
#include "UniqueIdsInModel.h"
#include "UniqueVarsInEventAssignments.h"
#include "UniqueVarsInRules.h"
#include "UniqueVarsInEventsAndRules.h"
#include "UniqueMetaId.h"

#include "FunctionReferredToExists.h"
#include "SpeciesReactionOrRule.h"
#include "UniqueSpeciesTypesInCompartment.h"
#include "UniqueSymbolsInInitialAssignments.h"
#include "UniqueVarsInInitialAssignmentsAndRules.h"
#include "StoichiometryMathVars.h"
#include "KineticLawVars.h"
#include "AssignmentCycles.h"

//#include "FormulaUnitsCheck.h"

#include "PowerUnitsCheck.h"
#include "ExponentUnitsCheck.h"
#include "ArgumentsUnitsCheck.h"
#include "ArgumentsUnitsCheckWarnings.h"

#include "LogicalArgsMathCheck.h"
#include "NumericArgsMathCheck.h"
#include "PieceBooleanMathCheck.h"
#include "PiecewiseValueMathCheck.h"
#include "EqualityArgsMathCheck.h"
#include "FunctionApplyMathCheck.h"
#include "CiElementMathCheck.h"
#include "LambdaMathCheck.h"
#include "NumericReturnMathCheck.h"
#include "LocalParameterMathCheck.h"
#include "NumberArgsMathCheck.h"
#include "KineticLawUnitsCheck.h"

#include "OverDeterminedCheck.h"

#endif


#include <sbml/validator/ConstraintMacros.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond */

/* check to report the use of parameters/numbers with undeclared units */
START_CONSTRAINT (99505, AssignmentRule, ar)
{
  const string& variable = ar.getVariable();

  pre ( ar.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_ASSIGNMENT_RULE);

  pre ( formulaUnits != NULL );

  char * formula = SBML_formulaToString(ar.getMath());
  msg = "The units of the <assignmentRule> <math> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);
  
  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT

START_CONSTRAINT (99505, RateRule, rr)
{
  const string& variable = rr.getVariable();

  pre ( rr.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_RATE_RULE);

  pre ( formulaUnits != NULL );

  char * formula = SBML_formulaToString(rr.getMath());
  msg = "The units of the <rateRule> <math> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT


START_CONSTRAINT (99505, InitialAssignment, ia)
{
  const string& variable = ia.getSymbol();

  pre ( ia.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_INITIAL_ASSIGNMENT);

  pre ( formulaUnits != NULL );

  char * formula = SBML_formulaToString(ia.getMath());
  msg = "The units of the <initialAssignment> <math> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT


START_CONSTRAINT (99505, KineticLaw, kl)
{
  pre ( kl.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                            m.getFormulaUnitsData(kl.getInternalId(), SBML_KINETIC_LAW);
  pre ( formulaUnits != NULL );

  char * formula = SBML_formulaToString(kl.getMath());
  msg = "The units of the <kineticLaw> <math> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT

  
START_CONSTRAINT (99505, Event, e)
{
  pre ( e.isSetDelay() == 1 );

  const FormulaUnitsData * formulaUnits = 
                                  m.getFormulaUnitsData(e.getId(), SBML_EVENT);

  pre ( formulaUnits != 0 );

  char * formula = SBML_formulaToString(e.getDelay()->getMath());
  msg = "The units of the <event> <delay> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT

  
START_CONSTRAINT (99505, Priority, e)
{
  const FormulaUnitsData * formulaUnits = 
                                  m.getFormulaUnitsData(e.getInternalId(), SBML_PRIORITY);

  pre ( formulaUnits != NULL );

  char * formula = SBML_formulaToString(e.getMath());
  msg = "The units of the <event> <priority> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT

  
START_CONSTRAINT (99505, EventAssignment, ea)
{
  EventAssignment *pEa = const_cast<EventAssignment *> (&ea);
  std::string eId = 
    static_cast <Event *> (pEa->getAncestorOfType(SBML_EVENT))->getId();
  const string& variable = ea.getVariable() + eId;

  pre ( ea.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                         m.getFormulaUnitsData(variable, SBML_EVENT_ASSIGNMENT);

  pre ( formulaUnits != NULL );
  
  char * formula = SBML_formulaToString(ea.getMath());
  msg = "The units of the <eventAssignment> <math> expression '";
  msg += formula;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";
  safe_free(formula);

  inv( !formulaUnits->getContainsUndeclaredUnits());
}
END_CONSTRAINT

START_CONSTRAINT (99505, Compartment, c)
{
  pre ( c.getLevel() > 2);
  pre ( c.getDerivedUnitDefinition() != NULL);
  
  msg = "The units of the <compartment> '";
  msg += c.getId() ;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";

  inv( !(c.getDerivedUnitDefinition()->getNumUnits() == 0));
}
END_CONSTRAINT

START_CONSTRAINT (99505, Species, s)
{
  pre ( s.getLevel() > 2);
  pre ( s.getDerivedUnitDefinition() != NULL);
  
  msg = "The units of the <species> '";
  msg += s.getId() ;
  msg += "' cannot be fully checked. Unit consistency reported as either no errors ";
  msg += "or further unit errors related to this object may not be accurate.";

  inv( !(s.getDerivedUnitDefinition()->getNumUnits() == 0));
}
END_CONSTRAINT

// General Unit validation


EXTERN_CONSTRAINT(10501, ArgumentsUnitsCheck)
EXTERN_CONSTRAINT(99502, ArgumentsUnitsCheckWarnings)
EXTERN_CONSTRAINT(99503, PowerUnitsCheck)
EXTERN_CONSTRAINT(99504, ExponentUnitsCheck)

EXTERN_CONSTRAINT(10503, KineticLawUnitsCheck)

// Specific unit checks 

START_CONSTRAINT (10511, AssignmentRule, ar)
{
  const string& variable = ar.getVariable();
  const Compartment* c = m.getCompartment(variable);

  pre ( c != NULL);
  pre ( ar.isSetMath() == 1 );

  //if (ar.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in an <assignmentRule> refers to a <compartment>, "
  //  //  "the units of the rule's right-hand side must be consistent with the "
  //  //  "units of that compartment's size. (References: L2V2 Section 4.11.3; "
  //  //  "L2V3 Section 4.11.3.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that in a <compartmentVolumeRule>, "
  //    "the units of the rule's right-hand side must be consistent with the "
  //    "units of that compartment's volume. Expected units are ";
  //  msg += printUnits(variableUnits->getUnitDefinition());
  //  msg += " but the units returned by the <compartmentVolumeRule>'s formula are ";
  //  msg += printUnits(formulaUnits->getUnitDefinition());
  //  msg += ".";
  //}


  const FormulaUnitsData * variableUnits = 
                              m.getFormulaUnitsData(variable, SBML_COMPARTMENT);
  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_ASSIGNMENT_RULE);

  pre ( formulaUnits != NULL );
  pre ( variableUnits != NULL); 

  /* in level 3 need to check that the compartment has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre ( !formulaUnits->getContainsUndeclaredUnits()
	|| (formulaUnits->getContainsUndeclaredUnits()
	    && formulaUnits->getCanIgnoreUndeclaredUnits()) );

  if (ar.getLevel() == 1)
  {
    msg =
      "In a level 1 model this implies that in a <compartmentVolumeRule>, "
      "the units of the rule's right-hand side must be consistent with the "
      "units of that <compartment>'s volume. Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <compartmentVolumeRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <assignmentRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);

}
END_CONSTRAINT


START_CONSTRAINT (10512, AssignmentRule, ar)
{
  const string& variable = ar.getVariable();
  const Species * s = m.getSpecies(variable);

  pre ( s != NULL);
  pre ( ar.isSetMath() == 1 );

  //if (ar.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in an <assignmentRule> refers to a <species>, the "
  //  //  "units of the rule's right-hand side must be consistent with the units "
  //  //  "of the species' quantity. (References: L2V2 Section 4.11.3; L2V3 "
  //  //  "Section 4.11.3.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that in a <speciesConcentrationRule>, the "
  //    "units of the rule's right-hand side must be consistent with the units "
  //    "of the species' quantity.";
  //}


  const FormulaUnitsData * variableUnits = 
                                  m.getFormulaUnitsData(variable, SBML_SPECIES);
  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_ASSIGNMENT_RULE);

  pre ( formulaUnits != NULL );
  pre ( variableUnits != NULL); 

  /* in level 3 need to check that the species has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  if (ar.getLevel() == 1)
  {
    msg =
      "In a level 1 model this implies that in a <speciesConcentrationRule>, "
      "the units of the rule's right-hand side must be consistent with the "
      "units of that <species> quantity. Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <speciesConcentrationRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <assignmentRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  //if (ar.getLevel() == 1)
  //{
  //  /* need to adapt for the fact that in level 1 the assignment rule was
  //   * for speciesConcetration although species only had substance units
  //   */

  //  inv (areEquivalent(formulaUnits->getUnitDefinition(), 
  //                      variableUnits->getL1SpeciesConcUnitDefinition()) == 1);

  //}
  //else
  //{
    inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                            variableUnits->getUnitDefinition()) == 1);
  //}
}
END_CONSTRAINT


START_CONSTRAINT (10513, AssignmentRule, ar)
{
  const string& variable = ar.getVariable();
  const Parameter* p = m.getParameter(variable);

  pre ( p != NULL);
  pre ( ar.isSetMath() == 1 );
  /* check that the parameter has units declared */
  pre ( p->isSetUnits());

  //if (ar.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in an <assignmentRule> refers to a <parameter>, the "
  //  //  "units of the rule's right-hand side must be consistent with the units "
  //  //  "declared for that parameter. (References: L2V2 Section 4.11.3; L2V3 "
  //  //  "Section 4.11.3.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that in a <parameterRule>, the "
  //    "units of the rule's right-hand side must be consistent with the units "
  //    "declared for that parameter.";
  //}

  const FormulaUnitsData * variableUnits = 
                                m.getFormulaUnitsData(variable, SBML_PARAMETER);
  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_ASSIGNMENT_RULE);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL); 

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  if (ar.getLevel() == 1)
  {
    msg =
      "In a level 1 model this implies that in a <parameterRule>, "
      "the units of the rule's right-hand side must be consistent with the "
      "units declared for that <parameter>. Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <parameterRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
    msg += " but the units returned by the <assignmentRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10514, AssignmentRule, ar)
{
  const string& variable = ar.getVariable();
  const SpeciesReference* sr = m.getSpeciesReference(variable);
  /* the getSpeciesReference function uses either the id or the species
   * field - so need to check that this is indeed a SpeciesReference
   * and not a Species we are dealing with
   */
  pre ( m.getSpecies(variable) == NULL);


  pre ( ar.getLevel() > 2);
  pre ( sr != NULL);
  pre ( ar.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                          m.getFormulaUnitsData(variable, SBML_ASSIGNMENT_RULE);

  pre ( formulaUnits != NULL );

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  " Expected units are dimensionless";
  msg += " but the units returned by the <assignmentRule>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";
  
  inv (formulaUnits->getUnitDefinition()->isVariantOfDimensionless());
}
END_CONSTRAINT


START_CONSTRAINT (10521, InitialAssignment, ia)
{
  const string& variable = ia.getSymbol();
  const Compartment* c = m.getCompartment(variable);

  pre ( c != NULL);
  pre ( ia.isSetMath() == 1 );

  //msg =
  //  "When the 'variable' in an <initialAssignment> refers to a "
  //  "<compartment>, the units of the <initialAssignment>'s <math> expression "
  //  "must be consistent with the units of that compartment's size. "
  //  "(References: L2V2 Section 4.10.4; L2V3 Section 4.10.)";


  const FormulaUnitsData * variableUnits = 
                              m.getFormulaUnitsData(variable, SBML_COMPARTMENT);
  const FormulaUnitsData * formulaUnits = 
                       m.getFormulaUnitsData(variable, SBML_INITIAL_ASSIGNMENT);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL); 

  /* in level 3 need to check that the compartment has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <initialAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10522, InitialAssignment, ia)
{
  const string& variable = ia.getSymbol();
  const Species * s = m.getSpecies(variable);

  pre ( s != NULL);
  pre ( ia.isSetMath() == 1 );

  //msg =
  //  "When the 'variable' in an <initialAssignment> refers to a <species>, "
  //  "the units of the <initialAssignment>'s <math> expression must be "
  //  "consistent with the units of that species' quantity. (References: L2V2 "
  //  "Section 4.10.4; L2V3 Section 4.11.3.)";
   

  const FormulaUnitsData * variableUnits = 
                                  m.getFormulaUnitsData(variable, SBML_SPECIES);
  const FormulaUnitsData * formulaUnits = 
                       m.getFormulaUnitsData(variable, SBML_INITIAL_ASSIGNMENT);

  pre ( formulaUnits != NULL );
  pre ( variableUnits != NULL); 

  /* in level 3 need to check that the species has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <initialAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10523, InitialAssignment, ia)
{
  const string& variable = ia.getSymbol();
  const Parameter* p = m.getParameter(variable);

  pre ( p != NULL);
  pre ( ia.isSetMath() == 1 );
  /* check that the parameter has units declared */
  pre ( p->isSetUnits());

  //msg =
  //  "When the 'variable' in an <initialAssignment> refers to a <parameter>, "
  //  "the units of the <initialAssignment>'s <math> expression must be "
  //  "consistent with the units declared for that parameter. (References: "
  //  "L2V2 Section 4.10.4; L2V3 Section 4.11.3.)";
   
  const FormulaUnitsData * variableUnits = 
                                m.getFormulaUnitsData(variable, SBML_PARAMETER);
  const FormulaUnitsData * formulaUnits = 
                       m.getFormulaUnitsData(variable, SBML_INITIAL_ASSIGNMENT);
  
  pre ( formulaUnits != NULL );
  pre ( variableUnits != NULL); 

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <initialAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10524, InitialAssignment, ia)
{
  const string& variable = ia.getSymbol();
  const SpeciesReference* sr = m.getSpeciesReference(variable);

  pre ( ia.getLevel() > 2);
  pre ( sr != NULL);
  pre ( ia.isSetMath() == 1 );

  /* the getSpeciesReference function uses either the id or the species
   * field - so need to check that this is indeed a SpeciesReference
   * and not a Species we are dealing with
   */
  pre ( m.getSpecies(variable) == NULL);

  const FormulaUnitsData * formulaUnits = 
                      m.getFormulaUnitsData(variable, SBML_INITIAL_ASSIGNMENT);

  pre ( formulaUnits != NULL );

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  " Expected units are dimensionless";
  msg += " but the units returned by the <initialAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";
  
  inv (formulaUnits->getUnitDefinition()->isVariantOfDimensionless());
}
END_CONSTRAINT


START_CONSTRAINT (10531, RateRule, rr)
{
  const string& variable = rr.getVariable();
  const Compartment* c = m.getCompartment(variable);

  pre ( c != NULL);
  pre ( rr.isSetMath() == 1 );

  //if (rr.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in a <rateRule> definition refers to a "
  //  //  "<compartment>, the units of the rule's right-hand side must be of the "
  //  //  "form _x per time_, where _x_ is either the 'units' in that "
  //  //  "<compartment> definition, or (in the absence of explicit units declared "
  //  //  "for the compartment size) the default units for that compartment, and "
  //  //  "_time_ refers to the units of time for the model. (References: L2V2 "
  //  //  "Section 4.11.4; L2V3 Section 4.11.4.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that "
  //    "when a <compartmentVolumeRule> definition is of type 'rate' "
  //    "the units of the rule's right-hand side must be of the "
  //    "form _x per time_, where _x_ is either the 'units' in that "
  //    "<compartment> definition, or (in the absence of explicit units declared "
  //    "for the compartment volume) the default units for that compartment, and "
  //    "_time_ refers to the units of time for the model.";
  //}
   

  const FormulaUnitsData * variableUnits = 
                              m.getFormulaUnitsData(variable, SBML_COMPARTMENT);
  const FormulaUnitsData * formulaUnits = 
                                m.getFormulaUnitsData(variable, SBML_RATE_RULE);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* in level 3 need to check that the compartment has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);
  /* in L3 need to check that time units were set */
  pre ( variableUnits->getPerTimeUnitDefinition()->getNumUnits() > 0);


  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  if (rr.getLevel() == 1)
  {
    msg =
    "In a level 1 model this implies that "
    "when a <compartmentVolumeRule> definition is of type 'rate' "
    "the units of the rule's right-hand side must be of the "
    "form _x per time_, where _x_ is either the 'units' in that "
    "<compartment> definition, or (in the absence of explicit units declared "
    "for the compartment volume) the default units for that compartment, and "
    "_time_ refers to the units of time for the model. Expected units are ";    
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <compartmentVolumeRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <rateRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                               variableUnits->getPerTimeUnitDefinition()) == 1);

}
END_CONSTRAINT


START_CONSTRAINT (10532, RateRule, rr)
{
  const string& variable = rr.getVariable();
  const Species* s = m.getSpecies(variable);

  pre ( s != NULL);
  pre ( rr.isSetMath() == 1 );

  //if (rr.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in a <rateRule> definition refers to a <species>, "
  //  //  "the units of the rule's right-hand side must be of the form _x per "
  //  //  "time_, where _x_ is the units of that species' quantity, and _time_ "
  //  //  "refers to the units of time for the model. (References: L2V2 Section "
  //  //  "4.11.4; L2V3 Section 4.11.4.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that "
  //    "when a <speciesConcentrationRule> definition is of type 'rate' "
  //    "the units of the rule's right-hand side must be of the form _x per "
  //    "time_, where _x_ is the units of that species' quantity, and _time_ "
  //    "refers to the units of time for the model.";
  //}
 
  const FormulaUnitsData * variableUnits = 
                                  m.getFormulaUnitsData(variable, SBML_SPECIES);
  const FormulaUnitsData * formulaUnits = 
                                m.getFormulaUnitsData(variable, SBML_RATE_RULE);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* in level 3 need to check that the species has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);
  /* in L3 need to check that time units were set */
  pre ( variableUnits->getPerTimeUnitDefinition()->getNumUnits() > 0);


  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  if (rr.getLevel() == 1)
  {
    msg =
    "In a level 1 model this implies that "
    "when a <speciesConcentrationRule> definition is of type 'rate' "
    "the units of the rule's right-hand side must be of the form _x per "
    "time_, where _x_ is the units of that species' quantity, and _time_ "
    "refers to the units of time for the model. Expected units are ";    
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <speciesConcentrationRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <rateRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  //if (rr.getLevel() == 1)
  //{
  //  /* need to adapt for the fact that in level 1 the assignment rule was
  //   * for speciesConcetration although species only had substance units
  //   */

  //  inv (areEquivalent(formulaUnits->getUnitDefinition(), 
  //              variableUnits->getL1SpeciesConcPerTimeUnitDefinition()) == 1);

  //}
  //else
  //{
    inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                            variableUnits->getPerTimeUnitDefinition()) == 1);
  //}
}
END_CONSTRAINT


START_CONSTRAINT (10533, RateRule, rr)
{
  const string& variable = rr.getVariable();
  const Parameter* p = m.getParameter(variable);

  pre ( p != NULL);
  pre ( rr.isSetMath() == 1 );
  /* check that the parameter has units declared */
  pre ( p->isSetUnits());

  //if (rr.getLevel() == 2)
  //{
  //  //msg =
  //  //  "When the 'variable' in a <rateRule> definition refers to a <parameter>, "
  //  //  "the units of the rule's right-hand side must be of the form _x per "
  //  //  "time_, where _x_ is the 'units' in that <parameter> definition, and "
  //  //  "_time_ refers to the units of time for the model. (References: L2V2 "
  //  //  "Section 4.11.4; L2V3 Section 4.11.4.)";
  //}
  //else
  //{
  //  msg =
  //    "In a level 1 model this implies that "
  //    "when a <parameterRule> definition has type 'rate' "
  //    "the units of the rule's right-hand side must be of the form _x per "
  //    "time_, where _x_ is the 'units' in that <parameter> definition, and "
  //    "_time_ refers to the units of time for the model.";
  //}

  const FormulaUnitsData * variableUnits = 
                                m.getFormulaUnitsData(variable, SBML_PARAMETER);
  const FormulaUnitsData * formulaUnits = 
                                m.getFormulaUnitsData(variable, SBML_RATE_RULE);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL); 

  /* in L3 need to check that time units were set */
  pre ( variableUnits->getPerTimeUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  if (rr.getLevel() == 1)
  {
    msg =
    "In a level 1 model this implies that "
    "when a <parameterRule> definition has type 'rate' "
    "the units of the rule's right-hand side must be of the form _x per "
    "time_, where _x_ is the 'units' in that <parameter> definition, and "
    "_time_ refers to the units of time for the model. Expected units are ";    
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <parameterRule>'s formula are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }
  else
  {
    msg =  " Expected units are ";
    msg += UnitDefinition::printUnits(variableUnits->getPerTimeUnitDefinition());
    msg += " but the units returned by the <rateRule>'s <math> expression are ";
    msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
    msg += ".";
  }

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                              variableUnits->getPerTimeUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10534, RateRule, rr)
{
  const string& variable = rr.getVariable();
  const SpeciesReference* sr = m.getSpeciesReference(variable);
  /* the getSpeciesReference function uses either the id or the species
   * field - so need to check that this is indeed a SpeciesReference
   * and not a Species we are dealing with
   */
  pre ( m.getSpecies(variable) == NULL);

  pre ( rr.getLevel() > 2);
  pre ( sr != NULL);
  pre ( rr.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                      m.getFormulaUnitsData(variable, SBML_RATE_RULE);
  const FormulaUnitsData * variableUnits = 
                      m.getFormulaUnitsData(variable, SBML_SPECIES_REFERENCE);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* in L3 need to check that time units were set */
  pre ( variableUnits->getPerTimeUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  " Expected units are dimensionless per time";
  msg += " but the units returned by the <rateRule>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";
  
  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                              variableUnits->getPerTimeUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10541, KineticLaw, kl)
{
  //msg =
  //  "The units of the 'math' formula in a <kineticLaw> definition must be "
  //  "the equivalent of _substance per time_. (References: L2V2 Section "
  //  "4.13.5.)";

  pre ( kl.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                            m.getFormulaUnitsData(kl.getInternalId(), SBML_KINETIC_LAW);
  const FormulaUnitsData * variableUnits = 
                           m.getFormulaUnitsData("subs_per_time", SBML_UNKNOWN);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  /* check that the variable is okay 
     ie has no parameters with undeclared units 
     IT MIGHT IN L3 */
  pre (!variableUnits->getContainsUndeclaredUnits()
    || (variableUnits->getContainsUndeclaredUnits() &&
        variableUnits->getCanIgnoreUndeclaredUnits()));

  if (m.getLevel() > 2)
  {
  msg =
    "In level 3 the expected units are extent_per_time.";
  msg +=  " Expected units are ";
  }
  else
  {
  msg =  "Expected units are ";
  }
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <kineticLaw>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";


  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                                      variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10542, Species, s)
{
  pre (s.getLevel() > 2);
  pre (m.getSpeciesReference(s.getId()) != NULL);

  //msg =
  //  "The units of the 'math' formula in a <kineticLaw> definition must be "
  //  "the equivalent of _substance per time_. (References: L2V2 Section "
  //  "4.13.5.)";

  const FormulaUnitsData * formulaUnits = 
                            m.getFormulaUnitsData(s.getId()+"subs", 
                                                  SBML_SPECIES);
  const FormulaUnitsData * variableUnits = 
                           m.getFormulaUnitsData(s.getId()+"extent", 
                                                 SBML_SPECIES);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  /* check that the variable is okay 
     ie has no parameters with undeclared units 
     IT MIGHT IN L3 */
  pre (!variableUnits->getContainsUndeclaredUnits()
    || (variableUnits->getContainsUndeclaredUnits() &&
        variableUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(formulaUnits->getSpeciesSubstanceUnitDefinition());
  msg += " but the units returned by the the 'extent times conversionFactor' expression are ";
  msg += UnitDefinition::printUnits(variableUnits->getSpeciesExtentUnitDefinition());
  msg += ".";


  inv (UnitDefinition::areEquivalent(formulaUnits->getSpeciesSubstanceUnitDefinition(), 
                                      variableUnits->getSpeciesExtentUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10551, Event, e)
{
  //msg =
  //  "When a value for <delay> is given in a <event> definition, the units of "
  //  "the delay formula must correspond to either the value of 'timeUnits' in "
  //  "the <event> or (if no 'timeUnits' are given), the model's default units "
  //  "of time. (References: L2V2 Section 4.14; L2V3 Section 4.14.3.)";

  pre ( e.isSetDelay() == 1 );

  const FormulaUnitsData * formulaUnits = 
                                  m.getFormulaUnitsData(e.getId(), SBML_EVENT);

  pre ( formulaUnits != NULL );

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(formulaUnits->getEventTimeUnitDefinition());
  msg += " but the units returned by the <event>'s <delay> are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areIdentical(formulaUnits->getUnitDefinition(), 
                              formulaUnits->getEventTimeUnitDefinition()) == 1);

}
END_CONSTRAINT


START_CONSTRAINT (10561, EventAssignment, ea)
{
  //msg =
  //  "When the 'variable' in an <eventAssignment> refers to a <compartment>, "
  //  "the units of the <eventAssignment>'s <math> expression must be consistent "
  //  "with the units of that compartment's size. (References: L2V2 Section "
  //  "4.14.2; L2V3 Section 4.14.4.)";

  EventAssignment *pEa = const_cast<EventAssignment *> (&ea);
  std::string eId = 
    static_cast <Event *> (pEa->getAncestorOfType(SBML_EVENT))->getId();
  const string& variable = ea.getVariable();
  const Compartment* c = m.getCompartment(variable);

  pre ( c != NULL);
  pre ( ea.isSetMath() == 1 );

  const FormulaUnitsData * variableUnits = 
                              m.getFormulaUnitsData(variable, SBML_COMPARTMENT);
  const FormulaUnitsData * formulaUnits = 
                         m.getFormulaUnitsData(variable+eId, SBML_EVENT_ASSIGNMENT);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* in level 3 need to check that the compartment has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <eventAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);

}
END_CONSTRAINT


START_CONSTRAINT (10562, EventAssignment, ea)
{
  //msg =
  //  "When the 'variable' in an <eventAssignment> refers to a <species>, the "
  //  "units of the <eventAssignment>'s <math> expression must be consistent "
  //  "with the units of the species' quantity. (References: L2V2 Section "
  //  "4.14.2; L2V3 Section 4.14.4.)";
   
  EventAssignment *pEa = const_cast<EventAssignment *> (&ea);
  std::string eId = 
    static_cast <Event *> (pEa->getAncestorOfType(SBML_EVENT))->getId();
  const string& variable = ea.getVariable();
  const Species * s = m.getSpecies(variable);

  pre ( s != NULL);
  pre ( ea.isSetMath() == 1 );

  const FormulaUnitsData * variableUnits = 
                                  m.getFormulaUnitsData(variable, SBML_SPECIES);
  const FormulaUnitsData * formulaUnits = 
                         m.getFormulaUnitsData(variable+eId, SBML_EVENT_ASSIGNMENT);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* in level 3 need to check that the species has units defined */
  pre (variableUnits->getUnitDefinition()->getNumUnits() > 0);

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <eventAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT


START_CONSTRAINT (10563, EventAssignment, ea)
{
  //msg =
  //  "When the 'variable' in an <eventAssignment> refers to a <parameter>, the "
  //  "units of the <eventAssignment>'s <math> expression must be consistent "
  //  "with the units declared for that parameter. (References: L2V2 Section "
  //  "4.14.2; L2V3 Section 4.14.4)";
   
  EventAssignment *pEa = const_cast<EventAssignment *> (&ea);
  std::string eId = 
    static_cast <Event *> (pEa->getAncestorOfType(SBML_EVENT))->getId();
  const string& variable = ea.getVariable();
  const Parameter* p = m.getParameter(variable);

  pre ( p != NULL);
  pre ( ea.isSetMath() == 1 );
  /* check that the parameter has units declared */
  pre ( p->isSetUnits());

  const FormulaUnitsData * variableUnits = 
                              m.getFormulaUnitsData(variable, SBML_PARAMETER);
  const FormulaUnitsData * formulaUnits = 
                       m.getFormulaUnitsData(variable+eId, SBML_EVENT_ASSIGNMENT);

  pre ( formulaUnits  != NULL );
  pre ( variableUnits != NULL ); 

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  "Expected units are ";
  msg += UnitDefinition::printUnits(variableUnits->getUnitDefinition());
  msg += " but the units returned by the <eventAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";

  inv (UnitDefinition::areEquivalent(formulaUnits->getUnitDefinition(), 
                          variableUnits->getUnitDefinition()) == 1);
}
END_CONSTRAINT

START_CONSTRAINT (10564, EventAssignment, ea)
{
  const string& variable = ea.getVariable();
  const SpeciesReference* sr = m.getSpeciesReference(variable);
  /* the getSpeciesReference function uses either the id or the species
   * field - so need to check that this is indeed a SpeciesReference
   * and not a Species we are dealing with
   */
  pre ( m.getSpecies(variable) == NULL);

  EventAssignment *pEa = const_cast<EventAssignment *> (&ea);
  std::string eId = 
    static_cast <Event *> (pEa->getAncestorOfType(SBML_EVENT))->getId();

  pre ( ea.getLevel() > 2);
  pre ( sr != NULL);
  pre ( ea.isSetMath() == 1 );

  const FormulaUnitsData * formulaUnits = 
                      m.getFormulaUnitsData(variable+eId, SBML_EVENT_ASSIGNMENT);

  pre ( formulaUnits != NULL );

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  " Expected units are dimensionless";
  msg += " but the units returned by the <eventAssignment>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";
  
  inv (formulaUnits->getUnitDefinition()->isVariantOfDimensionless());
}
END_CONSTRAINT


START_CONSTRAINT (10565, Priority, p)
{
  pre (p.isSetMath());

  const FormulaUnitsData * formulaUnits = 
                                  m.getFormulaUnitsData(p.getInternalId(), SBML_PRIORITY);

  pre ( formulaUnits != NULL );

  /* check that the formula is okay 
     ie has no parameters with undeclared units */
  pre (!formulaUnits->getContainsUndeclaredUnits()
    || (formulaUnits->getContainsUndeclaredUnits() &&
        formulaUnits->getCanIgnoreUndeclaredUnits()));

  msg =  " Expected units are dimensionless";
  msg += " but the units returned by the <priority>'s <math> expression are ";
  msg += UnitDefinition::printUnits(formulaUnits->getUnitDefinition());
  msg += ".";
  
  inv (formulaUnits->getUnitDefinition()->isVariantOfDimensionless());

}
END_CONSTRAINT


START_CONSTRAINT (20511, Compartment, c)
{
  pre( c.getLevel() > 2);
  pre( c.getSpatialDimensionsAsDouble() == 1);
  pre( !(c.isSetUnits()));

  inv( m.isSetLengthUnits());
}
END_CONSTRAINT

START_CONSTRAINT (20512, Compartment, c)
{
  pre( c.getLevel() > 2);
  pre( c.getSpatialDimensionsAsDouble() == 2);
  pre( !(c.isSetUnits()));

  inv( m.isSetAreaUnits());
}
END_CONSTRAINT

START_CONSTRAINT (20513, Compartment, c)
{
  pre( c.getLevel() > 2);
  pre( c.getSpatialDimensionsAsDouble() == 3);
  pre( !(c.isSetUnits()));

  inv( m.isSetVolumeUnits());
}
END_CONSTRAINT


START_CONSTRAINT (20518, Compartment, c)
{
  pre( c.getLevel() > 2);

  inv( !(!(c.isSetUnits()) && !(c.isSetSpatialDimensions())));
}
END_CONSTRAINT


START_CONSTRAINT (20616, Species, s)
{
  pre( s.getLevel() > 2);
  pre( !(s.isSetSubstanceUnits()));

  inv( m.isSetSubstanceUnits());
}
END_CONSTRAINT


START_CONSTRAINT (20702, Parameter, p)
{
  pre( p.getLevel() > 2 );

  inv( p.isSetUnits() );
}
END_CONSTRAINT



/** @endcond */
