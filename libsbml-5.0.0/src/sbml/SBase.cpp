/**
 * @file    SBase.cpp
 * @brief   Implementation of SBase, the base object of all SBML objects.
 * @author  Ben Bornstein
 *
 * $Id: SBase.cpp 10188 2009-09-23 11:49:40Z sarahkeating $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/sbml/SBase.cpp $
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

#include <sstream>

#include <sbml/xml/XMLError.h>
#include <sbml/xml/XMLErrorLog.h>
#include <sbml/xml/XMLOutputStream.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLNode.h>

#include <sbml/util/util.h>

#include <sbml/annotation/RDFAnnotation.h>

#include <sbml/KineticLaw.h>
#include <sbml/SBMLError.h>
#include <sbml/SBMLErrorLog.h>
#include <sbml/SBMLDocument.h>
#include <sbml/Model.h>
#include <sbml/ListOf.h>
#include <sbml/SBase.h>

#include <sbml/extension/SBasePlugin.h>
#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/extension/SBMLExtensionException.h>


/** @cond doxygen-ignored */

using namespace std;

LIBSBML_CPP_NAMESPACE_BEGIN

/** @endcond */


/** @cond doxygen-libsbml-internal */

SBMLConstructorException::SBMLConstructorException(std::string errmsg) :
       std::invalid_argument("Level/version/namespaces combination is invalid")
     , mSBMLErrMsg(errmsg)
{
}

SBMLConstructorException::~SBMLConstructorException() throw()
{
}


/** @endcond */

/** @cond doxygen-libsbml-internal */

/**
 * Used by the Destructor to delete each item in mPlugins.
 */
struct DeletePluginEntity : public unary_function<SBasePlugin*, void>
{
  void operator() (SBasePlugin* sb) { delete sb; }
};


/**
 * Used by the Copy Constructor to clone each item in mPlugins.
 */
struct ClonePluginEntity : public unary_function<SBasePlugin*, SBasePlugin*>
{
  SBasePlugin* operator() (SBasePlugin* sb) { 
    if (!sb) return 0;
    return sb->clone(); 
  }
};

/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Creates a new SBase object with the given level and version.
 * Only subclasses may create SBase objects.
 */
SBase::SBase (unsigned int level, unsigned int version) :
   mNotes     ( NULL )
 , mAnnotation( NULL )
 , mSBML      ( NULL )
 , mSBMLNamespaces (NULL)
 , mSBOTerm   ( -1 )
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentSBMLObject (NULL)
 , mCVTerms   ( NULL )
 , mHistory   ( NULL )
 , mHasBeenDeleted (false)
 , mEmptyString ("")
 , mURI("")
{
  mSBMLNamespaces = new SBMLNamespaces(level, version);

  //
  // Sets the XMLNS URI of corresponding SBML Level/Version to
  // the element namespace (mURI) of this object.
  //
  // (NOTES) Package developers must (1) override the mSBMLNamespaces of this
  //         object with the corresponding SBMLExtensionNamespaces (template) 
  //         class in their packages and (2) override the element namespace (mURI)
  //         of this object with the corresponding package's URI in the constructor
  //         of SBase derived class in thier packages.
  //
  setElementNamespace(mSBMLNamespaces->getURI());
}



/*
 * Creates a new SBase object with the given SBMLNamespaces.
 * Only subclasses may create SBase objects.
 */
SBase::SBase (SBMLNamespaces *sbmlns) :
   mNotes     ( NULL )
 , mAnnotation( NULL )
 , mSBML      ( NULL )
 , mSBMLNamespaces (NULL)
 , mSBOTerm   ( -1 )
 , mLine      ( 0 )
 , mColumn    ( 0 )
 , mParentSBMLObject (NULL)
 , mCVTerms   ( NULL )
 , mHistory   ( NULL )
 , mHasBeenDeleted (false)
 , mEmptyString ("")
 , mURI("")
{
  if (!sbmlns) 
  {
    std::string err("SBase::SBase(SBMLNamespaces*, SBaseExtensionPoint*) : SBMLNamespaces is null");
    throw SBMLConstructorException(err);
  }
  mSBMLNamespaces = sbmlns->clone();

  //
  // Sets the XMLNS URI of corresponding SBML Level/Version to
  // the element namespace (mURI) of this object.
  //
  // (NOTES) Package developers must override the element namespace (mURI)
  //         of this object with the corresponding package's URI in the constructor
  //         of SBase derived class in thier packages.
  //

#if 0
    cout << "[DEBUG] SBase::SBase(SBMLNamespaces*,...) " << static_cast<SBMLNamespaces>(*mSBMLNamespaces).getURI() << endl;
#endif

  setElementNamespace(static_cast<SBMLNamespaces>(*mSBMLNamespaces).getURI());
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Copy constructor. Creates a copy of this SBase object.
 */
SBase::SBase(const SBase& orig)
{
  if (&orig == NULL)
  {
    throw SBMLConstructorException("Null argument to copy constructor");
  }
  this->mMetaId = orig.mMetaId;

  if(orig.mNotes != NULL) 
    this->mNotes = new XMLNode(*const_cast<SBase&>(orig).getNotes());
  else
    this->mNotes = NULL;
  
  if(orig.mAnnotation != NULL) 
    this->mAnnotation = new XMLNode(*const_cast<SBase&>(orig).mAnnotation);
  else
    this->mAnnotation = NULL;
 
  /* the copy does not contain a pointer to the document since technically
   * a copy is not part of the document
   */
  this->mSBML       = NULL;
  this->mSBOTerm    = orig.mSBOTerm;
  this->mLine       = orig.mLine;
  this->mColumn     = orig.mColumn;
  this->mParentSBMLObject = NULL;

  /* if the object belongs to document that has had the level/version reset
   * the copy will end up with the wrong namespace information
   * need to use the default namespace NOT the namespace local to the object
   */
  if(orig.getSBMLNamespaces() != NULL)
    this->mSBMLNamespaces = 
    new SBMLNamespaces(*const_cast<SBase&>(orig).getSBMLNamespaces());
  else
    this->mSBMLNamespaces = NULL;

  if(orig.mCVTerms != NULL)
  {
    this->mCVTerms  = new List();
    unsigned int i,iMax = orig.mCVTerms->getSize();
    for(i = 0; i < iMax; ++i)
    {
      this->mCVTerms
        ->add(static_cast<CVTerm*>(orig.mCVTerms->get(i))->clone());
    }
  }
  else
  {
    this->mCVTerms = NULL;
  }

  if (orig.mHistory != NULL)
  {
    this->mHistory = orig.mHistory->clone();
  }
  else
  {
    this->mHistory = NULL;
  }

  this->mHasBeenDeleted = false;

  this->mURI = orig.mURI;

  mPlugins.resize( orig.mPlugins.size() );
  transform( orig.mPlugins.begin(), orig.mPlugins.end(), 
             mPlugins.begin(), ClonePluginEntity() );
}
/** @endcond */


/*
 * Destroy this SBase object.
 */
SBase::~SBase ()
{
  if (mNotes != NULL)       delete mNotes;
  if (mAnnotation != NULL)  delete mAnnotation;
  if (mSBMLNamespaces != NULL)  delete mSBMLNamespaces;
  if (mCVTerms != NULL)
  {  
    unsigned int size = mCVTerms->getSize();
    while (size--) delete static_cast<CVTerm*>( mCVTerms->remove(0) );
    delete mCVTerms;
  }
  if (mHistory != NULL) delete mHistory;
  mHasBeenDeleted = true;

  for_each( mPlugins.begin(), mPlugins.end(), DeletePluginEntity() );
}

/*
 * Assignment operator
 */
SBase& SBase::operator=(const SBase& rhs)
{
  if (&rhs == NULL)
  {
    throw SBMLConstructorException("Null argument to assignment operator");
  }
  else if(&rhs!=this)
  {
    this->mMetaId = rhs.mMetaId;

    delete this->mNotes;

    if(rhs.mNotes != NULL) 
      this->mNotes = new XMLNode(*const_cast<SBase&>(rhs).getNotes());
    else
      this->mNotes = NULL;

    delete this->mAnnotation;

    if(rhs.mAnnotation != NULL) 
      this->mAnnotation = new XMLNode(*const_cast<SBase&>(rhs).mAnnotation);
    else
      this->mAnnotation = NULL;

    this->mSBML       = rhs.mSBML;
    this->mSBOTerm    = rhs.mSBOTerm;
    this->mLine       = rhs.mLine;
    this->mColumn     = rhs.mColumn;
    this->mParentSBMLObject = rhs.mParentSBMLObject;

    delete this->mSBMLNamespaces;

    if(rhs.mSBMLNamespaces != NULL)
      this->mSBMLNamespaces = 
      new SBMLNamespaces(*const_cast<SBase&>(rhs).mSBMLNamespaces);
    else
      this->mSBMLNamespaces = NULL;


    if(this->mCVTerms != NULL)
    {  
      unsigned int size = this->mCVTerms->getSize();
      while (size--) delete static_cast<CVTerm*>( this->mCVTerms->remove(0) );
      delete this->mCVTerms;
    }

    if(rhs.mCVTerms != NULL)
    {
      this->mCVTerms  = new List();
      unsigned int i,iMax = rhs.mCVTerms->getSize();
      for(i = 0; i < iMax; ++i)
      {
        this->mCVTerms
          ->add(static_cast<CVTerm*>(rhs.mCVTerms->get(i))->clone());
      }
    }
    else
    {
      this->mCVTerms = NULL;
    }

    delete this->mHistory;
    if (rhs.mHistory != NULL)
    {
      this->mHistory = rhs.mHistory->clone();
    }
    else
    {
      this->mHistory = NULL;
    }

    this->mHasBeenDeleted = rhs.mHasBeenDeleted;
    this->mURI = rhs.mURI;

    for_each( mPlugins.begin(), mPlugins.end(), DeletePluginEntity() );
    mPlugins.resize( rhs.mPlugins.size() );
    transform( rhs.mPlugins.begin(), rhs.mPlugins.end(), 
               mPlugins.begin(), ClonePluginEntity() );
  }

  return *this;
}


/** @cond doxygen-libsbml-internal */
/*
 * Loads SBasePlugin derived objects corresponding to the URIs contained
 * in the given SBMLNamespaces (if any) for package extension.
 */
void
SBase::loadPlugins(SBMLNamespaces *sbmlns)
{
  if (!sbmlns) return;

  //
  // (EXTENSION)
  //
  XMLNamespaces *xmlns = sbmlns->getNamespaces();

  if (xmlns)
  {
    int numxmlns= xmlns->getLength();
    SBaseExtensionPoint extPoint(getPackageName(), getTypeCode());

    for (int i=0; i < numxmlns; i++)
    {
      const std::string &uri = xmlns->getURI(i);
      const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);

      if (sbmlext && sbmlext->isEnabled())
      {
#if 0
          cout << "[DEBUG] SBase::loadPlugins() " << uri 
               << " is registered in " 
               << SBMLTypeCode_toString(getTypeCode(), getPackageName().c_str()) 
               << endl;
#endif
        const std::string &prefix = xmlns->getPrefix(i);
        const SBasePluginCreatorBase* sbPluginCreator = sbmlext->getSBasePluginCreator(extPoint);
        if (sbPluginCreator)
        {
          // (debug)
          //cout << "sbPluginCreator " << sbPluginCreator << endl;
          //sbPluginCreator->createPlugin(uri,prefix);
          // (debug)
          SBasePlugin* entity = sbPluginCreator->createPlugin(uri,prefix,xmlns);
          entity->connectToParent(this);
          mPlugins.push_back(entity);
        }
#if 0
        else
        {
            cout << "[DEBUG] SBase::loadPlugins() " << uri 
                 << " is not registered in " 
                 << SBMLTypeCode_toString(getTypeCode(), getPackageName().c_str()) 
                 << endl;
        }
#endif
      }
      else 
      {
	//
	// (NOTE)
        //
	// SBMLExtensionException should be thrown if the corresponding package 
        // extension is not loaded.
        // However, currently, no idea how to check if the uri belongs to extension
        // package or not (e.g. XHTML namespace or other namespace can be given).
	//
#if 0
        std::ostringstream errMsg;

        if (sbmlext)
        {	  
          errMsg << "Package \"" << sbmlext->getName() << "\" (" << uri << ") for \"<" 
                 << SBMLTypeCode_toString(getTypeCode(), getPackageName().c_str()) 
                 << ">\" element is disabled.";
	}
	else
        {
          errMsg << "Package \"" << uri << "\" for \"<" 
                 << SBMLTypeCode_toString(getTypeCode(), getPackageName().c_str()) 
                 << ">\" element is not supported.";
        }	  

        throw SBMLExtensionException(errMsg.str());
#endif
      }
    }
  }
}
/** @endcond */


/*
 * @return the metaid of this SBML object.
 */
const string&
SBase::getMetaId () const
{
  return mMetaId;
}


/*
 * @return the metaid of this SBML object.
 */
string&
SBase::getMetaId ()
{
  return mMetaId;
}


/** @cond doxygen-libsbml-internal */

/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 *
 * @return the id of this SBML object.
 */
const string&
SBase::getId () const
{
  return mEmptyString;
}



/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 *
 * @return the name of this SBML object.
 */
const string&
SBase::getName () const
{
  return mEmptyString;
}

/** @endcond */

/*
 * @return the notes of this SBML object.
 */
XMLNode*
SBase::getNotes()
{
  return mNotes;
}


/*
 * @return the notes of this SBML object by string.
 */
std::string
SBase::getNotesString() 
{
  return XMLNode::convertXMLNodeToString(mNotes);
}


/*
 * @return the annotation of this SBML object.
 */
XMLNode* 
SBase::getAnnotation ()
{
  syncAnnotation();

  return mAnnotation;
}


/*
 * @return the annotation of this SBML object by string.
 */
std::string
SBase::getAnnotationString ()
{
  return XMLNode::convertXMLNodeToString(getAnnotation());
}


/*
 * @return the Namespaces associated with this SBML object
 */
XMLNamespaces*
SBase::getNamespaces() const
{
  if (mSBML != NULL)
    return mSBML->getSBMLNamespaces()->getNamespaces();
  else
    return mSBMLNamespaces->getNamespaces();
}


/*
 * @return the parent SBMLDocument of this SBML object.
 */
