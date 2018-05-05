BINARY = tgraph-plot tgraph-datos th1-datos tf1-plot tgraphpolar-plot
CDIR = src
ODIR = obj
HDIR = inc
ELF  = $(BINARY)


Objects = $(ODIR)/RootImprove.o $(ODIR)/Procesador.o $(ODIR)/AnalisisImagen.o


ROOTFLAGS = $(shell root-config --cflags) 
ROOTLIBS  = $(shell root-config --libs)

all: $(ELF)
tgraph-plot: tgraph-plot.cpp $(Objects)
	g++ -ggdb -o $@ tgraph-plot.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)
tgraph-datos: tgraph-datos.cpp $(Objects)
	g++ -ggdb -o $@ tgraph-datos.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)
th1-datos: th1-datos.cpp $(Objects)
	g++ -ggdb -o $@ th1-datos.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)
tf1-plot: tf1-plot.cpp $(Objects)
	g++ -ggdb -o $@ tf1-plot.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)
tgraphpolar-plot: tgraphpolar-plot.cpp $(Objects)
	g++ -ggdb -o $@ tgraphpolar-plot.cpp $(ROOTFLAGS) $(ROOTLIBS) $(Objects)




$(ODIR)/RootImprove.o:  $(CDIR)/RootImprove.cpp $(HDIR)/RootImprove.h
	g++ -ggdb -o $@ $(CDIR)/RootImprove.cpp -c $(ROOTFLAGS) 

$(ODIR)/Procesador.o: $(CDIR)/Procesador.cpp  $(HDIR)/Procesador.h 
	g++ -ggdb -o $@ $(CDIR)/Procesador.cpp -c $(ROOTFLAGS) 

$(ODIR)/AnalisisImagen.o: $(CDIR)/AnalisisImagen.cpp $(HDIR)/AnalisisImagen.h 
	g++ -ggdb -o $@ $(CDIR)/AnalisisImagen.cpp -c $(ROOTFLAGS)

clean:	
	rm -rf $(ELF) *~ $(ODIR)/*.o $(CDIR)/*~ $(HDIR)/*~ out/*.jpg
