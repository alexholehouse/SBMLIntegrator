// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#ifndef SBML_LISTPAIR_CONTAINER_CPP
#define SBML_LISTPAIR_CONTAINER_CPP

#include "sbml_formatter.h"
#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>

using std::string;

/*!
  \brief Simple template class which holds a pair of lists
  
*/
template<class T>
class SBML_listpair_container : public SBML_formatter {
  
public:

  /// \brief Constructor function - overwrites default constructor
  SBML_listpair_container(){
    num = 0;
    list_A = NULL;
    list_B = NULL;
  }
  
  /// \brief Explicit constructor that takes two list objects and the number of elements in the list (remember listpair objects contain two lists of equal lengt)
  SBML_listpair_container(T* _list_A, T* _list_B, int& _num) {
    
    num = _num;
    list_A = _list_A;
    list_B = _list_B;
    
  }
  
  /// \brief Get length of lists
  int& get_num(){
    return num; }
  
  /// \brief Returns a pointer to A
  T* get_listA(){
    return list_A; }
    
 /// \brief Returns a pointer to B
  T* get_listB(){
    return list_B; }

 /// \brief Sets list A to the argument pointer
  void set_listA(T* _list_A){
    list_A = _list_A;
  }
  
 /// \brief Sets list B to the argument pointer
  void set_listB(T* _list_B){
    list_B = _list_B;
  }
  
 /// \brief Sets the counter (DO NOT MESS AROUND WITH THIS!)
  void set_num(int new_num){
    num = new_num; 
  }
   
private:
  
  T* list_A;
  T* list_B;
  int num;
  
};

#endif
  
  