const SBMLDocument*
SBase::getSBMLDocument () const
{
  if (mSBML != NULL)
  {
    // if the doc object has been deleted the pointer is 
    // still valid but points to nothing
    try 
    {
      if (mSBML->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mSBML;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }

  return mSBML;
}

/*
 * @return the parent SBMLDocument of this SBML object.
 */
SBMLDocument*
SBase::getSBMLDocument ()
{
  if (mSBML != NULL)
  {
    // if the doc object has been deleted the pointer is 
    // still valid but points to nothing
    try 
    {
      if (mSBML->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mSBML;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }
  return mSBML;
}
SBase*
SBase::getParentSBMLObject ()
{
  if (mParentSBMLObject != NULL)
  {
    // if the parent object has been deleted the pointer is 
    // still valid but points to nothing
    try 
    {
      if (mParentSBMLObject->getHasBeenDeleted())
      {
        return NULL;
      }
      else
      {
        return mParentSBMLObject;
      }
    }
    catch ( ... )
    {
      return NULL;
    }
  }
  
  return mParentSBMLObject;
}

/*
 * @return the sboTerm as an integer.  If not set,
 * sboTerm will be -1. 
 */
int
SBase::getSBOTerm () const
{
  return mSBOTerm;
}


/*
 * @return the sboTerm as a string.  If not set,
 * return an empty string.
 */
std::string
SBase::getSBOTermID () const
{
  return SBO::intToString(mSBOTerm);
}


/*
 * @return the line number of this SBML object.
 */
unsigned int
SBase::getLine () const
{
  return mLine;
}


/*
 * @return the column number of this SBML object.
 */
unsigned int
SBase::getColumn () const
{
  return mColumn;
}


ModelHistory* 
SBase::getModelHistory() const
{
  return mHistory;
}

ModelHistory* 
SBase::getModelHistory()
{
  return mHistory;
}


/*
 * @return true if the metaid of this SBML object is set, false
 * otherwise.
 */
bool
SBase::isSetMetaId () const
{
  return (mMetaId.empty() == false);
}


/** @cond doxygen-libsbml-internal */

/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 *
 * @return true if the id of this SBML object is set, false
 * otherwise.
 */
bool
SBase::isSetId () const
{
  return (getId().empty() == false);
}


/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 *
 * @return true if the name of this SBML object is set, false
 * otherwise.
 */
bool
SBase::isSetName () const
{
  return (getName().empty() == false);
}


/** @endcond */


/*
 * @return true if the notes of this SBML object is set, false
 * otherwise.
 */
bool
SBase::isSetNotes () const
{
  return (mNotes != NULL);
}


/*
 * @return true if the annotation of this SBML object is set,
 * false otherwise.
 */
bool
SBase::isSetAnnotation () const
{
  const_cast <SBase *> (this)->syncAnnotation();
  return (mAnnotation != NULL);
}


/*
 * @return true if the sboTerm is set, false
 * otherwise.
 */
bool
SBase::isSetSBOTerm () const
{
  return (mSBOTerm != -1);
}


bool
SBase::isSetModelHistory()
{
  return (mHistory != NULL);
}


/*
 * Sets the metaid field of the given SBML object to a copy of metaid.
 */
int
SBase::setMetaId (const std::string& metaid)
{
  if (&(metaid) == NULL)
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else if (getLevel() == 1)
  {
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }
  else if (metaid.empty())
  {
    mMetaId.erase();
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (!(SyntaxChecker::isValidXMLID(metaid)))
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    mMetaId = metaid;
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/** @cond doxygen-libsbml-internal */

/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 *
 * Sets the id of this SBML object to a copy of sid.
 */
int
SBase::setId (const std::string& sid)
{
  return LIBSBML_UNEXPECTED_ATTRIBUTE;
}


/*
 * NOTE: THIS IS FOR BACKWARD COMPATABILITY REASONS
 * Sets the name of this SBML object to a copy of name.
 */
int
SBase::setName (const std::string& name)
{
  return LIBSBML_UNEXPECTED_ATTRIBUTE;
}


/** @endcond */


/*
 * Sets the annotation of this SBML object to a copy of annotation.
 */
int 
SBase::setAnnotation (const XMLNode* annotation)
{
  //
  // (*NOTICE*) 
  //
  // syncAnnotation() must not be invoked in this function.
  // 
  // 

  if (annotation == NULL)
  {
    delete mAnnotation;
    mAnnotation = NULL;
  }
  //else if (!(math->isWellFormedASTNode()))
  //{
  //  return LIBSBML_INVALID_OBJECT;
  //}
  else if (mAnnotation != annotation)
  { 
    delete mAnnotation;
    // check for annotation tags and add if necessary
    const string&  name = annotation->getName();
    if (name != "annotation")
    {
      XMLToken ann_t = XMLToken(XMLTriple("annotation", "", ""), 
                                XMLAttributes());
      mAnnotation = new XMLNode(ann_t);

      // The root node of the given XMLNode tree can be an empty XMLNode 
      // (i.e. neither start, end, nor text XMLNode) if the given annotation was 
      // converted from an XML string whose top level elements are neither 
      // "html" nor "body" and not enclosed with <annotation>..</annotation> tags
      // (e.g. <foo xmlns:foo="...">..</foo><bar xmlns:bar="...">..</bar> ) 
      if (!annotation->isStart() && !annotation->isEnd() && 
                                    !annotation->isText()) 
      {
        for (unsigned int i=0; i < annotation->getNumChildren(); i++)
        {
          mAnnotation->addChild(annotation->getChild(i));
        }
      }
      else
      {
        mAnnotation->addChild(*annotation);
      }
    }
    else
    {
      mAnnotation = annotation->clone();
    }
  }

  //
  // delete existing mCVTerms
  //
  // existing CVTerms (if any) needs to be deleted at any rate, otherwise
  // unsetAnnotation() ( setAnnotation(NULL) ) doesn't work as expected.
  // (These functions must clear all elements in an annotation.)
  //
  
  /* in L3 might be a model history */
  if (mHistory != NULL)
  {
    delete mHistory;
    mHistory = NULL;
  }

  if (mCVTerms != NULL)
  {
    // delete existing mCVTerms (if any)
    unsigned int size = mCVTerms->getSize();
    while (size--) delete static_cast<CVTerm*>( mCVTerms->remove(0) );
    delete mCVTerms;
    mCVTerms = NULL;
  }


  if(mAnnotation != NULL 
        && RDFAnnotationParser::hasCVTermRDFAnnotation(mAnnotation))
  {
    // parse mAnnotation (if any) and set mCVTerms 
    mCVTerms = new List();
    RDFAnnotationParser::parseRDFAnnotation(mAnnotation, mCVTerms);
  }

  if(getLevel() > 2 && mAnnotation != NULL 
     && RDFAnnotationParser::hasHistoryRDFAnnotation(mAnnotation))
  {
    // parse mAnnotation (if any) and set mHistory
    mHistory = RDFAnnotationParser::parseRDFAnnotation(mAnnotation);
  }

  return LIBSBML_OPERATION_SUCCESS;
}

/*
 * Sets the annotation (by string) of this SBML object to a copy of annotation.
 */
int
SBase::setAnnotation (const std::string& annotation)
{
  if (&(annotation) == NULL)
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else  
  {
    int success = LIBSBML_OPERATION_FAILED;

    //
    // (*NOTICE*) 
    //
    // syncAnnotation() must not be invoked in this function.
    // 
    // 

    if(annotation.empty()) 
    {
      unsetAnnotation();
      return LIBSBML_OPERATION_SUCCESS;
    }

    XMLNode* annt_xmln;

    // you might not have a document !!
    if (getSBMLDocument() != NULL)
    {
      XMLNamespaces* xmlns = getSBMLDocument()->getNamespaces();
      annt_xmln = XMLNode::convertStringToXMLNode(annotation,xmlns); 
    }
    else
    {
      annt_xmln = XMLNode::convertStringToXMLNode(annotation);
    }

    if(annt_xmln != NULL)
    {
      success = setAnnotation(annt_xmln);
      delete annt_xmln;
    }
    return success;
  }
}


/*
 * Appends annotation to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int 
SBase::appendAnnotation (const XMLNode* annotation)
{
  int success = LIBSBML_OPERATION_FAILED;

  //
  // (*NOTICE*)
  //
  // syncAnnotation() doesn't need to be invoked in this function because
  // existing mCVTerm objects are properly merged in the following code.
  //

  if(annotation == NULL) return LIBSBML_OPERATION_SUCCESS;

  XMLNode* new_annotation = NULL;
  const string&  name = annotation->getName();

  // check for annotation tags and add if necessary 
  if (name != "annotation")
  {
    XMLToken ann_t = XMLToken(XMLTriple("annotation", "", ""), XMLAttributes());
    new_annotation = new XMLNode(ann_t);
    new_annotation->addChild(*annotation);
  }
  else
  {
    new_annotation = annotation->clone();
  }

  // parse new_annotation and add mCVTerms (if any) 
  if (RDFAnnotationParser::hasCVTermRDFAnnotation(new_annotation))
  {
    RDFAnnotationParser::parseRDFAnnotation(new_annotation,mCVTerms);
  }

  // delete RDFAnnotation (CVTerm and ModelHistory) from new_annotation 
//  XMLNode* tmp_annotation = RDFAnnotationParser::deleteRDFAnnotation(new_annotation);
//  delete new_annotation;
//  new_annotation = tmp_annotation;

  if (mAnnotation != NULL)
  {
    // if mAnnotation is just <annotation/> need to tell
    // it to no longer be an end
    if (mAnnotation->isEnd())
    {
      mAnnotation->unsetEnd();
    }

    for(unsigned int i=0; i < new_annotation->getNumChildren(); i++)
    {
      if (new_annotation->getChild(i).getName() == "RDF")
      {
        if (RDFAnnotationParser::hasRDFAnnotation(mAnnotation))
        {
          unsigned int n = 0;
          while(n < mAnnotation->getNumChildren())
          {
            if (mAnnotation->getChild(n).getName() == "RDF")
            {
              break;
            }
            n++;
          }
          success = mAnnotation->getChild(n).addChild(
                                    new_annotation->getChild(i).getChild(0));
        }
        else
        {
          success = mAnnotation->addChild(new_annotation->getChild(i));
        }
      }
      else
      {
        success = mAnnotation->addChild(new_annotation->getChild(i));
      }
    }
  }
  else
  {
    success = setAnnotation(new_annotation);
  }

  delete new_annotation;

  return success;
}

/*
 * Appends annotation (by string) to the existing annotations.
 * This allows other annotations to be preserved whilst
 * adding additional information.
 */
int
SBase::appendAnnotation (const std::string& annotation)
{
  //
  // (*NOTICE*)
  //
  // syncAnnotation() doesn't need to be invoked in this function because
  // existing mCVTerm objects are properly merged in the following code.
  //

  int success = LIBSBML_OPERATION_FAILED;
  XMLNode* annt_xmln;
  if (getSBMLDocument() != NULL)
  {
    XMLNamespaces* xmlns = getSBMLDocument()->getNamespaces();
    annt_xmln = XMLNode::convertStringToXMLNode(annotation,xmlns);
  }
  else
  {
    annt_xmln = XMLNode::convertStringToXMLNode(annotation);
  }
  
  if(annt_xmln != NULL)
  {
    success = appendAnnotation(annt_xmln);
    delete annt_xmln;
  }

  return success;
}



/*
 * Sets the notes of this SBML object to a copy of notes.
 */
int 
SBase::setNotes(const XMLNode* notes)
{
  if (mNotes == notes) 
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (notes == NULL)
  {
    delete mNotes;
    mNotes = NULL;
    return LIBSBML_OPERATION_SUCCESS;
  }

  delete mNotes;
  const string&  name = notes->getName();

  /* check for notes tags and add if necessary */

  if (name == "notes")
  {
    mNotes = static_cast<XMLNode*>( notes->clone() );
  }
  else
  {
    XMLToken notes_t = XMLToken(XMLTriple("notes", "", ""), 
                                XMLAttributes());
    mNotes = new XMLNode(notes_t);
  
    // The root node of the given XMLNode tree can be an empty XMLNode 
    // (i.e. neither start, end, nor text XMLNode) if the given notes was 
    // converted from an XML string whose top level elements are neither 
    // "html" nor "body" and not enclosed with <notes>..</notes> tag 
    // (e.g. <p ...>..</p><br/>).
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() ) 
    {
      for (unsigned int i=0; i < notes->getNumChildren(); i++)
      {
        if (mNotes->addChild(notes->getChild(i)) < 0)
        {
          return LIBSBML_OPERATION_FAILED;
        }
      }
    }
    else
    {
      if (mNotes->addChild(*notes) < 0)
        return LIBSBML_OPERATION_FAILED;
    }
  }
  
  // in L2v2 and beyond the XHTML content of notes is restricted
  // but I need the notes tag to use the function
  // so I havent tested it until now
  if (getLevel() > 2 
    || (getLevel() == 2 && getVersion() > 1))
  {
    if (!SyntaxChecker::hasExpectedXHTMLSyntax(mNotes, getSBMLNamespaces()))
    {
      delete mNotes;
      mNotes = NULL;
      return LIBSBML_INVALID_OBJECT;
    }
  }

  return LIBSBML_OPERATION_SUCCESS;

}

/*
 * Sets the notes (by std::string) of this SBML object to a copy of notes.
 */
int
SBase::setNotes(const std::string& notes)
{
  int success = LIBSBML_OPERATION_FAILED;
  if (&(notes) == NULL)
  {
    success = LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else if (notes.empty())
  {
    success = unsetNotes();
  }
  else
  {
    XMLNode* notes_xmln;

    // you might not have a document !!
    if (getSBMLDocument() != NULL)
    {
      XMLNamespaces* xmlns = getSBMLDocument()->getNamespaces();
      notes_xmln = XMLNode::convertStringToXMLNode(notes,xmlns); 
    }
    else
    {
      notes_xmln = XMLNode::convertStringToXMLNode(notes);
    }

    if(notes_xmln != NULL)
    {
      success = setNotes(notes_xmln);
      delete notes_xmln;
    }
  }
  return success;
}


/*
 * Appends notes to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int 
SBase::appendNotes(const XMLNode* notes)
{
  int success = LIBSBML_OPERATION_FAILED;
  if(notes == NULL) 
  {
    return LIBSBML_OPERATION_SUCCESS;
  }

  const string&  name = notes->getName();

  // The content of notes in SBML can consist only of the following 
  // possibilities:
  //
  //  1. A complete XHTML document (minus the XML and DOCTYPE 
  //     declarations), that is, XHTML content beginning with the 
  //     html tag.
  //     (_NotesType is _ANotesHTML.)
  //
  //  2. The body element from an XHTML document.
  //     (_NotesType is _ANotesBody.) 
  //
  //  3. Any XHTML content that would be permitted within a body 
  //     element, each one must declare the XML namespace separately.
  //     (_NotesType is _ANotesAny.) 
  //

  typedef enum { _ANotesHTML, _ANotesBody, _ANotesAny } _NotesType;

  _NotesType addedNotesType = _ANotesAny; 
  XMLNode   addedNotes;

  //------------------------------------------------------------
  //
  // STEP1 : identifies the type of the given notes
  //
  //------------------------------------------------------------

  if (name == "notes")
  {
    /* check for notes tags on the added notes and strip if present and
       the notes tag has "html" or "body" element */

    if (notes->getNumChildren() > 0)  
    { 
      // notes->getChild(0) must be "html", "body", or any XHTML
      // element that would be permitted within a "body" element 
      // (e.g. <p>..</p>,  <br>..</br> and so forth).

      const string& cname = notes->getChild(0).getName();

      if (cname == "html")
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesHTML;
      }
      else if (cname == "body") 
      {
        addedNotes = notes->getChild(0);
        addedNotesType = _ANotesBody;
      }
      else
      {
        // the notes tag must NOT be stripped if notes->getChild(0) node 
        // is neither "html" nor "body" element because the children of 
        // the addedNotes will be added to the curNotes later if the node 
        // is neither "html" nor "body".
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
    }
    else
    {
      // the given notes is empty 
      return LIBSBML_OPERATION_SUCCESS;
    }
  }
  else
  {
    // if the XMLNode argument notes has been created from a string and 
    // it is a set of subelements there may be a single empty node
    // as parent - leaving this in doesnt affect the writing out of notes
    // but messes up the check for correct syntax
    if (!notes->isStart() && !notes->isEnd() && !notes->isText() ) 
    {
      if (notes->getNumChildren() > 0)
      { 
        addedNotes = *notes;
        addedNotesType = _ANotesAny;
      }
      else
      {
        // the given notes is empty 
        return LIBSBML_OPERATION_SUCCESS;
      }
    }
    else
    {
      if (name == "html")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesHTML;
      }
      else if (name == "body")
      {
        addedNotes = *notes;
        addedNotesType = _ANotesBody;
      }
      else
      {
        // The given notes node needs to be added to a parent node
        // if the node is neither "html" nor "body" element because the 
        // children of addedNotes will be added to the curNotes later if the 
        // node is neither "html" nor "body" (i.e. any XHTML element that 
        // would be permitted within a "body" element)
        addedNotes.addChild(*notes);
        addedNotesType = _ANotesAny;
      }
    }
  }

  //
  // checks the addedNotes of "html" if the html tag contains "head" and 
  // "body" tags which must be located in this order.
  //
  if (addedNotesType == _ANotesHTML)
  {
    if ((addedNotes.getNumChildren() != 2) ||
        ( (addedNotes.getChild(0).getName() != "head") ||
          (addedNotes.getChild(1).getName() != "body")
        )
       )
    {
      return LIBSBML_INVALID_OBJECT;
    }
  }

  // check whether notes is valid xhtml
  if (getLevel() > 2 
    || (getLevel() == 2 && getVersion() > 1))
  {
    XMLNode tmpNotes(XMLTriple("notes","",""), XMLAttributes());

    if (addedNotesType == _ANotesAny)
    {
      for (unsigned int i=0; i < addedNotes.getNumChildren(); i++)
      {
        tmpNotes.addChild(addedNotes.getChild(i));
      }
    }
    else
    {
      tmpNotes.addChild(addedNotes);
    }

    if (!SyntaxChecker::hasExpectedXHTMLSyntax(&tmpNotes, getSBMLNamespaces()))
    {
      return LIBSBML_INVALID_OBJECT;
    }
  }


  if ( mNotes != NULL )
  {
    //------------------------------------------------------------
    //
    //  STEP2: identifies the type of the existing notes 
    //
    //------------------------------------------------------------

    _NotesType curNotesType   = _ANotesAny; 
    XMLNode&  curNotes = *mNotes;

    // curNotes.getChild(0) must be "html", "body", or any XHTML
    // element that would be permitted within a "body" element .

    const string& cname = curNotes.getChild(0).getName();
  
    if (cname == "html")
    {
      XMLNode& curHTML = curNotes.getChild(0);
      //
      // checks the curHTML if the html tag contains "head" and "body" tags
      // which must be located in this order, otherwise nothing will be done.
      //
      if ((curHTML.getNumChildren() != 2) ||
          ( (curHTML.getChild(0).getName() != "head") ||
            (curHTML.getChild(1).getName() != "body")
          )
         )
      {
        return LIBSBML_INVALID_OBJECT;
      }
      curNotesType = _ANotesHTML;
    }
    else if (cname == "body") 
    {
      curNotesType = _ANotesBody;
    }
    else
    {
      curNotesType = _ANotesAny;
    }
  
    /*
     * BUT we also have the issue of the rules relating to notes
     * contents and where to add them ie we cannot add a second body element
     * etc...
     */

    //------------------------------------------------------------
    //
    //  STEP3: appends the given notes to the current notes
    //
    //------------------------------------------------------------
  
    unsigned int i;
  
    if (curNotesType == _ANotesHTML)
    {
      XMLNode& curHTML = curNotes.getChild(0); 
      XMLNode& curBody = curHTML.getChild(1);
      
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current html tag
  
        XMLNode& addedBody = addedNotes.getChild(1);   
  
        for (i=0; i < addedBody.getNumChildren(); i++)
        {
          if (curBody.addChild(addedBody.getChild(i)) < 0 )
            return LIBSBML_OPERATION_FAILED;          
        }
      }
      else if ((addedNotesType == _ANotesBody) 
             || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current 
        // html tag
  
        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0 )
            return LIBSBML_OPERATION_FAILED;
        }
      }
      success = LIBSBML_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesBody)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current body tag
  
        XMLNode  addedHTML(addedNotes);
        XMLNode& addedBody = addedHTML.getChild(1);
        XMLNode& curBody   = curNotes.getChild(0);
  
        for (i=0; i < curBody.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curBody.getChild(i));
        }
        
        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBSBML_OPERATION_FAILED;
      }
      else if ((addedNotesType == _ANotesBody) || (addedNotesType == _ANotesAny))
      {
        // adds the given body or other tag (permitted in the body) to the current 
        // body tag
  
        XMLNode& curBody = curNotes.getChild(0);
  
        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curBody.addChild(addedNotes.getChild(i)) < 0)
            return LIBSBML_OPERATION_FAILED;
        }
      }
      success = LIBSBML_OPERATION_SUCCESS;
    }
    else if (curNotesType == _ANotesAny)
    {
      if (addedNotesType == _ANotesHTML)
      {
        // adds the given html tag to the current any tag permitted in the body.
  
        XMLNode  addedHTML(addedNotes);
        XMLNode& addedBody = addedHTML.getChild(1);
  
        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }
  
        curNotes.removeChildren();
        if (curNotes.addChild(addedHTML) < 0)
          return LIBSBML_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesBody)
      {
        // adds the given body tag to the current any tag permitted in the body.
  
        XMLNode addedBody(addedNotes);
  
        for (i=0; i < curNotes.getNumChildren(); i++)
        {
          addedBody.insertChild(i,curNotes.getChild(i));
        }
  
        curNotes.removeChildren();
        if (curNotes.addChild(addedBody) < 0)
          return LIBSBML_OPERATION_FAILED;
      }
      else if (addedNotesType == _ANotesAny)
      {
        // adds the given any tag permitted in the boy to that of the current 
        // any tag.
  
        for (i=0; i < addedNotes.getNumChildren(); i++)
        {
          if (curNotes.addChild(addedNotes.getChild(i)) < 0)
            return LIBSBML_OPERATION_FAILED;
        }
      }
      success = LIBSBML_OPERATION_SUCCESS;
    }
  }
  else // if (mNotes == NULL)
  {
    // setNotes accepts XMLNode with/without top level notes tags.
    success = setNotes(notes);
  }

  return success;
}

