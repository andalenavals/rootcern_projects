#ifndef PROCESADOR
#define PROCESADOR 1

#include "RootImprove.h"

using namespace std;

class Procesador{
private:
  RootImprove R;
  TRandom *ran= new TRandom;

public:
  Procesador(void);
  TH1D * AgregarFWHM( TH1D * h ,const char* name,  double a, double b, double c);
  TH1D * Calibrar( TH1D * h , const char* name ,  double pendiente, double corte);
  TH1D * CalibrarGeneral( TH1D * h , const char* name ,  TF1 * func);
  TH1D * CalibrarPro( TH1D * h, const char* name ,   double pendiente, double corte,double newbinwidth, double xlow);
  double Chi2Abs( TH1 * h1 , TH1 * h2 );
  double Chi2Abs( TH1 * h1 , TH1 * h2 , int binlow, int binup);
  double Chi2Routine( TH1D * h1 , TH1D * h2, double a , double b, double c, double pe, double co );
  double ComptonEdge(double E_gamma ); //en keV
  void DefinirUmbrales(TH1D * &h , int binlow, int binsup);
  int EncontrarUmbralInferior(TH1D *h);
  int EncontrarUmbralSuperior(TH1D *h);
  TH1D * Escalar(TH1 * h, const char* name,  double escala);
  TH1D * EscalarTotalCounts(TH1 * hmove , TH1 * hfix , const char* name);
  TH1D * EscalarPartialCounts(TH1 * hmove , TH1 * hfix , const char* name, int binlow, int binup);
  TH1D * EscalarPartialCounts(TH1 * hmove , TH1 * hfix , const char* name, double xlow, double xup);
  double FWHM(double energia, double a, double b, double c);
  int MayorUmbralInferior(TH1D *h1, TH1D *h2 );
  int MenorUmbralSuperior(TH1D *h1, TH1D *h2);
  double MayorXInferior(TH1D *h1, TH1D *h2 );
  double MenorXSuperior(TH1D *h1, TH1D *h2 );
  int EncontrarOffSetInverso(TH1D *h);
  TH1D * ReBinear(TH1D * h, const char *, double newbinwidth, double xlow);
  double RetroDispersionEdge(double E_gamma){return E_gamma - ComptonEdge(E_gamma);}; //en keV
};
#endif



/*
NOTAS PENDIENTES 

1. Calibrar PRO basicamente es uan calibracion normal mas rebineo

2. Guardar histograma es para histogramas . Es importante recordar que
el numero de bines definido en el histograma no necesariamente es
igual al numero total de canales de los datos de entrada, de forma
analoga ocurre con los extremos. Es decir si el 3numero de bines no
coincide con el numero de canales el metod hace un rebineo.

4. Calibrar se puede usar en ambas direcciones canal energia o energia
canal lo importante es conocer los archivos de entrada

8. Port convencion todos los metods tienen como primeros parametros de
entrada los datos lu ego nombre y luego mas variables de procesamiento

9. Falta Poner Ejes Auxiliares en la superposición


*/






