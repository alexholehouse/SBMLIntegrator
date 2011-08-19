#ifndef SBML_LISTPAIR_CONTAINER_CPP
#define SBML_LISTPAIR_CONTAINER_CPP

#include "sbml_formatter.h"

#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>

using namespace std;

template<class T>
class SBML_listpair_container : public SBML_formatter {
  
public:

  // default constructor
  SBML_listpair_container(){
    num = 0;
    list_A = NULL;
    list_B = NULL;
  }
  
  // explicit constructor
  SBML_listpair_container(T* _list_A, T* _list_B, int& _num) {
    
    num = _num;
    list_A = _list_A;
    list_B = _list_B;
    
  }
  
  int& get_num(){
    return num; }
  
  T* get_listA(){
    return list_A; }

  T* get_listB(){
    return list_B; }

  void set_listA(T* _list_A){
    list_A = _list_A;
  }

  void set_listB(T* _list_B){
    list_B = _list_B;
  }
  
  void set_num(int new_num){
    num = new_num; 
  }
  
  
private:
  
  T* list_A;
  T* list_B;
  int num;
  
};

#endif
  
  

