#include "inc/Procesador.h"
#include "inc/RootImprove.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char** argv ){

  //TApplication theApp("tapp", &argc, argv);
  //theApp.Run();
  RootImprove R;
  TStyle * AStyle = new TStyle("Andres", "");
  R.DefinirEstilo(AStyle);
  AStyle->cd();
  TCanvas *c2 = new TCanvas ("c2","",800,600);
  R.DefinirCanvas(c2);
  c2->cd();
  
  //*****************************************************************
  //*******DEPENDENCIA CON EL ANGULO DE LA SECCION EFICAZ************
  //******************************511keV*****************************
  /*
  const char* formula = "TMath::Cos(x)+ 3*TMath::Log((2-TMath::Cos(x))/3) + 3/(2-TMath::Cos(x)) + 0.5/TMath::Power(2-TMath::Cos(x),2) - (1/18)";
  TF1 * F1 = new TF1 ("funcion", formula, 0, 2*TMath::Pi());
  R.DefinirTitulos(F1 ,"",  "#theta_{0} " , "(f(E_{#gamma})/#pi r_{e}^{2}" );
  // R.DefinirEjes(F1,0,34.6);
  F1->Draw("");
  c2->Print("plot1.eps");
  */
  
 

  //*****************************************************************
  //****DEPENDENCIA CON LA ENERGIA DE LA SECCION EFICAZ**************
  //****************************Detector Infinito*******************

  /*
  const char* formula = "(1-(2/x) -(2/(x*x)) )*(TMath::Log( (1+2*x)/(1+x))) + ((4+22*x+44*x*x+35*x*x*x+8*x*x*x*x)/(2*x*(1+x)*(1+x)*(1+2*x)*(1+2*x))) ";
  TF1 * F1 = new TF1 ("funcion", formula, 0, 10);
  R.DefinirTitulos(F1 ,"",  "E_{#gamma}/511 keV " , "f(E_{#gamma})/#pi r_{e}^{2}" );
  // R.DefinirEjes(F1,0,34.6);
  F1->Draw("");
  c2->Print("plot1.eps");
  */
 
  //******************************************************************
  //***********RETRODISPERSADOS VS PROFUNDIDAD DEL MATERIAL **********
  //*****************************Detector Infinito********************
  
  /*
  double t0 = TMath::Pi()*0.5;
  double tf = TMath::Pi();
  double mu = 2 ;
  double mu1 = 1 ;
  */
  



  

  
  return 0;
 }



