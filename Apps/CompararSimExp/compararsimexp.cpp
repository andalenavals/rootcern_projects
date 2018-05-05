#include "inc/Procesador.h"
#include "inc/RootImprove.h"


using namespace std;

int main(int argc, char** argv ){
  
  Procesador p;    RootImprove R;
  TStyle * AStyle = new TStyle("Andres",""); 
  R.DefinirEstilo(AStyle);
  AStyle->cd();
  TCanvas* c1 = new TCanvas ("c1","",800,600);
  R.DefinirCanvas(c1);
  c1->cd(); 
  
  //Extracting simu
  /*
  TH1D * h1 = R.CrearTH1Simu(argv[1],"Simu", 2048, 0, 2048);
  R.DefinirTH1(h1,1,1,R.Color(0));
  R.DefinirTitulos(h1, "", "Energy [keV]", "Counts");
  h1->Draw();
  c1->Print("simu.eps");
  */

  
  
  //Imprimir
  /*
  TH1D * h1 = R.GuardarEnTH1(argv[1],"Experimento");
  TH1D * h2 = R.GuardarEnTH1(argv[2],"Simulacion");
  R.DefinirTH1(h1,1,1,R.Color(0));
  R.DefinirTH1(h2,1,1, R.Color(1));
  R.DefinirTitulos(h1, "Espectro Experimental", "Canal", "Cuentas");
  R.DefinirTitulos(h2, "Espectro Simulado", "Energia [keV]", "Cuentas");
  h1->Draw();
  c1->Print("exp.jpg");
  h2->Draw();
  c1->Print("sim.jpg");
  */



  //Rebinear
  /*
  int pasos=50, k;
  double a = 0, b = 0, c=0;
  TH1D * h2 = R.GuardarEnTH1(argv[1],"Simulacion");
  R.DefinirTH1(h2,1,1, R.Color(1));
  TString  formula;
  for(k, a=-600 ; k<=pasos; a+=100, k++ )
    {
      formula = Form("Ch = %3.5g Chold ",a);
      // TH1D *h2c= p.Calibrar(h2, "", 1, a);
      //TH1D *h2r= p.ReBinear(h2c, "", 1 , 0);
      TH1D *h2r= p.CalibrarPro(h2, "", 0.7 , a , 1, 0);
      TH1F *frame = gPad->DrawFrame(0.,0.,4000.,3000.);
      gPad->Modified();
      R.DefinirTitulos(frame, "" , "Chanel", "Counts");
      h2r->Draw("SAME");
      R.DibujarAjuste(200, 3150 ,formula);
      c1->Print("animation.gif+50");
      formula.Clear();
      }
*/
  
 
 
  
  
  //COMPARAR ANIMACION
  /*
  int pasos=40, k;
  double a = 0, b = 0, c=0;
  TH1D * h2 = R.GuardarEnTH1(argv[1],"Simulacion");
  R.DefinirTH1(h2,1,1, R.Color(1));
  TString  formula;
  for(k, a=-600 ; k<=pasos; a+=100, k++ )
    {
      formula = Form("Chnew = Chold + %3.5g",a);
      //formula = Form("0.27*E+0.12#sqrt{E}+%3.2g",c);
      //TH1D *h2f= p.AgregarFWHM(h2, "", a,b,c);
      TH1D *h2c= p.Calibrar(h2, "", 1, a);
      // TH1D *h2c= p.CalibrarPro(h2, "", 1, a , 1, 0.5);
      TH1F *frame = gPad->DrawFrame(0.,0.,3000.,1200.);
      R.DibujarAjuste(500, 1300 ,formula);
      R.DefinirTitulos(frame, "" , "Chanel", "Counts");
      h2c->Draw("SAME");
      c1->Print("animation.gif+50");
      formula.Clear();
    }
  */
    

  
  //cout << R.Integrar(h2)-R.Integrar(h2f) <<endl;
 
  //escalado y sin escalar
  /*
  cout << R.Integrar(h1)<<" "<<h1->GetEffectiveEntries()<<endl;
  TH1D *h1e = p.Escalar(h1 ,"Experimento*0.5", 0.5);
  cout << R.Integrar(h1)*0.5- R.Integrar(h1e)<<endl;     
  R.SuperponerHistogramas(h1, h1e );
  c1->Print("exp+expe.jpg"); 
  */

  //SinRebineo y con rebineo
  /*
  TH1D *h1r = p.ReBinear(h1, 1.3 , 0.5 );
  R.DefinirTitulos(h1r,"Experimento Rebineado", "canal" , "Cuentas");
  R.ImprimirEnArchivoTexto(h1r, "rebineado.dat");
  cout << R.Integrar(h1) - R.Integrar(h1r) <<endl;
  cout<< h1->GetBinWidth(1)<<" "<< h1r->GetBinWidth(1)<<endl;
  cout<< h1->GetNbinsX()<<" "<< h1r->GetNbinsX()<<endl;
  cout<< R.GetXLow(h1) <<" "<< R.GetXLow(h1r) <<endl;
  cout<< R.GetXUp(h1) <<" "<< R.GetXUp(h1r) <<endl;
  //TLegend * leg= new TLegend( 0.6, 0.7, 0.80, 0.8,"");
  // TLegend * leg= new TLegend( 0.2, 0.7, 0.40, 0.8, "");
  //R.DefinirLegend(leg, h1, h1r);
  R.SuperponerHistogramas(h1r, h1);
  c1->Print("rebin+norebin.jpg");
  */

  
  //SIM VS EXP
  /*
  TH1D *exp = R.GuardarEnTH1(argv[1],"Experimento");
  TH1D *expc = p.Calibrar(exp,"Exp Calibrado", 0.77,1000 ); 
  TH1D *simu = R.GuardarEnTH1(argv[2],"Simulacion");
  TH1D *simuf= p.AgregarFWHM(simu,"Simu ConFWHM", 0.027 , 1.2 , 1);
  TH1D *simufe=p.EscalarTotalCounts(simuf, expc,"Simufe" );
  cout << R.Integrar(expc) - R.Integrar( simufe) <<endl;
  cout << expc->GetBinWidth(1) <<" "<<simufe->GetBinWidth(1) <<endl;
  cout << expc->GetBinWidth(expc->GetNbinsX()) <<" "<<simufe->GetBinWidth(simufe->GetNbinsX()) <<endl;
  cout << R.GetXLow(expc)  <<endl;
  cout << R.GetXUp(expc) <<endl;
  TH1D *expcr = p.ReBinear(expc ,"Exp Calibrado Rebineado", 1, 0.5 );
  TH1D *expcr = p.CalibrarPro(exp, "", 0.77, 1000, 1, 0.5 );
  R.DefinirTitulos(expc, "", "Energy [keV]", "Counts" );
  R.DefinirTitulos(exp, "", "Energy [keV]", "Counts" );
  R.SuperponerHistogramas(expcr,  exp);
  c1->Print("expcr+simufe.jpg");
  cout << R.Integrar(expcr) - R.Integrar( simufe) <<endl;
  cout << expcr->GetBinWidth(1) <<" "<<simufe->GetBinWidth(1) <<endl;
  cout << expcr->GetBinWidth(expcr->GetNbinsX()) <<" "<<simufe->GetBinWidth(simufe->GetNbinsX()) <<endl;
  cout << expcr->GetNbinsX() <<" "<< simufe->GetNbinsX() <<endl;
  cout << R.GetXLow(expcr) <<" "<< R.GetXLow(simufe) <<endl;
  cout << R.GetXUp(expcr) <<" "<< R.GetXUp(simufe) <<endl;
  cout<<  p.Chi2Abs(expcr, simufe, 1 , expcr->GetNbinsX() ) <<endl;
  */





  
  
  //TEST 6 CALIBRACION CON SIMULACION
  
  TH1D * exp = R.GuardarEnTH1(argv[1],"Experimento");
  TH1D * simu = R.GuardarEnTH1(argv[2],"Simu SinFWHM");
  TH1D * expr =  p.ReBinear(exp,"",1 , 0  );
  int i,j,k,l,m;
  double a, b, c, pe, co;

  int numbi=6;
  double maximum = 100000000;
  double ai, as, bi, bs, ci, cs, coi, cos, pei, pes;
  double chi,chiai, chias, chibi, chibs, chici, chics, chicoi, chicos, chipei, chipes;
  double am, bm, com, pem ;

  TString  formula;
  coi = -300 ; cos=  100;  co= coi;
  for(m=1 ; m<=numbi ; m++ )
    {
      pei =0.5 ; pes= 10 ;    pe = pei;
      for(l=1; l<= numbi ; l++ )
	{
	  ci = 0 ; cs = 100 ;  c= ci;
	  for(k=1; k<= numbi ; k++ )
	    {
	  
	      bi = 0 ; bs = 8 ;  b= bi;
	      for(j=1; j<= numbi ; j++ )
		{
		  ai = 0 ; as = 1 ;  a= ai;
		  for(i=1; i<= numbi ; i++ )
		    {	         	 
		      chi = p.Chi2Routine(simu, expr, a, b ,c, pe, co);

		      if(chi<maximum)
			{
			  maximum = chi;
			  TH1D * simuf, * simufc, * simufce;
			  double chi, xinf, xsup; 
			  simuf= p.AgregarFWHM(simu,"", a , b , c);
			  simufc = p.CalibrarPro(simuf, "", pe, co, 1 , 0);
			  xinf= p.MayorXInferior(expr, simufc);
			  xsup = p.MenorXSuperior(expr, simufc);
			  simufce= p.EscalarPartialCounts(simufc, expr,"", xinf , xsup );
			  R.DefinirTH1(simufce, 1, 1, R.Color(0) );
			  R.DefinirTH1(expr, 1, 1, R.Color(1) );
			  TH1F *frame = gPad->DrawFrame(0.,0.,1500.,1500.);
			  gPad->Modified();
			  
			  R.DefinirTitulos(frame, "", "Energy", "Counts");
			  expr->Draw("same");
			  simufce->Draw("same");
			  formula = Form("a = %3.3g  b = %3.3g  c = %3.3g  pen = %3.3g   cor = %3.3g chi = %3.9g ", a , b, c, pe, co, co);
			  R.DibujarAjuste(-100, 1700 ,formula);
			  c1->Print("animation.gif+100");
			  formula.Clear();
			}
		      
		      chiai = p.Chi2Routine(simu, expr, ai, b ,c, pe, co);
		      chias = p.Chi2Routine(simu, expr, as, b ,c, pe, co);
		      if(chiai > chias)
			ai= 0.5*(ai+as);
		      else { as= 0.5*(ai+as) ; }
		      a=(ai+as)*0.5;
		    }
		  chibi = p.Chi2Routine(simu, expr, a, bi ,c, pe, co);
		  chibs = p.Chi2Routine(simu, expr, a, bs ,c, pe, co);
		  if(chibi > chibs)
		    bi= 0.5*(bi+bs);
		  else { bs= 0.5*(bi+bs) ; }
		  b=(bi+bs)*0.5;
		}
	      chici = p.Chi2Routine(simu, expr, a, b, ci, pe, co);
	      chics = p.Chi2Routine(simu, expr, a, b, cs, pe, co);
	      if(chici > chics)
		ci= 0.5*(ci+cs);
	      else { cs= 0.5*(ci+cs) ; }
	      c=(ci+cs)*0.5;
	      
	    }
	  chipei = p.Chi2Routine(simu, expr, a, b ,c, pei, co);
	  chipes = p.Chi2Routine(simu, expr, a, b ,c, pes, co);
	  if(chipei > chipes)
	    pei= 0.5*(pei+pes);
	  else { pes= 0.5*(pei+pes) ; }
	  pe=(pei+pes)*0.5;
	}
      chicoi = p.Chi2Routine(simu, expr, a, b ,c, pe, coi);
      chicos = p.Chi2Routine(simu, expr, a, b ,c, pe, cos);
      if(chicoi > chicos)
	coi= 0.5*(coi+cos);
      else { cos= 0.5*(coi+cos) ; }
      co=(coi+cos)*0.5;
    }
  
  


  
  //TEST 7 comparacion final calibracion
  /*
  TH1D * exp = R.GuardarEnTH1(argv[1],"Experimento");
  TH1D * simu = R.GuardarEnTH1(argv[2],"Simu SinFWHM");
  TH1D * expr =  p.ReBinear(exp,"",1 , 0.5  );
  TH1D * simuf, * simufc, * simufce;
  int i,j,k,l,m;
  double a, b, c, pe, co;
  c=0;
  double chi, xinf, xsup;
  
  TH1F *frame = gPad->DrawFrame(0.,0.,1500.,1500.);
  gPad->Modified();
  R.DefinirTitulos(frame, "", "Energy", "Counts");
  

  //PARAMETROS ALGORITMO
  simuf = p.AgregarFWHM(simu,"1", 0 , 2.06 , 0 );
  simufc = p.CalibrarPro(simuf, "2",  1.69, -295 , 1, 0  );
  xinf= p.MayorXInferior(expr, simufc);
  xsup =p.MenorXSuperior(expr, simufc);
  simufce=p.EscalarPartialCounts(simufc, expr,"", xinf , xsup );
  R.DefinirTH1(simufce, 1, 1, R.Color(0) );
  R.DefinirTH1(expr, 1, 1, R.Color(1) );
  expr->Draw("same");
  simufce->Draw("same");
  TLegend * leg= new TLegend( 0.6, 0.9, 0.80, 1,"");
  leg->AddEntry(expr, "Experimento", "L");
  leg->AddEntry(simufce, "Simulacion", "L");
  leg->Draw("same");
  c1->Print("simexpcal2.eps");
  */
  
 
 
  
  

  
  //PARAMETROS EXPERIMENTO COMPARACION EN CANALES
  // simufwhm= p.AgregarFWHM(simu,"", 0.0269815  , 1.19548  , 1.05803); //Caracterizacion experimental
  // simucalibrado= p.CalibrarPro(simufwhm,"", 1.331451824 , -3.056720481 , 1 , 0.5  ); //Flechas 137Cs experimental 
  // simucalibrado= p.CalibrarPro(simufwhm,"", 1.26811 , 0.741527 , 1 , 0.5  ); //Navarro todas las fuentes
  // simucalibrado= p.CalibrarPro(simufwhm,"", 1.26833 , -0.368329 , 1 , 0.5  ); //Navarro 22Na experimental
  // simucalibrado= p.CalibrarPro(simufwhm,"", 1.36904 , -63.7895 , 1 , 0.5  ); //Navarro 137 experimental
  // simucalibradoescalado=p.EscalarRespectoCuentasParciales(simucalibrado, exp,"Simulacion",  p.MayorUmbralInferior(exp, simucalibrado), p.MenorUmbralSuperior(exp, simucalibrado) );
  // R.SuperponerHistogramas(exp,  simucalibradoescalado,"", "Canal", "Cuentas" , 0 , 1000 );

  //PARAMETROS EXPERIMENTO COMPARACION EN ENERGIA
  // simufwhm= p.AgregarFWHM(simu,"", 0.0269815  , 1.19548  , 1.05803); //Caracterizacion experimental
  //expcalibrado= p.CalibrarPro(exp,"", 0.7885751236091506 , -0.741527 , 1 , 0.5  ); //Navarro todas las fuentes
  //simucalibradoescalado=p.EscalarRespectoCuentasParciales(simucalibrado, exp,"Simulacion",  p.MayorUmbralInferior(exp, simucalibrado), p.MenorUmbralSuperior(exp, simucalibrado) );
  //R.SuperponerHistogramas(exp,  simucalibradoescalado, 0 , 1000 );
  




  
  //cout<< p.Chi2Abs(exp ,simucalibradoescalado, p.MayorUmbralInferior(exp, simucalibrado) ,  p.MenorUmbralSuperior(exp, simucalibrado) ) ; <endl;

  return 0;

}

