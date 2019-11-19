#include <netinet/in.h>
#include <istream>

/**
Parse out a big endian short
*/
uint16_t parse_be_short(std::istream&);

/**
Parse out a big endian long
*/
uint32_t parse_be_long(std::istream&);