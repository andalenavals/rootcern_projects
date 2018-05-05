Target = fitterplotter comparesimexp
ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)
all: $(Target)
fitterplotter: fitterplotter.cpp RootImprove.h Procesador.h
	g++ -o $@ fitterplotter.cpp $(ROOTFLAGS) $(ROOTLIBS)
comparesimexp: comparesimexp.cpp RootImprove.h Procesador.h
	g++ -o $@ comparesimexp.cpp $(ROOTFLAGS) $(ROOTLIBS)
clean:	
	rm -f $(Target)
