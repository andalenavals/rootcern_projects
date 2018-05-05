#ifndef IMPROVE
#define IMPROVE 1

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TRandom.h"
#include "TLegend.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
#include "TString.h"
#include "TMatrix.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TMath.h"
#include "TColor.h"




using namespace std;

class RootImprove{
private:
  TStyle *AndresStyle= new TStyle("","");
public:
  RootImprove(void);
  ~RootImprove(void);
  void DefinirMarco (TH2D * & h, int bx, int by);
  void DefinirEstilo (void);
  void DefinirPalette (void);
  void Dibujar( TGraphErrors * , const char * title , const char * titlex ,const char * titley,  double xlow, double xup , double ylow, double yup  );
  void Dibujar( TGraphErrors * , const char* title ,const char* titlex  ,const char* titley , double xlow, double xup);
  void Dibujar( TGraphErrors * , const char* title ,const char* titlex  ,const char* titley );
  void Dibujar(TH1 * h, const char * title , const char * titlex ,const char * titley,  double xlow, double xup , double ylow, double yup  );
  void Dibujar(TH1 *, const char* title ,const char* titlex  ,const char* titley , double xlow, double xup);
  void Dibujar(TH1 *, const char* title ,const char* titlex  ,const char* titley );
  void Dibujar(TH2 * h, const char * title , const char * titlex ,const char * titley,  double xlow, double xup , double ylow, double yup , const char * modo, int color  ); 
  void Dibujar(TH2 *, const char* title ,const char* titlex  ,const char* titley , const char * modo, int color);
  int GenerarSemilla(void);
  int GetMaximumBin(TH1 * h1, double xlow, double xup);
  double GetMaximumColumna(const char* argv, const char* col, const char* format);
  double GetMinimumColumna(const char* argv , const char* col, const char* format);
  int GetNumberFilas(const char* argv, const char* col, const char* format);
  int GetNumberOfDecimals(double a); //Solo funciona con doubles de hasta 6 digitos
  double GetBinUpEdge(TH1 * h , int y ){return h->GetBinLowEdge(y) + h->GetBinWidth(y) ;};
  double GetXLow(TH1 * h){return h->GetBinLowEdge(1);};
  //  double GetXLow(TH2 * h){return h->GetBinLowEdge(1);};
  double GetXUp(TH1 * h){return GetBinUpEdge( h ,h->GetNbinsX() ) ;};
  // double GetXUp(TH2 * h){return GetBinUpEdge( h ,h->GetNbinsX() ) ;};
  TH1D * GuardarEnTH1(const char* argv, const char* name);
  TH1D * GuardarEnTH1(const char* argv  , const char* name, int , double , double );
  TH2D * GuardarEnTH2(const char* argv  , const char* name, int nbinx , double xlow , double xup, int nbiny, double ylow, double yup);
  TTree * GuardarEnTTree(const char* argv, const char* name, const char* title, const char* format);
  void ImprimirAjuste(double x0, double y0 );
  void ImprimirEnArchivoTexto(TH1 * , const char* name);
  void ImprimirAllPalette(TH2D *h2,  TCanvas * c2,TString modo );
  double Integrar(TH1 * h);
  double Integrar(TH1 * h, double xlow, double xup);
  void SuperponerHistogramas(TH1 * h1 , TH1 * h2);
  void SuperponerHistogramas(TH1 * h1 , TH1 * h2, const char* title ,const char* titlex  ,const char* titley , double xlow, double xup);
  TH1D * ToD( TH1 * h);//Convertir histograma int a double
};

RootImprove::RootImprove(void)
{

}

