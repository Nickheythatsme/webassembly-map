#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include "src/shapefile.h"
#include <sstream>
#include <iostream>

int main()
{
  std::stringstream ss;
  uint16_t val = 0x3040;
  ss << val;
  std::cout << std::hex << "0x" << val << std::endl;
  std::cout << std::hex << "0x" << parse_be_short(ss) << std::endl;
  return 0;
}
