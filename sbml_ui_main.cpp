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
       << ")                     #" << endl;
  cout << "#################################################################################" 
       << endl << endl;
}

char SBML_UI_main::main_screen_display(bool integrate){
  
  char* input;
  cout << "   Select an option from below:" << endl << endl;
    
    if (integrate)
      cout  << "   Explore Model ----------------------------------------- A" << endl;
    else
      cout  << "   Explore Models ---------------------------------------- A" << endl;

    cout << "   Display model summary --------------------------------- S" << endl
	 << "   TESTFUNCTION -------------------------------------------T" << endl
	 << "   Help ---------------------------------------------------H" << endl;
    
    if (integrate){
      cout  << "   Integrate models ---------------------------------------I" << endl;
    }
    
    cout << endl;
    
    cout << "   Quit ---------------------------------------------------Q" << endl << endl;
    cout << "   Select: "; 
    
    while (true){
      input = selectorGet();
      switch (input[0]){
	
      case 'A':
	return 'A';
      
      case 'S':
	return 'S';
      
      case 'H':
	return 'H';

      case 'Q':
	return 'Q';
      
      case 'T':
	return 'T';
	
      case 'I':
	if (integrate)
	  return 'I';
	else
	  break;

      default:
	cout << "\n**** Invalid Selection (" << input[0] << ") **** - Please reselect :";
      }
    }
    
}

void SBML_UI_main::print_help(){

  print_usage();
  
  cerr << "Control options available within the tool, but can either take one or two sbml \nfiles. If one file is taken, the model can be displayed, and consolidated,\nremoving redundant components, and a copy saved. If two are files taken, \nthese can be integrated into a single SBML model."
    
	 << endl << endl << endl

	 << "We recommend writing the output of this program to a text file or piping to\nlessfor a clear method to overview the model being described. Hopefully in\nfuture releases we'll have a better interface and a GUI, but for now this is\nwhat we've got - functionality over usebility"

	 << endl << endl
      
	 << " [OPTIONS] " << endl
	 << "  --help        Display this message" << endl 
	 << "  --version     Display the program version" << endl
	 << "  -o            Define output model name (.xml added)" << endl
      
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
  cerr << "Pathway Viewer - version " << get_version() << endl;
}

void SBML_UI_main::print_logo(){
  cout <<
    "     .-://///:`  .:/+++++/-`      .--.             `---`  `--\n  -/++//:---:.`://+syyyssoo+`    ohhy`            /hhh.  -hy`\n`/++/-`       ::/ohhyyssssoss-   ohhh+           .yhhh.  .hy`\n:++/.        `:::sysoo+++++oss.  ohoyh-         `ohoyh.  .hy`\n++//`        `--:/oo+///://+os:  oh//hs`        :hs.yh.  .hy`\n/+//.       `..--:////:--:/oos.  oh/`sh/       `yh-`yh.  .hy`\n`////:-.......---::://///++oo-   oh/ -hy.      +h+ `yh.  .hy`\n  .:///:::::--::::://///++oo:    oh/  +hs     -hy` `yh.  .hy`\n`::-``..--::::::://osyyysoooo.   oh/  `yh:   `sh:  `yh.  .hy`\n:o+/`      .:////oyhyyyyyyssss`  oh/   :hy`  /ho`  `yh.  .hy`\n/oo/        .///oyysoo+++oosyy-  oh/    oho .hh.   `yh.  .hy`\n.sso:       `+++oso+//////syyy`  oh/    .hh-oh/    `yh.  .hy`\n :sss+-`   ./oooooo//:::+syyy.   oh/     /hhhs`    `yh.  -hy`\n  `/syssooossssssssssssyyyy/`    oh/      shh-     `yh.  -hhooooooooooo\n    `-/+oso+/-.-:/osyyso/-`      -:.      .:-      `--`  `:::::::::::::\n"
       << endl;
  cout <<"8888888          888                                     888\n  888            888                                     888\n  888            888                                     888\n  888   88888b.  888888 .d88b.   .d88b.  888d888 8888b.  888888 .d88b.  888d888\n  888   888 \"88b 888   d8P  Y8b d88P\"88b 888P\"      \"88b 888   d88\"\"88b 888P\"   \n  888   888  888 888   88888888 888  888 888    .d888888 888   888  888 888\n  888   888  888 Y88b. Y8b.     Y88b 888 888    888  888 Y88b. Y88..88P 888\n8888888 888  888  \"Y888 \"Y8888   \"Y88888 888    \"Y888888  \"Y888 \"Y88P\"  888\n                                     888\n                                Y8b d88P\n                                 \"Y88P\"\nAuthor: alex.holehouse@gmail.com\n"
    
       << endl;
  
  any_key_to_continue();
}

  