RootImprove::~RootImprove(void)
{
  
}
void RootImprove::DefinirEstilo(void)
{
  TGaxis::SetMaxDigits(5);
  AndresStyle->SetOptStat(kFALSE); //NO imprimir la informacion estadistica 
  AndresStyle->SetOptDate(0); //Fecha
  AndresStyle->SetOptFile(0);
  // AndresStyle->SetOptFit(11);  //Informacion de Fit
  AndresStyle->SetStatColor(0);
  //AndresStyle->SetStatX(0.82);
  // AndresStyle->SetStatY(0.31);
  AndresStyle->SetStatBorderSize(0);
  // AndresStyle->SetFitFormat("#11.2e");
  AndresStyle->SetCanvasColor(0); // Lienzo
  AndresStyle->SetFrameFillColor(0); //Region entre ejes
  AndresStyle->SetPadBorderMode(0);  
  AndresStyle->SetTitleFillColor(0); //Color de relleno cajita titulo
  AndresStyle->SetTitleBorderSize(0); // activar cajita titulo
  AndresStyle->SetTitleOffset(0.8 , "x"); //titulos ejes
  AndresStyle->SetTitleOffset(0.8 , "y");
  // AndresStyle->SetTitleOffset(1.5 , "z");
  AndresStyle->SetTitleSize(0.065, "x"); //Tamaño titulos ejes
  AndresStyle->SetTitleSize(0.065, "y");
  AndresStyle->SetLegendBorderSize(0); //Sin borde el legend
  AndresStyle->SetLegendFillColor(0); //Cuadra para referencias de Th1 o TF1
  AndresStyle->SetNdivisions(500 +10, "x"); //n = primarias + 100*secundarias + 10000*terciarias
  AndresStyle->SetNdivisions(500 +10, "y");
  AndresStyle->SetNdivisions(500 +5, "z");
  AndresStyle->SetLabelSize(0.03 , "x"); //Tamaño numero de los ejes
  AndresStyle->SetLabelSize(0.03 , "y"); 
  AndresStyle->SetLabelSize(0.03 , "z");
  // AndresStyle->SetLabelOffset(0.05 , "x");
  // AndresStyle->SetLabelOffset(0.05 , "y");
  // AndresStyle->SetLabelOffset(0.05 , "z");
  // AndresStyle->SetFuncStyle(1);
  //AndresStyle->SetFuncWidth(1); // Grosor de las lineas de las funciones
  //AndresStyle->SetFuncColor(1); //Color linea de las funciones
  // AndresStyle->SetLineColor(4); //Histogramas
  // AndresStyle->SetMarkerStyle(10); // TGraph
  // AndresStyle->SetMarkerSize(0.5);
  // AndresStyle->SetMarkerColor(1);
  // AndresStyle->SetOptLogy();
  // AndresStyle->SetOptLogx();
  // La funcion de fit no depende si esta en escala logaritmica


  AndresStyle->cd();
}


void RootImprove::DefinirMarco (TH2D * & h, int bx, int by)
{
  for (int i = 1; i < h->GetNbinsX(); ++i)
    for (int j = 1; j < by; ++j)
      {
	h->SetBinContent(i, j, 0);
	h->SetBinContent(i, h->GetNbinsY()-j, 0);
      }
  
  for (int j = 1; j < h->GetNbinsY(); ++j)
    for (int i = 1; i <= bx; ++i)
    {
      h->SetBinContent(i, j, 0);
      h->SetBinContent(h->GetNbinsX()-i, j, 0);
    }
}


