// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include "sbml_formatter.h"
#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>

using std::string;
using std::endl;

  /*!
    \brief Template class used to hold the list required for import, replacement and integration

    T1 should be instantiated to a SBML list type, and T2 to the element stored in that list. With this in mind, the class becomes a container for five lists, one import lists and two pairs of replacement and integration lists. In these paired lists the parallel elements are pared - i.e. replace_A_list[1] and replace_B_list[1] are a pair.

  */
template<class T1, class T2>
class SBML_integration_container : public SBML_formatter {
  
  
public:
  
  /** \brief Constructor method
      
      WARNING - lists are currently hard coded as SBML V1/L2. This may be a problem upon future API upgrades, so we'll look at making this 
      dynamic to reflect the models.
  */
  //-----------------------------------------------------------------------------------
  SBML_integration_container(){
    
    // we declare these on the heap (as opposed to making them automatic) so if the object goes out
    // of scope these variables are still accessible by objects far down the line if they're passed
    // (i.e. specifically the SBML_integrate class)
    
    import_list = new T1(1,2);
    replace_A_list = new T1(1,2); 
    replace_B_list = new T1(1,2);
    integrate_A_list = new T1(1,2);
    integrate_B_list = new T1(1,2);
    
    log_stream << "WARNING - currently SBML lists used to store elements for integration, replacement and importing from modelB to the newly created model are hardcoded as version 1/level 2. This may cause problems, although we don't anticipate it" << endl;
          
    // initialze counters to 0
    import_n = 0;
    replace_n = 0;
    integrate_n = 0;
  }
  
  ~SBML_integration_container(){
    delete import_list;
    delete replace_A_list;
    delete replace_B_list;
    delete integrate_A_list;
    delete integrate_B_list;
  }
  

  
  // functions to add element into the import list
  /* \brief Add element to the import list */
  //-----------------------------------------------------------------------------------
  void add_to_import(const T2 new_element){
    
    import_list->append(new_element);
    import_n++;
  }

  
  
  // function to add element a pair of elements in the replace list - fromB will replace all 
  // references of fromA in the integrated model
  //-----------------------------------------------------------------------------------
  /* \brief Add elements to the replace lists */
  void add_to_replace(const T2 fromA, const T2 fromB){
    replace_A_list->append(fromA);
    replace_B_list->append(fromB);
    replace_n++;
  }

  
  // function to add element a pair of elements in the integrate list - fromB and fromA will 
  // be combined 
  //-----------------------------------------------------------------------------------
  /* \brief Add elements to the integrate lists */
  void add_to_integrate(const T2 fromA, const T2 fromB){
    integrate_A_list->append(fromA);
    integrate_B_list->append(fromB);
    integrate_n++;
  }
  

  
  // functions to get how many elements are in each list
  //-----------------------------------------------------------------------------------
  /* \brief get the number of elements in the import list */
  int get_num_imports(){return import_n;}
  /* \brief get the number of elements in the replace list pair */
  int get_num_replacements() {return replace_n;}
  /* \brief get the number of elements in the integrate list pair */
  int get_num_integrates() {return integrate_n;}
  
  /* \brief get the import list */
  T1* get_import_list(){return import_list;}
  /* \brief get the replacement listA */
  T1* get_replace_A_list(){return replace_A_list;}
  /* \brief get the replacement listB */
  T1* get_replace_B_list(){return replace_B_list;}
  /* \brief get the integrate listA */
  T1* get_integrate_A_list(){return integrate_A_list;}
  /* \brief get the integrate listB */
  T1* get_integrate_B_list(){return integrate_B_list;}
  
private:
  // from Model B
  /// import list object
  T1* import_list;

  /// number of elements in import list
  int import_n;
  
  // two parallel lists, defining what in A is to be replaced by something in B
  
  /// replacement list - elements in A are replaced by the corresponding element in B
  T1* replace_A_list;
  /// replacement list - elements in B replace the corresponding element in A
  T1* replace_B_list;
  /// number of elements in the replacement list pair
  int replace_n;
  
  // from model A
  T1* integrate_A_list;
  T1* integrate_B_list;
  int integrate_n;
  
};
