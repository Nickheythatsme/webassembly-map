#include "shapefile.h"
#include <stdio.h>

ShapefileReader::ShapefileReader(const char* fname):
    file(fname),
    header(new ShapefileHeader())
{
    if (!fname) {
        printf("Could not open file: %s\n", fname);
        return;
    }
    readHeader();
}

void ShapefileReader::readHeader()
{
    file.seekg(0);
    header->file_code = readLongBE(file);
    printf("%u\n", header->file_code);
    file.ignore(20);
    header->file_length = readLongBE(file);
    printf("%u\n", header->file_length);
}