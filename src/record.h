//
// Created by Nick_Grout on 11/19/19.
//

#include <iostream>
#include <vector>
#include "serialize.h"

#ifndef MAP_SRC_RECORD_H_
#define MAP_SRC_RECORD_H_

class Record {
  public:
    Record() = default;
    Record(const Record &rhs) = default;
    virtual std::istream& readIn(std::istream& in);
    virtual std::ostream& print(std::ostream &out) const;
    [[nodiscard]] uint32_t getContentLength() const;
  private:
    uint32_t record_number{};
    uint32_t content_length{};
};

class Point {
  public:
    Point() = default;
    Point(double x, double y);
    double x {}; // x coordinate
    double y {}; // y coordinate
};

class PolygonRecord: public Record {
  public:
    std::istream& readIn(std::istream& in) override;
    std::ostream& print(std::ostream& out) const override;
  private:
    uint32_t shapeType;
    std::unique_ptr<double[]> box {new double[4]};
    uint32_t numParts;
    uint32_t numPoints;
    std::unique_ptr<uint32_t[]> parts;
    std::unique_ptr<Point[]> points;
};


#endif //MAP_SRC_RECORD_H_
