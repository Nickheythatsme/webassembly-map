//
// Created by Nick_Grout on 11/19/19.
//

#include "record.h"

std::istream& Record::readIn(std::istream& in)
{
  record_number = readLongBE(in);
  content_length = readLongBE(in);
  return in;
}

using std::endl;
std::ostream& Record::print(std::ostream &out) const
{
  return out << "Record number:  " << record_number << endl
             << "Content length: " << content_length << endl;
}

uint32_t Record::getContentLength() const
{
  return content_length;
}

std::istream& PolygonRecord::readIn(std::istream& in)
{
  Record::readIn(in);
  return in;
}

std::ostream& PolygonRecord::print(std::ostream& out) const
{
  Record::print(out);
  return out;
}
