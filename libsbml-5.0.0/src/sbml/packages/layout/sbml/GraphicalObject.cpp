/**
 * Filename    : GraphicalObject.cpp
 * Description : SBML Layout GraphicalObject source
 * Organization: European Media Laboratories Research gGmbH
 * Created     : 2004-07-15
 *
 * Copyright 2004 European Media Laboratories Research gGmbH
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * European Media Laboratories Research gGmbH have no obligations to
 * provide maintenance, support, updates, enhancements or modifications.
 * In no event shall the European Media Laboratories Research gGmbH be
 * liable to any party for direct, indirect, special, incidental or
 * consequential damages, including lost profits, arising out of the use of
 * this software and its documentation, even if the European Media
 * Laboratories Research gGmbH have been advised of the possibility of such
 * damage.  See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ralph Gauges
 *     Bioinformatics Group
 *     European Media Laboratories Research gGmbH
 *     Schloss-Wolfsbrunnenweg 31c
 *     69118 Heidelberg
 *     Germany
 *
 *     http://www.eml-research.de/english/Research/BCB/
 *     mailto:ralph.gauges@eml-r.villa-bosch.de
 *
 * Contributor(s):
 *
 *     Akiya Jouraku <jouraku@bio.keio.ac.jp>
 *     Modified this file for package extension in libSBML5
 *
 */


#include <sbml/packages/layout/sbml/GraphicalObject.h>
#include <sbml/packages/layout/util/LayoutUtilities.h>
#include <sbml/SBMLErrorLog.h>
#include <sbml/SBMLVisitor.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/xml/XMLAttributes.h>
#include <sbml/xml/XMLInputStream.h>
#include <sbml/xml/XMLOutputStream.h>

#include <sbml/packages/layout/extension/LayoutExtension.h>

LIBSBML_CPP_NAMESPACE_BEGIN

/**
 * Creates a new GraphicalObject.
 */
GraphicalObject::GraphicalObject(unsigned int level, unsigned int version, unsigned int pkgVersion) 
 : SBase (level,version)
  ,mId("")
  ,mBoundingBox(level,version,pkgVersion)
{
  setSBMLNamespacesAndOwn(new LayoutPkgNamespaces(level,version,pkgVersion));  
}


/**
 * Creates a new GraphicalObject with the given id.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns)
 : SBase(layoutns)
  ,mId ("")
  ,mBoundingBox(layoutns)
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/**
 * Creates a new GraphicalObject with the given id.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns, const std::string& id)
 : SBase(layoutns)
  ,mId (id)
  ,mBoundingBox(layoutns)
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/**
 * Creates a new GraphicalObject with the given id and 2D coordinates for
 * the bounding box.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns, const std::string& id,
                                  double x, double y, double w, double h)
  :  SBase(layoutns)
  , mId (id)
  , mBoundingBox( BoundingBox(layoutns, "", x, y, 0.0, w, h, 0.0))
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/**
 * Creates a new GraphicalObject with the given id and 3D coordinates for
 * the bounding box.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns, const std::string& id,
                                  double x, double y, double z,
                                  double w, double h, double d)
  : SBase(layoutns)
  ,mId (id)
  ,mBoundingBox( BoundingBox(layoutns, "", x, y, z, w, h, d))
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/**
 * Creates a new GraphicalObject with the given id and 3D coordinates for
 * the bounding box.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns, const std::string& id,
                                  const Point*       p,
                                  const Dimensions*  d)
  : SBase(layoutns)
  , mId (id)
  , mBoundingBox( BoundingBox(layoutns, "", p, d) )
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}


/**
 * Creates a new GraphicalObject with the given id and 3D coordinates for
 * the bounding box.
 */
GraphicalObject::GraphicalObject (LayoutPkgNamespaces* layoutns, const std::string& id, const BoundingBox* bb)
  : SBase(layoutns)
  , mId (id)
  , mBoundingBox(layoutns)
{
  //
  // set the element namespace of this object
  //
  setElementNamespace(layoutns->getURI());

  if(bb)
  {
      this->mBoundingBox=*bb;
  }

  connectToChild();

  //
  // load package extensions bound with this object (if any) 
  //
  loadPlugins(layoutns);
}

/**
 * Creates a new GraphicalObject from the given XMLNode
 */
GraphicalObject::GraphicalObject(const XMLNode& node, unsigned int l2version)
 : SBase(2,l2version)  
{
    const XMLAttributes& attributes=node.getAttributes();
    const XMLNode* child;
    //ExpectedAttributes ea(getElementName());
    ExpectedAttributes ea;
    addExpectedAttributes(ea);
    this->readAttributes(attributes,ea);
    unsigned int n=0,nMax = node.getNumChildren();
    while(n<nMax)
    {
        child=&node.getChild(n);
        const std::string& childName=child->getName();
        if(childName=="boundingBox")
        {
            this->mBoundingBox=BoundingBox(*child);
        }
        else if(childName=="annotation")
        {
            this->mAnnotation=new XMLNode(*child);
        }
        else if(childName=="notes")
        {
            this->mNotes=new XMLNode(*child);
        }
        else
        {
            //throw;
        }
        ++n;
    }    

  //
  // (TODO) check the xmlns of layout extension
  //
  setSBMLNamespacesAndOwn(new LayoutPkgNamespaces(2,l2version));  

  connectToChild();
}


