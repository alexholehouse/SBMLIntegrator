/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace libsbmlcs {

 using System;
 using System.Runtime.InteropServices;

/** 
 * The core component of SBML's package extension.
 *
 * SBMLExtension class (abstract class) is a core component of package extension
 * which needs to be extended by package developers. 
 * The class provides functions for getting common attributes of package extension 
 * (e.g., package name, package version, and etc.), functions for adding (registering) 
 * each instantiated SBasePluginCreator object, and a static function (defined in each 
 * SBMLExtension extended class) for initializing/registering the package extension 
 * when the library of the package is loaded.
 *
 * @section howto How to implement an SBMLExtension extended class for each package extension
 *
 * Package developers must implement an SBMLExtension extended class for
 * their packages (e.g. GroupsExtension class is implemented for groups extension).
 * The extended class is implemented based on the following steps:
 *
 * (NOTE: 
 *   'src/pacakges/groups/extension/GroupsExtension.{h,cpp}' and
 *   'src/pacakges/layout/extension/LayoutExtension.{h,cpp}' are
 *   example files in which SBMLExtension derived classes are implemented)
 *
 * <ol>
 *
 * <li> Define the following static functions in the extended class:
 *      (examples of groups extension are shown respectively)
 *   <ol>
 *     <li> <p>A string of package name (label) (The function name must be 'getPackageName'.)</p>
 *         
<code>
  string GroupsExtension::getPackageName ()
  {
	static string pkgName = 'groups';
	return pkgName;
  }
</code>
 *     </li>
 *
 *     <li> <p>
 *        Methods returning an integer of Default SBML level, version, and package version
 *        (The method names must be 'getDefaultLevel()', 'getDefaultVersion()', and 
 *        'getDefaultPackageVersion()' respectively.)
 *        </p>
<code>
  long GroupsExtension::getDefaultLevel()
  {
	return 3;
  }  
  long GroupsExtension::getDefaultVersion()
  {
	return 1; 
  }
  long GroupsExtension::getDefaultPackageVersion()
  {
	return 1;
  }  
</code>
 *     </li>
 *     <li> <p> Methods returning Strings that represent the URI of packages </p>
<code>
  string GroupsExtension::getXmlnsL3V1V1 ()
  {
	static string xmlns = 'http://www.sbml.org/sbml/level3/version1/groups/version1';
	return xmlns;
  }
</code> 
 *     </li>
 *     <li> <p>Strings that represent the other URI needed in this package (if any) </p>
 *     </li>
 *   </ol> 
 * </li>
 *
 * <li> Override the following pure virtual functions
      <ul>
       <li> <c>virtual string getName () =0</c>. This function returns the name of the package (e.g., 'layout', 'groups'). </li>
       <li> <c>virtual long getLevel (string uri) =0</c>. This function returns the SBML level with the given URI of this package. </li>
       <li> <c>virtual long getVersion (string uri) =0</c>. This function returns the SBML version with the given URI of this package. </li>
       <li> <c>virtual long getPackageVersion (string uri) =0</c>. This function returns the package version with the given URI of this package.</li>
       <li> <c>virtual long getURI (long sbmlLevel, long sbmlVersion, long pkgVersion) =0</c>. 
             This function returns the URI (namespace) of the package corresponding to the combination of the given sbml level, sbml version, and pacakege version</li>
       <li> <c>virtual SBMLExtension clone () = 0</c>. This function creates and returns a deep copy of this derived object.</li>
      </ul>
      <p>For example, the above functions are overridden in the groups
	package ('src/packages/groups/extension/GroupsExtension.cpp') as follows:</p>
<code>
string
GroupsExtension::getName() const
{
  return getPackageName();
}

long 
GroupsExtension::getLevel(string uri) const
{
  if (uri == getXmlnsL3V1V1())
  {
    return 3;
  }
  
  return 0;
}

long 
GroupsExtension::getVersion(string uri) const
{
  if (uri == getXmlnsL3V1V1())
  {
    return 1;
  }

  return 0;
}

long
GroupsExtension::getPackageVersion(string uri) const
{
  if (uri == getXmlnsL3V1V1())
  {
    return 1;
  }

  return 0;
}

string 
GroupsExtension::getURI(long sbmlLevel, long sbmlVersion, long pkgVersion) const
{
  if (sbmlLevel == 3)
  {
    if (sbmlVersion == 1)
    {
      if (pkgVersion == 1)
      {
        return getXmlnsL3V1V1();
      }
    }
  }

  static string empty = '';

  return empty;
}

GroupsExtension* 
GroupsExtension::clone () const
{
  return new GroupsExtension(*this);  
}
</code>
 *
 * Constructor, copy Constructor, and destructor also must be overridden
 * if additional data members are defined in the derived class.
 *
 * </li>
 *
 * <li> <p>
 *  Define typedef and template instantiation code for the package specific SBMLExtensionNamespaces template class
 *  </p>
 *
 *   <ol>
 *     <li> typedef for the package specific SBMLExtensionNamespaces template class
 *       <p> For example, the typedef for GroupsExtension (defined in the groups package) is implemented in GroupsExtension.h as follows:</p>
<code>
  // GroupsPkgNamespaces is derived from the SBMLNamespaces class and used when creating an object of 
  // SBase derived classes defined in groups package.
  typedef SBMLExtensionNamespaces<GroupsExtension> GroupsPkgNamespaces;
</code>
 *     </li>
 *
 *     <li> template instantiation code for the above typedef definition in the implementation file (i.e., *.cpp file).
 *       <p> For example, the template instantiation code for GroupsExtension is implemented in GroupsExtension.cpp 
 *           as follows:
 *       </p>
 *
<code>
  // Instantiate SBMLExtensionNamespaces<GroupsExtension> (GroupsPkgNamespaces) for DLL.
  template class LIBSBML_EXTERN SBMLExtensionNamespaces<GroupsExtension>;
</code>
 *
 *     </li>
 *  </ol>
 *
 *  <p> The SBMLExtensionNamespaces template class is a derived class of
 *      SBMLNamespaces and can be used as an argument of constructors 
 *      of SBase derived classes defined in the package extensions.
 *      For example, a GroupsPkgNamespaces object can be used when creating a group 
 *      object as follows:
 *  </P>
<code>
   GroupPkgNamespaces gpns(3,1,1);  // The arguments are SBML Level, SBML Version, and Groups Package Version.

   Group g = new Group(&gpns);      // Creates a group object of L3V1 Groups V1.
</code>
 *
 *   <p>
 *     Also, the GroupsPkgNamespaces object can be used when creating an
 *     SBMLDocument object with the groups package as follows:
 *   </p>
 *
<code>
   GroupsPkgNamespaces gpns(3,1,1);
   SBMLDocument doc;

   doc  = new SBMLDocument(&gnps); // Creates an SBMLDocument of L3V1 with Groups V1.
</code>
 *
 * </li>
 *
 * <li> Override the following pure virtual function which returns the SBMLNamespaces derived object 
<code>
       virtual SBMLNamespaces getSBMLExtensionNamespaces (string uri) =0
</code>
 *    <p> For example, the function is overridden in GroupsExtension
 class as follows:</p>
<code>
SBMLNamespaces
GroupsExtension::getSBMLExtensionNamespaces(string uri) const
{
  GroupsPkgNamespaces* pkgns = null;
  if ( uri == getXmlnsL3V1V1())
  {
    pkgns = new GroupsPkgNamespaces(3,1,1);    
  }  
  return pkgns;
}
</code>
   </li>
 *  
 *
 *  <li> Define an enum type for representing the typecode of elements (SBase extended classes) defined in the package extension
 *
 *   <p>  For example, SBMLGroupsTypeCode_t for groups package is
 *  defined in GroupsExtension.h as follows: </p>
<code>
      typedef enum
      {
         SBML_GROUPS_GROUP  = 200
       , SBML_GROUPS_MEMBER = 201
      } SBMLGroupsTypeCode_t;
</code>    
 *
 *  <p> <em>SBML_GROUPS_GROUP</em> corresponds to the Group class (&lt;group&gt;)
 * and <em>SBML_GROUPS_MEMBER</em> corresponds to the Member (&lt;member&gt;) class, respectively.
 *
 *
 *  <p> Similarly, SBMLLayoutTypeCode_t 
 *   for layout package is defined in LayoutExtension.h as follows: </p>
 *
<code>  
      typedef enum
      {
         SBML_LAYOUT_BOUNDINGBOX           = 100
       , SBML_LAYOUT_COMPARTMENTGLYPH      = 101
       , SBML_LAYOUT_CUBICBEZIER           = 102
       , SBML_LAYOUT_CURVE                 = 103
       , SBML_LAYOUT_DIMENSIONS            = 104
       , SBML_LAYOUT_GRAPHICALOBJECT       = 105
       , SBML_LAYOUT_LAYOUT                = 106   
       , SBML_LAYOUT_LINESEGMENT           = 107   
       , SBML_LAYOUT_POINT                 = 108    
       , SBML_LAYOUT_REACTIONGLYPH         = 109    
       , SBML_LAYOUT_SPECIESGLYPH          = 110    
       , SBML_LAYOUT_SPECIESREFERENCEGLYPH = 111
       , SBML_LAYOUT_TEXTGLYPH             = 112
      } SBMLLayoutTypeCode_t;
</code>
 *
 *  <p>
 *   These enum values are returned by corresponding getTypeCode() functions.
 *   (e.g. SBML_GROUPS_GROUP is returned in Group::getTypeCode())
 *  </p>
 *
 *  <p>
 *   The value of each typecode can be duplicated between those of different 
 *   packages (In the above SBMLayoutTypeCode_t and SBMLGroupsTypeCode_t types, 
 *   unique values are assigned to enum values, but this is not mandatory.)
 *  </p>
 *
 *  <p>
 *   Thus, to distinguish the typecodes of different packages, not only the return
 *   value of getTypeCode() function but also that of getPackageName()
 *   function should be checked as follows:
 *  </p>
<code>
          void example (SBase sb)
          {
            string pkgName = sb->getPackageName();
            if (pkgName == 'core') {
              switch (sb->getTypeCode()) {
                case SBML_MODEL:
                   ....
                   break;
                case SBML_REACTION:
                   ....
              }
            } 
            else if (pkgName == 'layout') {
              switch (sb->getTypeCode()) {
                case SBML_LAYOUT_LAYOUT:
                   ....
                   break;
                case SBML_LAYOUT_REACTIONGLYPH:
                   ....
              }
            } 
            else if (pkgName == 'groups') {
              switch (sb->getTypeCode()) {
                case SBML_GROUPS_GROUP:
                   ....
                   break;
                case SBML_GROUPS_MEMBER:
                   ....
              }
            }
            ...
          } 
</code>
 *
 *  </li>
 *  <li> Override the following pure virtual function which returns a string corresponding to the given typecode:
 *  
<code>  
       virtual string SBMLExtension::getStringFromTypeCode(int typeCode) const;
</code> 
 *
 *   <p> For example, the function for groups extension is implemented as follows: </p>
<code>  
static
string SBML_GROUPS_TYPECODE_STRINGS[] =
{
    'Group'
  , 'Member'
};

string 
GroupsExtension::getStringFromTypeCode(int typeCode) const
{
  int min = SBML_GROUPS_GROUP;
  int max = SBML_GROUPS_MEMBER;

  if ( typeCode < min || typeCode > max)
  {
    return '(Unknown SBML Groups Type)';  
  }

  return SBML_GROUPS_TYPECODE_STRINGS[typeCode - min];
}
</code> 
 *
 *  </li>
 *
 * <li> Implements a 'static void init()' function in the derived class
 *
 * <p> In the init() function, initialization code which creates an instance of 
 *     the derived class and registering code which registers the instance to 
 *     SBMLExtensionRegistry class are implemented.
 * </p>
 * 
 * For example, the init() function for groups package is implemented as follows: 
<code>
void 
GroupsExtension::init()
{
  //-------------------------------------------------------------------------
  //
  // 1. Checks if the groups pacakge has already been registered.
  //
  //-------------------------------------------------------------------------

  if (SBMLExtensionRegistry::getInstance().isRegistered(getPackageName()))
  {
    // do nothing;
    return;
  }

  //-------------------------------------------------------------------------
  //
  // 2. Creates an SBMLExtension derived object.
  //
  //-------------------------------------------------------------------------

  GroupsExtension groupsExtension;

  //-------------------------------------------------------------------------------------
  //
  // 3. Creates SBasePluginCreatorBase derived objects required for this 
  //    extension. The derived classes can be instantiated by using the following 
  //     template class.
  //
  //    temaplate<class SBasePluginType> class SBasePluginCreator
  //
  //    The constructor of the creator class has two arguments:
  //
  //        (1) SBaseExtensionPoint : extension point to which the plugin object connected
  //        (2) std::vector<string> : a std::vector object that contains a list of URI
  //                                       (package versions) supported by the plugin object.
  //
  //    For example, two plugin objects (plugged in SBMLDocument and Model elements) are 
  //    required for the groups extension.
  //
  //    Since only 'required' attribute is used in SBMLDocument by the groups package, existing
  //    SBMLDocumentPlugin class can be used as-is for the plugin.
  //
  //    Since the lists of supported package versions (currently only L3V1-groups-V1 supported )
  //    are equal in the both plugin objects, the same vector object is given to each 
  //    constructor.
  //
  //---------------------------------------------------------------------------------------

  std::vector<string> packageURIs;
  packageURIs.push_back(getXmlnsL3V1V1());

  SBaseExtensionPoint sbmldocExtPoint('core',SBML_DOCUMENT);
  SBaseExtensionPoint modelExtPoint('core',SBML_MODEL);

  SBasePluginCreator<SBMLDocumentPlugin, GroupsExtension> sbmldocPluginCreator(sbmldocExtPoint,packageURIs);
  SBasePluginCreator<GroupsModelPlugin,   GroupsExtension> modelPluginCreator(modelExtPoint,packageURIs);

  //--------------------------------------------------------------------------------------
  //
  // 3. Adds the above SBasePluginCreatorBase derived objects to the SBMLExtension derived object.
  //
  //--------------------------------------------------------------------------------------

  groupsExtension.addSBasePluginCreator(&sbmldocPluginCreator);
  groupsExtension.addSBasePluginCreator(&modelPluginCreator);

  //-------------------------------------------------------------------------
  //
  // 4. Registers the SBMLExtension derived object to SBMLExtensionRegistry
  //
  //-------------------------------------------------------------------------

  int result = SBMLExtensionRegistry::getInstance().addExtension(&groupsExtension);

  if (result != LIBSBML_OPERATION_SUCCESS)
  {
    std::cerr << '[Error] GroupsExtension::init() failed.' << std::endl;
  }
}
</code>
 *    </p> 
 * </li>
 *
 * <li> Instantiate a global SBMLExtensionRegister variable in appropriate 
 *      implementation file
 *       
 * <p> For example, the global variable for the groups extension is instantiated in GroupsExtension.cpp as follows: </p>
<code>
  static SBMLExtensionRegister<GroupsExtension> groupsExtensionRegister;
</code>
 *    The init() function is invoked when the global variable is instantiated,
 *    by which initialization and registering the package extension are performed.
 * </li>
 *
 *
 * </ol>
 * 
 */
public class SBMLExtension : IDisposable {
	private HandleRef swigCPtr;
	protected bool swigCMemOwn;
	
	internal SBMLExtension(IntPtr cPtr, bool cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(SBMLExtension obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (SBMLExtension obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~SBMLExtension() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_SBMLExtension(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public virtual SBasePlugin DowncastSBasePlugin(IntPtr cPtr, bool owner)
  {
    if (cPtr.Equals(IntPtr.Zero)) return null;
	return new SBasePlugin(cPtr, owner);
  }

  public virtual SBase DowncastSBase(IntPtr cPtr, bool owner)
  {
    if (cPtr.Equals(IntPtr.Zero)) return null;	  
    return new SBase(cPtr, owner);
  }

  
  /**
   * Returns the number of SBasePlugin objects stored in this object.
   *
   * @return the number of SBasePlugin objects stored in this object.
   */
 public int getNumOfSBasePlugins() {
    int ret = libsbmlPINVOKE.SBMLExtension_getNumOfSBasePlugins(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the number of supported package Namespace (package versions) of this 
   * package extension.
   *
   * @return the number of supported package Namespace (package versions) of this 
   * package extension.
   */
 public long getNumOfSupportedPackageURI() { return (long)libsbmlPINVOKE.SBMLExtension_getNumOfSupportedPackageURI(swigCPtr); }

  
  /**
   * Returns a flag indicating, whether the given URI (package version) is 
   * supported by this package extension.
   *
   * @return true if the given URI (package version) is supported by this 
   * package extension, otherwise false is returned.
   */
 public bool isSupported(string uri) {
    bool ret = libsbmlPINVOKE.SBMLExtension_isSupported(swigCPtr, uri);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  
  /**
   *
   * Returns the ith URI (the supported package version)
   *
   * @param i the index of the list of URI (the list of supporeted pacakge versions)
   * @return the URI of supported package version with the given index.
   */
 public string getSupportedPackageURI(long i) {
    string ret = libsbmlPINVOKE.SBMLExtension_getSupportedPackageURI(swigCPtr, i);
    return ret;
  }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Creates and returns a deep copy of this SBMLExtension object.
   *
   * @return a (deep) copy of this SBase object
   */
 public SBMLExtension clone() {
        SBMLExtension ret
	    = (SBMLExtension) libsbml.DowncastExtension(libsbmlPINVOKE.SBMLExtension_clone(swigCPtr), true);
        return ret;
}

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Returns the name of this package (e.g. 'layout', 'multi').
   *
   * @return the name of package extension
   */
 public string getName() {
    string ret = libsbmlPINVOKE.SBMLExtension_getName(swigCPtr);
    return ret;
  }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Returns the uri corresponding to the given SBML level, SBML version, and package version.
   *
   * @param sbmlLevel the level of SBML
   * @param sbmlVersion the version of SBML
   * @param pkgVersion the version of package
   *
   * @return a string of the package URI
   */
 public string getURI(long sbmlLevel, long sbmlVersion, long pkgVersion) {
    string ret = libsbmlPINVOKE.SBMLExtension_getURI(swigCPtr, sbmlLevel, sbmlVersion, pkgVersion);
    return ret;
  }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Returns the SBML level associated with the given URI of this package.
   *
   * @param uri the string of URI that represents a versions of the package
   * @return the SBML level associated with the given URI of this package.
   */
 public long getLevel(string uri) { return (long)libsbmlPINVOKE.SBMLExtension_getLevel(swigCPtr, uri); }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Returns the SBML version associated with the given URI of this package.
   *
   * @param uri the string of URI that represents a versions of the package
   * @return the SBML version associated with the given URI of this package.
   */
 public long getVersion(string uri) { return (long)libsbmlPINVOKE.SBMLExtension_getVersion(swigCPtr, uri); }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * Returns the package version associated with the given URI of this package.
   *
   * @param uri the string of URI that represents a versions of this package
   * @return the package version associated with the given URI of this package.
   */
 public long getPackageVersion(string uri) { return (long)libsbmlPINVOKE.SBMLExtension_getPackageVersion(swigCPtr, uri); }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function 
   *           in their derived class.
   *
   * This method takes a type code of this package and returns a string 
   * representing the code.
   */
 public string getStringFromTypeCode(int typeCode) {
    string ret = libsbmlPINVOKE.SBMLExtension_getStringFromTypeCode(swigCPtr, typeCode);
    return ret;
  }

  
  /**
   *  (NOTICE) Package developers MUST OVERRIDE this pure virtual function in 
   *           their derived class.
   *
   * Returns an SBMLExtensionNamespaces<class SBMLExtensionType> object 
   * (e.g. SBMLExtensionNamespaces<LayoutExtension> whose alias type is 
   * LayoutPkgNamespaces) corresponding to the given uri.
   * Null will be returned if the given uri is not defined in the corresponding 
   * package.
   *
   * @param uri the string of URI that represents one of versions of the package
   * @return an SBMLExtensionNamespaces<class SBMLExtensionType> object. null
   *         will be returned if the given uri is not defined in the corresponding 
   *         package. 
   */
 public SBMLNamespaces getSBMLExtensionNamespaces(string uri) {
	SBMLNamespaces ret
	    = (SBMLNamespaces) libsbml.DowncastSBMLNamespaces(libsbmlPINVOKE.SBMLExtension_getSBMLExtensionNamespaces(swigCPtr, uri), false);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
	return ret;
}

  
  /**
   * enable/disable this package.
   * Returned value is the result of this function.
   *
   * @param isEnabled the bool value: true (enabled) or false (disabled)
   *
   * @return true if this function call succeeded, otherwise false is returned.
   */
 public bool setEnabled(bool isEnabled) {
    bool ret = libsbmlPINVOKE.SBMLExtension_setEnabled(swigCPtr, isEnabled);
    return ret;
  }

  
  /**
   * Check if this package is enabled (true) or disabled (false).
   *
   * @return true if this package is enabled, otherwise false is returned.
   */
 public bool isEnabled() {
    bool ret = libsbmlPINVOKE.SBMLExtension_isEnabled(swigCPtr);
    return ret;
  }

}

}
