/**
 * @cond doxygen-libsbml-internal
 *
 * @file    L2v1CompatibilityConstraints.cpp
 * @brief   L1 compatibility for conversion from L2
 * @author  Sarah Keating
 *
 * $Id: L2v1CompatibilityConstraints.cpp 13423 2011-04-05 11:41:08Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/validator/constraints/L2v1CompatibilityConstraints.cpp $
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
#include <sbml/SBMLTypes.h>
#include <sbml/SBase.h>
#include <sbml/validator/VConstraint.h>
#include <math.h>
#endif


#include <sbml/validator/ConstraintMacros.h>

/** @cond doxygen-ignored */

using namespace std;

/** @endcond */


START_CONSTRAINT (92001, Model, x)
{
  //msg =
  //  "Conversion of a model with <constraints> to SBML Level 2 Version 1 may "
  //  "result in loss of information.";

  inv( m.getNumConstraints() == 0 );
}
END_CONSTRAINT


START_CONSTRAINT (92002, Model, x)
{
  //msg =
  //  "Conversion of a model with <initialAssignments> to SBML Level 2 Version 1 "
  //  "is not yet supported.";

  inv( m.getNumInitialAssignments() == 0 );
}
END_CONSTRAINT


START_CONSTRAINT (92003, Model, x)
{
  //msg =
  //  "<speciesType> definitions cannot be represented in SBML Level 2 "
  //  "Version 1.";

  inv( m.getNumSpeciesTypes() == 0 );
}
END_CONSTRAINT


START_CONSTRAINT (92004, Model, x)
{
  //msg =
  //  "<compartmentType> definitions cannot be represented in SBML Level 2 "
  //  "Version 1.";

  inv( m.getNumCompartmentTypes() == 0 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Model, x)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( m.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, FunctionDefinition, fd)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( fd.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, UnitDefinition, ud)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( ud.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Unit, u)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( u.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Compartment, c)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( c.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Species, s)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( s.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Parameter, p)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( p.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, AssignmentRule, r)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( r.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, RateRule, r)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( r.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, AlgebraicRule, r)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( r.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Reaction, r)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( r.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, SpeciesReference, sr)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( sr.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, KineticLaw, kl)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( kl.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Event, e)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( e.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, EventAssignment, ea)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( ea.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Trigger, t)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( t.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92005, Delay, d)
{
  //msg =
  //  "SBO terms cannot be represented directly in SBML Level 2 Version 1.";

  inv( d.getSBOTerm() == -1 );
}
END_CONSTRAINT


START_CONSTRAINT (92006, SpeciesReference, sr) 
{
  //msg =
  //  "The 'id' attribute value of a <speciesReference> cannot be "
  //  "represented directly in SBML Level 2 Version 1.";

  inv( sr.isSetId() == 0  );
}
END_CONSTRAINT


START_CONSTRAINT (92007, Event, e)
{
  inv( e.getUseValuesFromTriggerTime() == true);
}
END_CONSTRAINT


START_CONSTRAINT (92009, Compartment, c)
{
  inv_or( c.getSpatialDimensions() == 3 );
  inv_or( c.getSpatialDimensions() == 2 );
  inv_or( c.getSpatialDimensions() == 1 );
  inv_or( c.getSpatialDimensionsAsDouble() == 0.0 );
}
END_CONSTRAINT


START_CONSTRAINT (92010, SpeciesReference, sr) 
{
  //msg =
  //  "A <speciesReference> containing a non-integer or non-rational "
  //  "<stoichiometryMath> subelement cannot be represented in SBML Level 1.";

  /* doesnt apply if the SpeciesReference is a modifier */
  pre(!sr.isModifier());

  if (sr.getLevel() > 2)
  {
    inv( sr.getConstant());
  }
}
END_CONSTRAINT


START_CONSTRAINT (91015, Model, x)
{
  pre (m.getLevel() > 2);
  inv( !m.isSetConversionFactor() );
}
END_CONSTRAINT


START_CONSTRAINT (91015, Species, s)
{
  pre (s.getLevel() > 2);
  inv( !s.isSetConversionFactor() );
}
END_CONSTRAINT


START_CONSTRAINT (91016, Reaction, r)
{
  pre (r.getLevel() > 2);
  inv( !r.isSetCompartment() );
}
END_CONSTRAINT


START_CONSTRAINT (91017, Model, x)
{
  pre (m.getLevel() > 2);
  pre (m.isSetExtentUnits());

  std::string extent = m.getExtentUnits();
  const UnitDefinition * ud = m.getUnitDefinition(extent);
  if (ud != NULL)
  {
    UnitDefinition *ud1 = new UnitDefinition(m.getSBMLNamespaces());
    for (unsigned int i = 0; i < ud->getNumUnits(); i++)
    {
      Unit * u = new Unit(m.getSBMLNamespaces());
      u->setKind(ud->getUnit(i)->getKind());
      u->setScale(ud->getUnit(i)->getScale());
      u->setExponent(ud->getUnit(i)->getExponent());
      ud1->addUnit(u);
    }
  
    inv( ud1->isVariantOfSubstance());
  }
  else
  {
    inv_or( extent == "mole" );
    inv_or( extent == "item" );
  }
}
END_CONSTRAINT


START_CONSTRAINT (92011, Event, e)
{
  pre (e.getLevel() > 2);
  inv( !e.isSetPriority() );
}
END_CONSTRAINT


START_CONSTRAINT (92012, Event, e)
{
  pre (e.getLevel() > 2);
  pre (e.isSetTrigger());

  inv( e.getTrigger()->getPersistent() == true );
}
END_CONSTRAINT


START_CONSTRAINT (92013, Event, e)
{
  pre (e.getLevel() > 2);
  pre (e.isSetTrigger());

  inv( e.getTrigger()->getInitialValue() == true );
}
END_CONSTRAINT


START_CONSTRAINT (99926, Compartment, c)
{
  pre (c.getLevel() > 2);

  inv( c.isSetSpatialDimensions() == true );
}
END_CONSTRAINT


/** @endcond */
