#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#if  __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

#include "src/shapefile.h"

int main()
{
    uint64_t val = 0xffaaff;
    uint64_t val2 = 0;
    reverse_value(&val, &val2);
    std::stringstream ss;
    uint16_t value = 0x0123;
    uint16_t network_value = htons(value);
    ss.write((char*)&network_value, sizeof(network_value));
    uint16_t response = readShortBE(ss);
    std::cout << value << std::endl
            << response << std::endl;
    return 0;
}
