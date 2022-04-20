/*=============================================================================
 File         : obfuscator.cpp
 Author       : Walter Schreppers
 Description  : Little quick and dirty string obfuscation into a header of
                functions used by clips.cpp
=============================================================================*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>


// shortcut for less typing (don't do this in big projects ;) )
using namespace std;

string obfuscate(const string& in, const string& func_name="secret"){
  srand (time(NULL)); // seed
  string hdr = "";

  hdr += "std::string "+func_name+"(){\n";
  hdr += "  std::string s;\n";

  for(string::const_iterator s=in.begin(); s!=in.end(); ++s){
    int multiplier=rand() % 20 + 3; // 3 to 23
    int sub = rand() % 3000+2; // 2 to 3002

    hdr += "  s +=";
    hdr += " (char) (int)(";
    int ascii_val = (int)*s;
    ascii_val = (ascii_val+sub)*multiplier;

    ostringstream os1;
    os1<<ascii_val;
    hdr += os1.str();

    hdr += "/";
    ostringstream os2;
    os2<<multiplier;
    hdr+=os2.str();

    hdr+="-";
    ostringstream os3;
    os3<<sub;
    hdr+=os3.str();

    hdr+=");\n";
  }
  hdr += "  return s;\n";
  hdr += "}";

  return hdr;
}

int main(int argc, char *argv[]){
  string pin, sec;

  if(argc<3){
    // cerr << "USAGE ./" << argv[0] << "<pincode> <secret>" << endl;
    cout << "new pin     : ";
    cin >> pin;
    cout << "new secret  : ";
    cin >> sec;
  }
  else{
    pin = argv[1];
    sec = argv[2];
  }

  ofstream ofile("secrets.h");
  ofile << obfuscate(pin, "pincode");
  ofile << endl;
  ofile << endl;
  ofile << obfuscate(sec, "secret");
  ofile << endl;
  ofile.close();

  return 0;
}


