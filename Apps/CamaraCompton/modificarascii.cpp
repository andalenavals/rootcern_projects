#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char** argv ){
 
  ifstream filein;
  ofstream fileout;
  double value;
  double IN[64][64];
  double OUT[62][62];
  filein.open (  argv[1] , std::ios::in );
  for (int j = 0; j <= 63; ++j)
    for (int i = 0; i <= 63; ++i)
      {
	filein >> value;
	IN[i][j]=value;
      }

  for (int j = 0; j <= 61; ++j)
    for (int i = 0; i <= 61; ++i)
      {
      OUT[i][j]=IN[i+1][j+1];
      }

  string name, name1;
  name = std::string(argv[1]);
  name1.append(name.begin(),name.end()-4);
  name1.append("_OK.dat");
  fileout.open (name1.c_str());
  for (int j = 0; j <= 61; ++j)
    {
      for (int i = 0; i <= 61; ++i)
	{
	  fileout <<  OUT[i][j]<< " ";
	}
	    fileout<<endl;
    }
      
      fileout.close();
	  
  
  return 0;
}

 
