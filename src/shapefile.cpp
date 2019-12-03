#include "shapefile.h"
#include <stdio.h>
#include <sstream>
#include <memory>

namespace map {

ShapefileReader::ShapefileReader(const char* fname):
    file(fname),
    header(new ShapefileHeader())
{
  if (!file) {
    printf("Could not open file: %s\n", fname);
    return;
  }
  readHeader();
}

void ShapefileReader::readHeader()
{
  file.seekg(file.beg);
  header->file_code = readLongBE(file);
  file.ignore(20);
  header->file_length = readLongBE(file);
  header->version = readLong(file);
  header->shape_type = readLong(file);
  header->x_min = readDouble(file);
  header->y_min = readDouble(file);
  header->x_max = readDouble(file);
  header->y_max = readDouble(file);
  header->z_min = readDouble(file);
  header->z_max = readDouble(file);
  header->m_min = readDouble(file);
  header->m_max = readDouble(file);
  std::unique_ptr<Record> record {new PolygonRecord()};
  record->readIn(file);
  while (!file.eof()) {
    records.emplace_back(std::move(record));
    record = std::make_unique<PolygonRecord>();
    record->readIn(file);
  }
}

using std::endl;
std::string ShapefileReader::toString() const
{
    std::stringstream ss;
    ss << "File code:    " << header->file_code << endl
      << "File length:  " << header->file_length << endl
      << "File version: " << header->version << endl
      << "Shape type:   " << header->shape_type << endl
      << "x min:        " << header->x_min << endl
      << "x max:        " << header->x_max << endl
      << "y min:        " << header->y_min << endl
      << "y max:        " << header->y_max << endl
      << "z min:        " << header->z_min << endl
      << "z max:        " << header->z_max << endl
      << "m min:        " << header->m_min << endl
      << "m max:        " << header->m_max << endl;
  for (const auto& record: records) {
    ss << record->toString();
  }
  return ss.str();
}

} // namespace map

