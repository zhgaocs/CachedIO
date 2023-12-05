#ifndef CIO_READER_H
#define CIO_READER_H 1

#include "cio_base.h"

class CIOReader : virtual public CIOBase
{
public:
    CIOReader() = default;
    CIOReader(const char *filename);
    CIOReader(const CIOReader &other) = delete;
    CIOReader &operator=(const CIOReader &other) = delete;
    ~CIOReader() override = default;

public:
    void open(const char *filename);
    size_t read(char *buf, size_t bufsize);
};

#endif