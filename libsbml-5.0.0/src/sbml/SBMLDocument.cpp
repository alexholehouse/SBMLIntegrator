/**
 * @file    SBMLDocument.cpp
 * @brief   Implementation of the top-level container for an SBML Model and
 *          associated data. 
 * @author  Ben Bornstein
 *
 * $Id: SBMLDocument.cpp 10197 2009-09-25 15:05:08Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/sbml/SBMLDocument.cpp $
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

#include <iostream>

#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLNamespaces.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLError.h>

#include <sbml/validator/ConsistencyValidator.h>
#include <sbml/validator/IdentifierConsistencyValidator.h>
#include <sbml/validator/MathMLConsistencyValidator.h>
#include <sbml/validator/SBOConsistencyValidator.h>
#include <sbml/validator/UnitConsistencyValidator.h>
#include <sbml/validator/OverdeterminedValidator.h>
#include <sbml/validator/ModelingPracticeValidator.h>
#include <sbml/validator/L1CompatibilityValidator.h>
#include <sbml/validator/L2v1CompatibilityValidator.h>
#include <sbml/validator/L2v2CompatibilityValidator.h>
#include <sbml/validator/L2v3CompatibilityValidator.h>
#include <sbml/validator/L2v4CompatibilityValidator.h>
#include <sbml/validator/L3v1CompatibilityValidator.h>
#include <sbml/validator/InternalConsistencyValidator.h>

#include <sbml/Model.h>
#include <sbml/SBMLErrorLog.h>
#include <sbml/SBMLVisitor.h>
#include <sbml/SBMLError.h>
#include <sbml/SBMLDocument.h>
#include <sbml/SBMLReader.h>
#include <sbml/SBMLWriter.h>

#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/extension/SBasePluginCreatorBase.h>
#include <sbml/extension/SBasePlugin.h>
#include <sbml/extension/SBMLDocumentPlugin.h>

#ifdef USE_LAYOUT
  #include <sbml/packages/layout/extension/LayoutExtension.h>
  #include <sbml/packages/layout/extension/LayoutModelPlugin.h>
#endif

/** @cond doxygen-ignored */

using namespace std;

/** @endcond */

LIBSBML_CPP_NAMESPACE_BEGIN

/*
 * Function to check whether an error reported by a compatability validation
 * prior to conversion between levels/versions can be ignored.
 * Some conversions will lose information but the model will still be valid
 * when converted.
 */
//static unsigned int ignorable[] = {
//  92001,
//  92003,
//  92004,
//  92005,
//  92006,
//  93001,
//  91003,
//  91005,
//  91006,
//  91013
//};


/** @cond doxygen-libsbml-internal */
/*
 * Predicate returning true if the errors encountered are not ignorable.
 */
bool
SBMLDocument::conversion_errors(unsigned int errors, bool strictUnits)
{
  /* if we are converting back from L3 and do not care about units
   * then we will allow a conversion where the spatialDimensions
   * has not been set
   */
  if (!strictUnits && errors > 0)
  {
    for (unsigned int n = 0; n < errors; n++)
    {
      if (mErrorLog.getError(n)->getErrorId() == L3SpatialDimensionsUnset)
      {
        mErrorLog.remove(NoNon3DComparmentsInL1);
        mErrorLog.remove(IntegerSpatialDimensions);
      }
    }
  }
  /** 
   * changed this code in line with the rest of the validation 
   * errors: ie each now assigns a severity
   * Error would imply conversion not possible
   * Warning implies lose of data but conversion still possible
   */
  if (errors > 0)
  {
    if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
      return true;
    else
      return false;
  }
  else
  {
    return false;
  }

  //for (unsigned int i = 0; i < errors; i++)
  //{
  //  bool failure = true;
  //    
  //  for (unsigned int n = 0; n < sizeof(ignorable)/sizeof(ignorable[0]); n++)
  //  {
  //    if (getError(i)->getErrorId() == ignorable[n])
  //    {
  //      failure = false;
  //      break;
  //    }
  //  }

  //  if (failure) return failure;
  //}

  //return false;
}

bool
SBMLDocument::hasStrictUnits()
{
  unsigned int errors = 0;

  UnitConsistencyValidator unit_validator;
  unit_validator.init();
  errors = unit_validator.validate(*this);

  /* only want to return true if there are errors
  * not warnings
  * but in a L2V4 model they will only be warnings
  * so need to go by ErrorId
  * EventAssignParameterMismatch is the largest errorId that
  * would be considered an error in other level/versions
  */
  if (errors > 0)
  {
    std::list<SBMLError> fails = unit_validator.getFailures();
    std::list<SBMLError>::iterator iter;

    for (iter = fails.begin(); iter != fails.end(); iter++)
    {
      if ( iter->getErrorId() > EventAssignParameterMismatch)
      {
        errors--;
      }
    }
  }
    
  return (errors == 0);
}


bool
SBMLDocument::hasStrictSBO()
{
  unsigned int errors = 0;

  SBOConsistencyValidator sbo_validator;
  sbo_validator.init();
  errors = sbo_validator.validate(*this);

  /* only want to return true if there are errors
  * not warnings
  * but in a L2V4 model they will only be warnings
  * so need to go by ErrorId
  * InvalidDelaySBOTerm is the largest errorId that
  * would be considered an error in other level/versions
  */
  if (errors > 0)
  {
    std::list<SBMLError> fails = sbo_validator.getFailures();
    std::list<SBMLError>::iterator iter;

    for (iter = fails.begin(); iter != fails.end(); iter++)
    {
      if ( iter->getErrorId() > InvalidDelaySBOTerm)
      {
        errors--;
      }
    }
  }
    
  return (errors == 0);

}


/*
 * Predicate returning true if the errors encountered are not ignorable.
 */
bool
SBMLDocument::expandFD_errors(unsigned int errors)
{
  if (errors > 0)
  {
    if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
      return true;
    else
    {  /* in L2V1 error 10214 (ie function used but not defined)
        * is actually reported as a warning
        */
      for (unsigned int i = 0; i < mErrorLog.getNumErrors(); i++)
      {
        if (mErrorLog.getError(i)->getErrorId() == ApplyCiMustBeUserFunction)
        {
          return true;
        }
      }

      return false;
    }
  }
  else
  {
    return false;
  }
}
/** @endcond */


/*
 * Get the most recent Level of SBML supported by this release of
 * libSBML.
 *
 * This is the "default" level in the sense that libSBML will create
 * models of this SBML Level unless told otherwise.
 * 
 * @return the number representing the most recent SBML specification level
 * (at the time this libSBML was released).
 */
unsigned int
SBMLDocument::getDefaultLevel ()
{
  return SBML_DEFAULT_LEVEL;
}


/*
 * Get the most recent Version with the most recent Level of SBML supported
 * by this release of libSBML.
 *
 * This is the "default" version in the sense that libSBML will create
 * models of this SBML Level and Version unless told otherwise.
 * 
 * @return the number representing the most recent SBML specification
 * version (at the time this libSBML was released).
 */
unsigned int
SBMLDocument::getDefaultVersion ()
{
  return SBML_DEFAULT_VERSION;
}


/*
 * Creates a new SBMLDocument.  If not specified, the SBML level and
 * version attributes default to the most recent SBML specification (at the
 * time this libSBML was released).
 */
SBMLDocument::SBMLDocument (unsigned int level, unsigned int version) :
   SBase (level, version)
 , mLevel   ( level   )
 , mVersion ( version )
 , mModel   ( NULL       )
 , mApplicableValidators(AllChecksON)
 , mApplicableValidatorsForConversion(AllChecksON)
{
  mSBML = this;

  if (mLevel   == 0 && mVersion == 0)  
  {
    mLevel   = getDefaultLevel  ();
    mVersion = getDefaultVersion();

    mSBMLNamespaces->setLevel(mLevel);
    mSBMLNamespaces->setVersion(mVersion);
    XMLNamespaces *ns = new XMLNamespaces();
    ns->add(mSBMLNamespaces->getSBMLNamespaceURI(mLevel, mVersion));
    mSBMLNamespaces->setNamespaces(ns);
    delete ns;
  }

  if (!hasValidLevelVersionNamespaceCombination())
    throw SBMLConstructorException();

  setElementNamespace(mSBMLNamespaces->getURI());
}


SBMLDocument::SBMLDocument (SBMLNamespaces* sbmlns) :
   SBase (sbmlns)
 , mModel   ( NULL       )
 , mApplicableValidators(AllChecksON)
 , mApplicableValidatorsForConversion(AllChecksON)
{
  mSBML = this;
  mLevel   = sbmlns->getLevel();
  mVersion = sbmlns->getVersion();

  //
  // (TODO) Namespace check for extension packages 
  //        would need to be improved
  //
  if (!hasValidLevelVersionNamespaceCombination())
  {
    std::string err(getElementName());
    XMLNamespaces* xmlns = sbmlns->getNamespaces();
    if (xmlns)
    {
      std::ostringstream oss;
      XMLOutputStream xos(oss);
      xos << *xmlns;
      err.append(oss.str());
    }
    throw SBMLConstructorException(err);
  }

  //
  // (EXTENSION)
  //

  loadPlugins(sbmlns);

  //
  // (TODO) Checks if objects in mPlugins are SBMLDocumentPlugin derived
  //        objects.
  //
}


/*
 * Destroys this SBMLDocument.
 */
SBMLDocument::~SBMLDocument ()
{
  delete mModel;
}


/*
 * Creates a copy of this SBMLDocument.
 */
SBMLDocument::SBMLDocument (const SBMLDocument& orig) :
   SBase    ( orig          )
 , mModel   ( NULL             )
{
  if (&orig == NULL)
  {
    throw SBMLConstructorException("Null argument to copy constructor");
  }
  else
  {
    mSBML = this;

    mLevel                             = orig.mLevel;
    mVersion                           = orig.mVersion;
    mApplicableValidators              = orig.mApplicableValidators;
    mApplicableValidatorsForConversion = 
                                  orig.mApplicableValidatorsForConversion;

    if (orig.mModel != NULL) 
    {
      mModel = static_cast<Model*>( orig.mModel->clone() );
      mModel->setSBMLDocument(this);
    }
    
  }

  connectToChild();
  //if(orig.mNamespaces)
  //  this->mNamespaces = 
  //  new XMLNamespaces(*const_cast<SBMLDocument&>(orig).mNamespaces);
  //else
  //  this->mNamespaces = 0;

}


/*
 * Assignment operator of this SBMLDocument.
 */
