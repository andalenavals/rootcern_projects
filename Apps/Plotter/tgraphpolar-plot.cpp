#include "TGraphPolar.h"
#include "inc/RootImprove.h"
#include "inc/NuclearFunctions.h"

int main(int argc, char** argv ){
  RootImprove R;
  TCanvas *c2 = new TCanvas ("c2","",800,800);
  c2->cd();

  std::vector<TGraphPolar*> vgP;
  
  const double e[]={2., 10., 50, 170., 511.}; //keV
  int npoints = 100 ;
  double min=0.;  
  double max=2.*TMath::Pi();
  double r[npoints];
  double theta[npoints];

  TGraphPolar *gPaux;

  for (int i = 0; i <= npoints; i++)
    theta[i]= min+i*(max-min)/npoints;
   
  for (int k = 0; k < 5; k++) {    
    for (int i = 0; i <= npoints; i++){
      r[i] = KleinNishinaDC(theta[i], e[k] );
      // std::cout <<r[i] <<" "<< theta[i]<<std::endl;
    }
    gPaux = new TGraphPolar(npoints+1,theta,r);
    R.DefinirTGraph(gPaux, 10, 0.3, 3, R.Color(k), R.Color(k) );
    gPaux -> SetTitle("");
    gPaux -> SetLineWidth(3);
    vgP.push_back( gPaux );

  }
  for (int k=0;k<5;k++)
    vgP[k]->Draw("L SAME");
 
  c2->Update();
  vgP[0] -> GetPolargram()->SetTextColor(8);
   //N = i*100 + j. i minors, j majors
  vgP[0] -> GetPolargram()->SetNdivPolar(004);
  vgP[0] -> GetPolargram()->SetNdivRadial(100);
  vgP[0] -> GetPolargram()->SetToRadian();
  //VeryImportant Step
  vgP[0] -> GetPolargram()->SetRangeRadial(0,100); 

  c2->Print("plot.eps");
  return 0;
}
