SHAREDLIB = ../simulator/
OBJS_EVO = seqPermutation2.o randomNumberGenerator.o point.o
OBJS_SEEKER = seqPermutation.o randomNumberGenerator.o point.o residue.o seqSeeker.o configFileHandler.o utilities.o
LIBS = 
CMD_CMP = clang++ -Wno-deprecated


     seeker: $(OBJS_SEEKER)
	$(CMD_CMP) -o skaV21 $(OBJS_SEEKER) -O  $(LIBS)
     
     seq: $(OBJS_EVO)
	$(CMD_CMP) -o seqperm $(OBJS_EVO) -O
	
     residue.o: point.o $(SHAREDLIB)residue.h $(SHAREDLIB)residue.cpp $(SHAREDLIB)definitions.h
	$(CMD_CMP) -c $(SHAREDLIB)residue.cpp -O
	
     seqSeeker.o: point.o residue.o seqPermutation.o configFileHandler.o utilities.o seqSeeker.cpp seqSeeker.h
	$(CMD_CMP) -c seqSeeker.cpp -O $(LIBS)
	         
     seqPermutation.o: point.o randomNumberGenerator.o seqPermutation.h seqPermutation.cpp
	$(CMD_CMP) -c seqPermutation.cpp -O

		 seqPermutation2.o: point.o randomNumberGenerator.o seqPermutation.h seqPermutation2.cpp
	$(CMD_CMP) -c seqPermutation2.cpp -O
	
     configFileHandler.o: point.o $(SHAREDLIB)configFileHandler.cpp $(SHAREDLIB)configFileHandler.h
	$(CMD_CMP) -c $(SHAREDLIB)configFileHandler.cpp -O
	
     point.o: $(SHAREDLIB)point.cpp $(SHAREDLIB)point.h 
	$(CMD_CMP) -c $(SHAREDLIB)point.cpp -O

     randomNumberGenerator.o: $(SHAREDLIB)randomNumberGenerator.cpp $(SHAREDLIB)randomNumberGenerator.h $(SHAREDLIB)definitions.h
	$(CMD_CMP) -c $(SHAREDLIB)randomNumberGenerator.cpp -O $(LIBS)
	
     utilities.o: residue.o $(SHAREDLIB)utilities.cpp $(SHAREDLIB)utilities.h
	$(CMD_CMP) -c $(SHAREDLIB)utilities.cpp -O	
	
     pwd2file: residue.o utilities.o pwd2file.o
	$(CMD_CMP) -o pwd2f residue.o utilities.o pwd2file.o -O $(LIBS)
     pwd2file.o: residue.o utilities.o pwd2file.cpp
	$(CMD_CMP) -c pwd2file.cpp -O

     enumerate: point.o noFixedstructEnumeration.o
	$(CMD_CMP) -o noFixedStructEnum point.o noFixedstructEnumeration.o -O $(LIBS)
	
     noFixedstructEnumeration.o: point.o noFixedstructEnumeration.cpp
	$(CMD_CMP) -c noFixedstructEnumeration.cpp -O
     
     clean:
	rm $(OBJS_SEEKER) 

     backup:
	cp *.cpp *.h Makefile backupdir
		 
     copybin:
	mkdir ../bin; cp ./skaV21 ./noFixedStructEnum ./seqperm ../bin/

