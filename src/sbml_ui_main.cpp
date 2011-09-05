// Copyright Alex Holehouse 2011
// Distributed under the terms of the GNU general public license - see COPYING.txt for more details

#include <iostream>
#include <string>
#include <sbml/SBMLTypes.h>
#include "sbml_ui_main.h"
#include <cstdlib>


using namespace std;

void SBML_UI_main::intro(){

  system("clear");
  cout << "#################################################################################" 
       << endl;
  cout << "#           WELCOME TO SBML INTEGRATOR (version " << get_version() 
       << ")                    #" << endl;
  cout << "#################################################################################" 
       << endl << endl;
}

int SBML_UI_main::main_screen_display(bool integrate, bool reset){
  
  int i;
  double selector;
  
  if (reset)
    system("clear");

  if (integrate)
    i = 1;
  else
    i = 0;
  cout << "----- SBMLIntegrator - Main Menu -----" << endl;
  cout << "   Select an option from below:" << endl << endl;
    
  cout  << " [1] ------------ Explore Models  " << endl;
  cout  << " [2] ------------ Display Model Summary  " << endl;
  
  if (integrate)
    cout << " [3] ------------ Integrate models " << endl;
  
  cout << " [" << i+3 << "] ------------ Quit " << endl;
  
  cout << endl;
  
  cout << " Select: "; 
  selector = doubleGet_guarenteed(1,i+4);
  
  return (static_cast<int>(selector));
}

void SBML_UI_main::print_help(){
  
  print_usage();
  
  cerr << "Control options available within the tool, but can either take one or two sbml \nfiles. If one file is taken, the software acts a simple, text-based model \nviewer. If two are files taken, these can be integrated into a single\nSBML model."
    
       << endl << endl
    
       << "For the process of integration and correct configuration\nfile (integrate.conf) is required. This defines the elements\nto be imported, replaced and integrated. For more information\nsee theuser manual (README.txt)\n"
    
       << endl << endl
    
       << " [OPTIONS] " << endl
       << "  --help        Display this message" << endl 
       << "  --version     Display the program version" << endl
    
       << endl
       << endl
    
       << "About: This software was developed entirly by alex holehouse. For questions,\nconcerns, frustration and praise contact him at alex.holehouse@gmail.com" << endl;
}

void SBML_UI_main::print_usage(){
  cerr << "Usage: pathway_viewer [OPTIONS] sbml_model_1.xml [sbml_model_2.xml]" << endl
       << "For more help try 'pathway_viewer --help' " << endl;
  cerr << endl;
}

void SBML_UI_main::print_version(){
  cerr << "SBMLIntegrator - version " << get_version() << endl;
}

void SBML_UI_main::print_logo(){
  cout << endl;
  cout <<
    "    .-://///:`  .:/+++++/-`      .--.             `---`  `--\n  -/++//:---:.`://+syyyssoo+`    ohhy`            /hhh.  -hy`\n`/++/-`       ::/ohhyyssssoss-   ohhh+           .yhhh.  .hy`\n:++/.        `:::sysoo+++++oss.  ohoyh-         `ohoyh.  .hy`\n++//`        `--:/oo+///://+os:  oh//hs`        :hs.yh.  .hy`\n/+//.       `..--:////:--:/oos.  oh/`sh/       `yh-`yh.  .hy`\n`////:-.......---::://///++oo-   oh/ -hy.      +h+ `yh.  .hy`\n  .:///:::::--::::://///++oo:    oh/  +hs     -hy` `yh.  .hy`\n`::-``..--::::::://osyyysoooo.   oh/  `yh:   `sh:  `yh.  .hy`\n:o+/`      .:////oyhyyyyyyssss`  oh/   :hy`  /ho`  `yh.  .hy`\n/oo/        .///oyysoo+++oosyy-  oh/    oho .hh.   `yh.  .hy`\n.sso:       `+++oso+//////syyy`  oh/    .hh-oh/    `yh.  .hy`\n :sss+-`   ./oooooo//:::+syyy.   oh/     /hhhs`    `yh.  -hy`\n  `/syssooossssssssssssyyyy/`    oh/      shh-     `yh.  -hhooooooooooo\n    `-/+oso+/-.-:/osyyso/-`      -:.      .:-      `--`  `:::::::::::::\n"
       << endl;
  cout <<"8888888          888                                     888\n  888            888                                     888\n  888            888                                     888\n  888   88888b.  888888 .d88b.   .d88b.  888d888 8888b.  888888 .d88b.  888d888\n  888   888 \"88b 888   d8P  Y8b d88P\"88b 888P\"      \"88b 888   d88\"\"88b 888P\"   \n  888   888  888 888   88888888 888  888 888    .d888888 888   888  888 888\n  888   888  888 Y88b. Y8b.     Y88b 888 888    888  888 Y88b. Y88..88P 888\n8888888 888  888  \"Y888 \"Y8888   \"Y88888 888    \"Y888888  \"Y888 \"Y88P\"  888\n                                     888\n                                Y8b d88P\n                                 \"Y88P"
    
       << endl;
  
  any_key_to_continue();
}

void SBML_UI_main::explore_models(Model* model1, Model* model2, SBML_display* display_framework, string model1_name, string model2_name){

  int selector;
  print_header("Explore models", true);
  cout << "Please select one of the two models you wish to explore" << endl << endl
       << "  " << "[1] ------------ " << model1_name << endl
       << "  " << "[2] ------------ " << model2_name << endl 
       << endl << "  Please select (1 or 2): ";
  
  selector = doubleGet_guarenteed(1,2);
  
  string message = "Model filename is ";
    
  if (selector == 1)
    display_framework->select_components_to_show(model1, message.append(model1_name));
  else
    display_framework->select_components_to_show(model2, message.append(model2_name));
      
  

    
    
    
  

}
  
