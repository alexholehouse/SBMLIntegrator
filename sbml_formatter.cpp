#include "sbml_formatter.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sbml/SBMLTypes.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <math.h>

using namespace std;


// initial default values;
int SBML_formatter::unique = rand()% 1000;
bool SBML_formatter::logfile_set = false;
ofstream SBML_formatter::log_stream;

// function which takes a double and returns it as a string
//-----------------------------------------------------------------------------------
string SBML_formatter::dtostr(double in){

  ostringstream string_stream;
  string return_string;

  string_stream << in;
  return_string = string_stream.str();
  
  return (return_string);
}


double SBML_formatter::doubleGet(double lower, double upper){
  
  string in;
  char temp;
  double val;
  
  in = stringGet();
  const char* in_cstr = in.c_str();

  if (in.length() == 0)
    return c_FAIL_DOUBLEGET;
  
  for (unsigned int i = 0 ; i < in.length() ; i++){
    temp = in_cstr[i];
    if (static_cast<int>(temp) < 48 || static_cast<int>(temp) > 57){
      // non 0-9 character in input, so invalid
      return c_FAIL_DOUBLEGET;
    }
  }
  
  val = atoi(in_cstr);

  if (val < lower || val > upper)
    return c_FAIL_DOUBLEGET;

  return val;
}

double SBML_formatter::doubleGet_guarenteed(double lower, double upper){
  
  double val = doubleGet(lower, upper);
  
  while (val == c_FAIL_DOUBLEGET){
    cout << "**** Invalid selection ****" << endl;
    cout << "Please reselect :";
    val = doubleGet(lower,upper);
  }

  return val;
}

    


SpeciesReference* SBML_formatter::species2SpeciesReference(const Species* species, const Reaction* rxn){
  return (species2SpeciesReference(species, rxn, ""));
}

SpeciesReference* SBML_formatter::species2SpeciesReference(const Species* species, const Reaction* rxn, string addToSpeciesID){
  string value = species->getId(); 
  
  SpeciesReference* SR = new SpeciesReference(species->getLevel(), species->getVersion());
  
  value = species->getId();

  if (addToSpeciesID != ""){
    // sets the species name, as 
    value.append(addToSpeciesID);
  }
  
  SR->setSpecies(value);
  
  SR->setStoichiometry(1);
  SR->setId((value.append("_ref_")).append(dtostr(unique)));
  value.clear();
  value.append(species->getId());
  SR->setName((value.append("_in_rxn_")).append(rxn->getId()));
  // unique is a static variable which allows anything that needs a modelwide unique value to get
  // one;
  unique++;

  return SR;
}

ModifierSpeciesReference* SBML_formatter::species2ModifierSpeciesReference(const Species* species, const Reaction* rxn) {
  
  string value;
  
  ModifierSpeciesReference* MSR = new ModifierSpeciesReference(species->getLevel(), species->getVersion());
  
  value = species->getId();

  MSR->setSpecies(value);
  
  MSR->setId((value.append("_ref_")).append(dtostr(unique)));
  value.clear();
  value.append(species->getId());
  MSR->setName((value.append("_in_rxn_")).append(rxn->getId()));
  // unique is a static variable which allows anything that needs a modelwide unique value to get
  // one;
  unique++;

  return MSR;
}


void SBML_formatter::reset_cstr(char c_str[], int size){
  for (int i = 0 ; i < size ;i++)
    c_str[i] = ' ';
}

// default constructor -- called by all SBML_formatter inheriting classes
// This is a relic of a previous build, keeping it in for now but actually not necessary, just 
// use getline() inplace.
//-----------------------------------------------------------------------------------
string SBML_formatter::stringGet(){
  string input;
  getline(cin,input,'\n');

  return input;
}

char* SBML_formatter::selectorGet(){
  string input;
  const char* input_c;
  
  getline(cin, input,'\n');
  input_c = input.c_str();
  
  char* ret = new char[1];
  ret[0] = input_c[0];
  
  return ret;
}



void SBML_formatter::autoAbort(string message){
  cout << message << endl;
  log_stream << message << endl;
  SBML_EXIT();
  exit(1);
}

// default constructor -- called by all SBML_formatter inheriting classes
//-----------------------------------------------------------------------------------
SBML_formatter::SBML_formatter(){

  // If this is the first time a file with an SBML_formatter base is created you generate 
  // new logfile, which is then used throughout
  
  if (!logfile_set){

    
    system("mkdir logs\0");
    
    string name = "logs/";
    
    name.append("logat_");
    name.append(get_time());
    name.append(".txt");
    
    char* output = (char*)name.c_str();
    
    log_stream.open(output);
    
    log_stream << "PathwayViewer version " << get_version() << " logfile for " << get_time() << " on " << get_date() << endl;
    
    // set logfile so initial logfile message isn't printed again!
    logfile_set=true;
  }
}



// Should be the last thing main calls - closes the static log_stream. This is critical!
//-----------------------------------------------------------------------------------
int SBML_formatter::SBML_EXIT(){
  log_stream.close();
  // TODO - close conf_file logstream
  return 0;
}



// Function which returns the current date as "DD_MM_YYYY"
//-----------------------------------------------------------------------------------
string SBML_formatter::get_date(){
  time_t now;
  char the_date[12];
  
  the_date[0] = '\0';
  
  now = time(NULL);
  
  if (now != -1){
    strftime(the_date, 12, "%d_%m_%Y", gmtime(&now));
  }
  
  return string(the_date);
}



// function which returns the current time as HH_MM_SS
//-----------------------------------------------------------------------------------
string SBML_formatter::get_time(){
  time_t now;
  char the_time[9];
  
  the_time[0] = '\0';
  
  now = time(NULL);
  
  if (now != -1){
    strftime(the_time, 12, "%H_%M_%S", gmtime(&now));
  }
  
  return string(the_time);
}


// function which returns the current pathway_viewer version
//-----------------------------------------------------------------------------------
string SBML_formatter::get_version(){
  return "0.1 (alpha)";
}



void SBML_formatter::logfile_add_message(int error, std::string element, std::string new_owner){
  if (error !=0)
    log_stream << "WARNING - error " << error << " adding " << element << " to " << new_owner << endl;
}
 
char SBML_formatter::yes_or_no(){
  char input;
  cout << "    Please select Y/N: ";

  while (true){
    cin >> input;
    cin.ignore();
    
    if (input == 'Y'|| input == 'y')
      return 'Y';
    
    if (input == 'N' || input == 'n')
      return 'N';

    cout << "    Sorry - selection (" << input << ") not recognized. \n    Please select Y or N: ";
  }
}

//-----------------------------------------------------------------------------------
bool SBML_formatter::write_to_file(Model* input, string filename){
  
  ofstream SBMLDoc_out;
  
  SBMLDoc_out.open(filename.c_str());

  log_stream << "Writing to " << filename << " in PWD" << endl;
  
  SBMLDocument*  document = new SBMLDocument(input->getLevel(), input->getVersion());
  document->setModel(input);

  SBMLWriter* writer = new SBMLWriter;
  
  writer->writeSBML(document, SBMLDoc_out);
  
  if(SBMLDoc_out.fail() || SBMLDoc_out.bad())
    return false;

  else
    return true;
}
