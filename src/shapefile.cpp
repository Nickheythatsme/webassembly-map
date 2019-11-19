#include "shapefile.h"
#include <stdio.h>

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
  // TODO: read in the rest of the records
  Record record {};
  file >> record;
  while (!file.eof()) {
    records.emplace_back(record);
    file >> record;
  }
}

using std::endl;
std::ostream& ShapefileReader::print(std::ostream &out) const
{
  out << "File code:    " << header->file_code << endl
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
    record.print(out);
  }
  return out;
}

std::istream& operator>>(std::istream& in, Record& record)
{
  record.starting_pos = in.tellg();
  record.record_number = readLongBE(in);
  record.content_length = readLongBE(in);
  in.ignore(record.content_length * 2);
  return in;
}

using std::endl;
std::ostream& Record::print(std::ostream &out) const
{
  return out << "Record number: " << record_number << endl
      << "Content length: " << content_length << endl;
}
