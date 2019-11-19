#include <cstdint>
#include <arpa/inet.h>
#include <fstream>
#include <stdio.h>

#ifndef MAP_SERIALIZE
#define MAP_SERIALIZE

inline uint64_t readLongLongBE(std::istream& istr)
{
    uint64_t network_value = 0;
    uint64_t value = 0;
    istr.read((char*)&network_value, sizeof(network_value));
    value = ntohl((uint32_t) network_value);
    value <<= 32;
    network_value >>= 32;
    value += (uint32_t) ntohl((uint32_t) network_value);
    return value;
}

inline uint32_t readLongBE(std::istream& istr)
{
    uint32_t value = 0;
    istr.read((char*)&value, sizeof(value));
    return ntohl(value);
}

inline uint16_t readShortBE(std::istream& istr)
{
    uint16_t value = 0;
    istr.read((char*)&value, sizeof(value));
    return ntohs(value);
}

#endif // MAP_SERIALIZE