void RootImprove::DefinirPalette(void)
{
  const Int_t NRGBs = 5;  
  const Int_t NCont = 300; 


  //BANDERA COLOMBIANA
  /*
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  */
  
  //ROJO AZUL NEGRO
  /*
  Double_t stops[NRGBs] = { 0.00, 0.25, 0.5, 0.75, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.0, 0.75, 1.00 };
  Double_t green[NRGBs] = { 0.00, 0.00, 0.0, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.00, 0.2, 1.0, 0.00, 0.00 };
  */
  
  //ROJO AZUL BLANCO
  /*
  Double_t stops[NRGBs] = { 0.00, 0.25, 0.5, 0.75, 1.00 };
  Double_t red[NRGBs]   = { 1.00, 0.6, 0.0, 0.75, 1.00 };
  Double_t green[NRGBs] = { 1.00, 0.6, 0.0, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 1.00, 0.7, 1.0, 0.00, 0.00 };
  */

  //ROJO AZUL BLANCO GRADIENTE
  Double_t stops[NRGBs] = { 0.00, 0.25, 0.5, 0.75, 1.00 };
  Double_t red[NRGBs]   = { 1.00, 0.6, 0.3, 0.20, 0.10 };
  Double_t green[NRGBs] = { 1.00, 0.8, 0.5, 0.40, 0.30 };
  Double_t blue[NRGBs]  = { 1.00, 0.8, 0.6, 0.50, 0.4 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  AndresStyle->SetNumberContours(NCont);
}



void RootImprove::Dibujar(TGraphErrors * h, const char * title , const char * titlex ,const char * titley,  double xlow, double xup , double ylow, double yup  )
{
  h->GetYaxis()->SetRangeUser(ylow , yup);
  h->GetXaxis()->SetLimits(xlow , xup);
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  h->Draw("ap");
}

void RootImprove::Dibujar(TGraphErrors * h, const char * title , const char * titlex ,const char * titley )
{
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  h->Draw("ap");
}

void RootImprove::Dibujar(TGraphErrors * h, const char * title , const char * titlex ,const char * titley , double xlow, double xup)
{
  h->GetXaxis()->SetLimits(xlow , xup);
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  //h->SetMarkerStyle(10);
  //h->SetMarkerSize(0.5);
  //  h->SetMarkerColor(1);
  h->Draw("ap");
}

void RootImprove::Dibujar(TH1 * h, const char * title , const char * titlex ,const char * titley  )
{
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  // h->SetLineColor(1);
  h->Draw("");
}

void RootImprove::Dibujar(TH1 * h, const char * title , const char * titlex ,const char * titley,  double xlow, double xup)
{
  h->GetXaxis()->SetRangeUser(xlow , xup);
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  // h->SetLineColor(1);
  h->Draw("");
}

void RootImprove::Dibujar(TH1 * h, const char * title , const char * titlex ,const char * titley,  double xlow, double xup , double ylow, double yup  )
{
  h->GetYaxis()->SetRangeUser(ylow , yup);
  h->GetXaxis()->SetRangeUser(xlow , xup);
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  // h->SetLineColor(1);
  h->Draw("");
}

void RootImprove::Dibujar(TH2 * h, const char * title , const char * titlex ,const char * titley, double xlow, double xup, double ylow, double yup, const char * modo, int color )
{
  AndresStyle->SetPalette( color );
  h->GetYaxis()->SetRangeUser(ylow , yup);
  h->GetXaxis()->SetRangeUser(xlow , xup);
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  h->Draw(modo);
}

void RootImprove::Dibujar(TH2 * h, const char * title , const char * titlex ,const char * titley , const char * modo, int color  )
{
  AndresStyle->SetPalette( color );
  h->SetTitle(title);
  h->GetYaxis()->SetTitle(titley);
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitle(titlex);
  h->GetXaxis()->CenterTitle();
  h->SetLineColor(1);
  h->Draw(modo);
}

int RootImprove::GenerarSemilla(void)
{
  time_t t;
  struct tm birthday;
  birthday.tm_hour = 16;
  birthday.tm_min  = 0;
  birthday.tm_sec  = 0;
  birthday.tm_year = 93;
  birthday.tm_mon  = 12;
  birthday.tm_mday = 22;

  time(&t);
  int sec =  difftime( t, mktime( &birthday ) );
  return sec;
}

int RootImprove::GetMaximumBin(TH1 * h, double xlow, double xup)
{
  //Generalizar cuando haya mas de un maximo
  /*
  h->GetXaxis()->SetRangeUser(xlow , xup);
  return   h->GetMaximumBin() ;
  */
  
  int binmax;
  double content=0;
  for (int i = h->FindBin(xlow); i <= h->FindBin(xup) ; i++)
    {
      if(h->GetBinContent(i)> content )
	{
	content = h->GetBinContent(i);
	binmax = i;
	}
    }
  return binmax;
}

double RootImprove::GetMaximumColumna(const char* argv, const char* col, const char* format )
{
  TTree *temp = GuardarEnTTree(argv, "temp" , "temp" , format);
  temp->Print();
  return temp->GetMaximum(col);
}

double RootImprove::GetMinimumColumna(const char* argv, const char* col, const char* format )
{
  TTree * temp = GuardarEnTTree(argv, "temp" , "temp" , format);
  temp->Print();
  return temp->GetMinimum(col);
}

int RootImprove::GetNumberFilas(const char* argv,const char* col, const char* format)
{
  int entries;
  TTree * temp = GuardarEnTTree(argv, "temp" , "temp" , format);
  temp->Print();
  entries= (int) temp->GetEntries();
  return entries;
 
}

int RootImprove::GetNumberOfDecimals(double a)
{
  ostringstream tina;
  string banera;
  tina << a;
  banera = tina.str();
  int pos2= banera.length();
  int pos = banera.find(".");
  //cout<< pos <<" "<< pos2<<endl;
  return pos2-(pos+1);

}

TH1D * RootImprove::GuardarEnTH1(const char* argv, const char* name)
{
  return GuardarEnTH1(argv, name, GetNumberFilas(argv, "x", "x:y"), GetMinimumColumna(argv, "x", "x:y"), GetMaximumColumna(argv, "x", "x:y"));
}


TH1D * RootImprove::GuardarEnTH1(const char* argv, const char* name , int nbin, double xlow, double xup)
{
  TH1D *h= new TH1D (name , "", nbin , xlow , xup);
  ifstream file;
  double column1, column2;  
  file.open (  argv , std::ios::in );
  while( file >> column1 >> column2){
    h->SetBinContent( h->FindBin(column1) ,column2);
    //Si column1 cae en borde se mete a bin de la derecha.
  } 
  return h;
}

TH2D * RootImprove::GuardarEnTH2(const char* argv  , const char* name, int nbinx , double xlow , double xup, int nbiny, double ylow, double yup)
{
  TH2D *h= new TH2D (name , "", nbinx , xlow , xup, nbiny, ylow, yup);
  ifstream file;
  double value;  
  file.open (  argv , std::ios::in );
  for (int j = 1; j <= nbiny; ++j)
    for (int i = 1; i <= nbinx; ++i)
      {
	file >> value;
	h->SetBinContent(i, j, value);

      }
  return h;
}

TTree * RootImprove::GuardarEnTTree(const char* argv, const char* name, const char* title, const char* format)
{
  TTree *t = new TTree(name, title);
  t->ReadFile(argv,format);
  return t;
}


void RootImprove::ImprimirAjuste(double x0, double y0)
{ 
  TLatex latex;
  latex.SetTextSize(0.04);
  latex.SetTextAlign(13);  //align at top
  latex.DrawLatex(x0, y0 ,"#lambda = 0.2300(4)Pixeles + 173.8(8)");
}

void RootImprove::ImprimirEnArchivoTexto(TH1 * h, const char * name)
{
  ofstream file;
  file.open( name );
  for(int i=1; i<= h->GetNbinsX() ;i++){
    file << i <<" " << h->GetBinContent(i) <<endl;
  }
  file.close();
     
}

void RootImprove::ImprimirAllPalette( TH2D *h2,  TCanvas * c2, TString modo )
{
  TString name; 
  for (int i = 1; i <= 112; ++i)
    {
      name+=i;
      name.Append(".jpg");
      Dibujar(h2,"","","",modo, i); //BOX, COL2Z, CONT0, CONT4
      c2->Print(name);
      name.Clear();
    }     
}

double RootImprove::Integrar(TH1 * h)
{
  //return h->GetEffectiveEntries();
  double suma=0;
  for (int i = 1; i <= h->GetNbinsX() ; i++)
    suma+=h->GetBinContent(i);
  return suma;
   
}

double RootImprove::Integrar(TH1 * h, double xlow, double xup)
{
  //return h->GetEffectiveEntries();
  double suma=0;
  for (int i = h->FindBin(xlow); i <= h->FindBin(xup) ; i++)
    suma+=h->GetBinContent(i);
  return suma;
   
}

void RootImprove::SuperponerHistogramas(TH1 * h1 , TH1 * h2 )
{
  
  if(h1->GetMaximum() > h2->GetMaximum())
    {
      h1->SetLineColor(1);
      h2->SetLineColor(2);
      h1->Draw("");
      h2->Draw("same");
    }
  else
    {
      h1->SetLineColor(2);
      h2->SetLineColor(1);
      h2->Draw("");
      h1->Draw("same");
    }

  TLegend * leg= new TLegend( 0.6,0.7,0.80,0.8,"");
  leg->AddEntry( h1, h1->GetName(), "L");
  leg->AddEntry( h2, h2->GetName(), "L");
  leg->Draw();
 
}

void RootImprove::SuperponerHistogramas(TH1 * h1, TH1 * h2, const char * title, const char * titlex, const char * titley, double xlow, double xup )
{
  
  if(h1->GetMaximum() > h2->GetMaximum())
    {
      h1->GetXaxis()->SetRangeUser(xlow , xup);
      h1->SetTitle(title);
      h1->GetYaxis()->SetTitle(titley);
      h1->GetYaxis()->CenterTitle();
      h1->GetXaxis()->SetTitle(titlex);
      h1->GetXaxis()->CenterTitle();
      h1->SetLineColor(1);
      h2->SetLineColor(2);
      h1->Draw("");
      h2->Draw("same");
    }
  else
    {
      h2->GetXaxis()->SetRangeUser(xlow , xup);
      h2->SetTitle(title);
      h2->GetYaxis()->SetTitle(titley);
      h2->GetYaxis()->CenterTitle();
      h2->GetXaxis()->SetTitle(titlex);
      h2->GetXaxis()->CenterTitle();
      h1->SetLineColor(2);
      h2->SetLineColor(1);
      h2->Draw("");
      h1->Draw("same");
    }

  // TLegend * leg= new TLegend( 0.2,0.7,0.40,0.8,"");
  TLegend * leg= new TLegend( 0.6,0.7,0.80,0.8,"");
  leg->AddEntry( h1, h1->GetName(), "L");
  leg->AddEntry( h2, h2->GetName(), "L");
  leg->Draw();
 
}

TH1D * RootImprove::ToD( TH1 * h)
{
  TH1D *hd= new TH1D ( "", ""  , h->GetNbinsX() , GetXLow(h) , GetXUp(h) );
  for(int i=1; i<= h->GetNbinsX(); i++)
    {
      hd->SetBinContent( i ,h->GetBinContent(i) );
    }
  return hd;
}


#endif
