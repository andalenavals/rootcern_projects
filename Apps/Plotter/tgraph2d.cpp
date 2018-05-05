#include "TCanvas.h"
#include "TMath.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMarker.h"
#include "TH1.h"
#include "TStyle.h"
#include "TLatex.h"
#include <TGraph2D.h>
#include <TFormula.h>
#include <TF1.h>
#include <TVector.h>

using namespace std;
   

int main(int argc, char** argv){
 


  //**********************Estilo y Canvas***** ***********************
  //******************************************************************

  
  TStyle *ANDRESTYLE= new TStyle("","");
  ANDRESTYLE->SetOptStat(kFALSE); //NO imprimir la informacion estadistica en caja
  // ANDRESTYLE->SetOptDate(1);
  //ANDRESTYLE->SetOptFile(1);
  // ANDRESTYLE->SetOptFit(1); 
  ANDRESTYLE->SetCanvasColor(0); // Lienzo
  ANDRESTYLE->SetFrameFillColor(0); //Region entre ejes
  ANDRESTYLE->SetPadBorderMode(1); 
  ANDRESTYLE->SetStatBorderSize(0);
  ANDRESTYLE->SetTitleFillColor(0); //Color de relleno cajita titulo
  ANDRESTYLE->SetTitleBorderSize(0); // activar cajita titulo
  ANDRESTYLE->SetTitleOffset(2.1 , "x"); //titulos ejes
  ANDRESTYLE->SetTitleOffset(2.1 , "y");
  ANDRESTYLE->SetTitleOffset(1.5 , "z");
  ANDRESTYLE->SetLegendBorderSize(2); //
  ANDRESTYLE->SetLegendFillColor(0); //Cuadra para referencias de Th1 o TF1
  ANDRESTYLE->SetNdivisions(500 +5, "x"); //2 divisiones primarias 5 secundarias
  ANDRESTYLE->SetNdivisions(500 +5, "y");
  ANDRESTYLE->SetNdivisions(500 +5, "z");
  ANDRESTYLE->SetLabelSize(0.03 , "x"); //Tamaño numero de los ejes
  ANDRESTYLE->SetLabelSize(0.03 , "y"); 
  ANDRESTYLE->SetLabelSize(0.03 , "z");
  //ANDRESTYLE->SetLabelOffset(0.05 , "x");
  //ANDRESTYLE->SetLabelOffset(0.05 , "y");
  //ANDRESTYLE->SetLabelOffset(0.05 , "z");
  ANDRESTYLE->SetFuncWidth(2); // Grosor de las lineas de las funciones
  ANDRESTYLE->SetFuncColor(4); //Color linea de las funciones
  ANDRESTYLE->SetMarkerStyle(10); // TGraph
  ANDRESTYLE->SetMarkerSize(0.5);
  ANDRESTYLE->SetMarkerColor(1);
  //ANDRESTYLE->SetOptLogy();
  //ANDRESTYLE->SetOptLogx();
  // La funcion de fit depende si esta en escala logaritmica
  ANDRESTYLE->cd();
  TGaxis::SetMaxDigits(2);
  
 
  TCanvas *c= new TCanvas("canvas","",500,500);
  c->SetBottomMargin( 0.15 );
  c->SetTopMargin( 0.15 );
  c->SetLeftMargin( 0.15 );
  c->SetRightMargin( 0.15 );
  
  c->cd();

  //*******************************************
  //***************CON ERRORES*****************
  //*******************************************
 
  // EL formato de los archivos de entrada es:
  // X   Y   DX    DY
  
  TGraph2D *W= new TGraph2D(argv[1]); 
  W->SetTitle("Trayectoria Balon");
  W->GetZaxis()->SetTitle("Z");
  W->GetZaxis()->CenterTitle();
  W->GetYaxis()->SetTitle("Y");
  W->GetYaxis()->CenterTitle();
  W->GetXaxis()->SetTitle(" X ");
  W->GetXaxis()->CenterTitle();
  W->SetMarkerStyle(10);
  W->SetMarkerSize(0.5);
  W->SetMarkerColor(2);
  W->SetMaximum(10);
  W->SetMinimum(0);
  //W->GetZaxis()->SetRangeUser(0,5);
  W->GetYaxis()->SetRangeUser(0,40);
  W->GetXaxis()->SetLimits(-20,20);
  
  W->Draw("P");
 

  TGraph2D *Cancha = new TGraph2D(1);
  for(int i=0; i < 100 ; i++){
    Cancha->SetPoint(i, 3.66  ,32 , 2.44*i/100.);
    Cancha->SetPoint(100+i, -3.66  ,32 , 2.44*i/100.);
    Cancha->SetPoint(200+i, -3.66+7.32*i/100  ,32 , 2.44);
  }
  Cancha->SetMarkerStyle(10);
  Cancha->SetMarkerSize(0.5);
  Cancha->SetMarkerColor(1);
  Cancha->Draw("P same");
  

  c->Print("Plot.pdf");

  return 0;
}
