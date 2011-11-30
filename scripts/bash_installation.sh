#! /bin/bash

# get absolute directory location
mkdir libsbml
cd libsbml/
inst_dir=${PWD}
cd ..
cd libsbml-5.0.0/

# configure and build a local SBML library
echo "_________________________________________________________________________"
echo "Running configure for the LibSBML API"
echo "-------------------------------------------------------------------------"

./configure --prefix $inst_dir

echo -e "\n~~ Configuration complete ~~ \n\nIf it completed without any errors, press enter 
If not please press CTRL-C, try and rectify them (probably missing 
libraries) and re-run"
read ok1


# LibSBML make
echo "_________________________________________________________________________"
echo "Running make for LibSBML API"
echo "-------------------------------------------------------------------------"


make

echo -e "\n~~ Make complete ~~ \n\nIf it completed without any errors, press enter 
If not please press CTRL-C, try and rectify them and re-run"
read ok1


# LibSBML make install
echo "_________________________________________________________________________"
echo "Running make install"
echo "-------------------------------------------------------------------------"

make install

echo -e "\n~~Make install complete~~ \n\nIf it completed without any errors, press enter 
If not please press CTRL-C, try and rectify them and re-run. We deal with all
the LD_PATH madness at the end, so don't worry about it untill then."
read ok1
echo "_________________________________________________________________________"
echo "LibSBML C++ API succesfully installed locally at 
$inst_dir"
echo "-------------------------------------------------------------------------"
cd ../
cd libsbml/lib/
LD_LIB_dir=${PWD}

cd ../../
echo "_________________________________________________________________________"
echo "Running ldconfig"
echo "You will be promoted for the SUDO password - if you don't know it don't"
echo "worry - just press enter three times and you'll skip over this step."
echo "-------------------------------------------------------------------------"
sudo ldconfig -v

export LD_LIBRARY_PATH=$LD_LIB_dir:$LD_LIBRARY_PATH


echo "_________________________________________________________________________"
echo "Making SBMLIntegrator"
echo "-------------------------------------------------------------------------"

touch Makefile

echo "src/sbmlIntegrator: src/main.o src/sbml_display.o src/sbml_search.o src/sbml_formatter.o src/sbml_cleanup.o src/sbml_ui_general.o src/sbml_ui_main.o src/sbml_integrate.o src/sbml_confInput.o src/sbml_integration_container.o src/sbml_listpair_container.o src/sbml_integrate_helper.o src/sbml_integrate_replace.o src/sbml_integrate_import.o src/sbml_augment.o src/sbml_integrate_integrate.o

	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g src/main.o src/sbml_display.o src/sbml_search.o src/sbml_ui_main.o src/sbml_ui_general.o src/sbml_formatter.o src/sbml_cleanup.o src/sbml_integrate.o src/sbml_confInput.o src/sbml_integration_container.o src/sbml_listpair_container.o src/sbml_integrate_helper.o src/sbml_integrate_replace.o src/sbml_integrate_import.o src/sbml_integrate_integrate.o src/sbml_augment.o -o SBMLIntegrator

src/main.o: src/main.cpp src/sbml_display.h src/sbml_formatter.h src/sbml_search.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/main.cpp -o src/main.o

src/sbml_cleanup.o: src/sbml_cleanup.cpp src/sbml_display.h src/sbml_search.h src/sbml_formatter.h src/sbml_cleanup.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_cleanup.cpp -o src/sbml_cleanup.o

src/sbml_display.o: src/sbml_display.cpp src/sbml_display.h src/sbml_search.h src/sbml_formatter.h src/sbml_cleanup.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_display.cpp -o src/sbml_display.o

src/sbml_search.o: src/sbml_search.cpp src/sbml_search.h src/sbml_formatter.h src/sbml_display.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_search.cpp -o src/sbml_search.o

src/sbml_formatter.o: src/sbml_formatter.cpp src/sbml_search.h src/sbml_formatter.h src/sbml_display.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_formatter.cpp -o src/sbml_formatter.o

src/sbml_ui_general.o: src/sbml_ui_general.cpp src/sbml_ui_general.h src/sbml_formatter.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_ui_general.cpp -o src/sbml_ui_general.o

src/sbml_ui_main.o: src/sbml_ui_main.cpp src/sbml_ui_main.h src/sbml_ui_general.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_ui_main.cpp -o src/sbml_ui_main.o

src/sbml_confInput.o: src/sbml_confInput.cpp src/sbml_confInput.h src/sbml_formatter.h 
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_confInput.cpp -o src/sbml_confInput.o

src/sbml_integration_container.o: src/sbml_integration_container.cpp src/sbml_formatter.h 
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integration_container.cpp -o src/sbml_integration_container.o

src/sbml_listpair_container.o: src/sbml_listpair_container.cpp src/sbml_formatter.h 
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_listpair_container.cpp -o src/sbml_listpair_container.o

src/sbml_integrate.o: src/sbml_integrate.cpp src/sbml_integrate.h src/sbml_formatter.h src/sbml_search.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integrate.cpp -o src/sbml_integrate.o

src/sbml_integrate_helper.o: src/sbml_integrate_helper.cpp src/sbml_integrate_helper.h src/sbml_formatter.h 
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integrate_helper.cpp -o src/sbml_integrate_helper.o

src/sbml_integrate_replace.o: src/sbml_integrate_replace.cpp src/sbml_integrate_replace.h src/sbml_integrate_helper.h 
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integrate_replace.cpp -o src/sbml_integrate_replace.o

src/sbml_integrate_import.o: src/sbml_integrate_import.cpp src/sbml_integrate_import.h src/sbml_integrate_helper.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integrate_import.cpp -o src/sbml_integrate_import.o

src/sbml_integrate_integrate.o: src/sbml_integrate_integrate.cpp src/sbml_integrate_integrate.h src/sbml_integrate_helper.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_integrate_integrate.cpp -o src/sbml_integrate_integrate.o

src/sbml_augment.o: src/sbml_augment.cpp src/sbml_augment.h src/sbml_formatter.h src/sbml_cleanup.h
	g++ -I libsbml/include/ -L libsbml/lib/ -lsbml -lstdc++ -lm -Wall -g -c src/sbml_augment.cpp -o src/sbml_augment.o

clean:
	rm -f src/*.o
	rm -f src/*~" > Makefile


#make

echo "_________________________________________________________________________"
echo "Cleaning up installation...."
echo "-------------------------------------------------------------------------"

# Copy the two example models into the working directory
cp example/* .

# cleanup
rm -f src/*.o
rm -f src/*~


echo -e "\n\n#########################################################################"
echo "Cleaning up installation...."
echo "#########################################################################"
echo -e "

READ ME!
------------------------------------------------------
You may also need to add;

TL/DR

Add;
export LD_LIBRARY_PATH=:$LD_LIB_dir:\$LD_LIBRARY_PATH
to your .basrch


More detailed:
An error message 

'./SBMLIntegrator: error while loading  shared libraries: 
libsbml.so.5: cannot open shared object file: No such file or directory' 

is indicative of the need to update the LD_LIBRARY_PATH
variable. To do this carry out the following;

1) run cd ~ (change to your home directory)
2) open the file .bashrc with an editor of your choice 
3) Add the following line

export LD_LIBRARY_PATH=:$LD_LIB_dir:\$LD_LIBRARY_PATH

   to the end of the file
4) Save and close
5) Run source .cshrc

Alternativly, if you normally use csh you must add;

setenv LD_LIBRARY_PATH $LD_LIB_dir

to your .cshrc and then run source .bashrc. More details
on this can be found in the README.txt. 
------------------------------------------------------
"