SBMLDocument& SBMLDocument::operator=(const SBMLDocument& rhs)
{
  if (&rhs == NULL)
  {
    throw SBMLConstructorException("Null argument to assignment operator");
  }
  else if(&rhs!=this)
  {
    this->SBase::operator =(rhs);
    mSBML = this;

    mLevel                             = rhs.mLevel;
    mVersion                           = rhs.mVersion;
    mApplicableValidators              = rhs.mApplicableValidators;
    mApplicableValidatorsForConversion = 
                                  rhs.mApplicableValidatorsForConversion;

    if (rhs.mModel != NULL) 
    {
      mModel = static_cast<Model*>( rhs.mModel->clone() );
      mModel->setSBMLDocument(this);
    }
  }
  return *this;

}


/*
 * Accepts the given SBMLVisitor.
 */
bool
SBMLDocument::accept (SBMLVisitor& v) const
{
  v.visit(*this);
  if (mModel != NULL) mModel->accept(v);
  v.leave(*this);

  return true;
}


/*
 * @return a (deep) copy of this SBMLDocument.
 */
SBMLDocument*
SBMLDocument::clone () const
{
  return new SBMLDocument(*this);
}


/*
 * @return the Model contained in this SBMLDocument.
 */
const Model*
SBMLDocument::getModel () const
{
  return mModel;
}


/*
 * @return the Model contained in this SBMLDocument.
 */
Model*
SBMLDocument::getModel ()
{
  return mModel;
}

/* 
 * removes FD and expands them in math elements
 */
bool
SBMLDocument::expandFunctionDefinitions()
{
  bool success = false;
  unsigned int i, j;

  /* if there are no function definitions bail now */
  if (mModel->getNumFunctionDefinitions() == 0)
  {
    return true;
  }

  /* check consistency of model */
  /* since this function will write to the error log we should
   * clear anything in the log first
   */
  getErrorLog()->clearLog();
  unsigned char origValidators = mApplicableValidators;

  mApplicableValidators = AllChecksON;

  unsigned int errors = checkConsistency();
  
  if (!expandFD_errors(errors))
  {
    // for any math in document replace each function def
    for (i = 0; i < mModel->getNumRules(); i++)
    {
      if (mModel->getRule(i)->isSetMath())
      {
        SBMLTransforms::replaceFD(const_cast <ASTNode *>(mModel->getRule(i)
          ->getMath()), mModel->getListOfFunctionDefinitions());
      }
    }
    for (i = 0; i < mModel->getNumInitialAssignments(); i++)
    {
      if (mModel->getInitialAssignment(i)->isSetMath())
      {
        SBMLTransforms::replaceFD(const_cast <ASTNode *>(mModel
          ->getInitialAssignment(i)->getMath()), 
          mModel->getListOfFunctionDefinitions());
      }
    }
    for (i = 0; i < mModel->getNumConstraints(); i++)
    {
      if (mModel->getConstraint(i)->isSetMath())
      {
        SBMLTransforms::replaceFD(const_cast <ASTNode *>(mModel
          ->getConstraint(i)->getMath()), 
          mModel->getListOfFunctionDefinitions());
      }
    }
    for (i = 0; i < mModel->getNumReactions(); i++)
    {
      if (mModel->getReaction(i)->isSetKineticLaw())
      {
        if (mModel->getReaction(i)->getKineticLaw()->isSetMath())
        {
          SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
              ->getReaction(i)->getKineticLaw()->getMath()), 
              mModel->getListOfFunctionDefinitions());
        }
      }
      for (j = 0; j < mModel->getReaction(i)->getNumReactants(); j++)
      {
        if (mModel->getReaction(i)->getReactant(j)->isSetStoichiometryMath())
        {
          if (mModel->getReaction(i)->getReactant(j)->getStoichiometryMath()
            ->isSetMath())
          {
            SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
                ->getReaction(i)->getReactant(j)->getStoichiometryMath()->getMath()), 
                mModel->getListOfFunctionDefinitions());
          }
        }
      }
      for (j = 0; j < mModel->getReaction(i)->getNumProducts(); j++)
      {
        if (mModel->getReaction(i)->getProduct(j)->isSetStoichiometryMath())
        {
          if (mModel->getReaction(i)->getProduct(j)->getStoichiometryMath()
            ->isSetMath())
          {
            SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
                ->getReaction(i)->getProduct(j)->getStoichiometryMath()->getMath()), 
                mModel->getListOfFunctionDefinitions());
          }
        }
      }
    }
    for (i = 0; i < mModel->getNumEvents(); i++)
    {
      if (mModel->getEvent(i)->isSetTrigger())
      {
        if (mModel->getEvent(i)->getTrigger()->isSetMath())
        {
          SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
            ->getEvent(i)->getTrigger()->getMath()),
            mModel->getListOfFunctionDefinitions());
        }
      }
      if (mModel->getEvent(i)->isSetDelay())
      {
        if (mModel->getEvent(i)->getDelay()->isSetMath())
        {
          SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
            ->getEvent(i)->getDelay()->getMath()),
            mModel->getListOfFunctionDefinitions());
        }
      }

      for(j = 0; j < mModel->getEvent(i)->getNumEventAssignments(); j++)
      {
        if (mModel->getEvent(i)->getEventAssignment(j)->isSetMath())
        {
          SBMLTransforms::replaceFD(const_cast <ASTNode *> (mModel
            ->getEvent(i)->getEventAssignment(j)->getMath()),
            mModel->getListOfFunctionDefinitions());
        }
      }
    }

    unsigned int size = mModel->getNumFunctionDefinitions();
    while (size--) mModel->getListOfFunctionDefinitions()->remove(size);
  }

  success = (mModel->getNumFunctionDefinitions() == 0);

  /* replace original consistency checks */
  mApplicableValidators = origValidators;

  return success;
}


bool
SBMLDocument::expandInitialAssignments()
{
  bool success = false;
  /* if no initial assignments bail now */
  if (mModel->getNumInitialAssignments() == 0)
  {
    return true;
  }

  /* check consistency of model */
  /* since this function will write to the error log we should
   * clear anything in the log first
   */
  getErrorLog()->clearLog();
  unsigned char origValidators = mApplicableValidators;

  mApplicableValidators = AllChecksON;

  checkConsistency();
  
  if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) == 0)
  {
    SBMLTransforms::expandInitialAssignments(getModel());
  }

  /* replace original consistency checks */
  mApplicableValidators = origValidators;

  success = (mModel->getNumInitialAssignments() == 0);

  return success;
}


/*
 * Sets the level and version of this SBMLDocument.  Valid
 * combinations are currently:
 *
 * @li Level 1 Version 2
 * @li Level 2 Version 1
 * @li Level 2 Version 2
 * @li Level 2 Version 3
 *
 * @note Some models cannot be converted from their existing
 * level and version to other particular combinations.
 * This function checks whether the required conversion 
 * is possible.
 */