/*
 * Appends notes (by string) to the existing notes.
 * This allows other notes to be preserved whilst
 * adding additional information.
 */
int
SBase::appendNotes(const std::string& notes)
{
  int success = LIBSBML_OPERATION_FAILED;
  if (notes.empty())
  {
    return LIBSBML_OPERATION_SUCCESS;
  }

  XMLNode* notes_xmln;
  // you might not have a document !!
  if (getSBMLDocument() != NULL)
  {
      XMLNamespaces* xmlns = getSBMLDocument()->getNamespaces();
      notes_xmln = XMLNode::convertStringToXMLNode(notes,xmlns); 
  }
  else
  {
      notes_xmln = XMLNode::convertStringToXMLNode(notes);
  }

  if(notes_xmln != NULL)
  {
    success = appendNotes(notes_xmln);
    delete notes_xmln;
  }
  return success;
}


int
SBase::setModelHistory(ModelHistory * history)
{
  /* ModelHistory is only allowed on Model in L2
   * but on any element in L3
   */
  if (getLevel() < 3)
  {
    if (getTypeCode() != SBML_MODEL)
    {
      return LIBSBML_UNEXPECTED_ATTRIBUTE;
    }
  }

  if (mHistory == history) 
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (history == NULL)
  {
    delete mHistory;
    mHistory = NULL;
    return LIBSBML_OPERATION_SUCCESS;
  }
  else if (!(history->hasRequiredAttributes()))
  {
    delete mHistory;
    mHistory = NULL;
    return LIBSBML_INVALID_OBJECT;
  }
  else
  {
    delete mHistory;
    mHistory = static_cast<ModelHistory*>( history->clone() );
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/** @cond doxygen-libsbml-internal */

/*
 * Sets the parent SBMLDocument of this SBML object.
 */
void
SBase::setSBMLDocument (SBMLDocument* d)
{
  mSBML = d;

  //
  // (EXTENSION) 
  //
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    mPlugins[i]->setSBMLDocument(d);
  }
}


/*
  * Sets the parent SBML object of this SBML object.
  *
  * @param sb the SBML object to use
  */
void 
SBase::connectToParent (SBase* parent)
{
  mParentSBMLObject = parent;
  if (mParentSBMLObject)
  {
#if 0
	  cout << "[DEBUG] connectToParent " << this << " (parent) " << SBMLTypeCode_toString(parent->getTypeCode(),"core")
			   << " " << parent->getSBMLDocument() << endl;
#endif
	  setSBMLDocument(mParentSBMLObject->getSBMLDocument());
  }
  else
  {
	setSBMLDocument(0);
  }
}


/*
 * Sets this SBML object to child SBML objects (if any).
 * (Creates a child-parent relationship by the parent)
 *
 * Subclasses must override this function if they define
 * one ore more child elements.
 * Basically, this function needs to be called in
 * constructor, opy constructor and assignment operator.
 */
void
SBase::connectToChild()
{
	// do nothing.
}

/** @endcond */

SBase* 
SBase::getAncestorOfType(int type, const std::string pkgName)
{
  if (pkgName == "core" && type == SBML_DOCUMENT)
    return getSBMLDocument();

  SBase *child = this;
  SBase *parent = getParentSBMLObject();

  while ( parent != NULL && 
          !( parent->getPackageName() == "core" &&
             parent->getTypeCode() == SBML_DOCUMENT )
        )
  {
    if (parent->getTypeCode() == type && parent->getPackageName() == pkgName)
      return parent;
    else
    {
      child = parent;
      parent = child->getParentSBMLObject();
    }
  }

  // if we get here we havent found an ancestor of this type
  return NULL;

}


/*
 * Sets the sboTerm field to value.
 */
int
SBase::setSBOTerm (int value)
{
  if (getLevel() < 2 || (getLevel() == 2 && getVersion() < 2))
  {
    mSBOTerm = -1;
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }
  else
  {
    if ( !SBO::checkTerm(value) )
    {
      mSBOTerm = -1;
      return LIBSBML_INVALID_ATTRIBUTE_VALUE;
    }
    mSBOTerm = value;
    return LIBSBML_OPERATION_SUCCESS;
  }
}

/*
 * Sets the sboTerm field to value converted from the given string.
 */
int
SBase::setSBOTerm (const std::string &sboid)
{
  if (&(sboid) == NULL)
  {
    return LIBSBML_INVALID_ATTRIBUTE_VALUE;
  }
  else
  {
    return setSBOTerm(SBO::stringToInt(sboid));
  }
}


/*
 * Sets the namespaces relevant of this SBML object.
 *
 * @param xmlns the namespaces to set
 */
int 
SBase::setNamespaces(XMLNamespaces* xmlns)
{
  if (xmlns == NULL)
  {
    mSBMLNamespaces->setNamespaces(NULL);
    return LIBSBML_OPERATION_SUCCESS;
  }
  else
  {
    mSBMLNamespaces->setNamespaces(xmlns);
    return LIBSBML_OPERATION_SUCCESS;
  }
}



/*
 * Unsets the metaid of this SBML object.
 */
int
SBase::unsetMetaId ()
{
  /* only in L2 onwards */
  if (getLevel() < 2)
  {
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }

  mMetaId.erase();

  if (mMetaId.empty())
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else
  {
    return LIBSBML_OPERATION_FAILED;
  }
}


/*
 * Unsets the id of this SBML object.
 */
int
SBase::unsetId ()
{
  return LIBSBML_OPERATION_FAILED;  
}


/*
 * Unsets the name of this SBML object.
 */
int
SBase::unsetName ()
{
  return LIBSBML_OPERATION_FAILED;  
}


/*
 * Unsets the notes of this SBML object.
 */
int
SBase::unsetNotes ()
{
  delete mNotes;
  mNotes = NULL;
  return LIBSBML_OPERATION_SUCCESS;
}


/*
 * Unsets the annotation of this SBML object.
 */
int
SBase::unsetAnnotation ()
{
  XMLNode* empty = NULL;
  return setAnnotation(empty);
}


/*
 * Unsets the sboTerm of this SBML object.
 */
int
SBase::unsetSBOTerm ()
{
  if (getLevel() < 2 || (getLevel() == 2 && getVersion() < 2))
  {
    mSBOTerm = -1;
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }
  else
  {
    mSBOTerm = -1;
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/** @cond doxygen-libsbml-internal */
void SBase::removeDuplicatedResources(CVTerm *term, QualifierType_t type)
{
  int length = term->getResources()->getLength();
  if (type == BIOLOGICAL_QUALIFIER)
  {
    BiolQualifierType_t biolQual = BQB_UNKNOWN;
    for (int p = length-1; p > -1; p--)
    {
      biolQual = getResourceBiologicalQualifier(term->getResources()->getValue(p));
      if (biolQual != BQB_UNKNOWN)
      {
        /* resource is already present
        * - dont want to add again;
        * so delete it from set to be added
        */
        term->removeResource(term->getResources()->getValue(p));
      }
    }
  }
  else if (type == MODEL_QUALIFIER)
  {
    ModelQualifierType_t modelQual = BQM_UNKNOWN;
    for (int p = length-1; p > -1; p--)
    {
      modelQual = getResourceModelQualifier(term->getResources()->getValue(p));
      if (modelQual != BQM_UNKNOWN)
      {
        /* resource is already present
        * - dont want to add again;
        * so delete it from set to be added
        */
        term->removeResource(term->getResources()->getValue(p));
      }
    }
  }
}
/** @endcond */

/** @cond doxygen-libsbml-internal */
int SBase::addTermToExistingBag(CVTerm *term, QualifierType_t type )
{
  unsigned int added = 0;
  unsigned int length = mCVTerms->getSize();
  
  CVTerm* nthTerm = NULL;

  if (length == 0) return added;

  if (type == BIOLOGICAL_QUALIFIER)
  {
    BiolQualifierType_t biol = term->getBiologicalQualifierType();
    
    for (int n = (int)length -1; n >= 0  && added == 0; n--)
    {
      nthTerm = static_cast <CVTerm *>(mCVTerms->get(n));

      if (nthTerm != NULL && biol == nthTerm->getBiologicalQualifierType())
      {
        for (int r = 0; r < term->getResources()->getLength(); r++)
        {
          nthTerm->addResource(
            term->getResources()->getValue(r));
        }
        added = 1;
      }
    }
  }
  else if (type == MODEL_QUALIFIER)
  {
    ModelQualifierType_t model = term->getModelQualifierType();

    for (unsigned int n = 0; n < length && added == 0; n++)
    {
      nthTerm = static_cast <CVTerm *>(mCVTerms->get(n));

      if (nthTerm != NULL && model == nthTerm->getModelQualifierType())
      {
        for (int r = 0; r < term->getResources()->getLength(); r++)
        {
          nthTerm->addResource(
            term->getResources()->getValue(r));
        }
        added = 1;
      }
    }
  }
  return added;
}
/** @endcond */

/*
 * Adds a copy of the given CVTerm to this SBML object.
 */
int
SBase::addCVTerm(CVTerm * term, bool newBag)
{
  unsigned int added = 0;
  // shouldnt add a CVTerm to an object with no metaid 
  if (!isSetMetaId())
  {
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }

  if (term == NULL)
  {
    return LIBSBML_OPERATION_FAILED;
  }
  else if (!term->hasRequiredAttributes())
  {
    return LIBSBML_INVALID_OBJECT;
  }
  
  /* clone the term to be added so that I can adjust 
   * which resources are actually added
   */
  CVTerm * copyTerm = term->clone();

  if (mCVTerms == NULL)
  {
    mCVTerms = new List();
    mCVTerms->add((void *) term->clone());
  }
  else if (mCVTerms->getSize() == 0)
  {
    mCVTerms->add((void *) term->clone());
  }
  else
  {
    /* check whether the resources are already listed */
    QualifierType_t type = copyTerm->getQualifierType();
    removeDuplicatedResources(copyTerm, type);

    /* if the qualifier of the term being added is already present
     * add to the list of resources for that qualifier
     */
    if (newBag == false)
    {
      added = addTermToExistingBag(copyTerm, type);
    }

    if (added == 0 && copyTerm->getResources()->getLength() > 0)
    {
      /* no matching copyTerms already in list */
      mCVTerms->add((void *) copyTerm->clone());
    }

  }

  delete copyTerm;
  return LIBSBML_OPERATION_SUCCESS;
}


/*
 * @return the list of CVTerms for this SBML object.
 */
List*
SBase::getCVTerms()
{
  return mCVTerms;
}


/*
 * @return the list of CVTerms for this SBML object.
 */
List*
SBase::getCVTerms() const
{
  return mCVTerms;
}

/*
 * Returns the number of CVTerm objects in the annotations of this SBML
 * object.
 * 
 * @return the number of CVTerms for this SBML object.
 */
unsigned int 
SBase::getNumCVTerms()
{
  if (mCVTerms != NULL)
  {
    return mCVTerms->getSize();
  }
  else
  {
    return 0;
  }
}


/*
 * Returns the nth CVTerm in the list of CVTerms of this SBML
 * object.
 * 
 * @param n unsigned int the index of the CVTerm to retrieve
 *
 * @return the nth CVTerm in the list of CVTerms for this SBML object.
 */
CVTerm* 
SBase::getCVTerm(unsigned int n)
{
  return (mCVTerms) ? static_cast <CVTerm*> (mCVTerms->get(n)) : NULL;
}


/*
 * Clears the list of CVTerms of this SBML
 * object.
 */
int 
SBase::unsetCVTerms()
{
  if (mCVTerms != NULL)
  {  
    unsigned int size = mCVTerms->getSize();
    while (size--) delete static_cast<CVTerm*>( mCVTerms->remove(0) );
    delete mCVTerms;
  }
  mCVTerms = NULL;
  
  if (mCVTerms != NULL)
    return LIBSBML_OPERATION_FAILED;
  else
    return LIBSBML_OPERATION_SUCCESS;
}


int 
SBase::unsetModelHistory()
{
  delete mHistory;
  mHistory = NULL;

  /* ModelHistory is only allowed on Model in L2
   * but on any element in L3
   */
  if (getLevel() < 3 && getTypeCode() != SBML_MODEL)
  {
    return LIBSBML_UNEXPECTED_ATTRIBUTE;
  }

  if (mHistory != NULL)
  {
    return LIBSBML_OPERATION_FAILED;
  }
  else
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
}


/*
 * Returns the BiologicalQualifier associated with this resource,
 * an empty string if the resource does not exist.
 *
 * @param resource string representing the resource; e.g.,
 * "http://www.geneontology.org/#GO:0005892"
 *
 * @return the BiolQualifierType_t associated with the resource
 */
BiolQualifierType_t 
SBase::getResourceBiologicalQualifier(std::string resource)
{
  if (mCVTerms != NULL)
  {
    for (unsigned int n = 0; n < mCVTerms->getSize(); n++)
    {
      // does this term have a biological qualifier
      if (static_cast <CVTerm *>(mCVTerms->get(n))->getQualifierType() 
                                                              == BIOLOGICAL_QUALIFIER)
      {
        // check whether given resource is present
        for (int r = 0; 
          r < static_cast <CVTerm *>(mCVTerms->get(n))->getResources()->getLength(); r++)
        {
          if (resource == 
            static_cast <CVTerm *>(mCVTerms->get(n))->getResources()->getValue(r))
          {
            return static_cast <CVTerm *>(mCVTerms->get(n))->getBiologicalQualifierType();
          }
        }
      }
    }
  }

  return BQB_UNKNOWN;
}

/*
 * Returns the ModelQualifier associated with this resource,
 * an empty string if the resource does not exist.
 *
 * @param resource string representing the resource; e.g.,
 * "http://www.geneontology.org/#GO:0005892"
 *
 * @return the ModelQualifierType_t associated with the resource
 */
ModelQualifierType_t 
SBase::getResourceModelQualifier(std::string resource)
{
  if (mCVTerms != NULL)
  {
    for (unsigned int n = 0; n < mCVTerms->getSize(); n++)
    {
      // does this term have a biological qualifier
      if (static_cast <CVTerm *>(mCVTerms->get(n))->getQualifierType() 
                                                              == MODEL_QUALIFIER)
      {
        // check whether given resource is present
        for (int r = 0; 
          r < static_cast <CVTerm *>(mCVTerms->get(n))->getResources()->getLength(); r++)
        {
          if (resource == 
            static_cast <CVTerm *>(mCVTerms->get(n))->getResources()->getValue(r))
          {
            return static_cast <CVTerm *>(mCVTerms->get(n))->getModelQualifierType();
          }
        }
      }
    }
  }

  return BQM_UNKNOWN;
}


/*
 * @return the parent Model of this SBML object.
 */
const Model*
SBase::getModel () const
{
  return (mSBML != NULL) ? mSBML->getModel() : NULL;
}


/*
 * @return the SBML level of this SBML object.
 */
unsigned int
SBase::getLevel () const
{
  if (mSBML != NULL)
    return mSBML->mLevel;
  else if (mSBMLNamespaces != NULL)
    return mSBMLNamespaces->getLevel();
  else
    return SBMLDocument::getDefaultLevel();
}


/*
 * @return the SBML version of this SBML object.
 */
unsigned int
SBase::getVersion () const
{
  if (mSBML != NULL)
    return mSBML->mVersion;
  else if (mSBMLNamespaces != NULL)
    return mSBMLNamespaces->getVersion();
  else
    return SBMLDocument::getDefaultVersion();
}


/*
 * @return the version of package to which this SBML object 
 * belongs to.
 * 0 will be returned if this element belongs to Core package.
 *
 * @see getLevel()
 * @see getVersion()
 */
unsigned int 
SBase::getPackageVersion () const
{
  const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(mURI);

  if (sbmlext)
  {
    return sbmlext->getPackageVersion(mURI);
  }

  return 0;
}


/*
 * Returns the name of package in which this element is defined.
 *
 */
const std::string&
SBase::getPackageName () const
{
  if (SBMLNamespaces::isSBMLNamespace(mURI))
  {
    static const std::string pkgName = "core";
    return pkgName;
  }

  const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(mURI);

  if (sbmlext)
  {
    return sbmlext->getName();
  }

  static const std::string pkgName = "unknown";
  return pkgName;
}


/*
 * @return the typecode (int) of this SBML object or SBML_UNKNOWN
 * (default).
 *
 * This method MAY return the typecode of this SBML object or it MAY
 * return SBML_UNKNOWN.  That is, subclasses of SBase are not required to
 * implement this method to return a typecode.  This method is meant
 * primarily for the LibSBML C interface where class and subclass
 * information is not readily available.
 *
 * @see getElementName()
 */
int
SBase::getTypeCode () const
{
  return SBML_UNKNOWN;
}


//
//
// (EXTENSION)
//
//


/*
 * Returns a plugin object (extenstion interface) of package extension
 * with the given package name or URI.
 *
 * @param package the name or URI of the package
 *
 * @return the plugin object of package extension with the given package
 * name or URI. 
 */
SBasePlugin* 
SBase::getPlugin(const std::string& package)
{
  SBasePlugin* sbPlugin = 0;

  for (size_t i=0; i < mPlugins.size(); i++)
  {
    std::string uri = mPlugins[i]->getURI();
    const SBMLExtension* sbext = SBMLExtensionRegistry::getInstance().getExtensionInternal(uri);
    if (uri == package)
    {
      sbPlugin = mPlugins[i];
      break;
    }
    else if (sbext && (sbext->getName() == package) )
    {
      sbPlugin = mPlugins[i];
      break;
    }
  }

  return sbPlugin;
}


/*
 * Returns a plugin object (extenstion interface) of package extension
 * with the given package name or URI.
 *
 * @param package the name or URI of the package
 *
 * @return the plugin object of package extension with the given package
 * name or URI. 
 */
const SBasePlugin* 
SBase::getPlugin(const std::string& package) const
{
  return const_cast<SBase*>(this)->getPlugin(package);
}


/*
 * Returns the number of plugin objects of package extensions.
 *
 * @return the number of plugin objects of package extensions.
 */
int 
SBase::getNumPlugins() const
{
  return (int)mPlugins.size();
}


/*
 * Enables/Disables the given package with this object.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
 * @li LIBSBML_PKG_UNKNOWN      
 * @li LIBSBML_PKG_VERSION_MISMATCH 
 * @li LIBSBML_PKG_CONFLICTED_VERSION
 */
int 
SBase::enablePackage(const std::string& pkgURI, const std::string& prefix, bool flag)
{
  //
  // Checks if the package with the given URI is already enabled/disabled with
  // this element.
  //
  if (flag)
  {
    if (isPkgURIEnabled(pkgURI))
    {
      return LIBSBML_OPERATION_SUCCESS;
    }
  }
  else
  {
    if (!isPkgURIEnabled(pkgURI))
    {
      return LIBSBML_OPERATION_SUCCESS;
    }
  }

  //
  // Checks if the given pkgURI is registered in SBMLExtensionRegistry
  //
  if (!SBMLExtensionRegistry::getInstance().isRegistered(pkgURI))
  {
    return LIBSBML_PKG_UNKNOWN;
  }

  const SBMLExtension *sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(pkgURI);

  //
  // Checks version conflicts of the given package
  //
  if (flag && isPkgEnabled(sbmlext->getName()))
  {
    return LIBSBML_PKG_CONFLICTED_VERSION;
  }

  //
  // Checks if the SBML Level and Version of the given pkgURI is 
  // consistent with those of this object.
  //
  /* if we happen to be using layout in L2 we cannot do the version
   * check since the uri has no way of telling which sbml versio
   */
  if (sbmlext->getName() == "layout") 
  {
    if (sbmlext->getLevel(pkgURI)   != getLevel() )
    {
      return LIBSBML_PKG_VERSION_MISMATCH;
    }
  }
  else if ( (sbmlext->getLevel(pkgURI)   != getLevel()  ) ||
       (sbmlext->getVersion(pkgURI) != getVersion()) 
     )
  { 
    return LIBSBML_PKG_VERSION_MISMATCH;
  }

  SBase* rootElement = getRootElement();
  rootElement->enablePackageInternal(pkgURI,prefix,flag);

  return LIBSBML_OPERATION_SUCCESS;
}

/** @cond doxygen-libsbml-internal */
/*
 * Enables/Disables the given package with this element and child
 * elements (if any).
 * (This is an internal implementation for enablePakcage function)
 */
void 
SBase::enablePackageInternal(const std::string& pkgURI, const std::string& pkgPrefix, bool flag)
{
  if (flag)
  {
    if (mSBMLNamespaces)
    {
#if 0
      cout << "[DEBUG] SBase::enablePackageInternal() (uri) " <<  pkgURI
           << " (prefix) " << pkgPrefix << " (element) " << getElementName() << endl;
#endif
      mSBMLNamespaces->addNamespace(pkgURI,pkgPrefix);
    }
  
    //
    // enable the given package
    //
    const SBMLExtension* sbmlext = SBMLExtensionRegistry::getInstance().getExtensionInternal(pkgURI);

    if (sbmlext)
    {
      SBaseExtensionPoint extPoint(getPackageName(),getTypeCode());
      const SBasePluginCreatorBase* sbPluginCreator = sbmlext->getSBasePluginCreator(extPoint);
      if (sbPluginCreator)
      {
        SBasePlugin* entity = sbPluginCreator->createPlugin(pkgURI,pkgPrefix,getNamespaces());
        entity->connectToParent(this);
        mPlugins.push_back(entity);
      }

    }
  }
  else
  {
    //
    // disable the given package
    //
    for (size_t i=0; i < mPlugins.size(); i++)
    {
      std::string uri = mPlugins[i]->getURI();
      if (pkgURI == uri)
      {
        mPlugins.erase( mPlugins.begin() + i );
      }
    }

    if (mSBMLNamespaces)
    {
      mSBMLNamespaces->removeNamespace(pkgURI);
    }
  }

  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  for (size_t i=0; i < mPlugins.size(); i++)
  {
    mPlugins[i]->enablePackageInternal(pkgURI,pkgPrefix,flag);
  }
}
/** @endcond */


/*
 * Predicate returning @c true if 
 * the a package with the given URI is enabled with this object.
 *
 * @param pkgURI the URI of the package
 *
 * @return @c true if the given package is enabled with this object, @c
 * false otherwise.
 */
bool 
SBase::isPkgURIEnabled(const std::string& pkgURI) const
{
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    if (mPlugins[i]->getURI() == pkgURI) 
      return true;
  }
  return false;
}


/*
 * Predicate returning @c true if
 * the given package (don't care the package version) is enabled with 
 * this object.
 *
 * @param pkgName the URI of the package
 *
 * @return @c true if the given package is enabled with this object, @c
 * false otherwise.
 */
bool
SBase::isPkgEnabled(const std::string& pkgName) const
{
  for (size_t i=0; i < mPlugins.size(); i++)
  {
    if (mPlugins[i]->getPackageName() == pkgName)
      return true;
  }
  return false;
}

bool 
SBase::hasValidLevelVersionNamespaceCombination()
{
  int typecode = getTypeCode();
  XMLNamespaces *xmlns = getNamespaces();  

  return hasValidLevelVersionNamespaceCombination(typecode, xmlns);
}

/** @cond doxygen-libsbml-internal */

bool 
SBase::hasValidLevelVersionNamespaceCombination(int typecode, XMLNamespaces *xmlns)
{
  
  
  //
  // (TODO) Currently, the following check code works only for
  //        elements in SBML core.
  //        This function may need to be extented for other elements 
  //        defined in each package extension.
  //

  bool valid = true;
  bool sbmlDeclared = false;
  std::string declaredURI("");
  unsigned int version = getVersion();
  
  if (xmlns != NULL)
  {
    // 
    // checks defined SBML XMLNamespace
    // returns false if different SBML XMLNamespaces 
    // (e.g. SBML_XMLNS_L2V1 and SBML_XMLNS_L2V3) are defined.
    //
    int numNS = 0;

    if (xmlns->hasURI(SBML_XMLNS_L3V1))
    {
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L3V1);
    }

    if (xmlns->hasURI(SBML_XMLNS_L2V4))
    {
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L2V4);
    }

    if (xmlns->hasURI(SBML_XMLNS_L2V3))
    {
      // checks different SBML XMLNamespaces
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L2V3);
    }

    if (xmlns->hasURI(SBML_XMLNS_L2V2))
    {
      // checks different SBML XMLNamespaces
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L2V2);
    }

    if (xmlns->hasURI(SBML_XMLNS_L2V1))
    {
      // checks different SBML XMLNamespaces
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L2V1);
    }

    if (xmlns->hasURI(SBML_XMLNS_L1))
    {
      // checks different SBML XMLNamespaces
      if (numNS > 0) return false;
      ++numNS;
      declaredURI.assign(SBML_XMLNS_L1);
    }

    // checks if the SBML Namespace is explicitly defined.
    for (int i=0; i < xmlns->getLength(); i++)
    {
      if (!xmlns->getPrefix(i).empty() && 
                      xmlns->getURI(i) == declaredURI &&
					!declaredURI.empty())
      {
        sbmlDeclared = true;
        break;
      }
    }
  }

  const std::string& pkgName = getPackageName();
  if (&pkgName == NULL)
  {
	  // the pkgName was not initialized, so this is an invalid element
	  return false;
  }

  if (pkgName == "core")
  {
	// we need to consider whether it should be necessary to declare the sbml namespace.
	//if (!sbmlDeclared)
	//  return false;

    if (typecode == SBML_UNKNOWN)
    {
      valid = false;
      return valid;
    }
    switch (getLevel())
    {
      case 1:
        // some components didnt exist in level 1
        if ( typecode == SBML_COMPARTMENT_TYPE
          || typecode == SBML_CONSTRAINT
          || typecode == SBML_EVENT
          || typecode == SBML_EVENT_ASSIGNMENT
          || typecode == SBML_FUNCTION_DEFINITION
          || typecode == SBML_INITIAL_ASSIGNMENT
          || typecode == SBML_SPECIES_TYPE
          || typecode == SBML_MODIFIER_SPECIES_REFERENCE
          || typecode == SBML_TRIGGER
          || typecode == SBML_DELAY
        || typecode == SBML_STOICHIOMETRY_MATH
        || typecode == SBML_PRIORITY
        || typecode == SBML_LOCAL_PARAMETER)
          valid = false;
       switch (version)
        {
          case 1:
          case 2:
            // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L1))
              {
                valid = false;
              }
            }
            break;
          default:
            valid = false;
            break;
          }
        break;
      case 2:
        if ( typecode == SBML_PRIORITY
        || typecode == SBML_LOCAL_PARAMETER)
          valid = false;
        switch (version)
        {
          case 1:
            // some components didnt exist in l2v1
            if ( typecode == SBML_COMPARTMENT_TYPE
              || typecode == SBML_CONSTRAINT
              || typecode == SBML_INITIAL_ASSIGNMENT
              || typecode == SBML_SPECIES_TYPE)
              valid = false;
            // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L2V1))
              {
                valid = false;
              }
            }
            break;
          case 2:
            // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L2V2))
              {
                valid = false;
              }
            }
            break;
          case 3:
            // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L2V3))
              {
                valid = false;
              }
            }
            break;
          case 4:
            // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L2V4))
              {
                valid = false;
              }
            }
            break;
          default:
            valid = false;
            break;
          }
        break;
      case 3:
        // some components no longer exist in level 3
        if ( typecode == SBML_COMPARTMENT_TYPE
          || typecode == SBML_SPECIES_TYPE
          || typecode == SBML_STOICHIOMETRY_MATH)
          valid = false;
        switch (version)
        {
          case 1:
           // the namespaces contains the sbml namespaces
            // check it is the correct ns for the level/version
            if (sbmlDeclared)
            {
              if (declaredURI != string(SBML_XMLNS_L3V1))
              {
                valid = false;
              }
            }
            break;
          default:
            valid = false;
            break;
        }
        break;
      default:
        valid = false;
        break;
    }
  }

  return valid;
}

