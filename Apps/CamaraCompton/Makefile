BINARY = camaracompton
CDIR = src
ODIR = obj
HDIR = inc
ELF  = $(BINARY)


Objects = $(ODIR)/RootImprove.o $(ODIR)/Procesador.o $(ODIR)/AnalisisImagen.o


ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)

all: $(ELF)
$(ELF): camaracompton.cpp $(Objects)
	g++ -ggdb -o $@ camaracompton.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)

$(ODIR)/RootImprove.o:  $(CDIR)/RootImprove.cpp $(HDIR)/RootImprove.h
	g++ -ggdb -o $@ $(CDIR)/RootImprove.cpp -c $(ROOTFLAGS) 

$(ODIR)/Procesador.o: $(CDIR)/Procesador.cpp  $(HDIR)/Procesador.h 
	g++ -ggdb -o $@ $(CDIR)/Procesador.cpp -c $(ROOTFLAGS) 

$(ODIR)/AnalisisImagen.o: $(CDIR)/AnalisisImagen.cpp $(HDIR)/AnalisisImagen.h  
	g++ -ggdb -o $@ $(CDIR)/AnalisisImagen.cpp -c $(ROOTFLAGS)

clean:	
	rm -rf $(ELF) *~ $(ODIR)/*.o $(CDIR)/*~ $(HDIR)/*~ out/*.jpg
