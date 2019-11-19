#include "shapefile.h"


/**
Parse out a big endian short
*/
uint16_t parse_be_short(std::istream& in)
{
    uint16_t val = 0;
    in.read(reinterpret_cast<char*>(&val), sizeof(val));
    return ntohs(val);
}

/**
Parse out a big endian long
*/
uint32_t parse_be_long(std::istream& in)
{
    uint32_t val = 0;
    in.read(reinterpret_cast<char*>(&val), sizeof(val));
    return ntohl(val);
}
