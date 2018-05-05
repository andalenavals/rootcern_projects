#include "inc/RootImprove.h"
#include "inc/Procesador.h"
#include "inc/AnalisisImagen.h"

using namespace std;

int main(int argc, char** argv ){

 
  RootImprove R;  Procesador p; AnalisisImagen A;
  TStyle * AStyle= new TStyle("Andres","");
  R.DefinirEstilo(AStyle);
  AStyle->cd();
  TCanvas *c2 = new TCanvas ("c2","",1000,1000);
  R.DefinirCanvas(c2);
  c2->cd();
  TH2D *h2 = R.GuardarEnTH2(argv[1],"Experimento", 62 , 0.5 , 62.5, 62, 0.5, 62.5);
  TH2D *fondo = R.GuardarEnTH2(argv[2],"Fondo", 62 , 0.5 , 62.5, 62, 0.5, 62.5);
  h2->Add(fondo, -1);
  h2->Smooth(1);

  //R.DefinirPalette(AStyle);
  //h2->Draw("COLZ");
  // R.Dibujar(h2, "COLZ", AStyle, 1 );
  //c2->Print("test.jpg");

 
  //TH2D *h2g = A.GradientRobert(h2);
  //TH2D *h2g = A.Gradient1(h2);
  //TH2D *h2g = A.GradientPrewitt(h2);
  //TH2D *h3g = A.GradientSobel(h2);
  // h3g->Smooth(1);

  //TH2D *h2g = A.Laplacian(h2);
  //h2->Add(h2g, 1);
  R.DefinirTitulos(h2, "Suavizado resta region abolladura y cercana","","");
  R.ImprimirAllPalette(h2, c2, "COLZ", AStyle ) ;
  
 
  return 0;
}
