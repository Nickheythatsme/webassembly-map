#include <cstdint>
#include <arpa/inet.h>
#include <fstream>
#include <stdio.h>

#ifndef MAP_SERIALIZE
#define MAP_SERIALIZE

namespace map {

inline uint64_t readLongLongBE(std::istream& istr)
{
    uint64_t current_value = 0;
    uint64_t value = 0;
    istr.read(reinterpret_cast<char*>(&current_value), sizeof(current_value));
    value = ntohl(static_cast<uint32_t>(current_value));
    value <<= 32ul;
    current_value >>= 32ul;
    value += ntohl(static_cast<uint32_t>(current_value));
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

inline uint32_t readLong(std::istream& istr)
{
  uint32_t value = 0;
  istr.read(reinterpret_cast<char*>(&value), sizeof(value));
  return value;
}

inline double readDouble(std::istream& istr)
{
  double value = 0.0;
  istr.read(reinterpret_cast<char*>(&value), sizeof(value));
  return value;
}

} // namespace map

#endif // MAP_SERIALIZE
