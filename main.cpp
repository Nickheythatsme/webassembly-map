#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>

#if  __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

#include "src/shapefile.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
  std::string fname = "data/Neighborhoods_Regions.shp";
  if (argc == 2) {
      //cout << "Usage: ./map [shapefile]" << endl;
      //return 1;
      fname = argv[1];
  }
  ShapefileReader shapefile(fname.c_str());
  cout << "finished reading" << endl;
  shapefile.print(cout);
  return 0;
}
