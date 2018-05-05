#include "inc/Procesador.h"
#include "inc/RootImprove.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char** argv ){

  RootImprove R;
  TStyle * AStyle = new TStyle("Andres", "");
  R.DefinirEstilo(AStyle);
  AStyle->cd();
  TCanvas *c2 = new TCanvas ("c2","",800,600);
  R.DefinirCanvas(c2);
  c2->cd();
  
  TString sleg [24];
  
  sleg [0]= "#lambda = 587.57(23) [nm]"; 
  sleg [1]= "#lambda = 667.84(23) [nm]";  
  sleg [2]= "#lambda = 705.79(23) [nm]"; 
  
  int numfiles = argc -1; 
  TLegend *leg= new TLegend( 0.18,0.6,0.5,0.8);//sup-izq
  
  //Formato x y dx dy
  TGraphErrors * W[numfiles];
  for (int i = 0; i < numfiles ; i++)
    {
      W[i]= new TGraphErrors(argv[i+1]);
      R.DefinirTGraph(W[i], R.MarkerStyle(i) , 0.5, 5,  R.Color(i), R.Color(i));
      leg->AddEntry(W[i] , argv[i+1] , "P");
      //leg->AddEntry(W[i] , sleg[i] , "P");
    }
  
  R.DefinirTitulos(W[0],"", "Velocity [m/s]", "radius ratio " );
  R.DefinirEjes(W[0], 0.8 , 1.5 , 0 , 0.5 ); 
  W[0]->Draw("AP");
  for (int i = 1; i < numfiles; i++)
    {
      W[i]->Draw("same p");
    }
  // leg->Draw();

 
  //FIT
  // W[0]->Fit("pol1","", "", 3000, 3500); //po+p1x
  // W[0]->Fit("pol2","", "", 0.8, 1.5); //po+p1x+p2x*x
  // W[0]->Fit("expo", "", "", 1000, 4000); //exp(po+p1x)
  // W[0]->Fit("gaus", "", " ", 1000, 4000);
  // W[0]->Fit("gausn", "", " ", 1000, 4000);
 
  /*
  TF1 * f = new TF1("GauS","[0]*TMath::Gaus(x, [1], [2])+[3]*TMath::Sin([4]*x) ", 0, 4000);
  R.DefinirTF1(f, 3, 10, kRed);
  f->SetParName(0, "Amplitud Gausiana");
  f->SetParName(1, "Media");
  f->SetParName(2, "Sigma");
  f->SetParName(3, "Amplitud Sin");
  f->SetParName(4, "frecuencia");
  //f->SetParameter(0 , 1);
  f->SetParameters(0.45 , 2507 , 560, 0.05, 3);
  f->SetParLimits(0, 0, 1);
  f->SetParLimits(1, 0, 4000);
  f->SetParLimits(2, 0, 4000);
  f->FixParameter(3, 0.05);
  f->FixParameter(4, 0.2);
  //f->Draw("same");
  W[0]->Fit("GauS", "", " ", 1000, 4000);
  R.DibujarAjuste(500, 0.55, "#lambda = 0.2300(4)Pixeles + 173.8(8)");
  */

  
  /*
  TF1 * f = new TF1("test","[0]*TMath::Power(x, [1])+[2] ", 0.8, 1.5);
  // R.DefinirTF1(f, 3, 10, kRed);
  f->SetParName(0, "Max Velocity");
  f->SetParName(1, "n");
  f->SetParName(2, "slope");
  //f->SetParName(2, "Sigma");
  // f->SetParName(3, "Amplitud Sin");
  //f->SetParName(4, "frecuencia");
  //f->SetParameter(0 , 1);
  f->SetParameters(-3.0, 0.2, 0.5);
  // f->SetParLimits(0, 0, 1);
  //f->SetParLimits(1, 0, 4000);
  //f->SetParLimits(2, 0, 4000);
  //f->FixParameter(3, 0.05);
  //f->FixParameter(4, 0.2);
  //f->Draw("same");
  W[0]->Fit("test", "", " ", 0.8, 1.5);
  */
  
  
  
  
  c2->Print("plot4.eps");  
 
  
  return 0;

 }

  // La funcion de fit no depende si esta en escala logaritmica






