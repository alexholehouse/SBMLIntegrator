SBMLIntegrator: main.o sbml_display.o sbml_search.o sbml_formatter.o sbml_cleanup.o sbml_ui_general.o sbml_ui_main.o sbml_integrate.o sbml_confInput.o sbml_integration_container.o sbml_listpair_container.o sbml_integrate_helper.o sbml_integrate_replace.o sbml_integrate_import.o sbml_augment.o sbml_integrate_integrate.o

	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g main.o sbml_display.o sbml_search.o sbml_ui_main.o sbml_ui_general.o sbml_formatter.o sbml_cleanup.o sbml_integrate.o sbml_confInput.o sbml_integration_container.o sbml_listpair_container.o sbml_integrate_helper.o sbml_integrate_replace.o sbml_integrate_import.o sbml_integrate_integrate.o sbml_augment.o -o SBMLIntegrator

main.o: main.cpp sbml_display.h sbml_formatter.h sbml_search.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c main.cpp

sbml_cleanup.o: sbml_cleanup.cpp sbml_display.h sbml_search.h sbml_formatter.h sbml_cleanup.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_cleanup.cpp 

sbml_display.o: sbml_display.cpp sbml_display.h sbml_search.h sbml_formatter.h sbml_cleanup.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_display.cpp 

sbml_search.o: sbml_search.cpp sbml_search.h sbml_formatter.h sbml_display.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_search.cpp 

sbml_formatter.o: sbml_formatter.cpp sbml_search.h sbml_formatter.h sbml_display.h
	g++ -Wall -g -c sbml_formatter.cpp 

sbml_ui_general.o: sbml_ui_general.cpp sbml_ui_general.h sbml_formatter.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_ui_general.cpp

sbml_ui_main.o: sbml_ui_main.cpp sbml_ui_main.h sbml_ui_general.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_ui_main.cpp

sbml_confInput.o: sbml_confInput.cpp sbml_confInput.h sbml_formatter.h 
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_confInput.cpp

sbml_integration_container.o: sbml_integration_container.cpp sbml_formatter.h 
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integration_container.cpp

sbml_listpair_container.o: sbml_listpair_container.cpp sbml_formatter.h 
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_listpair_container.cpp

sbml_integrate.o: sbml_integrate.cpp sbml_integrate.h sbml_formatter.h sbml_search.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integrate.cpp

sbml_integrate_helper.o: sbml_integrate_helper.cpp sbml_integrate_helper.h sbml_formatter.h 
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integrate_helper.cpp

sbml_integrate_replace.o: sbml_integrate_replace.cpp sbml_integrate_replace.h sbml_integrate_helper.h 
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integrate_replace.cpp

sbml_integrate_import.o: sbml_integrate_import.cpp sbml_integrate_import.h sbml_integrate_helper.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integrate_import.cpp

sbml_integrate_integrate.o: sbml_integrate_integrate.cpp sbml_integrate_integrate.h sbml_integrate_helper.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_integrate_integrate.cpp

sbml_augment.o: sbml_augment.cpp sbml_augment.h sbml_formatter.h sbml_cleanup.h
	g++ -I /usr/local/include/ -L /usr/local/lib/ -lsbml -lstdc++ -lm -Wall -g -c sbml_augment.cpp

clean:
	rm -f *.o
	rm -f *~


