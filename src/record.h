//
// Created by Nick_Grout on 11/19/19.
//

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "serialize.h"

#ifndef MAP_SRC_RECORD_H_
#define MAP_SRC_RECORD_H_

struct Box {
  double x_min {};
  double x_max {};
  double y_min {};
  double y_max {};
};

class Point {
  public:
    Point() = default;
    Point(double x, double y);
    double x {}; // x coordinate
    double y {}; // y coordinate
};

Point normalizePoint(double xmin, double xmax, double ymin, double ymax, Point &ptr);

class Record {
  public:
    virtual uint32_t getShapeType() const = 0;
    virtual ~Record() = default;
    virtual std::istream& readIn(std::istream& in);
    virtual std::string toString() const;
    [[nodiscard]] uint32_t getContentLength() const;
  protected:
    uint32_t record_number {};
    uint32_t content_length {};
    uint32_t shapeType {};
};

class PolygonRecord: public Record {
  public:
    uint32_t getShapeType() const final;
    std::istream& readIn(std::istream& in) final;
    std::string toString() const final;
    Point calculateCenter() const;
  private:
    Box box {};
    uint32_t numParts;
    uint32_t numPoints;
    std::unique_ptr<uint32_t[]> parts;
    std::unique_ptr<Point[]> points;
};


#endif //MAP_SRC_RECORD_H_
