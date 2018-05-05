#include <iomanip> 
#include <iostream> 
#include <math.h>



//Energia en keV y theta en radianes
double KleinNishinaDC( double theta, double Energy)
{
  double epsilon = Energy/511. ; //keV
  double S= 1.-cos(theta);
  double P = 1./(1.+epsilon*S);
  double Const = 79.406*0.5 ; // mbarn2
  return Const*( pow(P,2.)) *(P +(1./P)-pow(sin(theta), 2));
}

double EgammaP(double theta, double Energy) 
{
  double epsilon = Energy/511. ;
  double S= 1.-cos(theta);
  return Energy/(1+epsilon*S);
}

double KelectronP(double theta, double Energy) 
{
  return Energy - EgammaP(theta, Energy) ;
}
