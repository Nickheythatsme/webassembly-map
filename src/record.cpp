//
// Created by Nick_Grout on 11/19/19.
//

#include "record.h"

Point::Point(double x, double y):
  y(y),
  x(x)
{ }

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
  shapeType = readLong(in);
  box[0] = readDouble(in);
  box[1] = readDouble(in);
  box[2] = readDouble(in);
  box[3] = readDouble(in);
  numParts = readLong(in);
  numPoints = readLong(in);

  parts = std::unique_ptr<uint32_t[]>(new uint32_t[numParts]);
  points = std::unique_ptr<Point[]>(new Point[numPoints]);
  for (int i=0; i<numParts; ++i) {
    parts[i] = readLong(in);
  }
  for (int i=0; i<numPoints; ++i) {
    points[i] = Point(
        readDouble(in),
        readDouble(in)
        );
  }
  return in;
}

using std::endl;
std::ostream& PolygonRecord::print(std::ostream& out) const
{
  Record::print(out);
  out << "Shape Type: " << shapeType << endl
      << "Box: " << box[0] << endl
      << "     " << box[1] << endl
      << "     " << box[2] << endl
      << "     " << box[3] << endl
      << "Num Parts: " << numParts << endl
      << "Num Points: " << numPoints << endl
      << "Parts: ";
  for (int i=0; i<numParts; ++i) {
    out << parts[i] << ", ";
  }
  out << endl
      << "Points: ";
  for (int i=0; i<numPoints; ++i) {
    out << "(" << points[i].x << ", " << points[i].y << ") ";
  }
  return out;
}
