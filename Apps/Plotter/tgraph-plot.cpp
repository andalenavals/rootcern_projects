#include "inc/Procesador.h"
#include "inc/RootImprove.h"
#include "TROOT.h"
#include "inc/NuclearFunctions.h"

using namespace std;

int main(int argc, char** argv ){
 
  RootImprove R; 
  TStyle * AStyle = new TStyle("Andres", "");
  R.DefinirEstilo(AStyle);
  AStyle->cd();
  TCanvas *c2 = new TCanvas ("c2","",800,600);
  R.DefinirCanvas(c2);
  c2->cd();
  

  
  //**********************************************************************************
  //***************DEPENDENCIA CON LA DISTANCIA QUE VIAJA EL FOTON********************
  //**********************************************************************************
  /*
  double r, x, teta, c,f;
  TLegend leg( 0.57,0.35,0.8, 0.8,""); //Lateral Derecha
  TString sleg [24]; 
  sleg [0]= "r = 5 cm";   sleg [1]= "r = 15 cm";  sleg [2]= "r = 25 cm";
  sleg [3]= "r = 35 cm";  sleg [4]= "r = 45 cm";  sleg [5]= "r = 55 cm";  
  sleg [6]= "r = 65 cm";  sleg [7]= "r = 75 cm";  sleg [8]= "r = 95 cm";
  sleg [9]= "r = 105 cm";
  int puntos = 70;
  int ngrapgh = 10;
  TGraph *g[10] ;
  for (int i = 0; i < 10; ++i)
      g[i] = new TGraph(1);
  for(int j= 0 ; j< 10 ; j++)
    {
      r=5*(2*j+1);
      for(int i=0; i<puntos ; i++){
	x=i*0.5;
	teta= x/sqrt(pow(x,2)+r);
	c= TMath::Cos(teta);
	f= 13./9. -3*TMath::Log(3) + 3*TMath::Log(2+c) -2*c- (pow(c,2)/(2+c)) -0.5*pow((1+c)/(2+c),2); 
	g[j]->SetPoint(i, x, -f);
      }
      R.DefinirTGraph( g[j] , R.MarkerStyle(j) ,  0.5 , R.Color(j) , R.Color(j) );
      leg.AddEntry(g[j] , sleg[j] , "L");    
    }
  
  R.DefinirTitulos(g[0] ,"",  "Profundidad [cm]" , "f(511 keV)/#pi r_{e}^{2}" );
  R.DefinirEjes(g[0],0,34.6);
  g[0]->Draw("APC");

  for (int i = 1; i < 10; ++i)
      g[i]->Draw("pc same");
  leg.Draw();


  c2->Print("plot1.eps");
  */

  

  //**********************************************************************************
  //***************DEPENDENCIA CON LA ENERGIA QUE VIAJA EL FOTON**********************
  //**********************************************************************************
  /*
  TGraph *g2 = new TGraph(1);
  int puntos2 = 100;
  double e, f2;

  for(int i=1; i<puntos2 ; i++){
    e=i*0.02;
    f2=(1/e)*(  ( 1- 2*(e+1)*pow(e,-2) )*TMath::Log((2*e+1)*pow(e+1,-1)) + (2/e) -pow(1+2*e,-1) -0.5*pow(2*e/(1+2*e),3) +0.5*pow( e/(1+e) ,2)  ); 
    g2->SetPoint(i-1,e,f2);
  }
  
  R.DefinirTitulos(g2 ,"", "Energia [#epsilon]" , "f(#epsilon)/#pi r_{e}^{2}" );
  R.DefinirTGraph(g2 , R.MarkerStyle(1) , 0.5, R.Color(1), R.Color(1) );
  g2->GetXaxis()->SetRangeUser(0,1.8);
  g2->Draw("APC");
  c2->Print("plot2.eps");
  */

  //**************************************************************
  //************************ KleinNishina DC *********************
  //**************************************************************
  /*
  double pi = TMath::Pi();
  TH1F *frame = gPad->DrawFrame(0, 0 , pi, 85);
  
  TAxis* a = frame->GetXaxis();
  TGaxis* ax = new TGaxis(-pi, gPad->GetUymin(), pi, gPad->GetUymin(), -pi, pi, 510);
  a->SetBinLabel(1,"0");
  a->SetBinLabel(500,"#pi/2");
  a->SetBinLabel(1000,"#pi");
  a->SetBit(TAxis::kLabelsHori);
  a->SetLabelSize(0.075);
  
  gPad->Modified();
  R.DefinirTitulos(frame, "",
		   "#theta", "#frac{d#sigma_{K}}{d#Omega} [mb^{2}]" );
  TGraph *g[6];
  TLegend * leg = new TLegend( 0.4,0.7,0.6, 0.9,""); //Lateral Derecha
  R.DefinirLegend(leg, 2, kWhite , 0.03 );
  const TString sleg[] = {"E_{#gamma} = 2 keV","E_{#gamma} = 10 keV", "E_{#gamma} = 50 keV","E_{#gamma} = 200 keV","E_{#gamma} = 511 keV","E_{#gamma} = 1000 keV",};
  const double e[]={2.0, 10., 50, 200., 511. , 1000}; //keV
  int npoints = 100;
  double min=0.;  
  double max=2.*TMath::Pi();
  double theta;
  for (int j = 0; j < 6; j++) {
    g[j]  = new TGraph(1);
    R.DefinirTGraph(g[j] , R.MarkerStyle(1) , 0.2, 2, R.Color(j), R.Color(j) );
    for(int i=1; i< npoints ; i++){
      theta = min+i*(max-min)/npoints;
      g[j]->SetPoint(i-1, theta , KleinNishinaDC(theta, e[j]));
    }
    leg->AddEntry(g[j] , sleg[j]  , "L");
    g[j]->Draw("L");
  }

  leg->Draw();
  c2->Print("plot.tex");
  c2->Print("plot.eps");
  */
 

  
  //**************************************************************
  //***************** Energy gamma posterior *********************
  //**************************************************************
 
  double pi = TMath::Pi();
  TH1F *frame = gPad->DrawFrame(0, 0 , pi, 1100);
  TAxis* a = frame->GetXaxis();
  TGaxis* ax = new TGaxis(-pi, gPad->GetUymin(), pi, gPad->GetUymin(), -pi, pi, 510);
  a->SetBinLabel(1,"0");
  a->SetBinLabel(500,"#pi/2");
  a->SetBinLabel(1000,"#pi");
  a->SetBit(TAxis::kLabelsHori);
  a->SetLabelSize(0.075);
  gPad->Modified();
  R.DefinirTitulos(frame, "",
		   "#theta", "E'_{#gamma} [keV]" );
  TGraph *g[6];
  
  TLegend * leg = new TLegend( 0.5,0.5,0.75, 0.7); //Lateral Derecha
  R.DefinirLegend(leg, 2, kWhite , 0.035 );
  const TString sleg[] = {"E_{#gamma} = 200 keV","E_{#gamma} = 511 keV","E_{#gamma} = 1000 keV"};
  const double e[]={200., 511. , 1000}; //keV
  int npoints = 100;
  double min=0.;  
  double max=2.*TMath::Pi();
  double theta;
  for (int j = 0; j < 3; j++) {
    g[j]  = new TGraph(1);
    R.DefinirTGraph(g[j] , R.MarkerStyle(1) , 0.2, 2, R.Color(j), R.Color(j) );
    for(int i=1; i< npoints ; i++){
      theta = min+i*(max-min)/npoints;
      g[j]->SetPoint(i-1, theta , EgammaP(theta, e[j]));
    }
    leg->AddEntry(g[j] , sleg[j]  , "L");
    g[j]->Draw("L");
  }

  leg->Draw();
  c2->Print("plot.tex");
  c2->Print("plot.eps");
    
 

 //**************************************************************
  //***************** Energy electron posterior *********************
  //**************************************************************
  /*
  double pi = TMath::Pi();
  TH1F *frame = gPad->DrawFrame(0, 0 , pi, 820);
  TAxis* a = frame->GetXaxis();
  TGaxis* ax = new TGaxis(-pi, gPad->GetUymin(), pi, gPad->GetUymin(), -pi, pi, 510);
  a->SetBinLabel(1,"0");
  a->SetBinLabel(500,"#pi/2");
  a->SetBinLabel(1000,"#pi");
  a->SetBit(TAxis::kLabelsHori);
  a->SetLabelSize(0.075);
  gPad->Modified();
  R.DefinirTitulos(frame, "",
		   "#theta", "K_{e} [keV]" );
  TGraph *g[6];
  
  TLegend * leg = new TLegend( 0.7,0.6,0.93, 0.8); //Lateral Derecha
  R.DefinirLegend(leg, 2, kWhite , 0.035 );
  const TString sleg[] = {"E_{#gamma} = 200 keV","E_{#gamma} = 511 keV","E_{#gamma} = 1000 keV"};
  const double e[]={200., 511. , 1000}; //keV
  int npoints = 100;
  double min=0.;  
  double max=2.*TMath::Pi();
  double theta;
  for (int j = 0; j < 3; j++) {
    g[j]  = new TGraph(1);
    R.DefinirTGraph(g[j] , R.MarkerStyle(1) , 0.2, 2, R.Color(j), R.Color(j) );
    for(int i=1; i< npoints ; i++){
      theta = min+i*(max-min)/npoints;
      g[j]->SetPoint(i-1, theta , KelectronP(theta, e[j]));
    }
    leg->AddEntry(g[j] , sleg[j]  , "L");
    g[j]->Draw("L");
  }

  leg->Draw();
  c2->Print("ePOST.tex"); 
  */

  
  return 0;

 }
 

/*
 Double_t xlist, ylist;
  for (int i = 0; i < 599; ++i)
    {
      W->GetPoint(i, xlist, ylist);
      cout<< xlist<< " "<< func->Eval(ylist/100)<<endl;
      W2->SetPoint(i, xlist, func->Eval(ylist) );
    }
*/