bool
SBMLDocument::setLevelAndVersion (unsigned int level, unsigned int version,
                                  bool strict)
{
  /* check we are not already the level and version */
  if ((unsigned int) mLevel == level && (unsigned int) mVersion == version)
  {
    return true;
  }

  /* since this function will write to the error log we should
   * clear anything in the log first
   */
  getErrorLog()->clearLog();

  bool conversionSuccess = false;

  /* if model has extensions we cannot convert */
  if (this->getNumPlugins() > 0)
  {
    /* if it is layout extension and we are converting between l2 versions
     * that is okay
     */
    if (mLevel == 2 && getPlugin("layout") != NULL)
    {
      bool problem = false;
      /* if there is no layout - no problem ! */
#ifdef USE_LAYOUT
      if (mModel != NULL)
      {
        LayoutModelPlugin * mplugin = static_cast<LayoutModelPlugin*>
                      (mModel->getPlugin("layout"));
      
        if (mplugin != NULL && mplugin->getNumLayouts() > 0 && level != 2)
        {
          problem = true;
        }
        else if (getNumPlugins() > 1)
        {
          problem = true;
        }
      }
#endif      
      if (problem == true)
      {
        logError(PackageConversionNotSupported, mLevel, mVersion);
        return conversionSuccess;
      }
    }
    else
    {
      logError(PackageConversionNotSupported, mLevel, mVersion);
      return conversionSuccess;
    }
  }

  unsigned char origValidators = mApplicableValidators;
  mApplicableValidators = mApplicableValidatorsForConversion;
  /* if strict = true we will only convert a valid model
   * to a valid model with a valid internal representation
   */
  /* see whether the unit validator is on */
  bool strictSBO   = ((mApplicableValidatorsForConversion & 0x04) == 0x04);
  bool strictUnits = ((mApplicableValidatorsForConversion & 0x10) == 0x10);
  
  if (strict)
  {
    /* use validators that the user has selected
    */
    /* hack to catch errors caught at read time */
    char* doc = writeSBMLToString(this);
    SBMLDocument *d = readSBMLFromString(doc);
    util_free(doc);
    unsigned int errors = d->getNumErrors();

    for (unsigned int i = 0; i < errors; i++)
    {
      mErrorLog.add(*(d->getError(i)));
    }
    delete d;

    errors += checkConsistency();
    errors = getErrorLog()->getNumFailsWithSeverity(LIBSBML_SEV_ERROR);

    /* if the current model is not valid dont convert 
    */
    if (errors > 0)
    {
      return conversionSuccess;
    }

    getErrorLog()->clearLog();
  }



  //mLevel   = level;
  //mVersion = version;
  //mSBMLNamespaces->setLevel(mLevel);
  //mSBMLNamespaces->setVersion(mVersion);

  unsigned int i;
  bool duplicateAnn = false;
  //look at annotation on sbml element - since validation only happens on teh model :-(
  XMLNode *ann = getAnnotation();
  if (ann != NULL)
  {
    for (i = 0; i < ann->getNumChildren(); i++)
    {
      std::string name = ann->getChild(i).getPrefix();
      for( unsigned int n= i+1; n < ann->getNumChildren(); n++)
      {
        if (ann->getChild(n).getPrefix() == name)
          duplicateAnn = true;
      }
    }
  }

  if (mModel != NULL)
  {
    if (!strict)
    {
      if (mLevel == 1)
      {
        switch (level)
        {
        case 1:
          switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            conversionSuccess = true;
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility()))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility()))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility()))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility()))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL3v1Compatibility()))
            {
              mModel->convertParametersToLocals(level, version);
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL3();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }
      }
      else if (mLevel == 2)
      {
        switch (level)
        {
        case 1:
          switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            if (!conversion_errors(checkL1Compatibility()))
            {
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (mVersion == 4 && !hasStrictUnits())
              {
                logError(StrictUnitsRequiredInL1);
              }
              mModel->convertL2ToL1();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility()))
            {
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (mVersion == 4 && !hasStrictUnits())
              {
                logError(StrictUnitsRequiredInL2v1);
              }
              conversionSuccess = true;
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility()))
            {
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (mVersion == 4 && !hasStrictUnits())
              {
                logError(StrictUnitsRequiredInL2v2);
              }
              
              if (mVersion == 4 && !hasStrictSBO())
              {
                logError(StrictSBORequiredInL2v2);
              }
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                    == DuplicateAnnotationInvalidInL2v2)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              conversionSuccess = true;
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility()))
            {
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (mVersion == 4 && !hasStrictUnits())
              {
                logError(StrictUnitsRequiredInL2v3);
              }
              if (mVersion == 4 && !hasStrictSBO())
              {
                logError(StrictSBORequiredInL2v3);
              }
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                == DuplicateAnnotationInvalidInL2v3)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              conversionSuccess = true;
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility()))
            {
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                == DuplicateAnnotationInvalidInL2v4)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL3v1Compatibility()))
            {
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                == DuplicateAnnotationInvalidInL2v4)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              mModel->convertParametersToLocals(level, version);
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL2ToL3();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }

      }
      else if (mLevel == 3)
      {
        switch (level)
        {
        case 1:
          // we are L3 and want to go backwards
          // NOT YET
          //logError(L3NotSupported, mLevel, mVersion);
          //return conversionSuccess;
          switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            if (!conversion_errors(checkL1Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL1();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          //// we are L3 and want to go backwards
          //// NOT YET
          //logError(L3NotSupported, mLevel, mVersion);
          //return conversionSuccess;
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            conversionSuccess = true;
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }

      }

      if (!conversionSuccess)
      {
        return conversionSuccess;
      }
    }
    else
    {
      unsigned int origLevel = mLevel;
      unsigned int origVersion = mVersion;
      /* here we are strict and only want to do
       * conversion if output will be valid
       *
       * save a copy of the model
       */
      Model *origModel = mModel->clone();
      if (mLevel == 1)
      {
        switch (level)
        {
        case 1:
          switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            conversionSuccess = true;
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility()))
            {
              mModel->removeParameterRuleUnits();
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility()))
            {
              mModel->removeParameterRuleUnits();
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility()))
            {
              mModel->removeParameterRuleUnits();
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility()))
            {
              mModel->removeParameterRuleUnits();
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL2();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL3v1Compatibility()))
            {
              mModel->removeParameterRuleUnits();
              mModel->convertParametersToLocals(level, version);
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL1ToL3();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }
      }
      else if (mLevel == 2)
      {
        switch (level)
        {
        case 1:
          switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            if (!conversion_errors(checkL1Compatibility()))
            {
              bool strictFailed = false;
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (strictUnits)
              {
                if (mVersion == 4 && !hasStrictUnits())
                {
                  logError(StrictUnitsRequiredInL1);
                  strictFailed = true;
                }
              }
              if (!strictFailed)
              {
                mModel->convertL2ToL1(strict);
                conversionSuccess = true;
              }
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility()))
            {
              bool strictFailed = false;
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (strictUnits)
              {
                if (mVersion == 4 && !hasStrictUnits())
                {
                  logError(StrictUnitsRequiredInL2v1);
                  strictFailed = true;
                }
              }
              if (!strictFailed)
              {
                mModel->removeSBOTerms();
                conversionSuccess = true;
              }
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility()))
            {
              bool strictFailed = false;
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (strictUnits)
              {
                if (mVersion == 4 && !hasStrictUnits())
                {
                  logError(StrictUnitsRequiredInL2v2);
                  strictFailed = true;
                }
              }

              if (strictSBO)
              {
                if (mVersion == 4 && !hasStrictSBO())
                {
                  logError(StrictSBORequiredInL2v2);
                  strictFailed = true;
                }
              }

              if (!strictFailed)
              {
                mModel->removeSBOTermsNotInL2V2();
                // look for duplicate top level annotations
                for (i = 0; i < getErrorLog()->getNumErrors(); i++)
                {
                  if (getErrorLog()->getError(i)->getErrorId() 
                                  == DuplicateAnnotationInvalidInL2v2)
                    duplicateAnn = true;
                }
                if (duplicateAnn)
                {
                  this->removeDuplicateAnnotations();
                  mModel->removeDuplicateTopLevelAnnotations();
                }
                conversionSuccess = true;
              }
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility()))
            {
              bool strictFailed = false;
              /* if existing model is L2V4 need to check that
              * units are strict
              */
              if (strictUnits)
              {
                if (mVersion == 4 && !hasStrictUnits())
                {
                  logError(StrictUnitsRequiredInL2v3);
                  strictFailed = true;
                }
              }

              if (strictSBO)
              {
                if (mVersion == 4 && !hasStrictSBO())
                {
                  logError(StrictSBORequiredInL2v3);
                  strictFailed = true;
                }
              }

              if (!strictFailed)
              {
                // look for duplicate top level annotations
                for (i = 0; i < getErrorLog()->getNumErrors(); i++)
                {
                  if (getErrorLog()->getError(i)->getErrorId() 
                                  == DuplicateAnnotationInvalidInL2v3)
                    duplicateAnn = true;
                }
                if (duplicateAnn)
                {
                  this->removeDuplicateAnnotations();
                  mModel->removeDuplicateTopLevelAnnotations();
                }
                conversionSuccess = true;
              }
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility()))
            {
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                == DuplicateAnnotationInvalidInL2v4)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL3v1Compatibility()))
            {
              // look for duplicate top level annotations
              for (i = 0; i < getErrorLog()->getNumErrors(); i++)
              {
                if (getErrorLog()->getError(i)->getErrorId() 
                                == DuplicateAnnotationInvalidInL2v4)
                  duplicateAnn = true;
              }
              if (duplicateAnn)
              {
                this->removeDuplicateAnnotations();
                mModel->removeDuplicateTopLevelAnnotations();
              }
              mModel->convertParametersToLocals(level, version);
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL2ToL3();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }

      }
      else if (mLevel == 3)
      {
        switch (level)
        {
        case 1:
          // we are L3 and want to go backwards
          // NOT YET
          //logError(L3NotSupported, mLevel, mVersion);
          //return conversionSuccess;
         switch (version)
          {
          case 1:
            mErrorLog.add(CannotConvertToL1V1);
            break;
          case 2:
            if (!conversion_errors(checkL1Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL1();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 2:
          // we are L3 and want to go backwards
          // NOT YET
//          logError(L3NotSupported, mLevel, mVersion);
//          return conversionSuccess;
          switch (version)
          {
          case 1:
            if (!conversion_errors(checkL2v1Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 2:
            if (!conversion_errors(checkL2v2Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 3:
            if (!conversion_errors(checkL2v3Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          case 4:
            if (!conversion_errors(checkL2v4Compatibility(), strictUnits))
            {
              mLevel   = level;
              mVersion = version;
              mSBMLNamespaces->setLevel(mLevel);
              mSBMLNamespaces->setVersion(mVersion);
              mModel->convertL3ToL2();
              conversionSuccess = true;
            }
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        case 3:
          switch (version)
          {
          case 1:
            conversionSuccess = true;
            break;
          default:
            logError(InvalidTargetLevelVersion, mLevel, mVersion);
            break;
          }
          break;
        default:
          logError(InvalidTargetLevelVersion, mLevel, mVersion);
          break;
        }
      }

      if (!conversionSuccess)
      {
        delete origModel;
        mApplicableValidators = origValidators;
        mLevel   = origLevel;
        mVersion = origVersion;
        mSBMLNamespaces->setLevel(mLevel);
        mSBMLNamespaces->setVersion(mVersion);
        return conversionSuccess;
      }
      else
      {
        /* now we want to check whether the resulting model is valid
         * but need to make it think its new level/version
         */
        mLevel   = level;
        mVersion = version;
        this->checkConsistency();
        unsigned int errors = 
                     getErrorLog()->getNumFailsWithSeverity(LIBSBML_SEV_ERROR);
        if (errors > 0)
        { /* error - we dont covert
           * restore original values and return
           */
          conversionSuccess = false;
          mModel = origModel->clone();
          mLevel   = origLevel;
          mVersion = origVersion;
          mSBMLNamespaces->setLevel(mLevel);
          mSBMLNamespaces->setVersion(mVersion);
          mApplicableValidators = origValidators;
          delete origModel;
          return conversionSuccess;
        }
        else
        {
          mLevel   = origLevel;
          mVersion = origVersion;
          mApplicableValidators = origValidators;
          delete origModel;
        }
      }
    }
  }
  else
  {
    conversionSuccess = true;
  }

  /* restore original value */
  mApplicableValidators = origValidators; 
  
  mLevel   = level;
  mVersion = version;

  if (mSBMLNamespaces == NULL) 
    mSBMLNamespaces = new SBMLNamespaces(mLevel, mVersion);;

  /**
   * check for the case where the sbml namespace has been expicitly declared
   * as well as being the default
   */
  bool sbmlDecl = false;
  int index;
  for (index = 0; index < mSBMLNamespaces->getNamespaces()->getLength(); 
                                                                  index++)
  {
    if (!mSBMLNamespaces->getNamespaces()->getPrefix(index).empty() 
      && mSBMLNamespaces->getNamespaces()->getPrefix(index)=="sbml")
    {
      sbmlDecl = true;
      break;
    }
  }
  if (sbmlDecl)
  {
    XMLNamespaces * copyNamespaces = mSBMLNamespaces->getNamespaces()->clone();
    mSBMLNamespaces->getNamespaces()->clear();
    for (int i = 0; i < copyNamespaces->getLength(); i++)
    {
      if ( i != index)
        mSBMLNamespaces->getNamespaces()->add(copyNamespaces->getURI(i),
                         copyNamespaces->getPrefix(i));
    }
    delete copyNamespaces;
  }

  if (mLevel == 1)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level1", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level1");
  }
  else if (mLevel == 2 && mVersion == 1)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2");
  }
  else if (mLevel == 2 && mVersion == 2)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version2", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version2");
  }
  else if (mLevel == 2 && mVersion == 3)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version3", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version3");
  }
  else if (mLevel == 2 && mVersion == 4)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version4", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level2/version4");
  }
  else if (mLevel == 3 && mVersion == 1)
  {
    if (sbmlDecl)
      mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level3/version1/core", "sbml");
    mSBMLNamespaces->getNamespaces()->add("http://www.sbml.org/sbml/level3/version1/core");
  }

  mSBMLNamespaces->setLevel(mLevel);
  mSBMLNamespaces->setVersion(mVersion);

  return conversionSuccess;
}