/**
 * Copy constructor.
 */
GraphicalObject::GraphicalObject(const GraphicalObject& source):SBase(source)
{
    this->mId = source.mId;
    this->mBoundingBox=*source.getBoundingBox();

    connectToChild();
}

/**
 * Assignment operator.
 */
GraphicalObject& GraphicalObject::operator=(const GraphicalObject& source)
{
  if(&source!=this)
  {
    this->SBase::operator=(source);
    this->mId = source.mId;
    this->mBoundingBox=*source.getBoundingBox();

    connectToChild();
  }

  return *this;
}

/**
 * Destructor.
 */ 
GraphicalObject::~GraphicalObject ()
{
}


/**
  * Returns the value of the "id" attribute of this GraphicalObject.
  */
const std::string& GraphicalObject::getId () const
{
  return mId;
}


/**
  * Predicate returning @c true or @c false depending on whether this
  * GraphicalObject's "id" attribute has been set.
  */
bool GraphicalObject::isSetId () const
{
  return (mId.empty() == false);
}

/**
  * Sets the value of the "id" attribute of this GraphicalObject.
  */
int GraphicalObject::setId (const std::string& id)
{
  if (&id != NULL && id.empty())
       return unsetId();
  return SyntaxChecker::checkAndSetSId(id,mId);
}


/**
  * Unsets the value of the "id" attribute of this GraphicalObject.
  */
int GraphicalObject::unsetId ()
{
  mId.erase();
  if (mId.empty())
  {
    return LIBSBML_OPERATION_SUCCESS;
  }
  else
  {
    return LIBSBML_OPERATION_FAILED;
  }
}

/**
 * Sets the boundingbox for the GraphicalObject.
 */ 
void
GraphicalObject::setBoundingBox (const BoundingBox* bb)
{
  if(bb==NULL) return;  
  this->mBoundingBox = *bb;
  this->mBoundingBox.connectToParent(this);
}


/**
 * Returns the bounding box for the GraphicalObject.
 */ 
const BoundingBox*
GraphicalObject::getBoundingBox () const
{
  return &this->mBoundingBox;
} 


/**
 * Returns the bounding box for the GraphicalObject.
 */ 
BoundingBox*
GraphicalObject::getBoundingBox ()
{
  return &this->mBoundingBox;
}


/**
 * Does nothing. No defaults are defined for GraphicalObject.
 */ 
void
GraphicalObject::initDefaults ()
{
}

/**
 * Subclasses should override this method to return XML element name of
 * this SBML object.
 */
const std::string& GraphicalObject::getElementName () const 
{
  static const std::string name = "graphicalObject";
  return name;
}

/**
 * @return a (deep) copy of this Model.
 */
SBase* 
GraphicalObject::clone () const
{
    return new GraphicalObject(*this);
}


/**
 * @return the SBML object corresponding to next XMLToken in the
 * XMLInputStream or NULL if the token was not recognized.
 */
SBase*
GraphicalObject::createObject (XMLInputStream& stream)
{

  const std::string& name   = stream.peek().getName();
  SBase*        object = 0;

  if (name == "boundingBox")
  {
    object = &mBoundingBox;
  }

  return object;
}

/**
 * Subclasses should override this method to get the list of
 * expected attributes.
 * This function is invoked from corresponding readAttributes()
 * function.
 */
void
GraphicalObject::addExpectedAttributes(ExpectedAttributes& attributes)
{
  SBase::addExpectedAttributes(attributes);

  attributes.add("id");
}


/**
 * Subclasses should override this method to read values from the given
 * XMLAttributes set into their specific fields.  Be sure to call your
 * parents implementation of this method as well.
 */

void GraphicalObject::readAttributes (const XMLAttributes& attributes,
                                      const ExpectedAttributes& expectedAttributes)
{
  SBase::readAttributes(attributes,expectedAttributes);

  const unsigned int sbmlLevel   = getLevel  ();
  const unsigned int sbmlVersion = getVersion();

  bool assigned = attributes.readInto("id", mId, getErrorLog(), true);
  if (assigned && mId.size() == 0)
  {
    logEmptyString(mId, sbmlLevel, sbmlVersion, "<" + getElementName() + ">");
  }
  if (!SyntaxChecker::isValidInternalSId(mId)) logError(InvalidIdSyntax);
}

/**
 * Subclasses should override this method to write out their contained
 * SBML objects as XML elements.  Be sure to call your parents
 * implementation of this method as well.
 */
void
GraphicalObject::writeElements (XMLOutputStream& stream) const
{
  SBase::writeElements(stream);

  mBoundingBox.write(stream);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionElements(stream);
}



/**
 * Subclasses should override this method to write their XML attributes
 * to the XMLOutputStream.  Be sure to call your parents implementation
 * of this method as well.  For example:
 *
 *   SBase::writeAttributes(stream);
 *   stream.writeAttribute( "id"  , mId   );
 *   stream.writeAttribute( "name", mName );
 *   ...
 */