/* sets the SBMLnamespaces - internal use only*/
void 
SBase::setSBMLNamespaces(SBMLNamespaces * sbmlns)
{
  SBMLNamespaces* sbmlnsClone = (sbmlns) ? sbmlns->clone() : 0;
  setSBMLNamespacesAndOwn(sbmlnsClone);
}

/*
 * sets the SBMLnamespaces - only for internal use in the
 * constructors of SBase subclasses in extension packages.
 */
void
SBase::setSBMLNamespacesAndOwn(SBMLNamespaces * sbmlns)
{
  delete mSBMLNamespaces;
  mSBMLNamespaces = sbmlns;

  if(sbmlns != NULL)
    setElementNamespace(sbmlns->getURI());
}


/* gets the SBMLnamespaces - internal use only*/
SBMLNamespaces *
SBase::getSBMLNamespaces() const
{
  if (mSBML != NULL)
    return mSBML->mSBMLNamespaces;
  else if (mSBMLNamespaces != NULL)
    return mSBMLNamespaces;
  else
    return new SBMLNamespaces();
}

/** @endcond */



/*
 * @return the partial SBML that describes this SBML object.
 */
char*
SBase::toSBML ()
{
  ostringstream    os;
  XMLOutputStream  stream(os, "UTF-8", false);

  write(stream);

  return safe_strdup( os.str().c_str() );
}


/** @cond doxygen-libsbml-internal */
/*
 * Reads (initializes) this SBML object by reading from XMLInputStream.
 */