/*
 * Sets the Model for this SBMLDocument to a copy of the given Model.
 */
int
SBMLDocument::setModel (const Model* m)
{
  if (mModel == m)
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (m == NULL)
  {
    delete mModel;
    mModel = NULL;
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (getLevel() != m->getLevel())
  {
    return LIBSBML_LEVEL_MISMATCH;
  }
  else if (getVersion() != m->getVersion())
  {
    return LIBSBML_VERSION_MISMATCH;
  }
  else
  {
    delete mModel;
    mModel = (m != NULL) ? new Model(*m) : NULL;

    if (mModel != NULL) mModel->connectToParent(this);
    
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/*
 * Creates a new Model (optionally with its id attribute set) inside this
 * SBMLDocument and returns it.
 */
Model*
SBMLDocument::createModel (const std::string& sid)
{
  if (mModel != NULL) delete mModel;

  try
  {
    mModel = new Model(getSBMLNamespaces());
  }
  catch (...)
  {
    /* here we do not create a default object as the level/version must
     * match the parent object
     *
     * so do nothing
     */
  }
  
  if (mModel != NULL)
  {
    mModel->setId(sid);

    mModel->connectToParent(this);
  }
  return mModel;
}


void 
SBMLDocument::setConsistencyChecks(SBMLErrorCategory_t category,
                                   bool apply)
{
  switch (category)
  {
  case LIBSBML_CAT_IDENTIFIER_CONSISTENCY:
    if (apply)
    {
      mApplicableValidators |= IdCheckON;
    }
    else
    {
      mApplicableValidators &= IdCheckOFF;
    }

    break;

  case LIBSBML_CAT_GENERAL_CONSISTENCY:
    if (apply)
    {
      mApplicableValidators |= SBMLCheckON;
    }
    else
    {
      mApplicableValidators &= SBMLCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_SBO_CONSISTENCY:
    if (apply)
    {
      mApplicableValidators |= SBOCheckON;
    }
    else
    {
      mApplicableValidators &= SBOCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_MATHML_CONSISTENCY:
    if (apply)
    {
      mApplicableValidators |= MathCheckON;
    }
    else
    {
      mApplicableValidators &= MathCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_UNITS_CONSISTENCY:
    if (apply)
    {
      mApplicableValidators |= UnitsCheckON;
    }
    else
    {
      mApplicableValidators &= UnitsCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_OVERDETERMINED_MODEL:
    if (apply)
    {
      mApplicableValidators |= OverdeterCheckON;
    }
    else
    {
      mApplicableValidators &= OverdeterCheckOFF;
    }

    break;

  case LIBSBML_CAT_MODELING_PRACTICE:
    if (apply)
    {
      mApplicableValidators |= PracticeCheckON;
    }
    else
    {
      mApplicableValidators &= PracticeCheckOFF;
    }

    break;

  default:
    // If it's a category for which we don't have validators, ignore it.
    break;
  }

}


void 
SBMLDocument::setConsistencyChecksForConversion(SBMLErrorCategory_t category,
                                   bool apply)
{
  switch (category)
  {
  case LIBSBML_CAT_IDENTIFIER_CONSISTENCY:
    if (apply)
    {
      mApplicableValidatorsForConversion |= IdCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= IdCheckOFF;
    }

    break;

  case LIBSBML_CAT_GENERAL_CONSISTENCY:
    if (apply)
    {
      mApplicableValidatorsForConversion |= SBMLCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= SBMLCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_SBO_CONSISTENCY:
    if (apply)
    {
      mApplicableValidatorsForConversion |= SBOCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= SBOCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_MATHML_CONSISTENCY:
    if (apply)
    {
      mApplicableValidatorsForConversion |= MathCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= MathCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_UNITS_CONSISTENCY:
    if (apply)
    {
      mApplicableValidatorsForConversion |= UnitsCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= UnitsCheckOFF;
    }

    break;
  
  case LIBSBML_CAT_OVERDETERMINED_MODEL:
    if (apply)
    {
      mApplicableValidatorsForConversion |= OverdeterCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= OverdeterCheckOFF;
    }

    break;

  case LIBSBML_CAT_MODELING_PRACTICE:
    if (apply)
    {
      mApplicableValidatorsForConversion |= PracticeCheckON;
    }
    else
    {
      mApplicableValidatorsForConversion &= PracticeCheckOFF;
    }

    break;

  default:
    // If it's a category for which we don't have validators, ignore it.
    break;
  }

}


/*
 * Performs a set of semantic consistency checks on the document.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkConsistency ()
{
  unsigned int nerrors = 0;
  unsigned int total_errors = 0;

  //if (getLevel() == 3)
  //{
  //  logError(L3NotSupported);
  //  return 1;
  //}
  /* determine which validators to run */
  bool id    = ((mApplicableValidators & 0x01) == 0x01);
  bool sbml  = ((mApplicableValidators & 0x02) == 0x02);
  bool sbo   = ((mApplicableValidators & 0x04) == 0x04);
  bool math  = ((mApplicableValidators & 0x08) == 0x08);
  bool units = ((mApplicableValidators & 0x10) == 0x10);
  bool over  = ((mApplicableValidators & 0x20) == 0x20);
  bool practice = ((mApplicableValidators & 0x40) == 0x40);

  /* taken the state machine concept out for now
  if (LibSBMLStateMachine::isActive()) 
  {
    units = LibSBMLStateMachine::getUnitState();
  }
  */

  IdentifierConsistencyValidator id_validator;
  ConsistencyValidator validator;
  SBOConsistencyValidator sbo_validator;
  MathMLConsistencyValidator math_validator;
  UnitConsistencyValidator unit_validator;
  OverdeterminedValidator over_validator;
  ModelingPracticeValidator practice_validator;

  /* calls each specified validator in turn 
   * - stopping when errors are encountered */

  if (id)
  {
    id_validator.init();
    nerrors = id_validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( id_validator.getFailures() );
      return total_errors;
    }
  }

  if (sbml)
  {
    validator.init();
    nerrors = validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( validator.getFailures() );
      /* only want to bail if errors not warnings */
      if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
        return total_errors;
    }
  }

  if (sbo)
  {
    sbo_validator.init();
    nerrors = sbo_validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( sbo_validator.getFailures() );
      /* only want to bail if errors not warnings */
      if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
        return total_errors;
    }
  }

  if (math)
  {
    math_validator.init();
    nerrors = math_validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( math_validator.getFailures() );
      /* at this point bail if any problems
       * unit checks may crash if there have been math errors/warnings
       */
      return total_errors;
    }
  }


  if (units)
  {
    unit_validator.init();
    nerrors = unit_validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( unit_validator.getFailures() );
      /* only want to bail if errors not warnings */
      if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
        return total_errors;
    }
  }

  /* do not even try if there have been unit warnings 
   * changed this as would have bailed */
  if (over)
  {
    over_validator.init();
    nerrors = over_validator.validate(*this);
    total_errors += nerrors;
    if (nerrors > 0) 
    {
      mErrorLog.add( over_validator.getFailures() );
      /* only want to bail if errors not warnings */
      if (mErrorLog.getNumFailsWithSeverity(LIBSBML_SEV_ERROR) > 0)
        return total_errors;
    }
  }

  if (practice)
  {
    practice_validator.init();
    nerrors = practice_validator.validate(*this);
    if (nerrors > 0) 
    {
      unsigned int errorsAdded = 0;
      const std::list<SBMLError> practiceErrors = practice_validator.getFailures();
      list<SBMLError>::const_iterator end = practiceErrors.end();
      list<SBMLError>::const_iterator iter;
      for (iter = practiceErrors.begin(); iter != end; ++iter)
      {
        if (SBMLError(*iter).getErrorId() != 80701)
        {
          mErrorLog.add( SBMLError(*iter) );
          errorsAdded++;
        }
        else
        {
          if (units) 
          {
            mErrorLog.add( SBMLError(*iter) );
            errorsAdded++;
          }
        }
      }
      total_errors += errorsAdded;

    }
  }


  return total_errors;
}


/*
 * Performs consistency checking on libSBML's internal representation of 
 * an SBML Model.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkInternalConsistency()
{
  unsigned int nerrors = 0;
  unsigned int totalerrors = 0;

  InternalConsistencyValidator validator;

  validator.init();
  nerrors = validator.validate(*this);
  if (nerrors > 0) 
  {
    mErrorLog.add( validator.getFailures() );
  }
  totalerrors += nerrors;
  
  /* hack to catch errors normally caught at read time */
  char* doc = writeSBMLToString(this);
  SBMLDocument *d = readSBMLFromString(doc);
  util_free(doc);
  nerrors = d->getNumErrors();

  for (unsigned int i = 0; i < nerrors; i++)
  {
    mErrorLog.add(*(d->getError(i)));
  }
  delete d;
  totalerrors += nerrors;


  return totalerrors;

}

/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L1 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL1Compatibility ()
{
  if (mModel == NULL) return 0;

  L1CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L2v1 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL2v1Compatibility ()
{
  if (mModel == NULL) return 0;

  L2v1CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L2v2 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL2v2Compatibility ()
{
  if (mModel == NULL) return 0;

  L2v2CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L2v3 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL2v3Compatibility ()
{
  if (mModel == NULL) return 0;

  L2v3CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L2v4 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL2v4Compatibility ()
{
  if (mModel == NULL) return 0;

  L2v4CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * Performs a set of semantic consistency checks on the document to establish
 * whether it is compatible with L2v1 and can be converted.  Query
 * the results by calling getNumErrors() and getError().
 *
 * @return the number of failed checks (errors) encountered.
 */
unsigned int
SBMLDocument::checkL3v1Compatibility ()
{
  if (mModel == NULL) return 0;

  L3v1CompatibilityValidator validator;
  validator.init();

  unsigned int nerrors = validator.validate(*this);
  if (nerrors > 0) mErrorLog.add( validator.getFailures() );

  return nerrors;
}


/*
 * @return the nth error encountered during the parse of this
 * SBMLDocument or @c NULL if n > getNumErrors() - 1.
 */
const SBMLError*
SBMLDocument::getError (unsigned int n) const
{
  return mErrorLog.getError(n);
}


/*
 * @return the number of errors encountered during the parse of this
 * SBMLDocument.
 */
unsigned int
SBMLDocument::getNumErrors () const
{
  return mErrorLog.getNumErrors();
}


/*
 * Prints all errors encountered during the parse of this SBMLDocument to
 * the given stream.  If no errors have occurred, i.e.  getNumErrors() ==
 * 0, no output will be sent to stream. The format of the output is:
 *
 *   N error(s):
 *     line N: (id) message
 */
void
SBMLDocument::printErrors (std::ostream& stream) const
{
  unsigned int numErrors = getNumErrors();

  if (numErrors > 0)
  {
    for (unsigned int n = 0; n < numErrors; n++)
    {
      stream << *(getError(n));
    }
  }
}

/** @cond doxygen-libsbml-internal */

/*
 * Sets the parent SBMLDocument of this SBML object.
 */
void
SBMLDocument::setSBMLDocument (SBMLDocument* d)
{
  SBase::setSBMLDocument(d);
  // No-op
}

/*
 * Sets this SBML object to child SBML objects (if any).
 * (Creates a child-parent relationship by the parent)
  */
void
SBMLDocument::connectToChild()
{
	if (mModel) mModel->connectToParent(this);
}

/** @endcond */


/*
 * @return the typecode (int) of this SBML object or SBML_UNKNOWN
 * (default).
 *
 * @see getElementName()
 */
int
SBMLDocument::getTypeCode () const
{
  return SBML_DOCUMENT;
}


/*
 * @return the name of this element ie "sbml".
 */
const string&
SBMLDocument::getElementName () const
{
  static const string name = "sbml";
  return name;
}


/** @cond doxygen-libsbml-internal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
SBMLDocument::getElementPosition () const
{
  return 1;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return the SBML object corresponding to next XMLToken in the
 * XMLInputStream or @c NULL if the token was not recognized.
 */
SBase*
SBMLDocument::createObject (XMLInputStream& stream)
{
  const string& name   = stream.peek().getName();
  SBase*        object = NULL;


  if (name == "model")
  {
    delete mModel;

    try
    {
      mModel = new Model(getSBMLNamespaces());
    }
    catch ( ... )
    {
      mModel = new Model(SBMLDocument::getDefaultLevel(),
        SBMLDocument::getDefaultVersion());
    }
    //catch ( ... )
    //{
    //  // do nothing
    //}

    object = mModel;
  }

  return object;
}
/** @endcond */


/**
  * @return the Namespaces associated with this SBML object
  */
XMLNamespaces* 
SBMLDocument::getNamespaces() const
{
  return mSBMLNamespaces->getNamespaces();
}


/*
 * @return the SBMLErrorLog used to log errors during while reading and
 * validating SBML.
 */
SBMLErrorLog*
SBMLDocument::getErrorLog ()
{
  return &mErrorLog;
}


int
SBMLDocument::enableDefaultNS(const std::string& package, bool flag)
{
  std::string pkgURI = "";
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (    (uri == package)
         || (sbext && (sbext->getName() == package))
       )	     
    {
      pkgURI = uri;
    }
  }

  if (pkgURI.empty()) 
  {
    return LIBSBML_PKG_UNKNOWN_VERSION;
  }

  PkgUseDefaultNSMapIter it = mPkgUseDefaultNSMap.find(pkgURI);
  if (it != mPkgUseDefaultNSMap.end()) 
  {
    (*it).second = flag;
  }
  else
  {
    mPkgUseDefaultNSMap.insert(pair<string,bool>(pkgURI,flag));
  }

  return LIBSBML_OPERATION_SUCCESS;
}


bool 
SBMLDocument::isEnabledDefaultNS(const std::string& package)
{
  std::string pkgURI;
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (    (uri == package)
         || (sbext && (sbext->getName() == package))
       )	     
    {
      pkgURI = uri;
    }
  }

  PkgUseDefaultNSMapIter it = mPkgUseDefaultNSMap.find(pkgURI);

  return (it != mPkgUseDefaultNSMap.end()) ? (*it).second : false;
}


int
SBMLDocument::setPkgRequired(const std::string& package, bool flag)
{
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (   (uri == package)
         || (sbext && (sbext->getName() == package))
       )
    {
      //
      // (NOTE) objects in mPlugins must be derived
      //        from SBMLDocumentPlugin to invoke the corresponding
      //        setReuired(), getRequired() functions
      //
      return static_cast<SBMLDocumentPlugin*>(mPlugins[i])->setRequired(flag);
    }
  }

  //
  // checks required attributes in unknown packages
  //
  if (mRequiredAttrOfUnknownPkg.getValue("required",package) != "")
  {
    int index = mRequiredAttrOfUnknownPkg.getIndex("required",package);
    std::string prefix = mRequiredAttrOfUnknownPkg.getPrefix(index);
    std::string value = (flag) ? "true" : "false";

    mRequiredAttrOfUnknownPkg.add("required", value, package, prefix);
    return LIBSBML_OPERATION_SUCCESS;
  }

  return LIBSBML_PKG_UNKNOWN_VERSION;
}


bool 
SBMLDocument::getPkgRequired(const std::string& package)
{
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (   (uri == package)
        || (sbext && (sbext->getName() == package) )
       )
    {
      //
      // (NOTE) objects in mPlugins must be derived
      //        from SBMLDocumentPlugin to invoke the corresponding
      //        setReuired(), getRequired() functions
      //
      return static_cast<SBMLDocumentPlugin*>(mPlugins[i])->getRequired();
    }
  }

  //
  // checks required attributes in unknown packages
  //
  std::string req = mRequiredAttrOfUnknownPkg.getValue("required",package);
  if (req == "true") return true;

  return false;
}


bool 
SBMLDocument::isSetPkgRequired(const std::string& package)
{
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (   (uri == package)
        || (sbext && (sbext->getName() == package) )
       )
    {
      return true;
    }
  }

  //
  // checks required attributes in unknown packages
  //
  std::string req = mRequiredAttrOfUnknownPkg.getValue("required",package);
  if (!req.empty()) return true;

  return false;
}


/**
 * Returnes @c true if the given package extension is one of ignored
 * packages (i.e. the package is defined in this document but the package
 * is not available), otherwise returns @c false.
 */
bool 
SBMLDocument::isIgnoredPkg(const std::string& pkgURI)
{
  if (isSetPkgRequired(pkgURI) && !isPkgURIEnabled(pkgURI))
    return true;

  return false;
}

/** @cond doxygen-libsbml-internal */

/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
SBMLDocument::addExpectedAttributes(ExpectedAttributes& attributes)
{
  SBase::addExpectedAttributes(attributes);

  //
  // (NOTICE)
  //
  // getLevel() and getVersion() functions MUST NOT BE USED in this
  // function, because level and version are unknown until the level 
  // and version attributes parsed by readAttributes() function.
  //

  attributes.add("level");
  attributes.add("version");
  attributes.add("metaid");
  attributes.add("schemaLocation");
}


/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
SBMLDocument::readAttributes (const XMLAttributes& attributes,
                              const ExpectedAttributes& expectedAttributes)
{
  //
  // level: positiveInteger  { use="required" fixed="1" }  (L1v1)
  // level: positiveInteger  { use="required" fixed="2" }  (L2v1)
  //
  bool levelRead = attributes.readInto("level", mLevel, getErrorLog(), false);

  //
  // version: positiveInteger  { use="required" fixed="1" }  (L1v1, L2v1)
  // version: positiveInteger  { use="required" fixed="2" }  (L1v2, L2v2)
  // version: positiveInteger  { use="required" fixed="3" }  (L2v3)
  //
  bool versionRead = attributes.readInto("version", mVersion, getErrorLog(), false);

  // 
  // (EXTENSION)  SBMLDocument specific code
  //
  // The code for creating an extension IF below is almost equal to that in 
  // SBase::SBase(SBMLNamespaces*,typecode (int)).
  //
  XMLNamespaces *xmlns = getNamespaces();
  if (xmlns == NULL)
  {
//     std::string err("SBase: xmlns is empty");
//     XMLNamespaces* xmlns = sbmlns->getNamespaces();
//     std::ostringstream oss;
//     oss << "\nTypeCode " << typeCode << endl;
//     if (xmlns)
//     {
//       XMLOutputStream xos(oss);
//       xos << *xmlns;
//     }
//     err.append(oss.str());
//     throw SBMLConstructorException(err);
  }
  else
  {
    int numxmlns= xmlns->getLength();
    for (int i=0; i < numxmlns; i++)
    {
      const std::string &uri = xmlns->getURI(i);
      const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);

      if (sbmlext && sbmlext->isEnabled())
      {
        const std::string &prefix = xmlns->getPrefix(i);
        SBaseExtensionPoint extPoint(getPackageName(), SBML_DOCUMENT);
        const SBasePluginCreatorBase* sbPluginCreator = sbmlext->getSBasePluginCreator(extPoint);
        if (sbPluginCreator)
        {
          // (debug)
          //cout << "sbPlugin " << sbPlugin << endl;
          //sbPlugin->createPlugin(uri,prefix);
          // (debug)
          SBasePlugin* entity = sbPluginCreator->createPlugin(uri,prefix,xmlns);
          entity->connectToParent(this);
          mPlugins.push_back(entity);
        }
      }
      else
      {
        //
        //  1) Checks if there exists a "required" attribute with the prefix of
        //     this namespace.
        //  2) If such attribute exists then checks if the value is true or false.
        //  3) Logs an error (e..g The package is required but the package is not available)
        //     if the value is true.
        //  4) Added a check that the uri could possibly be a l3 ns
        //
        size_t pos = uri.find("http://www.sbml.org/sbml/level3/version1");
        std::string requiredAttr = attributes.getValue("required",uri);
        if (pos == 0 && !requiredAttr.empty())
        {
          mRequiredAttrOfUnknownPkg.add("required", requiredAttr, uri, xmlns->getPrefix(i));
#if 0
          cout << "[DEBUG] SBMLDocument::readAttributes() uri " << uri 
               << " has required attribute : " << attributes.getValue("required",uri) << endl;
#endif
          ostringstream msg;

          if (requiredAttr == "true")
          {
            msg << "Package '" << xmlns->getPrefix(i) << 
                "' is a required package and the model cannot be properly "
                "interpreted.";
            logError(RequiredPackagePresent, mLevel, mVersion, msg.str());
          }
          else
          {
            msg << "Package '" << xmlns->getPrefix(i) << 
                "' is not a required package. The information relating "
                "to '" << xmlns->getPrefix(i) << "' will be "
                "saved but cannot be interpreted.";
            logError(UnrequiredPackagePresent, mLevel, mVersion, msg.str());
          }
        } 
      }
    }
  }

 
  //
  // (NOTE)
  //
  // In SBMLDocument, level and version are unknown until the attributes
  // read by the above function calls.
  //
  ExpectedAttributes addedEA(expectedAttributes);
 
  if (getLevel() > 2)
    addedEA.add("required");

  SBase::readAttributes(attributes,addedEA);


  /* check that the level and version are valid */
  if (mLevel == 1)
  {
    if (mVersion > 2)
    {
      logError(InvalidSBMLLevelVersion);
    }
  }
  else if (mLevel == 2)
  {
    if (mVersion > 4)
    {
      logError(InvalidSBMLLevelVersion);
    }
  }
  else if (mLevel == 3)
  {
    if (mVersion > 1)
    {
      logError(InvalidSBMLLevelVersion);
    }
  }
  else
  {
    logError(InvalidSBMLLevelVersion);
    return;
  }
  
  /* check that sbml namespace has been set */
  XMLNamespaces *ns = mSBMLNamespaces->getNamespaces();
  unsigned int match = 0;
  if (ns == NULL)
  {
    logError(InvalidNamespaceOnSBML);
  }
  else 
  {
    for (int n = 0; n < ns->getLength(); n++)
    {
      if (!strcmp(ns->getURI(n).c_str(), 
                  "http://www.sbml.org/sbml/level1"))
      {
        match = 1;
        if (mLevel != 1 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if ((mVersion != 1 && mVersion != 2) || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
       break;
      }
      else if (!strcmp(ns->getURI(n).c_str(), 
                "http://www.sbml.org/sbml/level2"))
      {
        match = 1;
        if (mLevel != 2 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if (mVersion != 1 || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
        break;
      }
      else if (!strcmp(ns->getURI(n).c_str(), 
                "http://www.sbml.org/sbml/level2/version2"))
      {
        match = 1;
        if (mLevel != 2 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if (mVersion != 2 || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
        break;
      }
      else if (!strcmp(ns->getURI(n).c_str(), 
                "http://www.sbml.org/sbml/level2/version3"))
      {
        match = 1;
        if (mLevel != 2 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if (mVersion != 3 || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
        break;
      }
      else if (!strcmp(ns->getURI(n).c_str(), 
                "http://www.sbml.org/sbml/level2/version4"))
      {
        match = 1;
        if (mLevel != 2 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if (mVersion != 4 || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
        break;
      }
      else if (!strcmp(ns->getURI(n).c_str(), 
                "http://www.sbml.org/sbml/level3/version1/core"))
      {
        match = 1;
        if (mLevel != 3 || !levelRead)
        {
          logError(MissingOrInconsistentLevel);
        }
        if (mVersion != 1 || !versionRead)
        {
          logError(MissingOrInconsistentVersion);
        }
        break;
      }
    }
    if (match == 0)
    {
      logError(InvalidNamespaceOnSBML);
    }
    else
    {
      mSBMLNamespaces->setLevel(mLevel);
      mSBMLNamespaces->setVersion(mVersion);
      setElementNamespace(mSBMLNamespaces->getURI());
    }

  }

#ifdef USE_LAYOUT
  /* if using layout and reading an L2 model the package
   * is not enabled by the read since the l3 ns is missing
   * force the package to be enabled
   */
  if (SBMLExtensionRegistry::getInstance().isRegistered("layout"))
  {
    if (mLevel == 2)
    {
      enablePackage(LayoutExtension::getXmlnsL2(),"layout", true);
    }
  }
#endif

//   if (getLevel() > 2)
//   {
//     bool reqd;
//    cout << "[DEBUG] SBMLDocument::readAttributes " << endl;
//     /* look for namespaces with other prefixes */
//     for (int i = 0; i < ns->getLength(); i++)
//     {
//       std::string uri    = ns->getURI(i);
//       std::string prefix = ns->getPrefix(i);

//       const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtension(uri);
//       if (sbmlext && sbmlext->isEnabled())
//       {
//         XMLTriple triple("required", uri, prefix);
//         attributes.readInto(triple, reqd, getErrorLog(), true);
//         mPkgRequiredMap.insert(pair<string,bool>(uri,reqd));
//         cout << "[DEBUG] SBMLDocument::readAttributes" << uri << endl;
//       }
//       else
//       { 
//         cout << "[DEBUG] SBMLDocument::readAttributes: No such package " << uri << endl;
//       }
//     }
//   }

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 */
void
SBMLDocument::writeAttributes (XMLOutputStream& stream) const
{
  SBase::writeAttributes(stream);

  if (mSBMLNamespaces->getNamespaces() == NULL)
  {
     XMLNamespaces xmlns;

     if (mLevel == 1)
     {
        xmlns.add("http://www.sbml.org/sbml/level1");
     }
     else if (mLevel == 2 && mVersion == 1)
     {
       xmlns.add("http://www.sbml.org/sbml/level2");
     }
     else if (mLevel == 2 && mVersion == 2)
     {
       xmlns.add("http://www.sbml.org/sbml/level2/version2");
     }
     else if (mLevel == 2 && mVersion == 3)
     {
       xmlns.add("http://www.sbml.org/sbml/level2/version3");
     }
     else if (mLevel == 2 && mVersion == 4)
     {
       xmlns.add("http://www.sbml.org/sbml/level2/version4");
     }
     else if (mLevel == 3 && mVersion == 1)
     {
       xmlns.add("http://www.sbml.org/sbml/level3/version1/core");
     }
     stream << xmlns;

     mSBMLNamespaces->setNamespaces(&xmlns);
  }  

  //
  // level: positiveInteger  { use="required" fixed="1" }  (L1v1)
  // level: positiveInteger  { use="required" fixed="2" }  (L2v1)
  //
  stream.writeAttribute("level", mLevel);

  //
  // version: positiveInteger  { use="required" fixed="1" }  (L1v1, L2v1)
  // version: positiveInteger  { use="required" fixed="2" }  (L1v2, L2v2)
  // version: positiveInteger  { use="required" fixed="3" }  (L2v3)
  //
  stream.writeAttribute("version", mVersion);


  //
  // (EXTENSION)
  //
  SBase::writeExtensionAttributes(stream);

  //
  // required attributes of unknown packages
  //
  for (int i=0; i < mRequiredAttrOfUnknownPkg.getLength(); i++)
  {
    std::string prefix = mRequiredAttrOfUnknownPkg.getPrefix(i);
    std::string value  = mRequiredAttrOfUnknownPkg.getValue(i);
    stream.writeAttribute("required", prefix, value);
  }
  //
  // writing required attribute of package extensions.
  //
//   if (getLevel() > 2) 
//   {
//     cout << "[DEBUG] SBMLDocument::writeAttribute() " << endl;
//     std::map<std::string, bool>::const_iterator it = mPkgRequiredMap.begin();
//     while (it != mPkgRequiredMap.end())
//     {
//       std::string name = (*it).first + ":required";
//       bool isreq       = (*it).second;
//       cout << "[DEBUG] SBMLDocument::writeAttribute() " << name << endl;
//       stream.writeAttribute(name, isreq);
//       ++it;
//     }
//   }
}


/**
 *
 * Subclasses should override this method to write their xmlns attriubutes
 * (if any) to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 *
 */
void
SBMLDocument::writeXMLNS (XMLOutputStream& stream) const
{
  // we do not want to write the l2 layout ns on the top level
  XMLNamespaces * xmlns = this->getNamespaces()->clone();
  if (xmlns != NULL) 
  {
#ifdef USE_LAYOUT
    for (int n = 0; n < xmlns->getNumNamespaces(); n++)
    {
      if (xmlns->getURI(n) == LayoutExtension::getXmlnsL2())
      {
        xmlns->remove(n);
      }
    }
#endif
    stream << *(xmlns);
    delete xmlns;
  }
}


/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to write out their contained
 * SBML objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
SBMLDocument::writeElements (XMLOutputStream& stream) const
{
  SBase::writeElements(stream);
  if (mModel != NULL) mModel->write(stream);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionElements(stream);
}


/**
 * Enables/Disables the given package with this element and child
 * elements (if any).
 * (This is an internal implementation for enablePakcage function)
 */
void 
SBMLDocument::enablePackageInternal(const std::string& pkgURI, const std::string& pkgPrefix, bool flag)
{
  SBase::enablePackageInternal(pkgURI,pkgPrefix,flag);

  if (!flag)
  {
    //
    // disable the given package
    //

    // (1) remove the entry of mPkgUseDefaultNSMap

    mPkgUseDefaultNSMap.erase(pkgURI);

    // (2) remove the xmlns from mSBMLNamespaces

//    XMLNamespaces *xmlns = mSBMLNamespaces->getNamespaces();
//    if (xmlns)
//    {
//      xmlns->remove(xmlns->getIndex(pkgURI));
//    }
  }

  if (mModel)
    mModel->enablePackageInternal(pkgURI,pkgPrefix,flag);
}

/** @endcond */



/** @cond doxygen-c-only */



/**
 * Creates a new, empty SBMLDocument_t structure.
 *
 * The SBML Level and Version attributes default to the most recent SBML
 * specification (at the time this libSBML was released).
 *
 * @return the SBMLDocument_t structure created
 */
LIBSBML_EXTERN
SBMLDocument_t *
SBMLDocument_create ()
{
  try
  {
    SBMLDocument* obj = new SBMLDocument();
    return obj;
  }
  catch (SBMLConstructorException)
  {
    return NULL;
  }
}


/**
 * Creates a new, empty SBMLDocument_t structure with given values for the
 * SBML Level and Version.
 *
 * If not specified, the SBML Level and Version attributes default to the
 * most recent SBML specification (at the time this libSBML was
 * released).
 *
 * @param level an integer for the SBML Level
 * @param version an integer for the Version within the SBML Level
 *
 * @return the SBMLDocument_t structure created
 */
LIBSBML_EXTERN
SBMLDocument_t *
SBMLDocument_createWithLevelAndVersion (unsigned int level, unsigned int version)
{
  try
  {
    SBMLDocument* obj = new SBMLDocument(level, version);
    return obj;
  }
  catch (SBMLConstructorException)
  {
    return NULL;
  }
}


/**
 * Frees the given SBMLDocument_t structure.
 *
 * @param d the SBMLDocument_t structure
 */
LIBSBML_EXTERN
void
SBMLDocument_free (SBMLDocument_t *d)
{
  delete d;
}


/**
 * Creates and returns a deep copy of the given SBMLDocument_t structure
 *
 * @param d the SBMLDocument_t structure
 * 
 * @return a (deep) copy of the SBMLDocument_t structure
 */
LIBSBML_EXTERN
SBMLDocument_t *
SBMLDocument_clone (const SBMLDocument_t *d)
{
  return (d != NULL) ? static_cast<SBMLDocument_t*>( d->clone() ) : NULL;
}


/**
 * Returns the SBML Level of the given SBMLDocument_t structure.
 *
 * @param d the SBMLDocument_t structure
 * 
 * @return the SBML Level number
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_getLevel (const SBMLDocument_t *d)
{
  return (d != NULL) ? d->getLevel() : SBML_INT_MAX;
}


/**
 * Returns the Version within the SBML Level of the given SBMLDocument_t
 * structure.
 *
 * @param d the SBMLDocument_t structure
 * 
 * @return the version number
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_getVersion (const SBMLDocument_t *d)
{
  return (d != NULL) ? d->getVersion() : SBML_INT_MAX;
}


/**
 * Returns the Model object stored in this SBMLDocument_t structure.
 *
 * @param d the SBMLDocument_t structure
 * 
 * @return the Model contained in this SBMLDocument_t structure.
 */
LIBSBML_EXTERN
Model_t *
SBMLDocument_getModel (SBMLDocument_t *d)
{
  return (d != NULL) ? d->getModel() : NULL;
}


/**
 * Removes any FunctionDefinitions from the document and expands
 * any instances of their use within <math> elements.
 *
 * For example a Model contains a FunctionDefinition with id f
 * representing the math expression: f(x, y) = x * y.
 * The math element of the KineticLaw uses f(s, p).
 * The outcome of the function is that the math of the KineticLaw
 * now represents the math expression: s * p and the model no longer
 * contains any FunctionDefinitions.
 * 
 * @param d the SBMLDocument_t structure
 *
 * @return true (non-zero) if the transformation was successful,
 * false (0) otherwise.
 *
 * @note This function will check the consistency of a model
 * before attemptimg the transformation.  In the case of a model
 * with invalid SBML the transformation will not be done and the
 * function will return @false.
 * 
 */
LIBSBML_EXTERN
int
SBMLDocument_expandFunctionDefintions (SBMLDocument_t *d)
{
  return (d != NULL) ? 
    static_cast <int> (d->expandFunctionDefinitions()) : 0;
}


/**
 * Removes any InitialAssignments from the document and replaces
 * the appropriate values.
 *
 * For example a Model contains a InitialAssignment with symbol k
 * where k is the id of a Parameter.
 * The outcome of the function is that the value attribute of
 * the Parameter is the value calculated using the math expression
 * of the InitialAssignment and the corresponding InitialAssignment
 * has been removed from the Model.
 * 
 * @param d the SBMLDocument_t structure
 *
 * @return true (non-zero) if the transformation was successful,
 * false (0) otherwise.
 *
 *
 * @note This function will check the consistency of a model
 * before attemptimg the transformation.  In the case of a model
 * with invalid SBML the transformation will not be done and the
 * function will return @false.  As part of the process the 
 * function will check that it has values for any components
 * referred to by the math elements of InitialAssignments.  In
 * the case where not all values have been declared the particular
 * InitialAssignment will not be removed and the function will 
 * return @false.
 */
LIBSBML_EXTERN
int
SBMLDocument_expandInitialAssignments (SBMLDocument_t *d)
{
  return (d != NULL) ? 
    static_cast <int> (d->expandInitialAssignments()) : 0;
}


/**
 * Sets the SBML Level and Version of this SBMLDocument, attempting to
 * convert the model as needed.
 *
 * This method is used to convert models between Levels and Versions of
 * SBML.  Generally, models can be converted upward without difficulty
 * (e.g., from SBML Level 1 to Level 2, or from an earlier version of
 * Level 2 to the latest version of Level 2).  Sometimes models can be
 * translated downward as well, if they do not use constructs specific to
 * more advanced Levels of SBML.
 *
 * Callers can also check compatibility directly using the methods
 * checkL1Compatibility(), checkL2v1Compatibility(), and 
 * checkL2v2Compatibility().
 * 
 * The valid combinations as of this release of libSBML are the
 * following: 
 *
 * @li Level 1 Version 1
 * @li Level 1 Version 2
 * @li Level 2 Version 1
 * @li Level 2 Version 2
 * @li Level 2 Version 3
 * @li Level 2 Version 4
 *
 * @param d the SBMLDocument_t structure
 *
 * @param level the desired SBML Level
 *
 * @param version the desired Version within the SBML Level
 *
 * @note Calling this method will not @em necessarily lead to successful
 * conversion.  If the conversion fails, it will be logged in the error
 * list associated with this SBMLDocument_t structure.  Callers should
 * consult getNumErrors() to find out if the conversion succeeded without
 * problems.  For conversions from Level 2 to Level 1, callers can also
 * check the Level of the model after calling this method to find out
 * whether it is Level 1.  (If the conversion to Level 1 failed, the Level
 * of this model will be left unchanged.)
 */
LIBSBML_EXTERN
int
SBMLDocument_setLevelAndVersion (  SBMLDocument_t *d
                                 , unsigned int    level
                                 , unsigned int    version )
{
  return (d != NULL) ? 
    static_cast <int> (d->setLevelAndVersion(level, version, true)) : 0;
}


/**
 * Sets the SBML Level and Version of this SBMLDocument, attempting to
 * convert the model as needed.
 *
 * This method is used to convert models between Levels and Versions of
 * SBML.  Generally, models can be converted upward without difficulty
 * (e.g., from SBML Level 1 to Level 2, or from an earlier version of
 * Level 2 to the latest version of Level 2).  Sometimes models can be
 * translated downward as well, if they do not use constructs specific to
 * more advanced Levels of SBML.
 *
 * Callers can also check compatibility directly using the methods
 * checkL1Compatibility(), checkL2v1Compatibility(), and 
 * checkL2v2Compatibility().
 * 
 * The valid combinations as of this release of libSBML are the
 * following: 
 *
 * @li Level 1 Version 1
 * @li Level 1 Version 2
 * @li Level 2 Version 1
 * @li Level 2 Version 2
 * @li Level 2 Version 3
 * @li Level 2 Version 4
 *
 * @param d the SBMLDocument_t structure
 *
 * @param level the desired SBML Level
 *
 * @param version the desired Version within the SBML Level
 *
 * @note Calling this method will not @em necessarily lead to successful
 * conversion.  If the conversion fails, it will be logged in the error
 * list associated with this SBMLDocument_t structure.  Callers should
 * consult getNumErrors() to find out if the conversion succeeded without
 * problems.  For conversions from Level 2 to Level 1, callers can also
 * check the Level of the model after calling this method to find out
 * whether it is Level 1.  (If the conversion to Level 1 failed, the Level
 * of this model will be left unchanged.)
 *
 *
 * Strict conversion applies the additional criteria that both the source
 * and the target model must be consistent SBML.  Users can control the
 * consistency checks that are applied using the 
 * SBMLDocument::setConsistencyChecks function.  If either the source
 * or the potential target model have validation errors, the conversion
 * is not performed.  When a strict conversion is successful, the
 * underlying SBML object model is altered to reflect the new level
 * and version.  Thus information that cannot be converted (e.g. sboTerms)
 * will be lost.  
 */
LIBSBML_EXTERN
int
SBMLDocument_setLevelAndVersionStrict (  SBMLDocument_t *d
                                       , unsigned int    level
                                       , unsigned int    version )
{
  return (d != NULL) ? 
    static_cast <int> (d->setLevelAndVersion(level, version, true)) : 0;
}


/**
 * Sets the SBML Level and Version of this SBMLDocument, attempting to
 * convert the model as needed.
 *
 * This method is used to convert models between Levels and Versions of
 * SBML.  Generally, models can be converted upward without difficulty
 * (e.g., from SBML Level 1 to Level 2, or from an earlier version of
 * Level 2 to the latest version of Level 2).  Sometimes models can be
 * translated downward as well, if they do not use constructs specific to
 * more advanced Levels of SBML.
 *
 * Callers can also check compatibility directly using the methods
 * checkL1Compatibility(), checkL2v1Compatibility(), and 
 * checkL2v2Compatibility().
 * 
 * The valid combinations as of this release of libSBML are the
 * following: 
 *
 * @li Level 1 Version 1
 * @li Level 1 Version 2
 * @li Level 2 Version 1
 * @li Level 2 Version 2
 * @li Level 2 Version 3
 * @li Level 2 Version 4
 *
 * @param d the SBMLDocument_t structure
 *
 * @param level the desired SBML Level
 *
 * @param version the desired Version within the SBML Level
 *
 * @note Calling this method will not @em necessarily lead to successful
 * conversion.  If the conversion fails, it will be logged in the error
 * list associated with this SBMLDocument_t structure.  Callers should
 * consult getNumErrors() to find out if the conversion succeeded without
 * problems.  For conversions from Level 2 to Level 1, callers can also
 * check the Level of the model after calling this method to find out
 * whether it is Level 1.  (If the conversion to Level 1 failed, the Level
 * of this model will be left unchanged.)
 */
LIBSBML_EXTERN
int
SBMLDocument_setLevelAndVersionNonStrict (  SBMLDocument_t *d
                                 , unsigned int    level
                                 , unsigned int    version )
{
  return (d != NULL) ? 
    static_cast <int> (d->setLevelAndVersion(level, version, false)) : 0;
}


/**
 * Sets the model contained in the given SBMLDocument_t structure to a copy
 * of the given Model_t structure.
 *
 * @param d the SBMLDocument_t structure
 *
 * @param m the new Model_t structure to use.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_LEVEL_MISMATCH
 * @li LIBSBML_VERSION_MISMATCH
 */
LIBSBML_EXTERN
int
SBMLDocument_setModel (SBMLDocument_t *d, const Model_t *m)
{
  return (d != NULL) ? d->setModel(m) : LIBSBML_INVALID_OBJECT;
}


/**
 * Creates a new Model_t structure inside the given SBMLDocument_t
 * structure and returns a pointer to it.
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the Model_t structure created
 */
LIBSBML_EXTERN
Model_t *
SBMLDocument_createModel (SBMLDocument_t *d)
{
  return (d != NULL) ? d->createModel() : NULL;
}

/**
 * Allows particular validators to be turned on or off prior to
 * calling checkConsistency. 
 *
 * The second argument (@p category) to this method indicates which
 * category of consistency/error checks are being turned on or off, and
 * the second argument (a boolean) indicates whether to turn on (value of
 * @c true) or off (value of @c false) that particula category of checks.
 * The possible categories are represented as values of the enumeration
 * SBMLErrorCategory_t.  The following are the possible choices in libSBML
 * version 3.0.2:
 *
 * @li LIBSBML_CAT_GENERAL_CONSISTENCY:    General overall SBML consistency.
 * 
 * @li LIBSBML_CAT_IDENTIFIER_CONSISTENCY: Consistency of identifiers.  An
 * example of inconsistency would be using a species identifier in a
 * reaction rate formula without first having declared the species.
 * 
 * @li LIBSBML_CAT_UNITS_CONSISTENCY:      Consistency of units of measure.
 * 
 * @li LIBSBML_CAT_MATHML_CONSISTENCY:     Consistency of MathML constructs.
 * 
 * @li LIBSBML_CAT_SBO_CONSISTENCY:        Consistency of SBO identifiers.
 * 
 * @li LIBSBML_CAT_OVERDETERMINED_MODEL:   Checking whether the system of
 * equations implied by a model is mathematically overdetermined.
 * 
 * @li LIBSBML_CAT_MODELING_PRACTICE:      General good practice in
 * model construction.
 * 
 * By default, all validation checks are applied to the model in an
 * SBMLDocument object @em unless setConsistencyChecks() is called to
 * indicate that only a subset should be applied.
 *
 * @param d the SBMLDocument_t structure
 *
 * @param category a value drawn from SBMLErrorCategory_t indicating the
 * consistency checking/validation to be turned on or off
 *
 * @param apply a boolean indicating whether the checks indicated by @p
 * category should be applied or not. 
 * 
 * @note The default (i.e., performing all checks) applies to each new
 * SBMLDocument object created.  This means that each time a model is
 * read using SBMLReader::readSBML(), SBMLReader::readSBMLFromString, or
 * the global functions readSBML() and readSBMLFromString(), a new
 * SBMLDocument is created and for that document all checks are enabled.
 *
 * @see SBMLDocument_checkConsistency()
 */
LIBSBML_EXTERN
void
SBMLDocument_setConsistencyChecks(SBMLDocument_t * d, 
                                  SBMLErrorCategory_t category,
                                  int apply)
{
  if (d != NULL)
    d->setConsistencyChecks(SBMLErrorCategory_t(category), apply);
}


/**
 * Allows particular validators to be turned on or off prior to
 * calling setLevelAndVersion. 
 *
 * The second argument (@p category) to this method indicates which
 * category of consistency/error checks are being turned on or off, and
 * the second argument (a boolean) indicates whether to turn on (value of
 * @c true) or off (value of @c false) that particula category of checks.
 * The possible categories are represented as values of the enumeration
 * SBMLErrorCategory_t.  The following are the possible choices in libSBML
 * version 3.0.2:
 *
 * @li LIBSBML_CAT_GENERAL_CONSISTENCY:    General overall SBML consistency.
 * 
 * @li LIBSBML_CAT_IDENTIFIER_CONSISTENCY: Consistency of identifiers.  An
 * example of inconsistency would be using a species identifier in a
 * reaction rate formula without first having declared the species.
 * 
 * @li LIBSBML_CAT_UNITS_CONSISTENCY:      Consistency of units of measure.
 * 
 * @li LIBSBML_CAT_MATHML_CONSISTENCY:     Consistency of MathML constructs.
 * 
 * @li LIBSBML_CAT_SBO_CONSISTENCY:        Consistency of SBO identifiers.
 * 
 * @li LIBSBML_CAT_OVERDETERMINED_MODEL:   Checking whether the system of
 * equations implied by a model is mathematically overdetermined.
 * 
 * @li LIBSBML_CAT_MODELING_PRACTICE:      General good practice in
 * model construction.
 * 
 * By default, all validation checks are applied to the model in an
 * SBMLDocument object @em unless setConsistencyChecks() is called to
 * indicate that only a subset should be applied.
 *
 * @param d the SBMLDocument_t structure
 *
 * @param category a value drawn from SBMLErrorCategory_t indicating the
 * consistency checking/validation to be turned on or off
 *
 * @param apply a boolean indicating whether the checks indicated by @p
 * category should be applied or not. 
 * 
 * @note The default (i.e., performing all checks) applies to each new
 * SBMLDocument object created.  This means that each time a model is
 * read using SBMLReader::readSBML(), SBMLReader::readSBMLFromString, or
 * the global functions readSBML() and readSBMLFromString(), a new
 * SBMLDocument is created and for that document all checks are enabled.
 *
 * @see SBMLDocument_setLevelAndVersionStrict()
 */
LIBSBML_EXTERN
void
SBMLDocument_setConsistencyChecksForConversion(SBMLDocument_t * d, 
                                  SBMLErrorCategory_t category,
                                  int apply)
{
  if (d != NULL)
    d->setConsistencyChecksForConversion(SBMLErrorCategory_t(category), apply);
}


/**
 * Performs a set of consistency and validation checks on the given SBML
 * document.
 *
 * If this method returns a nonzero value (meaning, one or more
 * consistency checks have failed for SBML document), the failures may be
 * due to warnings @em or errors.  Callers should inspect the severity
 * flag in the individual SBMLError objects returned by getError() to
 * determine the nature of the failures.
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_checkConsistency (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkConsistency() : SBML_INT_MAX;
}


/**
 * Performs consistency checking on libSBML's internal representation of 
 * an SBML Model.
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 *
 * @note The consistency checks performed by this function are limited
 * to inconsistencies that are not caught by other consistency checks.
 * @see setConsistencyChecks()
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_checkInternalConsistency (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkInternalConsistency() : SBML_INT_MAX;
}


/**
 * Performs a set of consistency checks on the document to establish
 * whether it is compatible with SBML Level 1 and can be converted to
 * Level 1.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int 
SBMLDocument_checkL1Compatibility (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkL1Compatibility() : SBML_INT_MAX;
}


/**
 * Performs a set of consistency checks on the document to establish
 * whether it is compatible with SBML Level 2 Version 1 and can be
 * converted to Level 2 Version 1.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int 
SBMLDocument_checkL2v1Compatibility (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkL2v1Compatibility() : SBML_INT_MAX;
}



/**
 * Performs a set of consistency checks on the document to establish
 * whether it is compatible with SBML Level 2 Version 2 and can be
 * converted to Level 2 Version 2.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int 
SBMLDocument_checkL2v2Compatibility (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkL2v2Compatibility() : SBML_INT_MAX;
}



/**
 * Performs a set of consistency checks on the document to establish
 * whether it is compatible with SBML Level 2 Version 3 and can be
 * converted to Level 2 Version 3.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int 
SBMLDocument_checkL2v3Compatibility (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkL2v3Compatibility() : SBML_INT_MAX;
}


/**
 * Performs a set of consistency checks on the document to establish
 * whether it is compatible with SBML Level 2 Version 4 and can be
 * converted to Level 2 Version 4.
 *
 * Callers should query the results of the consistency check by calling
 * getError().
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of failed checks (errors) encountered.
 */
LIBSBML_EXTERN
unsigned int 
SBMLDocument_checkL2v4Compatibility (SBMLDocument_t *d)
{
  return (d != NULL) ? d->checkL2v4Compatibility() : SBML_INT_MAX;
}


/**
 * Returns the nth error or warning encountered during parsing,
 * consistency checking, or attempted translation of this model.
 *
 * Callers can use method XMLError_getSeverity() on the result to assess
 * the severity of the problem.  The severity levels range from
 * informationl messages to fatal errors.
 *
 * @return the error or warning indexed by integer @p n, or return @c NULL
 * if n > (SBMLDocument_getNumErrors() - 1).
 *
 * @param d the SBMLDocument_t structure
 *
 * @param n the index of the error sought.
 *
 * @see SBMLDocument_getNumErrors(), SBMLDocument_setLevelAndVersion(),
 * SBMLDocument_checkConsistency(), SBMLDocument_checkL1Compatibility(),
 * SBMLDocument_checkL2v1Compatibility()
 * SBMLDocument_checkL2v2Compatibility(), SBMLReader_readSBML(),
 * SBMLReader_readSBMLFromString().
 */
LIBSBML_EXTERN
const SBMLError_t *
SBMLDocument_getError (SBMLDocument_t *d, unsigned int n)
{
  return (d != NULL) ? d->getError(n) : NULL;
}


/**
 * Returns the number of errors or warnings encountered during parsing,
 * consistency checking, or attempted translation of this model.
 *
 * @param d the SBMLDocument_t structure
 *
 * @return the number of errors or warnings encountered
 *
 * @see SBMLDocument_setLevelAndVersion(), SBMLDocument_checkConsistency(),
 * SBMLDocument_checkL1Compatibility(),
 * SBMLDocument_checkL2v1Compatibility()
 * SBMLDocument_checkL2v2Compatibility(), SBMLReader_readSBML(),
 * SBMLReader_readSBMLFromString().
 */
LIBSBML_EXTERN
unsigned int
SBMLDocument_getNumErrors (const SBMLDocument_t *d)
{
  return (d != NULL) ? d->getNumErrors() : SBML_INT_MAX;
}


/**
 * Prints to the given output stream all the errors or warnings
 * encountered during parsing, consistency checking, or attempted
 * translation of this model.
 *
 * If no errors have occurred, i.e., SBMLDocument_getNumErrors() == 0, no
 * output will be sent to the stream.
 *
 * The format of the output is:
 *
 *   N error(s):
 *     line NNN: (id) message
 *
 * @param d the SBMLDocument_t structure
 * 
 * @param stream the output stream where the messages should be printed
 */
LIBSBML_EXTERN
void
SBMLDocument_printErrors (SBMLDocument_t *d, FILE *stream)
{
  if (d == NULL) return;
  unsigned int numErrors = d->getNumErrors();

  if (numErrors > 0)
  {
    for (unsigned int n = 0; n < numErrors; n++)
    {
      XMLError_print(d->getError(n), stream);
    }
  }
}


/**
 * @return the most recent SBML specification level (at the time this
 * libSBML was released).
 */
unsigned int
SBMLDocument_getDefaultLevel ()
{
  return SBMLDocument::getDefaultLevel();
}


/**
 * @return the most recent SBML specification version (at the time this
 * libSBML was released).
 */
unsigned int
SBMLDocument_getDefaultVersion ()
{
  return SBMLDocument::getDefaultVersion();
}

/**
 * Returns a list of XMLNamespaces_t associated with the XML content
 * of this SBML document.
 *
 * @param d the SBMLDocument_t structure
 * 
 * @return pointer to the XMLNamespaces_t structure associated with this SBML object
 */
LIBSBML_EXTERN
const XMLNamespaces_t *
SBMLDocument_getNamespaces(SBMLDocument_t *d)
{
  return (d != NULL) ? d->getNamespaces() : NULL;
}

/** @endcond */
LIBSBML_CPP_NAMESPACE_END