void GraphicalObject::writeAttributes (XMLOutputStream& stream) const
{
  SBase::writeAttributes(stream);
  stream.writeAttribute("id", getPrefix(), mId);

  //
  // (EXTENSION)
  //
  SBase::writeExtensionAttributes(stream);
}


/**
 * Returns the package type code  for this object.
 */
int
GraphicalObject::getTypeCode () const
{
  return SBML_LAYOUT_GRAPHICALOBJECT;
}


/**
 * Accepts the given SBMLVisitor.
 */
bool
GraphicalObject::accept (SBMLVisitor& v) const
{
  /*  
  bool result=v.visit(*this);
  this->mBoundingBox.accept(v);
  v.leave(*this);
  */
  return false;
}

/**
 * Creates an XMLNode object from this.
 */
XMLNode GraphicalObject::toXML() const
{
  XMLNamespaces xmlns = XMLNamespaces();
  XMLTriple triple = XMLTriple("graphicalObject", "", "");
  XMLAttributes att = XMLAttributes();
  // add the SBase Ids
  addSBaseAttributes(*this,att);
  addGraphicalObjectAttributes(*this,att);
  XMLToken token = XMLToken(triple, att, xmlns); 
  XMLNode node(token);
  // add the notes and annotations
  if(this->mNotes) node.addChild(*this->mNotes);
  if(this->mAnnotation) node.addChild(*this->mAnnotation);
  // write the bounding box
  node.addChild(this->mBoundingBox.toXML());
  return node;
}


/*
 * Sets the parent SBMLDocument of this SBML object.
 */
void
GraphicalObject::setSBMLDocument (SBMLDocument* d)
{
  SBase::setSBMLDocument(d);

  mBoundingBox.setSBMLDocument(d);
}


/*
 * Sets this SBML object to child SBML objects (if any).
 * (Creates a child-parent relationship by the parent)
 */
void
GraphicalObject::connectToChild()
{
  mBoundingBox.connectToParent(this);
}


/**
 * Enables/Disables the given package with this element and child
 * elements (if any).
 * (This is an internal implementation for enablePakcage function)
 */
void
GraphicalObject::enablePackageInternal(const std::string& pkgURI,
                                       const std::string& pkgPrefix, bool flag)
{
  SBase::enablePackageInternal(pkgURI,pkgPrefix,flag);

  mBoundingBox.enablePackageInternal(pkgURI,pkgPrefix,flag);
}




/**
 * Creates a new GraphicalObject.
 */
LIBSBML_EXTERN
GraphicalObject_t *
GraphicalObject_create (void)
{
  return new(std::nothrow) GraphicalObject;
}


/**
 * Creates a GraphicalObject from a template.
 */
LIBSBML_EXTERN
GraphicalObject_t *
GraphicalObject_createFrom (const GraphicalObject_t *temp)
{
  return new(std::nothrow) GraphicalObject(*temp);
}

/**
 * Frees all memory taken up by the GraphicalObject.
 */ 
LIBSBML_EXTERN
void
GraphicalObject_free (GraphicalObject_t *go)
{
  delete go;
}



/**
 * Sets the boundingbox for the GraphicalObject.
 */ 
LIBSBML_EXTERN
void
GraphicalObject_setBoundingBox (GraphicalObject_t *go, const BoundingBox_t *bb)
{
  go->setBoundingBox(bb);
}


/**
 * Returns the bounding box for the GraphicalObject.
 */ 
LIBSBML_EXTERN
BoundingBox_t *
GraphicalObject_getBoundingBox (GraphicalObject_t *go)
{
  return go->getBoundingBox();
}


/**
 * Does nothing. No defaults are defined for GraphicalObject.
 */ 
LIBSBML_EXTERN
void
GraphicalObject_initDefaults (GraphicalObject_t *go)
{
  go->initDefaults();
}



/**
 * @return a (deep) copy of this Model.
 */
LIBSBML_EXTERN
GraphicalObject_t *
GraphicalObject_clone (const GraphicalObject_t *m)
{
  return static_cast<GraphicalObject*>( m->clone() );
}


/**
 * Returns non-zero if the id is set
 */
LIBSBML_EXTERN
int
GraphicalObject_isSetId (const GraphicalObject_t *go)
{
  return static_cast <int> (go->isSetId());
}

/**
 * Returns the id
 */
LIBSBML_EXTERN
const char *
GraphicalObject_getId (const GraphicalObject_t *go)
{
  return go->isSetId() ? go->getId().c_str() : NULL;
}

/**
 * Sets the id
 */
LIBSBML_EXTERN
int
GraphicalObject_setId (GraphicalObject_t *go, const char *sid)
{
  return (sid == NULL) ? go->setId("") : go->setId(sid);
}

/**
 * Unsets the id
 */
LIBSBML_EXTERN
void
GraphicalObject_unsetId (GraphicalObject_t *go)
{
  go->unsetId();
}

LIBSBML_CPP_NAMESPACE_END

