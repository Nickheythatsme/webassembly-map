#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include "serialize.h"
#include "record.h"

#ifndef MAP_SHAPEFILE
#define MAP_SHAPEFILE

struct ShapefileHeader {
  uint32_t file_code;
  uint32_t file_length;
  uint32_t version;
  uint32_t shape_type;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
  double m_max;
  double m_min;
};

class ShapefileReader {
  public:
    ShapefileReader() = delete;
    explicit ShapefileReader(const char* fname);
    std::ostream& print(std::ostream &out) const;
  protected:
  private:
    void readHeader();
    std::ifstream file;
    std::unique_ptr<ShapefileHeader> header;
    std::vector<Record> records;
};


class Shapefile {
  public:
    Shapefile() = default;
};


#endif  // MAP_SHAPEFILE