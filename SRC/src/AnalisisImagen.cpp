#include "../inc/AnalisisImagen.h"

using namespace std;
AnalisisImagen::AnalisisImagen(void)
{

}

TH2D * AnalisisImagen::Gradient1( TH2D * h )
{
  double gx;
  double gy;
  double M;
  
  TH2D *hg= new TH2D ("", "" , h->GetNbinsX(), 0.5, h->GetNbinsX()+0.5, h->GetNbinsY() ,0.5 ,h->GetNbinsY()+0.5);
  
  for(int i =1  ; i<= h->GetNbinsX()-1; ++i)
    for(int j =2 ; j<= h->GetNbinsY(); ++j)
      {
	gx = 0.5*(h->GetBinContent(i-1,j)-h->GetBinContent(i+1,j));
	gy = 0.5*(h->GetBinContent(i,j-1)-h->GetBinContent(i,j+1));
	M = fabs(gx*gx)+fabs(gy*gy);
	hg->SetBinContent(i, j, sqrt(M) );
      }

  return hg;
}

TH2D * AnalisisImagen::GradientPrewitt( TH2D * h )
{
  double gx;
  double gy;
  double M;
  
  TH2D *hg= new TH2D ("", "" , h->GetNbinsX(), 0.5, h->GetNbinsX()+0.5, h->GetNbinsY() ,0.5 ,h->GetNbinsY()+0.5);
  
  for(int i =1  ; i<= h->GetNbinsX()-1; ++i)
    for(int j =2 ; j<= h->GetNbinsY(); ++j)
      {
	gx = h->GetBinContent(i-1,j-1)+h->GetBinContent(i,j-1)+h->GetBinContent(i+1,j-1)-(h->GetBinContent(i-1,j+1)+h->GetBinContent(i,j+1)+h->GetBinContent(i+1,j+1));
	gy = h->GetBinContent(i+1,j-1)+h->GetBinContent(i+1,j)+h->GetBinContent(i+1,j+1)-(h->GetBinContent(i-1,j-1)+h->GetBinContent(i-1,j)+h->GetBinContent(i-1,j+1));
	M = fabs(gx*gx)+fabs(gy*gy);
	hg->SetBinContent(i, j, sqrt(M) );
      }

  return hg;
}

TH2D * AnalisisImagen::GradientRobert( TH2D * h )
{
  double gx;
  double gy;
  double M;
  
  TH2D *hg= new TH2D ("", "" , h->GetNbinsX(), 0.5, h->GetNbinsX()+0.5, h->GetNbinsY() ,0.5 ,h->GetNbinsY()+0.5);
  
  for(int i =1  ; i<= h->GetNbinsX()-1; ++i)
    for(int j =2 ; j<= h->GetNbinsY(); ++j)
      {
	gx = h->GetBinContent(i+1,j-1)-h->GetBinContent(i,j);
	gy = h->GetBinContent(i,j-1)-h->GetBinContent(i+1,j);
	M = fabs(gx*gx)+fabs(gy*gy);
	hg->SetBinContent(i, j, sqrt(M) );
      }

  return hg;
}

TH2D * AnalisisImagen::GradientSobel( TH2D * h  )
{
  double gx;
  double gy;
  double M;
  
  TH2D *hg= new TH2D ("", "" , h->GetNbinsX(), 0.5, h->GetNbinsX()+0.5, h->GetNbinsY() ,0.5 ,h->GetNbinsY()+0.5);
  
  for(int i =2  ; i<= h->GetNbinsX()-1; ++i)
    for(int j =2 ; j<= h->GetNbinsY()-1; ++j)
      {
	gx = h->GetBinContent(i-1,j-1)+2*h->GetBinContent(i,j-1)+h->GetBinContent(i+1,j-1)-(h->GetBinContent(i-1,j+1)+2*h->GetBinContent(i,j+1)+h->GetBinContent(i+1,j+1));
	gy = h->GetBinContent(i+1,j-1)+2*h->GetBinContent(i+1,j)+h->GetBinContent(i+1,j+1)-(h->GetBinContent(i-1,j-1)+2*h->GetBinContent(i-1,j)+h->GetBinContent(i-1,j+1));
	M = fabs(gx*gx)+fabs(gy*gy);
	hg->SetBinContent(i, j, sqrt(M) );
      }

  return hg;
}

TH2D * AnalisisImagen::Laplacian( TH2D * h  )
{
  TH2D *hl= new TH2D ("", "" , h->GetNbinsX(),0.5, h->GetNbinsX()+0.5, h->GetNbinsY() ,0.5 ,h->GetNbinsY()+0.5);
  double gxx,gyy,gxy,gyx, value;
 for(int i =2  ; i<= h->GetNbinsX()-1; ++i)
    for(int j =2 ; j<= h->GetNbinsY()-1; ++j)
      {
	gxx = h->GetBinContent(i-1,j)+h->GetBinContent(i+1,j);
	gyy = h->GetBinContent(i,j+1)+h->GetBinContent(i,j-1);
	gxy = h->GetBinContent(i-1,j-1)+h->GetBinContent(i+1,j+1);
	gyx = h->GetBinContent(i-1,j+1)+h->GetBinContent(i+1,j-1);
	value = (gxx + gyy + gxy + gyx - 8*h->GetBinContent(i,j) )/8; 
	hl->SetBinContent(i, j, value );
      }
 return hl;
} 
