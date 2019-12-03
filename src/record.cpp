//
// Created by Nick_Grout on 11/19/19.
//

#include "record.h"
#include <sstream>

namespace map {

std::istream& Record::readIn(std::istream& in)
{
  record_number = readLongBE(in);
  content_length = readLongBE(in);
  shapeType = readLong(in);
  return in;
}

using std::endl;
std::string Record::toString() const
{
    std::stringstream ss;
    ss << "Record number:  " << record_number << endl
             << "Content length: " << content_length << endl
             << "Shape Type: " << shapeType << endl;
    return ss.str();
}

uint32_t Record::getContentLength() const
{
  return content_length;
}

std::istream& PolygonRecord::readIn(std::istream& in)
{
  Record::readIn(in);
  box.x_min = readDouble(in);
  box.y_min = readDouble(in);
  box.x_max = readDouble(in);
  box.y_max = readDouble(in);
  numParts = readLong(in);
  numPoints = readLong(in);

  parts = std::unique_ptr<uint32_t[]>(new uint32_t[numParts]);
  points = std::unique_ptr<Vec2<double>[]>(new Vec2<double>[numPoints]);
  for (int i=0; i<numParts; ++i) {
    parts[i] = readLong(in);
  }
  for (int i=0; i<numPoints; ++i) {
    points[i] = Vec2(
        readDouble(in),
        readDouble(in)
        );
  }
  return in;
}

using std::endl;
std::string PolygonRecord::toString() const
{
  std::stringstream ss;
  ss << Record::toString();
  ss << "Box:" << endl
      << " x min: " << box.x_min << endl
      << " x max: " << box.x_max << endl
      << " y min: " << box.y_min << endl
      << " y max: " << box.y_max << endl
      << "Num Parts:  " << numParts << endl
      << "Num Points: " << numPoints << endl
      << "Parts: ";
  for (int i=0; i<numParts; ++i) {
    ss << parts[i] << ", ";
  }
  ss << endl
      << "Points: ";
  for (int i=0; i<numPoints; ++i) {
    ss << "(" << points[i].getX() << ", " << points[i].getY() << ") ";
  }
  ss << endl;
  return ss.str();
}

uint32_t PolygonRecord::getShapeType() const
{
    return shapeType;
}

Vec2<double> PolygonRecord::calculateCenter() const
{
    double avg_x = box.x_min - (box.x_min - box.x_max);
    double avg_y = box.y_min - (box.y_min - box.y_max);
    return Vec2(avg_x, avg_y);
}

} // namespace map
