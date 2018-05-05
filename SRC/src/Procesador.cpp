#include "../inc/Procesador.h"

using namespace std;

Procesador::Procesador(void)
{
  ran =new TRandom(R.GenerarSemilla());
}

TH1D * Procesador::AgregarFWHM(TH1D * h,const char* name, double a, double b, double c)
{
  int nbin= h->GetNbinsX();
  TH1D *h1= new TH1D (name, "" , nbin , R.GetXLow(h) ,  R.GetXUp(h) );
  double r1;
  for(int j =1 ; j<= nbin ; j ++)
    for(int k= 1 ; k<= h->GetBinContent(j) ; k++ ){
      r1=ran->Gaus(h->GetBinCenter(j), FWHM(h->GetBinCenter(j) , a, b, c)/2.35);
      h1->Fill(r1);
    }
  return h1;
}

TH1D * Procesador::Calibrar( TH1D * h , const char* name ,  double pendiente, double corte)
{
  TH1D *h2= (TH1D*) h->Clone(name);  
  int nbin= h2->GetNbinsX();
  double new_bins[nbin+1];
  for(int i=0; i <= nbin; i++)
    new_bins[i] = pendiente*h2->GetBinLowEdge(i+1)+corte ;
  h2->SetBins(nbin, new_bins);
  return h2;
}

TH1D * Procesador::CalibrarGeneral( TH1D * h , const char* name ,  TF1 * func)
{
  TH1D *h2 = new TH1D(name,"", h->GetNbinsX(), func->GetMinimum(R.GetXLow(h), R.GetXUp(h)), func->GetMaximum(R.GetXLow(h), R.GetXUp(h)));   
  for(int i=1; i <=  h->GetNbinsX(); i++)
    h2->SetBinContent( h2->FindBin( func->Eval(h->GetBinCenter(i)) ) , h->GetBinContent(i) );
  return h2;  
}

TH1D * Procesador::CalibrarPro( TH1D * h , const char* name,   double pendiente , double corte,double newbinwidth, double xlow)
{
  return ReBinear( Calibrar(h , "", pendiente, corte ), name,  newbinwidth , xlow ) ;
}

double Procesador::Chi2Abs( TH1 * h1 , TH1 * h2, int binlow, int binup )
{
  /*
  cout<<endl;
  cout<<"Control del Test"<<endl;
  cout<<"Diferencia de width: "<< TMath::Abs(h2->GetBinWidth(1)-h1->GetBinWidth(1)) <<endl;
  cout<<"Diferencia de xlow: "<< TMath::Abs( GetXLow(h1)-GetXLow(h2) ) <<endl;
  cout<<"Diferencia de xup: "<< TMath::Abs(GetXUp(h1)-GetXUp(h2)) <<endl;
  cout<<endl;
  */  
  double suma=0;
  for (int i = binlow ; i <= binup ; i++)
    suma+=TMath::Abs(h1->GetBinContent(i)-h2->GetBinContent(i));
  return suma;
}

double Procesador::ComptonEdge(double E_gamma )
{
  double ep_gamma=E_gamma/511.; //keV
  double BORDEC = E_gamma*((2*ep_gamma)/(1+2*ep_gamma));//keV
  return BORDEC;
}

void Procesador::DefinirUmbrales(TH1D * &h , int binlow, int binup)
{
for (int i = 1; i < binlow; i++)
    h->SetBinContent(i,0);
 for (int i = binup ; i < h->GetNbinsX(); i++)
    h->SetBinContent(i,0);
}

int Procesador::EncontrarUmbralInferior(TH1D *h)
{
  //Cuantos bines sin contenido hay!, de izquierda a derecha
  int offset=0;
  for (int i = 1; i <= h->GetNbinsX() ; i++)
    {
      if(h->GetBinContent(i)==0)
	offset+=1;
      else
	break;
    }
  return offset;
}

int Procesador::EncontrarUmbralSuperior(TH1D *h)
{
  //Cuantos bines sin contenido hay, de derecha a izquierda
  int offset= h->GetNbinsX() ;
  for (int i = h->GetNbinsX() ; i >=1  ; i-=1)
    {
      if(h->GetBinContent(i)==0)
	offset-=1;
      else
	break;
    }
  return offset;
}

TH1D * Procesador::Escalar(TH1 * h, const char* name,  double escala)
{
  TH1D * escalado= R.ToD(h);
  escalado->SetName(name);
  escalado->Scale(escala);
  return escalado;
  escalado->Clear();
}

TH1D * Procesador::EscalarTotalCounts(TH1 *  hmove , TH1 * hfix, const char* name )
{
 return Escalar(hmove, name , R.Integrar(hfix)/R.Integrar(hmove) );  
}

TH1D * Procesador::EscalarPartialCounts(TH1 * hmove , TH1 * hfix , const char* name, int binlow, int binup)
{
  return Escalar(hmove, name , R.Integrar(hfix, hfix->GetBinCenter(binlow) , hfix->GetBinCenter(binup) )/R.Integrar(hmove, hmove->GetBinCenter(binlow) , hmove->GetBinCenter(binup) ) );  
}

double Procesador::FWHM(double energia, double a, double b, double c)
{
  int r;
  r=  a*energia + b*sqrt(energia) + c; //NaI3x3 en keV
  return r;
}

int Procesador::MayorUmbralInferior(TH1D *h1, TH1D *h2 )
{
  if ( EncontrarUmbralInferior(h1) > EncontrarUmbralInferior(h2) )
    return EncontrarUmbralInferior(h1) ;
  else return EncontrarUmbralInferior(h2) ;
}

int Procesador::MenorUmbralSuperior(TH1D *h1, TH1D *h2 )
{
 if ( EncontrarUmbralSuperior(h1) < EncontrarUmbralSuperior(h2) )
    return EncontrarUmbralSuperior(h1) ;
  else return EncontrarUmbralSuperior(h2) ;
}

TH1D * Procesador::ReBinear(TH1D * h , const char* name,  double newbinwidth, double xlow)
{
  double binwidth = h->GetBinWidth(1);
  int nbin=h->GetNbinsX(),newnbin, aux;
  double xup = R.GetXUp(h);
  double L = xup-xlow;
  TH1D * h2;

  if( (L/newbinwidth) - int(L/newbinwidth) == 0 )
    {
      newnbin= int(L/newbinwidth) ;
      h2= new TH1D (name, "" , newnbin , xlow , xup  ) ;
    }
  if( (L/newbinwidth) - int(L/newbinwidth) >0 )
    {
      newnbin= int(L/newbinwidth)+1 ;
      double newxup=xup+newbinwidth;
      h2= new TH1D (name , "" , newnbin , xlow , newxup ) ; 
    }

  for(int i = h->FindBin(xlow) ; i<= nbin ; i++)
    for(int j = 1 ; j<=h->GetBinContent(i); j++ )
      h2->Fill( ran->Uniform(h->GetBinLowEdge(i) , h->GetBinLowEdge(i) + binwidth ) );

    return h2;

}





