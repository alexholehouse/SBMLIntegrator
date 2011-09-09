// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_INTEGRATE_REPLACE_H
#define SBML_INTEGRATE_REPLACE_H

#include "sbml_listpair_container.cpp"
#include "sbml_cleanup.h"
#include <iostream>
#include <sbml/SBMLTypes.h>
#include "sbml_integrate_helper.h"
/*!
  \brief Class to hold and carry out replacement functionality
  
  This uses a nested template function to facilitate the replacement of elements throughout a model
  
*/

class SBML_integrate_replace : SBML_integrate_helper {
  
 public:

  /// Overwritten default constructor - has no functionality
  SBML_integrate_replace();

  /*!
    \brief Template function to replace any element in a model with another
    
    \b Preconditions: Takes two objects of type T1 and T2. Type T1 should be an instantiated template class object of the SBML_listpair_container_type, while type T2 should be of ListOf* type, where * matches with the type of instantiation used in the SBML_listpair_container_type. For example, we could call the function with 
    
    replacement_framework.replace_elements<SBML_listpair_container<ListOfFunctionDefinitions>, ListOfFunctionDefinitions>(model_new, functionDefinitions_rep_container, 0); \n \n

    T1 = SBML_listpair_container<ListOfFunctionDefinitions>\n
    T2 = ListOfFunctionDefinition\n\n

    i defines where in the list we begin from

    \b Postconditions: The function goes through the replacement lists, replacing each pair appropriately, where in each pair the element from listB will replace the element from listA
  */

  template <class T1, class T2>
    void replace_elements(Model* model, T1 element_list_container, int i){

    int num = element_list_container.get_num();

    T2* listA = element_list_container.get_listA();
    T2* listB = element_list_container.get_listB();
  
    SBML_cleanup cleanup(model, false);
    
    for (; i < num ;i++){
    
      log_stream << "Replacing " << (listB->get(i))->getId() << " with " 
	   << (listA->get(i))->getId() << endl;
      cleanup.replace(listB->get(i), listA->get(i));
    
    }
  }

};


#endif
