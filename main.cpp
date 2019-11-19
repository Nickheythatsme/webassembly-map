#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#if  __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

#include "src/shapefile.h"

using std::cout;
using std::endl;

int main()
{
    ShapefileReader shapefile("data/Neighborhoods_Regions.shp");
    cout << "finished reading" << endl;
    return 0;
}
