//
// Created by Nick_Grout on 11/19/19.
//

#include <iostream>
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

class PolygonRecord: public Record {
  public:
    std::istream& readIn(std::istream& in);
    std::ostream& print(std::ostream& out) const;
};


#endif //MAP_SRC_RECORD_H_
