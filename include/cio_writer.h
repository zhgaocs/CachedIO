#ifndef CIO_WRITER_H
#define CIO_WRITER_H 1

#include "cio_base.h"

class CIOWriter : virtual public CIOBase
{
public:
    CIOWriter() = default;
    CIOWriter(const char *filename, int oflag);
    CIOWriter(const char *filename, int oflag, mode_t mode);
    CIOWriter(const CIOWriter &other) = delete;
    CIOWriter &operator=(const CIOWriter &other) = delete;
    ~CIOWriter() override; // virtual

public:
    void open(const char *filename, int oflag);
    void open(const char *filename, int oflag, mode_t mode);
    size_t write(const char *buf, size_t nbytes);
    void flush();
};

#endif