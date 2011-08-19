#ifndef SBML_INTEGRATE_REPLACE_H
#define SBML_INTEGRATE_REPLACE_H

#include "sbml_listpair_container.cpp"
#include "sbml_cleanup.h"
#include <iostream>
#include <sbml/SBMLTypes.h>
#include "sbml_integrate_helper.h"


class SBML_integrate_replace : SBML_integrate_helper {
  
 public:

  SBML_integrate_replace();
  // based on the replace_lists extracted and presented by inputConf and updated by 
  // integrate_elements, we go through the entire model_A updating references to names 
  // which are no longer relevant

  void replace_common_elements();
  
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