void
SBase::read (XMLInputStream& stream)
{
  if ( !stream.peek().isStart() ) return;

  const XMLToken  element  = stream.next();
  int             position =  0;

  setSBaseFields( element );

  ExpectedAttributes expectedAttributes;
  addExpectedAttributes(expectedAttributes);
  readAttributes( element.getAttributes(), expectedAttributes );

  /* if we are reading a document pass the
   * SBML Namespace information to the input stream object
   * thus the MathML reader can find out what level/version
   * of SBML it is parsing
   */
  if (element.getName() == "sbml")
  {
    stream.setSBMLNamespaces(this->getSBMLNamespaces());
  }
  else
  {
    //
    // checks if the given default namespace (if any) is a valid
    // SBML namespace
    //
    checkDefaultNamespace(mSBMLNamespaces->getNamespaces(), element.getName());
    if (!element.getPrefix().empty())
    {
      XMLNamespaces * prefixedNS = new XMLNamespaces();
      prefixedNS->add(element.getURI(), element.getPrefix());
      checkDefaultNamespace(prefixedNS, element.getName(), element.getPrefix());
      delete prefixedNS;
    }
  }

  if ( element.isEnd() ) return;

  while ( stream.isGood() )
  {
    stream.skipText();
    const XMLToken& next = stream.peek();

    // Re-check stream.isGood() because stream.peek() could hit something.
    if ( !stream.isGood() ) break;

    if ( next.isEndFor(element) )
    {
      stream.next();
      break;
    }
    else if ( next.isStart() )
    {
      const std::string nextName = next.getName();
#if 0
      cout << "[DEBUG] SBase::read " << nextName << " uri "
           << stream.peek().getURI() << endl;
#endif

      SBase * object = createObject(stream);
      
      if (!object)
      {
        object = createExtensionObject(stream);	
      }

      if (object != NULL)
      {
        checkOrderAndLogError(object, position);
        position = object->getElementPosition();

        object->connectToParent(static_cast <SBase*>(this));

        object->read(stream);

        if ( !stream.isGood() ) break;

        if (object->getPackageName() == "core" 
            && object->getTypeCode() == SBML_SPECIES_REFERENCE 
            && object->getLevel() > 1)
        {
          static_cast <SpeciesReference *> (object)->sortMath();
        }
        checkListOfPopulated(object);
      }
      else if ( !( storeUnknownExtElement(stream)
                   || readOtherXML(stream)
                   || readAnnotation(stream)
                   || readNotes(stream) ))
      {
        logUnknownElement(nextName, getLevel(), getVersion());
        stream.skipPastEnd( stream.next() );
      }
    }
    else
    {
      stream.skipPastEnd( stream.next() );
    }
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Writes (serializes) this SBML object by writing it to XMLOutputStream.
 */
void
SBase::write (XMLOutputStream& stream) const
{
  XMLNamespaces *xmlns = getNamespaces();

  if (0)
  {
    cout << "[DEBUG] SBase::write (element name) " << getElementName()
         << " (element ns) " << getElementNamespace(); 

    if (xmlns)
    {
      cout << " (xmlns) ";
      XMLOutputStream xos(std::cout);
      xos << *xmlns;
      cout << endl;
    }
  
  }

  stream.startElement( getElementName(), getPrefix() );

  writeXMLNS     ( stream );
  writeAttributes( stream );
  writeElements  ( stream );

  stream.endElement( getElementName(), getPrefix() );

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to write out their contained
 * SBML objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
SBase::writeElements (XMLOutputStream& stream) const
{
  if ( mNotes != NULL ) stream << *mNotes;

  /*
   * NOTE: CVTerms on a model have already been dealt with
   */

  const_cast <SBase *> (this)->syncAnnotation();
  if (mAnnotation != NULL) stream << *mAnnotation;
}

void
SBase::writeExtensionElements (XMLOutputStream& stream) const
{
  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  for (size_t i=0; i < mPlugins.size(); i++)
  {
    mPlugins[i]->writeElements(stream);
  }

  //  
  // writes elements of unkown packages
  //
  if (getLevel() > 2)
  {
    stream << mElementsOfUnknownPkg;
  }

  /////////////////////////////////////////////////////////////////////////

}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to create, store, and then
 * return an SBML object corresponding to the next XMLToken in the
 * XMLInputStream.
 *
 * @return the SBML object corresponding to next XMLToken in the
 * XMLInputStream or @c NULL if the token was not recognized.
 */
SBase*
SBase::createObject (XMLInputStream& stream)
{
  return NULL;
}


SBase*
SBase::createExtensionObject (XMLInputStream& stream)
{
  SBase* object = NULL;

  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  const string& uri  = stream.peek().getURI();
  SBasePlugin* sbext = NULL;

  for (size_t i=0; i < mPlugins.size(); i++)
  {
    if (mPlugins[i]->getURI() == uri)
    {
      sbext = mPlugins[i];
      break;
    }
  }

  if (sbext)
  {
#if 0
    std::cout << "[DEBUG] SBase::createExtensionObject " << getElementName() 
         << " " << uri << std::endl;
#endif
    object = sbext->createObject(stream);
  }
#if 0
  else
  {
    std::cout << "[DEBUG] SBase::createExtensionObject " << getElementName() 
              << " " << uri << " is NULL" << std::endl;
  }
#endif

  /////////////////////////////////////////////////////////////////////////

  return object;
} 


/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Subclasses should override this method to read (and store) XHTML,
 * MathML, etc. directly from the XMLInputStream.
 *
 * @return true if the subclass read from the stream, false otherwise.
 */
bool
SBase::readOtherXML (XMLInputStream& stream)
{
  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  bool read = false;

  for (size_t i=0; i < mPlugins.size(); i++)
  {
    if (mPlugins[i]->readOtherXML(this, stream))
      read = true;
  }

  return read;
}


/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return true if read an <annotation> element from the stream
 */
bool
SBase::readAnnotation (XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "annotation" 
    || (getLevel() == 1 && getVersion() == 1 && name == "annotations"))
  {
//    XMLNode* new_annotation = NULL;
    // If this is a level 1 document then annotations are not allowed on
    // the sbml container
    if (getLevel() == 1 && getTypeCode() == SBML_DOCUMENT)
    {
      logError(AnnotationNotesNotAllowedLevel1);
    }


    // If an annotation already exists, log it as an error and replace
    // the content of the existing annotation with the new one.

    if (mAnnotation != NULL)
    {
      if (getLevel() < 3) 
      {
        logError(NotSchemaConformant, getLevel(), getVersion(),
	        "Only one <annotation> element is permitted inside a "
	        "particular containing element.");
      }
      else
      {
        logError(MultipleAnnotations, getLevel(), getVersion());
      }
    }

    delete mAnnotation;
    mAnnotation = new XMLNode(stream);
    checkAnnotation();
    if(mCVTerms != NULL)
    {
      unsigned int size = mCVTerms->getSize();
      while (size--) delete static_cast<CVTerm*>( mCVTerms->remove(0) );
      delete mCVTerms; 
    }
    mCVTerms = new List();
    /* might have model history on sbase objects */
    if (getLevel() > 2 && getTypeCode()!= SBML_MODEL)
    {
      delete mHistory;
      if (RDFAnnotationParser::hasHistoryRDFAnnotation(mAnnotation))
      {
        mHistory = RDFAnnotationParser::parseRDFAnnotation(mAnnotation);
        setModelHistory(mHistory);
      }
      else
      {
        mHistory = NULL;
      }
    }
    if (RDFAnnotationParser::hasCVTermRDFAnnotation(mAnnotation))
      RDFAnnotationParser::parseRDFAnnotation(mAnnotation, mCVTerms);
//    new_annotation = RDFAnnotationParser::deleteRDFAnnotation(mAnnotation);
//    delete mAnnotation;
//    mAnnotation = new_annotation;
    return true;
  }

  return false;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return true if read a <notes> element from the stream
 */
bool
SBase::readNotes (XMLInputStream& stream)
{
  const string& name = stream.peek().getName();

  if (name == "notes")
  {
    // If this is a level 1 document then notes are not allowed on
    // the sbml container
    if (getLevel() == 1 && getTypeCode() == SBML_DOCUMENT)
    {
      logError(AnnotationNotesNotAllowedLevel1);
    }

    // If a notes element already exists, then it is an error.
    // If an annotation element already exists, then the ordering is wrong.
    // In either case, replace existing content with the new notes read.

    if (mNotes != NULL)
    {
      if (getLevel() < 3)
      {
        logError(NotSchemaConformant, getLevel(), getVersion(),
                "Only one <notes> element is permitted inside a "
	        "particualr containing element.");
      }
      else
      {
        logError(OnlyOneNotesElementAllowed, getLevel(), getVersion());
      }
    }
    else if (mAnnotation != NULL)
    {
      logError(NotSchemaConformant, getLevel(), getVersion(),
               "Incorrect ordering of <annotation> and <notes> elements -- "
	       "<notes> must come before <annotation> due to the way that "
	       "the XML Schema for SBML is defined.");
    }

    delete mNotes;
    mNotes = new XMLNode(stream);

    //
    // checks if the given default namespace (if any) is a valid
    // SBML namespace
    //
    const XMLNamespaces &xmlns = mNotes->getNamespaces();
    checkDefaultNamespace(&xmlns,"notes");

    if (getSBMLDocument() != NULL)
    {
      if (getSBMLDocument()->getNumErrors() == 0)
      {
        checkXHTML(mNotes);
      }
    }
    return true;
  }

  return false;
}

bool
SBase::getHasBeenDeleted()
{
  return mHasBeenDeleted;
}

/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return the ordinal position of the element with respect to its siblings
 * or -1 (default) to indicate the position is not significant.
 */
int
SBase::getElementPosition () const
{
  return -1;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * @return the SBMLErrorLog used to log errors during while reading and
 * validating SBML.
 */
SBMLErrorLog*
SBase::getErrorLog ()
{
  return (mSBML != NULL) ? mSBML->getErrorLog() : NULL;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Helper to log a common type of error.
 */
void
SBase::logUnknownAttribute( const string& attribute,
                            const unsigned int level,
                            const unsigned int version,
                            const string& element )
{
  ostringstream msg;

  msg << "Attribute '" << attribute << "' is not part of the "
      << "definition of an SBML Level " << level
      << " Version " << version << " " << element << " element.";

  /* Akiya made this note - so it needs checking BUT if it can crash due to no
   * SBMLDocument object then it can crash whatever level - so I put the catch outside
   */
  if (mSBML)
  {
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no SBMLDocument attached.
  //
    if (level < 3)
    {
        
      getErrorLog()->logError(NotSchemaConformant,
  			    level, version, msg.str());
    }
    else
    {
      if (element == "<listOfFunctionDefinitions>" 
        || element == "listOfFunctionDefinitions")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfFuncs, level,
          version, msg.str());
      }
      else if (element == "<sbml>" || element == "sbml")
      {
        getErrorLog()->logError(AllowedAttributesOnSBML, level,
          version, msg.str());
      }
      else if (element == "<listOfUnitDefinitions>"
        || element == "listOfUnitDefinitions")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfUnitDefs, level,
          version, msg.str());
      }
      else if (element == "<listOfCompartments>" 
        || element == "listOfCompartments")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfComps, level,
          version, msg.str());
      }
      else if (element == "<listOfSpecies>" || element == "listOfSpecies")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfSpecies, level,
          version, msg.str());
      }
      else if (element == "<listOfParameters>"
        || element == "listOfParameters")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfParams, level,
          version, msg.str());
      }
      else if (element == "<listOfInitialAssignments>"
        || element == "listOfInitialAssignments")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfInitAssign, level,
          version, msg.str());
      }
      else if (element == "<listOfRules>" || element == "listOfRules")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfRules, level,
          version, msg.str());
      }
      else if (element == "<listOfConstraints>"
        || element == "listOfConstraints")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfConstraints, level,
          version, msg.str());
      }
      else if (element == "<listOfReactions>" || element == "listOfReactions")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfReactions, level,
          version, msg.str());
      }
      else if (element == "<listOfEvents>" || element == "listOfEvents")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfEvents, level,
          version, msg.str());
      }
      else if (element == "<model>" || element == "model")
      {
        getErrorLog()->logError(AllowedAttributesOnModel, level,
          version, msg.str());
      }
      else if (element == "<listOfUnits>" || element == "listOfUnits")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfUnits, level,
          version, msg.str());
      }
      else if (element == "<unitDefinition>" || element == "unitDefinition")
      {
        getErrorLog()->logError(AllowedAttributesOnUnitDefinition, level,
          version, msg.str());
      }
      else if (element == "<unit>" || element == "unit")
      {
        getErrorLog()->logError(AllowedAttributesOnUnit, level,
          version, msg.str());
      }
      else if (element == "<functionDefinition>" 
        || element == "functionDefinition")
      {
        getErrorLog()->logError(AllowedAttributesOnFunc, level,
          version, msg.str());
      }
      else if (element == "<compartment>" || element == "compartment")
      {
        getErrorLog()->logError(AllowedAttributesOnCompartment, level,
          version, msg.str());
      }
      else if (element == "<species>" || element == "species")
      {
        getErrorLog()->logError(AllowedAttributesOnSpecies, level,
          version, msg.str());
      }
      else if (element == "<parameter>" || element == "parameter")
      {
        getErrorLog()->logError(AllowedAttributesOnParameter, level,
          version, msg.str());
      }
      else if (element == "<initialAssignment>" 
        || element == "initialAssignment")
      {
        getErrorLog()->logError(AllowedAttributesOnInitialAssign, level,
          version, msg.str());
      }
      else if (element == "<assignmentRule>"
        || element == "assignmentRule")
      {
        getErrorLog()->logError(AllowedAttributesOnAssignRule, level,
          version, msg.str());
      }
      else if (element == "<rateRule>" || element == "rateRule")
      {
        getErrorLog()->logError(AllowedAttributesOnRateRule, level,
          version, msg.str());
      }
      else if (element == "<algebraicRule>" || element == "algebraicRule")
      {
        getErrorLog()->logError(AllowedAttributesOnAlgRule, level,
          version, msg.str());
      }
      else if (element == "<constraint>" || element == "constraint")
      {
        getErrorLog()->logError(AllowedAttributesOnConstraint, level,
          version, msg.str());
      }
      else if (element == "<reaction>" || element == "reaction")
      {
        getErrorLog()->logError(AllowedAttributesOnReaction, level,
          version, msg.str());
      }
      else if (element == "<listOfReactants>" 
        || element == "listOfReactants")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfSpeciesRef, level,
          version, msg.str());
      }
      else if (element == "<listOfProducts>"
        || element == "listOfProducts")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfSpeciesRef, level,
          version, msg.str());
      }
      else if (element == "<listOfModifiers>"
        || element == "listOfModifiers")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfMods, level,
          version, msg.str());
      }
      else if (element == "<speciesReference>"
        || element == "speciesReference")
      {
        getErrorLog()->logError(AllowedAttributesOnSpeciesReference, level,
          version, msg.str());
      }
      else if (element == "<modifierSpeciesReference>"
        || element == "modifierSpeciesReference")
      {
        getErrorLog()->logError(AllowedAttributesOnModifier, level,
          version, msg.str());
      }
      else if (element == "<listOfLocalParameters>"
        || element == "listOfLocalParameters")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfLocalParam, level,
          version, msg.str());
      }
      else if (element == "<kineticLaw>" || element == "kineticLaw")
      {
        getErrorLog()->logError(AllowedAttributesOnKineticLaw, level,
          version, msg.str());
      }
      else if (element == "<localParameter>" || element == "localParameter")
      {
        getErrorLog()->logError(AllowedAttributesOnLocalParameter, level,
          version, msg.str());
      }
      else if (element == "<event>" || element == "event")
      {
        getErrorLog()->logError(AllowedAttributesOnEvent, level,
          version, msg.str());
      }
      else if (element == "<listOfEventAssignments>"
        || element == "listOfEventAssignments")
      {
        getErrorLog()->logError(AllowedAttributesOnListOfEventAssign, level,
          version, msg.str());
      }
      else if (element == "<trigger>" || element == "trigger")
      {
        getErrorLog()->logError(AllowedAttributesOnTrigger, level,
          version, msg.str());
      }
      else if (element == "<delay>" || element == "delay")
      {
        getErrorLog()->logError(AllowedAttributesOnDelay, level,
          version, msg.str());
      }
      else if (element == "<eventAssignment>" || element == "eventAssignment")
      {
        getErrorLog()->logError(AllowedAttributesOnEventAssignment, level,
          version, msg.str());
      }
      else if (element == "<priority>" || element == "priority")
      {
        getErrorLog()->logError(AllowedAttributesOnPriority, level,
          version, msg.str());
      }
  }
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Helper to log a common type of error.
 */
