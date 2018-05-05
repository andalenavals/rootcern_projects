#ifndef AIMAGEN
#define AIMAGEN 1

#include "RootImprove.h"

using namespace std;

class AnalisisImagen{
private:
  RootImprove R;
public:
  AnalisisImagen (void);
  TH2D * Gradient1( TH2D * h );
  TH2D * GradientPrewitt( TH2D * h );
  TH2D * GradientRobert( TH2D * h );
  TH2D * GradientSobel( TH2D * h  );
  TH2D * Laplacian( TH2D * h  ); 
};
#endif
