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
  uint16_t value = 0x0123;
  uint16_t network_value = htons(value);
  ss.write((char*)&network_value, sizeof(network_value));
  uint16_t response = readShortBE(ss);
  std::cout << value << std::endl;
  std::cout << response << std::endl;
  return 0;
}