void
SBase::logUnknownElement( const string& element,
			  const unsigned int level,
			  const unsigned int version )
{
  bool logged = false;
  ostringstream msg;

  if (level > 2 && getTypeCode() == SBML_LIST_OF)
  {
    int tc = static_cast<ListOf*>(this)->getItemTypeCode();
    msg << "Element '" << element << "' is not part of the definition of "
      << this->getElementName() << ".";
    switch (tc)
    {
    case SBML_UNIT:
      getErrorLog()->logError(OnlyUnitsInListOfUnits, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_FUNCTION_DEFINITION:
    
      getErrorLog()->logError(OnlyFuncDefsInListOfFuncDefs, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_UNIT_DEFINITION:
    
      getErrorLog()->logError(OnlyUnitDefsInListOfUnitDefs, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_COMPARTMENT:
    
      getErrorLog()->logError(OnlyCompartmentsInListOfCompartments, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_SPECIES:
    
      getErrorLog()->logError(OnlySpeciesInListOfSpecies, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_PARAMETER:
    
      getErrorLog()->logError(OnlyParametersInListOfParameters, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_INITIAL_ASSIGNMENT:
    
      getErrorLog()->logError(OnlyInitAssignsInListOfInitAssigns, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_CONSTRAINT:
    
      getErrorLog()->logError(OnlyConstraintsInListOfConstraints, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_RULE:
    
      getErrorLog()->logError(OnlyRulesInListOfRules, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_REACTION:
    
      getErrorLog()->logError(OnlyReactionsInListOfReactions, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_EVENT:
    
      getErrorLog()->logError(OnlyEventsInListOfEvents, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_LOCAL_PARAMETER:
    
      getErrorLog()->logError(OnlyLocalParamsInListOfLocalParams, 
                                level, version, msg.str());
      logged = true;
      break;
    case SBML_EVENT_ASSIGNMENT:
    
      getErrorLog()->logError(OnlyEventAssignInListOfEventAssign, 
                                level, version, msg.str());
      logged = true;
      break;
    }
  }

  if (!logged)
  {
    ostringstream msg;

    msg << "Element '" << element << "' is not part of the definition of "
        << "SBML Level " << level << " Version " << version << ".";
      
    if (mSBML != NULL)
    getErrorLog()->logError(UnrecognizedElement,
			    level, version, msg.str());
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Helper to log a common type of error.
 */
void
SBase::logEmptyString( const string& attribute,
                       const unsigned int level,
                       const unsigned int version,
                       const string& element )
                       
{
  ostringstream msg;

  msg << "Attribute '" << attribute << "' on an "
    << element << " must not be an empty string.";
      
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no SBMLDocument attached.
  //
  if (mSBML != NULL)
    getErrorLog()->logError(NotSchemaConformant,
                            level, version, msg.str());
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Convenience method for easily logging problems from within method
 * implementations.
 *
 * This is essentially a short form of getErrorLog()->logError(...)
 */
void
SBase::logError (  unsigned int       id
                 , const unsigned int level
                 , const unsigned int version
                 , const std::string& details )
{
  //
  // (TODO) Needs to be fixed so that error can be added when
  // no SBMLDocument attached.
  //
  if ( SBase::getErrorLog() != NULL && mSBML != NULL) 
    getErrorLog()->logError(id, getLevel(), getVersion(), details);
}
/** @endcond */


/** @cond doxygen-libsbml-internal */

/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
SBase::addExpectedAttributes(ExpectedAttributes& attributes)
{
  //
  // metaid: ID { use="optional" }  (L2v1 ->)
  //
  if (getLevel() > 1 )
    attributes.add("metaid");  

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v3 ->)
  //
  if (getLevel() > 2 || (getLevel() == 2 && getVersion() > 2) )
    attributes.add("sboTerm");  
}


/*
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */
void
SBase::readAttributes (const XMLAttributes& attributes, 
                       const ExpectedAttributes& expectedAttributes)
{
  const_cast<XMLAttributes&>(attributes).setErrorLog(getErrorLog());

  const unsigned int level   = getLevel  ();
  const unsigned int version = getVersion();

  //
  // check that all attributes are expected
  //
  for (int i = 0; i < attributes.getLength(); i++)
  {
    std::string name   = attributes.getName(i);
    std::string uri    = attributes.getURI(i);
    std::string prefix = attributes.getPrefix(i);

    //
    // To allow prefixed attribute whose namespace doesn't belong to
    // core or extension package.
    //
    // (e.g. xsi:type attribute in Curve element in layout extension)
    //
    if (!prefix.empty())
    {
      if ( expectedAttributes.hasAttribute(prefix + ":" + name) ) continue;
    }
   

    //
    // Checks if there are attributes of unknown package extensions
    //
    if (!prefix.empty() && (prefix != getPrefix()) && (uri != mURI) )
    {
      storeUnknownExtAttribute(getElementName(), attributes, i);
    }
    else if (!expectedAttributes.hasAttribute(name))
    {
      logUnknownAttribute(name, level, version, getElementName());
    }
  }

  if (level > 1)
  {
    bool assigned = attributes.readInto("metaid", mMetaId);
  
    if (assigned && mMetaId.empty())
    {
      logEmptyString("metaid", level, version,
                     SBMLTypeCode_toString(getTypeCode(), getPackageName().c_str()));
    }

    if (isSetMetaId())
    {
      if (!SyntaxChecker::isValidXMLID(mMetaId))
      {
        logError(InvalidMetaidSyntax, getLevel(), getVersion());
      }
    }
  }

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v3 ->)
  //
  // (NOTE) 
  //
  //  SBO::readTerm() must be invoked for L2V2 object in each 
  //  readAttributes function in SBase derived class if the sboTerm 
  //  attribute is required in L2V2.
  //
  if (level > 2 || ( (level == 2) && (version > 2) ) )
  {
    mSBOTerm = SBO::readTerm(attributes, this->getErrorLog());
  }

  //
  // (EXTENSION)
  //
  readExtensionAttributes(attributes);
}


void
SBase::readExtensionAttributes (const XMLAttributes& attributes)
{
  const_cast<XMLAttributes&>(attributes).setErrorLog(getErrorLog());

  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  for (size_t i=0; i < mPlugins.size(); i++)
  {
#if 0
    std::cout << "[DEBUG] SBase::readExtensionAttributes " 
              << mPlugins[i]->getURI()  << " "
              << getElementName() << std::endl;
#endif
    ExpectedAttributes ea;
    mPlugins[i]->addExpectedAttributes(ea);
    mPlugins[i]->readAttributes(attributes,ea);
  }

  /////////////////////////////////////////////////////////////////////////

}


/**
 * Stores the given attribute to the list of ignored attributes if
 * the given attribute belongs to some unknown package.
 * Unknown attribute error will be logged if the "required" attribute
 * of the package in SBMLDocument element is "true".
 */
void 
SBase::storeUnknownExtAttribute(const std::string& element,
                                const XMLAttributes& xattr, unsigned int index)
{
  if (!mSBML) return;

  if (element == "sbml" && xattr.getName(index) == "required")
    return;

  std::string uri = xattr.getURI(index);

  //
  // Checks if the extension package is enabled.
  //
  if (!mSBML->isPkgURIEnabled(uri))
  {
    //
    // Checks if the extension package with the uri is unsupporeted
    // (ignored)
    //
    if (mSBML->isIgnoredPkg(uri))
    {
      std::string name   = xattr.getName(index);
      std::string prefix = xattr.getPrefix(index);
      std::string value  = xattr.getValue(index);

      mAttributesOfUnknownPkg.add(name,value,uri,prefix);

      /* this is now caught earlier and so can be ignored here
      if (mSBML->getPkgRequired(uri))
      {
        logUnknownAttribute(prefix + ":" + name, getLevel(), getVersion(), element);
      }
      */
    }
    else
    {
      std::string name   = xattr.getName(index);
      std::string prefix = xattr.getPrefix(index);
      logUnknownAttribute(prefix + ":" + name, getLevel(), getVersion(), element);
    }
  }
}


/**
 *
 */
bool
SBase::storeUnknownExtElement(XMLInputStream &stream)
{
  string uri = stream.peek().getURI();

  if (SBMLNamespaces::isSBMLNamespace(uri))
  {
    return false;
  }
  else if (mSBML->isIgnoredPkg(uri))
  {
    //
    // Checks if the extension package with the uri is unknown
    // (ignored)
    //
    /* do not need to do this now i have logged this as
     * a required package that cannot be interpreted
     
    if (mSBML->getPkgRequired(uri))
    {
      const string& name   = stream.peek().getName();
      string prefix = stream.peek().getPrefix();
      if (!prefix.empty()) prefix += ":";
      logUnknownElement(prefix + name, getLevel(), getVersion());
    }
    */

    XMLNode xmlnode(stream);
    mElementsOfUnknownPkg.addChild(xmlnode);

    return true;
  }

  return false;
}

/** @endcond */


/** @cond doxygen-libsbml-internal */


/**
 * Returns the prefix of this element.
 */
std::string 
SBase::getPrefix() const
{
  std::string prefix = "";

  XMLNamespaces *xmlns = getNamespaces();

  if(xmlns && mSBML && !mSBML->isEnabledDefaultNS(mURI))
  {
    prefix = xmlns->getPrefix(mURI);  
#if 0
    std::cout << "[DEBUG] SBase::getPrefix() " << prefix << " URI " << mURI 
              << " element " << getElementName() << std::endl;
#endif
  }
#if 0
  else
  {
    if (!xmlns)
    {
      std::cout << "[DEBUG] SBase::getPrefix() [NO XMLNS] " << prefix << " URI " << mURI 
              << " element " << getElementName() << std::endl;
    }
    if (!mSBML)
    {
      std::cout << "[DEBUG] SBase::getPrefix() [NO mSBML] " << prefix << " URI " << mURI 
              << " element " << getElementName() << std::endl;
    }
  
  }
#endif

  return prefix;
}


/**
 * Returns the root element of this element.
 *
 * @note The root element may not be an SBMLDocument element. For example,
 * this element is the root element if this element doesn't have a parent
 * SBML object (i.e. mParentSBMLObject is NULL)
 */
SBase* 
SBase::getRootElement()
{
  if (mSBML)
  {
    return mSBML;
  }
  else if (mParentSBMLObject)
  {
    return mParentSBMLObject->getRootElement();
  }
  else
  {
    return this;
  }
}


/*
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 */
void
SBase::writeAttributes (XMLOutputStream& stream) const
{
//  if (getTypeCode() == SBML_DOCUMENT)
//  {
//    if (this->getNamespaces()) stream << *(this->getNamespaces());
//  }
  unsigned int level   = getLevel();
  unsigned int version = getVersion();

  if ( level > 1 && !mMetaId.empty() )
  {
    stream.writeAttribute("metaid", getPrefix(), mMetaId);
  }

  //
  // sboTerm: SBOTerm { use="optional" }  (L2v3 ->)
  //
  // (NOTE) 
  //
  //  SBO::writeTerm() must be invoked for L2V2 object in each 
  //  readAttributes function in SBase derived class if the sboTerm 
  //  attribute is required in L2V2.
  //
  if (level > 2 || ( (level == 2) && (version > 2) ) )
  {
    SBO::writeTerm(stream, mSBOTerm);
  }
}


/**
 *
 * Subclasses should override this method to write their xmlns attriubutes
 * (if any) to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.
 *
 */
void 
SBase::writeXMLNS (XMLOutputStream& stream) const
{
  // do nothing.
}



void
SBase::writeExtensionAttributes (XMLOutputStream& stream) const
{
  /* ---------------------------------------------------------
   *
   * (EXTENSION)
   *
   * ----------------------------------------------------------
   */

  // debug
#if 0
  cout << "[DEBUG] SBase::writeExtensionAttributes() " << getTypeCode() << endl;
#endif

  for (size_t i=0; i < mPlugins.size(); i++)
  {
#if 0
    cout << "[DEBUG] SBase::writeExtensionAttributes() " << i << endl;
#endif
    mPlugins[i]->writeAttributes(stream);
  }

  //
  // writes attributes of unknown packages
  //
  for (int i=0; i < mAttributesOfUnknownPkg.getLength(); i++)
  {
    std::string name   = mAttributesOfUnknownPkg.getName(i);
    std::string prefix = mAttributesOfUnknownPkg.getPrefix(i);
    std::string value  = mAttributesOfUnknownPkg.getValue(i);
    stream.writeAttribute(name, prefix, value); 
  }

  /////////////////////////////////////////////////////////////////////////
}


/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Synchronizes the annotation of this SBML object. 
 */
void
SBase::syncAnnotation ()
{
  bool hasRDF = false;
  bool hasAdditionalRDF = false;

  //
  // (*NOTICE*) 
  //
  // syncAnnotation() must not exit here even if the CVTerm objects (mCVTerms) 
  // in this SBase object is null or empty (0 CVTerm object).
  // The reason is that syncAnnotation updates the mAnnotation (an XMLNode object 
  // of annotation element in this SBase object) as follows:
  //
  //   (1) removes XMLNode elements corresponding to CVTerm and/or ModelHistory 
  //       objects from the mAnnotation, and
  //   (2) converts the current mCVTerms object (and mHistory objcect in 
  //       Model::syncAnnotation()) into corresponding temporary XMLNode objects,
  //       and
  //   (3) merges the temporary XMLNode objects into the mAnnotation 
  //
  // For example, an SBase object with null or empty mCVTerms needs to be updated
  // if mAnnotation contains XMLNode objects corresponding to CVTerm. 
  // (This can happen when unsetCVTerms() function invoked after addCVTerm() function.)
  //

  // determine status of existing annotation before doing anything
  if (mAnnotation != NULL)
  {
    hasRDF = RDFAnnotationParser::hasRDFAnnotation(mAnnotation);
    hasAdditionalRDF = 
      RDFAnnotationParser::hasAdditionalRDFAnnotation(mAnnotation);
  }

  if(mAnnotation != NULL && hasRDF)
  {
    XMLNode* new_annotation = 
      RDFAnnotationParser::deleteRDFAnnotation(mAnnotation);
    
    if(new_annotation == NULL)
    {
        XMLToken ann_token = XMLToken(XMLTriple("annotation", "", ""), 
                                      XMLAttributes());
        new_annotation = new XMLNode(ann_token);
        new_annotation->addChild(*mAnnotation);
    }
    *mAnnotation = *new_annotation;
    delete new_annotation;
  }

  XMLNode * history = NULL;
  if (getTypeCode() != SBML_MODEL)
  {
    history = RDFAnnotationParser::parseModelHistory(this);
  }

  XMLNode * cvTerms = RDFAnnotationParser::parseCVTerms(this);

  if (history != NULL)
  {
    if (mAnnotation == NULL)
    {
      mAnnotation = history;
    }
    else
    {
      if (mAnnotation->isEnd())
      {
        mAnnotation->unsetEnd();
      }
      if (hasAdditionalRDF)
      {
        //need to insert the history into existing RDF
        unsigned int n = 0;
        while (n < mAnnotation->getNumChildren())
        {
          if (mAnnotation->getChild(n).getName() == "RDF")
          {
            mAnnotation->getChild(n).insertChild(0, 
              history->getChild(0).getChild(0));
            break;
          }
          n++;
        }
      }
      else
      {
        mAnnotation->addChild(history->getChild(0));
      }
      delete history;
    }
  }
  else if (cvTerms != NULL)
  {
    if (mAnnotation == NULL)
    {
      mAnnotation = cvTerms;
    }
    else
    {
      if (mAnnotation->isEnd())
      {
        mAnnotation->unsetEnd();
      }
      if (hasAdditionalRDF)
      {
        //need to insert the CVTerms into existing RDF
        unsigned int n = 0;
        while (n < mAnnotation->getNumChildren())
        {
          if (mAnnotation->getChild(n).getName() == "RDF")
          {
            mAnnotation->getChild(n).insertChild(0, 
              cvTerms->getChild(0).getChild(0));
            break;
          }
          n++;
        }
      }
      else
      {
        mAnnotation->addChild(cvTerms->getChild(0));
      }
      delete cvTerms;
    }
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Checks that SBML element has been read in the proper order.  If object
 * is not in the expected position, an error is logged.
 */
void
SBase::checkOrderAndLogError (SBase* object, int expected)
{
  int actual = object->getElementPosition();

  if (actual != -1 && actual < expected)
  {
    SBMLErrorCode_t error = IncorrectOrderInModel;

    if (object->getPackageName() == "core")
    {
      if (object->getTypeCode() == SBML_LIST_OF)
      {
        int tc = static_cast<ListOf*>(object)->getItemTypeCode();
        //typecode (int) tc = static_cast<ListOf*>(object)->getItemTypeCode();

        if (tc == SBML_SPECIES_REFERENCE || tc == SBML_MODIFIER_SPECIES_REFERENCE)
        {
          error = IncorrectOrderInReaction;
        }
      }
      else if (object->getTypeCode() == SBML_TRIGGER)
      {
        error = IncorrectOrderInEvent;
      }

      logError(error, getLevel(), getVersion());
    }
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/**
  * Checks that an SBML ListOf element has been populated.  
  * If a listOf element has been declared with no elements, 
  * an error is logged.
  */
void 
SBase::checkListOfPopulated(SBase* object)
{
  //
  // (TODO) Currently, the following check code works only for
  //        elements in SBML core.
  //        This function may need to be extented for other elements 
  //        defined in each package extension.
  //
  if (object->getPackageName() != "core") 
  {
    return;
  }

  if (object->getTypeCode() == SBML_LIST_OF)
  {
    // Check that the list has at least one element.
    if (static_cast <ListOf*> (object)->size() == 0)
    {
      //typecode (int) tc = static_cast<ListOf*>(object)->getItemTypeCode();
      int tc = static_cast<ListOf*>(object)->getItemTypeCode();
      SBMLErrorCode_t error = EmptyListElement;

      // By default, the error will be the EmptyListElement error, unless
      // we have a special case for which SBML has a separate error code.
      switch (tc)
      {
      case SBML_UNIT:
        if (object->getLevel() < 3)
          error = EmptyListOfUnits;
        else
          error = EmptyUnitListElement;
        break;

      case SBML_SPECIES_REFERENCE:
      case SBML_MODIFIER_SPECIES_REFERENCE:
        error = EmptyListInReaction;
        break;

      case SBML_PARAMETER:
        // If listOfParameters is inside a KineticLaw, we have a separate code.
        if (this->getTypeCode() == SBML_KINETIC_LAW)
        {
          error = EmptyListInKineticLaw;
        }
        break;
      case SBML_LOCAL_PARAMETER:
        error = EmptyListInKineticLaw;
        break;

      default:;
      }

      logError(error, getLevel(), getVersion());
    }
  }
  else if (object->getTypeCode() == SBML_KINETIC_LAW)
  {
    /* 
     * if nothing has been set in the kineticLaw we assume its is empty
     */
    if (static_cast <KineticLaw *> (object)->isSetMath()           == 0  &&
        static_cast <KineticLaw *> (object)->isSetFormula()        == 0  &&
        static_cast <KineticLaw *> (object)->isSetTimeUnits()      == 0  &&
        static_cast <KineticLaw *> (object)->isSetSubstanceUnits() == 0  &&
        static_cast <KineticLaw *> (object)->isSetSBOTerm()        == 0  &&
        static_cast <KineticLaw *> (object)->getNumParameters()    == 0)
    {
      logError(EmptyListInReaction, getLevel(), getVersion());
    }
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
const std::string
SBase::checkMathMLNamespace(const XMLToken elem)
{
  std::string prefix = "";
  unsigned int match = 0;
  int n;
  if (elem.getNamespaces().getLength() != 0)
  {
    for (n = 0; n < elem.getNamespaces().getLength(); n++)
    {
      if (!strcmp(elem.getNamespaces().getURI(n).c_str(), 
                  "http://www.w3.org/1998/Math/MathML"))
      {
        match = 1;
        break;
      }
    }
  }
  if (match == 0)
  {
    if( mSBML->getNamespaces() != NULL)
    /* check for implicit declaration */
    {
      for (n = 0; n < mSBML->getNamespaces()->getLength(); n++)
      {
        if (!strcmp(mSBML->getNamespaces()->getURI(n).c_str(), 
                    "http://www.w3.org/1998/Math/MathML"))
        {
          match = 1;
          prefix = mSBML->getNamespaces()->getPrefix(n);
          break;
        }
      }
    }
  }
  if (match == 0)
  {
    logError(InvalidMathElement);
  }

  return prefix;
}
/** @endcond */


/** @cond doxygen-libsbml-internal */

void 
SBase::checkDefaultNamespace(const XMLNamespaces* xmlns, 
                             const std::string& elementName,
                             const std::string& prefix)
{
  //
  // checks if the given default namespace (if any) is a valid
  // SBML namespace
  //
  if (xmlns != NULL && xmlns->getLength() > 0)
  {
    const std::string defaultURI = xmlns->getURI(prefix);
    if (!defaultURI.empty() && mURI != defaultURI)
    {
      static ostringstream errMsg;
      errMsg.str("");
      errMsg << "xmlns=\"" << defaultURI << "\" in <" << elementName
             << "> element is an invalid namespace." << endl;
      
      logError(NotSchemaConformant, getLevel(), getVersion(), errMsg.str());
    }
  }
}

/**
  * Checks the annotation does not declare an sbml namespace.
  * If the annotation declares an sbml namespace an error is logged.
  */
void
SBase::checkAnnotation()
{
  unsigned int nNodes = 0;
  unsigned int match = 0;
  int n = 0;
  std::vector<std::string> uri_list;
  uri_list.clear();

  if (mAnnotation == NULL) return;

  //
  // checks if the given default namespace (if any) is a valid
  // SBML namespace
  //
  const XMLNamespaces &xmlns = mAnnotation->getNamespaces();
  checkDefaultNamespace(&xmlns,"annotation");

  while (nNodes < mAnnotation->getNumChildren())
  {
    XMLNode topLevel = mAnnotation->getChild(nNodes);

    std::string uri = topLevel.getURI();
    std::string prefix = topLevel.getPrefix();

#ifdef USE_LIBXML
    // sometimes libxml does not catch an empty ns with a prefix
    if (uri.empty() && !prefix.empty())
    {
      logError(BadXMLPrefix);
      nNodes++;
      continue;
    }
#endif

    // cannot be other toplevel element with this uri
    if (!uri.empty())
    {
      if (find(uri_list.begin(), uri_list.end(), uri) 
                                               != uri_list.end())
      {
        logError(DuplicateAnnotationNamespaces);
      }
      uri_list.push_back(uri);
    }

    match = 0;
    n = 0;

    bool implicitNSdecl = false;
   // must have a namespace
    if (topLevel.getNamespaces().getLength() == 0)
    {
      // not on actual element - is it explicit ??
      if( mSBML->getNamespaces() != NULL)
      /* check for implicit declaration */
      {
        for (n = 0; n < mSBML->getNamespaces()->getLength(); n++)
        {
          if (!strcmp(mSBML->getNamespaces()->getPrefix(n).c_str(), 
                        prefix.c_str()))
          {
            implicitNSdecl = true;
            break;
          }
        }
     }


      if (!implicitNSdecl)
      {
        logError(MissingAnnotationNamespace);
      }
    }
    // cannot declare sbml namespace
    while(!match && n < topLevel.getNamespaces().getLength())
    {
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                          "http://www.sbml.org/sbml/level1");
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                          "http://www.sbml.org/sbml/level2");
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                "http://www.sbml.org/sbml/level2/version2");
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                "http://www.sbml.org/sbml/level2/version3");
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                "http://www.sbml.org/sbml/level2/version4");
      match += !strcmp(topLevel.getNamespaces().getURI(n).c_str(), 
                                "http://www.sbml.org/sbml/level3/version1/core");
      n++;
    }
    if (match > 0)
    {
      logError(SBMLNamespaceInAnnotation);
      break;
    }

    if (implicitNSdecl && prefix.empty())
    {
      /* if this is L3 a missing namespace with empty prefix means 
       * it is using the sbml ns - which is allowed in L3
       */
      if (getLevel() < 3)
      {
        logError(MissingAnnotationNamespace);
      }
      logError(SBMLNamespaceInAnnotation);   
    }
    nNodes++;
  }
}
/** @endcond */


/** @cond doxygen-libsbml-internal */
/*
 * Checks that the XHTML is valid.
 * If the xhtml does not conform to the specification of valid xhtml within
 * an sbml document, an error is logged.
 */
void
SBase::checkXHTML(const XMLNode * xhtml)
{
  if (xhtml == NULL) return;

  const string&  name = xhtml->getName();
  unsigned int i, errorNS, errorXML, errorDOC, errorELEM;

  if (name == "notes")
  {
    errorNS   = NotesNotInXHTMLNamespace;
    errorXML  = NotesContainsXMLDecl;
    errorDOC  = NotesContainsDOCTYPE;
    errorELEM = InvalidNotesContent;
  }
  else if (name == "message")
  {
    errorNS   = ConstraintNotInXHTMLNamespace;
    errorXML  = ConstraintContainsXMLDecl;
    errorDOC  = ConstraintContainsDOCTYPE;
    errorELEM = InvalidConstraintContent;
  }
  else                                  // We shouldn't ever get to this point.
  {
    logError(UnknownError);
    return;
  }

  /*
  * errors relating to a misplaced XML or DOCTYPE declaration 
  * will also cause a parser error.
  * since parsing will terminate at this error, then if it has occurred
  * it will be in the XML currently being checked and so a more
  * informative message can be added
  */
  for (i = 0; i < getErrorLog()->getNumErrors(); i++)
  {
    if (getErrorLog()->getError(i)->getErrorId() == BadXMLDeclLocation)
    {
      logError(errorXML);
    }
    if (getErrorLog()->getError(i)->getErrorId() == BadlyFormedXML)
    {
      logError(errorDOC);
    }
  }

  XMLNamespaces* toplevelNS = (mSBML) ? mSBML->getNamespaces() : NULL;

  /*
  * namespace declaration is variable
  * if a whole html tag has been used
  * or a whole body tag then namespace can be implicitly declared
  */
  unsigned int children = xhtml->getNumChildren();

  if (children > 1)
  {
    for (i=0; i < children; i++)
    {
      if (SyntaxChecker::isAllowedElement(xhtml->getChild(i)))
      {
        if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(i),
                                                  toplevelNS))
        {
          logError(errorNS);
        }
      }
      else
      {
        logError(errorELEM);
      }
    }
  }
  else
  {
    /* only one element which can be html or body with either implicit/explicit
    * namespace declaration
    * OR could be one of the listed elements.
    */

    const string& top_name = xhtml->getChild(0).getName();

    if (top_name != "html" && top_name != "body"
      && !SyntaxChecker::isAllowedElement(xhtml->getChild(0)))
    {
      logError(errorELEM);
    }
    else
    {
      if (!SyntaxChecker::hasDeclaredNS(xhtml->getChild(0), toplevelNS))
      {
        logError(errorNS);
      }
      if (top_name == "html" 
        && !SyntaxChecker::isCorrectHTMLNode(xhtml->getChild(0)))
      {
        logError(errorELEM);
      }
    }
  }
}

/** @endcond */
/** @cond doxygen-libsbml-internal */
/* default for components that have no required attributes */
bool
SBase::hasRequiredAttributes() const
{
  return true;
}

/* default for components that have no required elements */
bool
SBase::hasRequiredElements() const
{
  return true;
}

void
SBase::removeDuplicateAnnotations()
{
  bool resetNecessary = false;
  XMLNamespaces xmlns = XMLNamespaces();
  xmlns.add("http://www.sbml.org/libsbml/annotation", "");
  XMLTriple triple = XMLTriple("duplicateTopLevelElements",
    "http://www.sbml.org/libsbml/annotation", "");
  XMLAttributes att = XMLAttributes();
  XMLToken token = XMLToken(triple, att, xmlns);
  XMLNode * newNode = NULL;
  if (isSetAnnotation())
  { 
    //make a copy to work with
    XMLNode * newAnnotation = mAnnotation->clone();

    unsigned int numChildren = newAnnotation->getNumChildren();
    if (numChildren == 1)
      return;

    bool duplicate = false;
    for (unsigned int i = 0; i < numChildren; i++)
    {
      duplicate = false;
      std::string name = newAnnotation->getChild(i).getName();
      for (unsigned int j = numChildren-1; j > i; j--)
      {
        if (name == newAnnotation->getChild(j).getName())
        {
          resetNecessary = true;
          duplicate = true;
          if (newNode == NULL)
          {
            // need to  create the new node
            newNode = new XMLNode(token);
          }
          newNode->addChild(static_cast <XMLNode> 
                            (*(newAnnotation->removeChild(j))));
        }
      }
      if (duplicate)
        newNode->addChild(static_cast <XMLNode>
                          (*(newAnnotation->removeChild(i))));
      numChildren = newAnnotation->getNumChildren();
    }
    if (resetNecessary)
    {
      newAnnotation->addChild(*(newNode));
      setAnnotation(newAnnotation);
    }
  }


}


/** @endcond */

/** @cond doxygen-libsbml-internal */
/*
 * Stores the location (line and column) and any XML namespaces (for
 * roundtripping) declared on this SBML (XML) element.
 */
void
SBase::setSBaseFields (const XMLToken& element)
{
  mLine   = element.getLine  ();
  mColumn = element.getColumn();

  if (element.getNamespaces().getLength() > 0)
  {
    XMLNamespaces tmpxmlns(element.getNamespaces());
    setNamespaces(&tmpxmlns);
  }
  else
  {
    setNamespaces(NULL);
  }
}


/**
 *
 * (Extension)
 *
 * Sets the XML namespace to which this element belogns to.
 * For example, all elements that belong to SBML Level 3 Version 1 Core
 * must set the namespace to "http://www.sbml.org/sbml/level3/version1/core";
 * all elements that belong to Layout Extension Version 1 for SBML Level 3
 * Version 1 Core must set the namespace to
 * "http://www.sbml.org/sbml/level3/version1/layout/version1/"
 *
 */
int
SBase::setElementNamespace(const std::string &uri)
{
//  cout << "[DEBUG] SBase::setElementNamespace() " << uri << endl;
  mURI = uri;

  return LIBSBML_OPERATION_SUCCESS;
}

/**
 * Gets the XML namespace to which this element belongs to.
 */
const std::string& 
SBase::getElementNamespace() const
{
  return mURI;
}

/** @endcond */



/** @cond doxygen-c-only */

/**
 * Adds a copy of the given CVTerm to this SBML object.
 *
 * @param sb the object to add the CVTerm to
 * @param term the CVTerm_t to assign
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 * @li LIBSBML_INVALID_OBJECT
 *
 * @note The annotation constructed from a CVTerm uses the metaid
 * of the object to identify it.  Adding a CVTerm to an object
 * where the 'metaId' attribute has not been set will fail with the
 * return value LIBSBML_UNEXPECTED_ATTRIBUTE.
 */
LIBSBML_EXTERN
int 
SBase_addCVTerm(SBase_t *sb, CVTerm_t *term)
{
  return (sb != NULL) ? sb->addCVTerm(term) : LIBSBML_INVALID_OBJECT;
}


/**
 * Adds a copy of the given CVTerm to this SBML object creating
 * a new bBag element with the same identifier.
 *
 * @param sb the object to add the CVTerm to
 * @param term the CVTerm_t to assign
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 * @li LIBSBML_INVALID_OBJECT
 *
 * @note The annotation constructed from a CVTerm uses the metaid
 * of the object to identify it.  Adding a CVTerm to an object
 * where the 'metaId' attribute has not been set will fail with the
 * return value LIBSBML_UNEXPECTED_ATTRIBUTE.
 */
LIBSBML_EXTERN
int 
SBase_addCVTermNewBag(SBase_t *sb, CVTerm_t *term)
{
  return (sb != NULL) ? sb->addCVTerm(term, true) : LIBSBML_INVALID_OBJECT;
}


/**
 * Returns a list of CVTerm objects in the annotations of this SBML
 * object.
 *
 * @param sb the object to getCVTerms from
 * 
 * @return the list of CVTerms for this SBML object.
 */
LIBSBML_EXTERN
List_t* 
SBase_getCVTerms(SBase_t *sb)
{
  return (sb != NULL) ? sb->getCVTerms() : 0;
}


/**
 * Returns the number of CVTerm objects in the annotations of this SBML
 * object.
 *
 * @param sb the object to getCVTerms from
 * 
 * @return the number of CVTerms for this SBML object.
 */
LIBSBML_EXTERN
unsigned int 
SBase_getNumCVTerms(SBase_t *sb)
{
  return (sb != NULL) ? sb->getNumCVTerms() : SBML_INT_MAX;
}

/**
 * Returns the nth CVTerm in the list of CVTerms of this SBML
 * object.
 *
 * @param sb the object to getCVTerms from
 * @param n unsigned int the index of the CVTerm to retrieve
 *
 * @return the nth CVTerm in the list of CVTerms for this SBML object.
 */
LIBSBML_EXTERN
CVTerm_t* 
SBase_getCVTerm(SBase_t *sb, unsigned int n)
{
  return (sb != NULL) ? static_cast <CVTerm_t *> (sb->getCVTerm(n)) : NULL;
}

/**
 * Clears the list of CVTerms of this SBML
 * object.
 *
 * @param sb the object to clear CVTerms from
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int 
SBase_unsetCVTerms(SBase_t *sb)
{
  return (sb != NULL) ? sb->unsetCVTerms() : LIBSBML_INVALID_OBJECT;
}


/**
 * Returns the ModelHistory of the given SBase_t structure.
 *
 * @return the ModelHistory of the given SBase_t structure.
 * 
 * @param m the SBase_t structure
 */
LIBSBML_EXTERN
ModelHistory_t * 
SBase_getModelHistory(SBase_t *sb)
{
  return (sb != NULL) ? sb->getModelHistory() : NULL;
}

/**
 * Predicate for testing whether the ModelHistory of a given SBase_t structure is
 * assigned.
 * 
 * @param m the SBase_t structure
 * 
 * @return nonzero if the ModelHistory of this SBase_t structure is
 * set, zero (0) otherwise.
 */LIBSBML_EXTERN
int 
SBase_isSetModelHistory(SBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetModelHistory() ) : 0;
}


/**
 * Set the ModelHistory of the given SBase_t structure.
 * 
 * @param m the SBase_t structure
 * @param history the ModelHistory_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 */
LIBSBML_EXTERN
int 
SBase_setModelHistory(SBase_t *sb, ModelHistory_t *history)
{
  return (sb != NULL) ? sb->setModelHistory(history) : LIBSBML_INVALID_OBJECT;
}

/**
 * Unsets the ModelHistory of the given SBase_t structure.
 * 
 * @param m the SBase_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int 
SBase_unsetModelHistory(SBase_t *sb)
{
  return (sb != NULL) ? sb->unsetModelHistory() : LIBSBML_INVALID_OBJECT;
}


/**
 * Returns the BiologicalQualifier associated with this resource,
 * BQB_UNKNOWN if the resource does not exist.
 *
 * @param sb the object to query
 * @param resource string representing the resource; e.g.,
 * "http://www.geneontology.org/#GO:0005892"
 *
 * @return the BiolQualifierType_t associated with the resource
 */
LIBSBML_EXTERN
BiolQualifierType_t 
SBase_getResourceBiologicalQualifier(SBase_t *sb, const char * resource)
{
  if (sb != NULL)
    return (resource != NULL) ? 
    sb->getResourceBiologicalQualifier(resource) : BQB_UNKNOWN;
  else
    return BQB_UNKNOWN;
}


/**
 * Returns the ModelQualifier associated with this resource,
 * BQM_UNKNOWN if the resource does not exist.
 *
 * @param sb the object to query
 * @param resource string representing the resource; e.g.,
 * "http://www.geneontology.org/#GO:0005892"
 *
 * @return the ModelQualifierType_t associated with the resource
 */
LIBSBML_EXTERN
ModelQualifierType_t 
SBase_getResourceModelQualifier(SBase_t *sb, const char * resource)
{ 
  if (sb != NULL)
    return (resource != NULL) ? 
    sb->getResourceModelQualifier(resource) : BQM_UNKNOWN;
  else
    return BQM_UNKNOWN;
}




/**
 * Returns the value of the "metaid" attribute of the given SBase_t
 * structure.
 *
 * @param sb the SBase_t structure
 * 
 * @return the value of the "metaid" attribute of @p sb
 */
LIBSBML_EXTERN
const char *
SBase_getMetaId (SBase_t *sb)
{
  return (sb != NULL && sb->isSetMetaId()) ? sb->getMetaId().c_str() : NULL;
}


///**
// * Returns the value of the "id" attribute of the given SBase_t
// * structure.
// *
// * @param sb the SBase_t structure
// * 
// * @return the value of the "id" attribute of @p sb
// */
//LIBSBML_EXTERN
//const char *
//SBase_getId (const SBase_t *sb)
//{
//  return sb->isSetId() ? sb->getId().c_str() : NULL;
//}
//
//
///**
// * Returns the value of the "name" attribute of the given SBase_t
// * structure.
// *
// * @param sb the SBase_t structure
// * 
// * @return the value of the "name" attribute of @p sb
// */
//LIBSBML_EXTERN
//const char *
//SBase_getName (const SBase_t *sb)
//{
//  return sb->isSetName() ? sb->getName().c_str() : NULL;
//}


/**
 * Returns the parent SBMLDocument_t structure of the given SBase_t
 * structure.
 *
 * @param sb the SBase_t structure
 * 
 * @return the parent SBMLDocument of this SBML object.
 */
LIBSBML_EXTERN
const SBMLDocument_t *
SBase_getSBMLDocument (SBase_t *sb)
{
  return (sb != NULL) ? sb->getSBMLDocument() : NULL;
}


/**
 * Returns the parent SBase_t structure of the given SBase_t
 * structure.
 *
 * @param sb the SBase_t structure
 * 
 * @return the parent SBase  of this SBML object.
 */
LIBSBML_EXTERN
const SBase_t *
SBase_getParentSBMLObject (SBase_t *sb)
{
  return (sb != NULL) ? sb->getParentSBMLObject() : NULL;
}


/**
 * Returns the ancestor SBase_t structure of the given SBase_t
 * structure that corresponds to the given type.
 *
 * This function allows any object to determine its exact 
 * location/function within a model. For example a 
 * StoichiometryMath object has ancestors of type SpeciesReference,
 * ListOf(Products/Reactants), Reaction, ListOfReactions and Model; 
 * any of which can be accessed via this function.
 *
 * @param sb the SBase_t structure
 * @param type the typecode (int) of the structure to be returned
 * 
 * @return the ancestor SBase_t structure of this SBML object with
 * the corresponding typecode (int), NULL if there is no ancestor of
 * this type.
 */
LIBSBML_EXTERN
const SBase_t *
SBase_getAncestorOfType (SBase_t *sb, int type, const char* pkgName)
{
  return (sb != NULL) ? sb->getAncestorOfType(type, pkgName) : NULL;
}


/**
 * Returns the integer portion of the value of the "sboTerm" attribute of
 * the given SBase_t structure.
 *
 * In SBML Level 2 Versions 2 and 3, the data type of the attribute is a
 * string of the form SBO:NNNNNNN, where NNNNNNN is a seven digit integer
 * number; libSBML simplifies the representation by only storing the
 * NNNNNNN integer portion.  Thus, in libSBML, the "sboTerm" attribute on
 * SBase_t has data type @c int, and SBO identifiers are stored simply as
 * integers.  SBO terms are a type of optional annotation, and each
 * different class of SBML object derived from SBase_t imposes its own
 * requirements about the values permitted for "sboTerm".  Please consult
 * the SBML Level 2 Version 4 specification for more information about
 * the use of SBO and the "sboTerm" attribute.
 *
 * @param sb the SBase_t structure
 * 
 * @return the value of the "sboTerm" attribute as an integer, or @c -1
 * if the value is not set.
 */
LIBSBML_EXTERN
int
SBase_getSBOTerm (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getSBOTerm() : SBML_INT_MAX;
}


/**
 * Returns the string representation of the "sboTerm" attribute of
 * this object.
 *
 * In SBML Level 2 Versions 2, 3 and 4, the data type of the attribute is a
 * string of the form SBO:NNNNNNN, where NNNNNNN is a seven digit integer
 * number; libSBML simplifies the representation by only storing the
 * NNNNNNN integer portion.  Thus, in libSBML, the "sboTerm" attribute on
 * SBase has data type @c int, and SBO identifiers are stored simply as
 * integers.  This function recreates the string representation from the
 * stored value.  SBO terms are a type of optional annotation, and each
 * different class of SBML object derived from SBase imposes its own
 * requirements about the values permitted for "sboTerm".  Please consult
 * the SBML Level 2 Version 4 specification for more information about
 * the use of SBO and the "sboTerm" attribute.
 *
 * @return the value of the "sboTerm" attribute as a string of the form
 * SBO:NNNNNNN, or @c NULL if the value is not set.
 */
LIBSBML_EXTERN
char*
SBase_getSBOTermID (const SBase_t *sb)
{
  return (sb != NULL && sb->isSetSBOTerm())? 
    safe_strdup(sb->getSBOTermID().c_str()) : NULL;
}


/**
 * Returns the SBML Level of the overall SBML document.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return the SBML level of the given object.
 * 
 * @see getVersion()
 */
LIBSBML_EXTERN
unsigned int
SBase_getLevel (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getLevel() : SBML_INT_MAX;
}


/**
 * Returns the Version within the SBML Level of the overall SBML document.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return the SBML version of the given object.
 *
 * @see getLevel()
 */
LIBSBML_EXTERN
unsigned int
SBase_getVersion (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getVersion() : SBML_INT_MAX;
}


/**
 * Returns the notes from given SBML object.
 *
 * @param sb the given SBML object.
 *
 * @return the XMLNode_t structure representing the notes from this object.
 */
LIBSBML_EXTERN
XMLNode_t *
SBase_getNotes (SBase_t *sb)
{
  return (sb != NULL) ? sb->getNotes() : NULL;
}


/**
 * Returns the notes string from given SBML object.
 * The string is owned by the caller and should be freed
 * (with free()) when no longer needed.  
 *
 * @param sb the given SBML object.
 *
 * @return the string (char*) representing the notes from this object.
 */
LIBSBML_EXTERN
char*
SBase_getNotesString (SBase_t *sb)
{
  return (sb != NULL && sb->isSetNotes()) ? 
    safe_strdup(sb->getNotesString().c_str()) : NULL;
}


/**
 * Returns the annotation from given SBML object.
 *
 * @param sb the given SBML object.
 *
 * @return the XMLNode_t structure representing the annotation from this object.
 */
LIBSBML_EXTERN
XMLNode_t *
SBase_getAnnotation (SBase_t *sb)
{
  return (sb != NULL) ? sb->getAnnotation() : NULL;
}


/**
 * Returns the annotation string from given SBML object.
 * The string is owned by the caller and should be freed
 * (with free()) when no longer needed.
 *
 * @param sb the given SBML object.
 *
 * @return the string (char*) representing the annotation from this object.
 */
LIBSBML_EXTERN
char*
SBase_getAnnotationString (SBase_t *sb)
{
  return (sb != NULL && sb->isSetAnnotation()) ? 
    safe_strdup(sb->getAnnotationString().c_str()) : NULL;
}


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "metaid" attribute is set.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return nonzero (for true) if the "metaid" attribute of this SBML object
 * is set, zero (for false) otherwise.
 */
LIBSBML_EXTERN
int
SBase_isSetMetaId (const SBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetMetaId() ) : 0;
}


///**
// * Predicate returning nonzero true or false depending on whether the given
// * structure's "id" attribute is set.
// *
// * @param sb the SBase_t structure to query
// * 
// * @return nonzero (for true) if the "id" attribute of this SBML object
// * is set, zero (for false) otherwise.
// */
//LIBSBML_EXTERN
//int
//SBase_isSetId (const SBase_t *sb)
//{
//  return static_cast<int>( sb->isSetId() );
//}
//
//
///**
// * Predicate returning nonzero true or false depending on whether the given
// * structure's "name" attribute is set.
// *
// * @param sb the SBase_t structure to query
// * 
// * @return nonzero (for true) if the "name" attribute of this SBML object
// * is set, zero (for false) otherwise.
// */
//LIBSBML_EXTERN
//int
//SBase_isSetName (const SBase_t *sb)
//{
//  return static_cast<int>( sb->isSetName() );
//}


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "notes" subelement is set.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return nonzero (for true) if the "notes" subelement of this SBML object
 * is set, zero (for false) otherwise.
 */
LIBSBML_EXTERN
int
SBase_isSetNotes (const SBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetNotes() ) : 0;
}


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "annotation" subelement is set.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return nonzero (for true) if the "annotation" subelement of this SBML object
 * is set, zero (for false) otherwise.
 */
LIBSBML_EXTERN
int
SBase_isSetAnnotation (const SBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetAnnotation() ) : 0;
}


/**
 * Predicate returning nonzero true or false depending on whether the given
 * structure's "sboTerm" attribute is set.
 *
 * @param sb the SBase_t structure to query
 * 
 * @return nonzero (for true) if the "sboTerm" attribute of this SBML object
 * is set, zero (for false) otherwise.
 */
LIBSBML_EXTERN
int
SBase_isSetSBOTerm (const SBase_t *sb)
{
  return (sb != NULL) ? static_cast<int>( sb->isSetSBOTerm() ) : 0;
}


/**
 * Sets the value of the "metaid" attribute of the given object.
 *
 * The string @p metaid is copied.  The value of @p metaid must be an
 * identifier conforming to the syntax defined by the XML 1.0 data type
 * ID.  Among other things, this type requires that a value is unique
 * among all the values of type XML ID in an SBMLDocument.  Although SBML
 * only uses XML ID for the "metaid" attribute, callers should be careful
 * if they use XML ID's in XML portions of a model that are not defined
 * by SBML, such as in the application-specific content of the
 * "annotation" subelement.
 *
 * @param sb the SBase_t structure
 *
 * @param metaid the identifier string to use as the value of the
 * "metaid" attribute
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_ATTRIBUTE_VALUE
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 *
 * @note Using this function with the metaid set to NULL is equivalent to
 * unsetting the "metaid" attribute.
 */
LIBSBML_EXTERN
int
SBase_setMetaId (SBase_t *sb, const char *metaid)
{
  if (sb != NULL)
    return (metaid == NULL) ? sb->unsetMetaId() : sb->setMetaId(metaid);
  else
    return LIBSBML_INVALID_OBJECT;
}


///**
// * Sets the value of the "id" attribute of this SBML object.
// *
// * The string @p sid is copied.  Note that SBML has strict requirements
// * for the syntax of identifiers.  The following is summary of the
// * definition of the SBML identifier type @c SId (here expressed in an
// * extended form of BNF notation):
// * @code
// *   letter ::= 'a'..'z','A'..'Z'
// *   digit  ::= '0'..'9'
// *   idChar ::= letter | digit | '_'
// *   SId    ::= ( letter | '_' ) idChar*
// * @endcode
// * The equality of SBML identifiers is determined by an exact character
// * sequence match; i.e., comparisons must be performed in a
// * case-sensitive manner.  In addition, there are a few conditions for
// * the uniqueness of identifiers in an SBML model.  Please consult the
// * SBML specifications for the exact formulations.
// *
// * @param sb the SBase_t structure
// *
// * @param sid the string to use as the identifier of this object
// *
// * @return integer value indicating success/failure of the
// * function.  @if clike The value is drawn from the
// * enumeration #OperationReturnValues_t. @endif The possible values
// * returned by this function are:
// *
// * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
// * @li @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE @endlink
// *
// * @note Using this function with an id of NULL is equivalent to
// * unsetting the "id" attribute.
// */
//LIBSBML_EXTERN
//int
//SBase_setId (SBase_t *sb, const char *sid)
//{
//  return (sid == NULL) ? sb->unsetId() : sb->setId(sid);
//}
//
//
///**
// * Sets the value of the "name" attribute of this SBML object.
// *
// * The string in @p name is copied.
// *
// * @param sb the SBase_t structure
// *
// * @param name the new name for the object
// *
// * @return integer value indicating success/failure of the
// * function.  @if clike The value is drawn from the
// * enumeration #OperationReturnValues_t. @endif The possible values
// * returned by this function are:
// *
// * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
// * @li @link OperationReturnValues_t#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE @endlink
// *
// * @note Using this function with the name set to NULL is equivalent to
// * unsetting the "name" attribute.
// */
//LIBSBML_EXTERN
//int
//SBase_setName (SBase_t *sb, const char *name)
//{
//  return (name == NULL) ? sb->unsetName() : sb->setName(name);
//}


/**
 * Sets the value of the "sboTerm" attribute.
 *
 * In SBML Level 2 Versions 2, 3 and 4, the data type of the SBML "sboTerm"
 * attribute is a string of the form SBO:NNNNNNN, where NNNNNNN is a seven
 * digit integer number; libSBML simplifies the representation by only
 * storing the NNNNNNN integer portion.  Thus, in libSBML, the "sboTerm"
 * attribute on SBase_t has data type @c int, and SBO identifiers are
 * stored simply as integers.  SBO terms are a type of optional annotation,
 * and each different class of SBML object derived from SBase_t imposes its
 * own requirements about the values permitted for "sboTerm".  Please
 * consult the SBML Level 2 Version 4 specification for more information
 * about the use of SBO and the "sboTerm" attribute.
 *
 * @param sb the SBase_t structure
 *
 * @param value the NNNNNNN integer portion of the SBO identifier
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_ATTRIBUTE_VALUE
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 */
LIBSBML_EXTERN
int
SBase_setSBOTerm (SBase_t *sb, int value)
{
  if (sb != NULL)
    return sb->setSBOTerm(value);
  else
    return LIBSBML_INVALID_OBJECT;
}


/*
 * Sets the value of the "sboTerm" attribute by string.
 *
 * In SBML Level 2 Versions 2, 3 and 4, the data type of the SBML "sboTerm"
 * attribute is a string of the form SBO:NNNNNNN, where NNNNNNN is a
 * seven digit integer number; libSBML simplifies the representation by
 * only storing the NNNNNNN integer portion converted from the given string.
 * Thus, in libSBML, the "sboTerm" attribute on SBase has data type @c int,
 * and SBO identifiers are stored simply as integers.  SBO terms are a type
 * of optional annotation, and each different class of SBML object derived
 * from SBase imposes its own requirements about the values permitted for
 * "sboTerm".  Please consult the SBML Level 2 Version 4 specification for
 * more information about the use of SBO and the "sboTerm" attribute.
 *
 * @param sb the SBase_t structure
 *
 * @param value the SBO identifier string of the form SBO:NNNNNNN 
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_ATTRIBUTE_VALUE
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 */
LIBSBML_EXTERN
int
SBase_setSBOTermID (SBase_t *sb, const char* sboid)
{
  if (sb != NULL)
    return sb->setSBOTerm(sboid);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the namespaces relevant of this SBML object.
 *
 * @param sb the SBase_t structure
 *
 * @param xmlns the namespaces to set
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 */
LIBSBML_EXTERN
int
SBase_setNamespaces (SBase_t *sb, XMLNamespaces_t *xmlns)
{
  if (sb != NULL)
    return sb->setNamespaces(xmlns);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the notes for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param notes the XMLNode_t structure respresenting the notes.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 */
LIBSBML_EXTERN
int
SBase_setNotes (SBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->setNotes(notes);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the notes for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param notes the string (const char*) respresenting the notes.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_setNotesString (SBase_t *sb, char *notes)
{
  if (sb != NULL)
  {
    if(notes == NULL)
    {
      return sb->unsetNotes();
    }
    else
    {
      return sb->setNotes(notes);
    }
  }
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Appends the notes for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param notes the XMLNode_t structure respresenting the notes.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_appendNotes (SBase_t *sb, XMLNode_t *notes)
{
  if (sb != NULL)
    return sb->appendNotes(notes);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Appends the notes for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param notes the string (const char*) respresenting the notes.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_INVALID_OBJECT
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_appendNotesString (SBase_t *sb, char *notes)
{
  if (sb != NULL)
  {
    if (notes != NULL)
      return sb->appendNotes(notes);
    else
      return LIBSBML_INVALID_OBJECT;
  }
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the annotation for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param annotation the XMLNode_t structure respresenting the annotation.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 */
LIBSBML_EXTERN
int
SBase_setAnnotation (SBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->setAnnotation(annotation);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Sets the annotation for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param annotation the string (const char*) respresenting the annotation.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_setAnnotationString (SBase_t *sb, char *annotation)
{
  if (sb != NULL)
  {
    if(annotation == NULL)
    {
      return sb->unsetAnnotation();
    }
    else
    {
      return sb->setAnnotation(annotation);
    }
  }
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Appends the annotation for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param annotation the XMLNode_t structure respresenting the annotation.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_appendAnnotation (SBase_t *sb, XMLNode_t *annotation)
{
  if (sb != NULL)
    return sb->appendAnnotation(annotation);
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Appends the annotation for the given SBML object.
 *
 * @param sb the given SBML object.
 * @param annotation the string (const char*) respresenting the annotation.
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_appendAnnotationString (SBase_t *sb, char *annotation)
{
  if (sb != NULL)
  {
    if (annotation != NULL)
      return sb->appendAnnotation(annotation);
    else
      return LIBSBML_INVALID_OBJECT;
  }
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Unsets the "metaid" attribute of the given object.
 *
 * @param sb the SBase_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_OPERATION_FAILED
 */
LIBSBML_EXTERN
int
SBase_unsetMetaId (SBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetMetaId();
  else
    return LIBSBML_INVALID_OBJECT;
}


/*
* Unsets the "id" attribute of the given object.
*
* @param sb the SBase_t structure
*
* @return integer value indicating success/failure of the
* function.  @if clike The value is drawn from the
* enumeration #OperationReturnValues_t. @endif The possible values
* returned by this function are:
*
* @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
* @li @link OperationReturnValues_t#LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED @endlink
*/
LIBSBML_EXTERN
int
SBase_unsetId (SBase_t *sb)
{
 return sb->unsetId();
}


///**
// * Unsets the "name" attribute of the given object.
// *
// * @param sb the SBase_t structure
// *
// * @return integer value indicating success/failure of the
// * function.  @if clike The value is drawn from the
// * enumeration #OperationReturnValues_t. @endif The possible values
// * returned by this function are:
// *
// * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
// * @li @link OperationReturnValues_t#LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED @endlink
// */
//LIBSBML_EXTERN
//int
//SBase_unsetName (SBase_t *sb)
//{
//  return sb->unsetName();
//}


/**
 * Unsets the "notes" subelement of the given object.
 *
 * @param sb the SBase_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 */
LIBSBML_EXTERN
int
SBase_unsetNotes (SBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetNotes();
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Unsets the "annotation" subelement of the given object.
 *
 * @param sb the SBase_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 */
LIBSBML_EXTERN
int
SBase_unsetAnnotation (SBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetAnnotation();
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Unsets the "sboTerm" attribute of the given object.
 *
 * @param sb the SBase_t structure
 *
 * @return integer value indicating success/failure of the
 * function.  @if clike The value is drawn from the
 * enumeration #OperationReturnValues_t. @endif The possible values
 * returned by this function are:
 * @li LIBSBML_OPERATION_SUCCESS
 * @li LIBSBML_UNEXPECTED_ATTRIBUTE
 */
LIBSBML_EXTERN
int
SBase_unsetSBOTerm (SBase_t *sb)
{
  if (sb != NULL)
    return sb->unsetSBOTerm();
  else
    return LIBSBML_INVALID_OBJECT;
}


/**
 * Returns the Model_t structure in which the given instance is located.
 *
 * @param sb the SBase_t structure
 * 
 * @return the parent Model_t strucdture of the given object.
 */
LIBSBML_EXTERN
const Model_t *
SBase_getModel (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getModel() : NULL;
}

/**
 * Returns the libSBML type code for this object.
 *
 * This method MAY return the typecode of this SBML object or it MAY
 * return SBML_UNKNOWN.  That is, subclasses of SBase are not required to
 * implement this method to return a typecode.  This method is meant
 * primarily for the LibSBML C interface where class and subclass
 * information is not readily available.
 *
 * @note In libSBML 5, the type of return value has been changed from
 *       typecode (int) to int. The return value is one of enum values defined
 *       for each package. For example, return values will be one of
 *       typecode (int) if this object is defined in SBML core package,
 *       return values will be one of SBMLLayoutTypeCode_t if this object is
 *       defined in Layout extension (i.e. similar enum types are defined in
 *       each pacakge extension for each SBase subclass)
 *       The value of each typecode can be duplicated between those of
 *       different packages. Thus, to distinguish the typecodes of different
 *       packages, not only the return value of getTypeCode() but also that of
 *       getPackageName() must be checked.
 *
 * @param sb the SBase_t structure
 *
 * @return the typecode (int value) of this SBML object or SBML_UNKNOWN
 * (default).
 *
 * @see getElementName()
 * @see getPackageName()
 */
LIBSBML_EXTERN
int
SBase_getTypeCode (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getTypeCode() : SBML_UNKNOWN;
}


/**
 * Returns the XML element name of the given structure.
 *
 * This is overridden by subclasses to return a string appropriate to the
 * SBML component.  For example, Model defines it as returning "model",
 * CompartmentType defines it as returning "compartmentType", etc.
 *
 * @param sb the SBase_t structure
 */
LIBSBML_EXTERN
const char *
SBase_getElementName (const SBase_t *sb)
{
  return (sb != NULL && !(sb->getElementName().empty())) ? 
    sb->getElementName().c_str() : NULL;
}


/**
 * Returns the line number on which the given object first appears in the
 * XML representation of the SBML document.
 *
 * @param sb the SBase_t structure
 * 
 * @return the line number of the given structure
 *
 * @see getColumn().
 */
LIBSBML_EXTERN
unsigned int
SBase_getLine (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getLine() : SBML_INT_MAX;
}


/**
 * Returns the column number on which the given object first appears in the
 * XML representation of the SBML document.
 *
 * @param sb the SBase_t structure
 * 
 * @return the column number of this SBML object.
 * 
 * @see getLine().
 */
LIBSBML_EXTERN
unsigned int
SBase_getColumn (const SBase_t *sb)
{
  return (sb != NULL) ? sb->getColumn() : SBML_INT_MAX;
}


/**
  * Predicate returning nonzero true or false depending on whether the
  * object's level/version and namespace values correspond to a valid
  * SBML specification.
  *
  * The valid combinations of SBML Level, Version and Namespace as of this release
  * of libSBML are the following: 
  * <ul>
  * <li> Level&nbsp;1 Version&nbsp;2 "http://www.sbml.org/sbml/level1"
  * <li> Level&nbsp;2 Version&nbsp;1 "http://www.sbml.org/sbml/level2"
  * <li> Level&nbsp;2 Version&nbsp;2 "http://www.sbml.org/sbml/level2/version2"
  * <li> Level&nbsp;2 Version&nbsp;3 "http://www.sbml.org/sbml/level2/version3"
  * <li> Level&nbsp;2 Version&nbsp;4 "http://www.sbml.org/sbml/level2/version4"
  * </ul>
  *
  * @param sb the SBase_t structure
  *
  * @return nonzero (true) if the level, version and namespace values of this 
  * SBML object correspond to a valid set of values, zero (false) otherwise.
  */
LIBSBML_EXTERN
int
SBase_hasValidLevelVersionNamespaceCombination(SBase_t *sb)
{
  return (sb != NULL) ? 
    static_cast <int> (sb->hasValidLevelVersionNamespaceCombination()) : 0;
}


LIBSBML_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_create()
{
  return new ExpectedAttributes();
}

LIBSBML_EXTERN 
ExpectedAttributes_t *
ExpectedAttributes_clone(ExpectedAttributes_t *attr)
{
  if (attr == NULL) return NULL;
  return new ExpectedAttributes(*attr);
}

LIBSBML_EXTERN 
int
ExpectedAttributes_add(ExpectedAttributes_t *attr, const char* attribute)
{
  if (attr == NULL || attribute == NULL) return LIBSBML_INVALID_OBJECT;
  attr->add(string(attribute));
  return LIBSBML_OPERATION_SUCCESS;
}

LIBSBML_EXTERN 
char*
ExpectedAttributes_get(ExpectedAttributes_t *attr, unsigned int index)
{
  if (attr == NULL) return NULL;
  return safe_strdup(attr->get(index).c_str());
}

LIBSBML_EXTERN 
int
ExpectedAttributes_hasAttribute(ExpectedAttributes_t *attr, const char* attribute)
{
  if (attr == NULL) return (int)false;
  return attr->hasAttribute(string(attribute));
}


/** @endcond */

LIBSBML_CPP_NAMESPACE_END
