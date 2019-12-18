OBJS = protchap.o dynamicLibEnum.o randomNumberGenerator.o\
point.o localConformations.o residue.o utilities.o configFileHandler.o\
turingMachine.o  chaperon.o smartChaperone.o proteinChaperonComplex.o dimersChaperonComplex.o main.o
OBJS_V21 = multiTempDoubleDomain.o doubleDomain.o protchap.o dynamicLibEnum.o\
randomNumberGenerator.o point.o localConformations.o residue.o utilities.o configFileHandler.o\
toysimu.cpp
OBJS_V21b = doubleDomain.o protchap.o dynamicLibEnum.o\
randomNumberGenerator.o point.o localConformations.o residue.o utilities.o configFileHandler.o\
toysimu.cpp
LIBS = 
CMD_CMP = g++ -v -Wno-deprecated

     TOYFOLD: $(OBJS_V21b)
	$(CMD_CMP) -o ../bin/V21 $(OBJS_V21b) $(LIBS) -O 
		
     toysimu.o: doubleDomain.o protchap.o toysimu.cpp
	$(CMD_CMP) -c toysimu.cpp -O   $(LIBS)

     main.o: dimersChaperonComplex.o main.cpp
	$(CMD_CMP) -c main.cpp -O   $(LIBS)

     dimersChaperonComplex.o: utilities.o proteinChaperonComplex.o dimersChaperonComplex.h dimersChaperonComplex.cpp
	$(CMD_CMP) -c dimersChaperonComplex.cpp -O  $(LIBS)
         
     pcsimu.o: protchap.o dynamicLibEnum.o pcsimu.cpp
	$(CMD_CMP) -c pcsimu.cpp -O   $(LIBS)

     proteinChaperonComplex.o: protchap.o smartChaperone.o chaperon.o proteinChaperonComplex.h proteinChaperonComplex.cpp
	$(CMD_CMP) -c proteinChaperonComplex.cpp -O  $(LIBS)
	  	
	   doubleDomain.o: protchap.o utilities.o doubleDomain.h doubleDomain.cpp
	$(CMD_CMP) -c doubleDomain.cpp -O  $(LIBS)

    multiTempDoubleDomain.o: doubleDomain.o multiTempDoubleDomain.h multiTempDoubleDomain.cpp
	$(CMD_CMP) -c multiTempDoubleDomain.cpp -O  $(LIBS)

     protchap.o: residue.o randomNumberGenerator.o point.o localConformations.o utilities.o configFileHandler.o protchap.cpp protchap.h definitions.h
	$(CMD_CMP) -c protchap.cpp -O  $(LIBS)

     dynamicLibEnum.o: point.o dynamicLibEnum.cpp dynamicLibEnum.h
	$(CMD_CMP) -c dynamicLibEnum.cpp -O  
	
     localConformations.o: point.o randomNumberGenerator.o localConformations.cpp localConformations.h dynamicLibEnum.o
	$(CMD_CMP) -c localConformations.cpp -O 
	
     point.o: point.cpp point.h 
	$(CMD_CMP) -c point.cpp -O 

     residue.o: point.o residue.cpp residue.h definitions.h
	$(CMD_CMP) -c residue.cpp -O 
		     	
     randomNumberGenerator.o: randomNumberGenerator.cpp randomNumberGenerator.h definitions.h
	$(CMD_CMP) -c randomNumberGenerator.cpp -O  

     util: point.o residue.o utilities.o 
	$(CMD_CMP) -o his point.o residue.o utilities.o  $(LIBS)
	
     his: point.o residue.o utilities.o configFileHandler.o histograms.o
	$(CMD_CMP) -o clust point.o residue.o utilities.o configFileHandler.o histograms.o  $(LIBS)
   
     histograms.o: point.o residue.o utilities.o configFileHandler.o histograms.cpp
	$(CMD_CMP) -c histograms.cpp -O 
	 
     utilities.o: residue.o utilities.cpp utilities.h
	$(CMD_CMP) -c utilities.cpp -O 
	
     configFileHandler.o: point.o utilities.o configFileHandler.cpp configFileHandler.h 
	$(CMD_CMP) -c configFileHandler.cpp -O

     smartChaperone.o: chaperon.o protchap.o smartChaperone.h smartChaperone.cpp
	$(CMD_CMP) -c smartChaperone.cpp -O

     chaperon.o: residue.o configFileHandler.o turingMachine.o chaperon.h chaperon.cpp
	$(CMD_CMP) -c chaperon.cpp -O  	

     turingMachine.o: tree.o turingMachine.h turingMachine.cpp
	$(CMD_CMP) -c turingMachine.cpp -O    	

     tree.o: tree.h tree.cpp
	#$(CMD_CMP) -c tree.cpp -O      
	
     tree: tree.o
	$(CMD_CMP) -o tr tree.o -O 
	
     turing: turingMachine.o
	$(CMD_CMP) -o tm tree.o turingMachine.o point.o utilities.o residue.o configFileHandler.o $(LIBS) -O 

     smart: smartChaperone.o smartChaperone.cpp smartChaperone.h
	$(CMD_CMP) -o ../RUN13/test tree.o turingMachine.o chaperon.o smartChaperone.o point.o utilities.o residue.o configFileHandler.o $(LIBS) -O -64
		
     chap: chaperon.o configFileHandler.o turingMachine.o
	$(CMD_CMP) -o chap tree.o turingMachine.o chaperon.o point.o utilities.o residue.o configFileHandler.o $(LIBS) -O  
	     
     locidx: configFileHandler.o
	$(CMD_CMP) -o tstp point.o utilities.o residue.o configFileHandler.o $(LIBS) -O  
	
     fnat: configFileHandler.o
	$(CMD_CMP) -o DIMERS/SRC_SEQUENCES/makeDimers point.o utilities.o residue.o configFileHandler.o $(LIBS) -O  
	
     clean:
	rm $(OBJS) 

     backup: $(OBJS_V21)
	cp *.cpp *.h *.pl Makefile backup/simulator/
	cp Database/*.pm backup/simulator/Database/
	cp ../seqSeeker/*.cpp ../seqSeeker/*.h ../seqSeeker/*.pl backup/seqSeeker/
	 