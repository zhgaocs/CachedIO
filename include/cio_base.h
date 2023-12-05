#ifndef CIO_BASE_H
#define CIO_BASE_H 1

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdexcept>

#ifndef CACHE_CAPACITY
#define CACHE_CAPACITY 16
#endif

class CIOBase
{
public:
    CIOBase(const CIOBase &other) = delete;
    CIOBase &operator=(const CIOBase &other) = delete;

protected: // prevent base class instantiation
    CIOBase();
    virtual ~CIOBase();

public:
    bool is_open() const noexcept;
    void seek(off_t offset, int whence) noexcept;
    off_t tell() const noexcept;
    bool eof() const noexcept;
    void close();

protected:
    int fd;
    off_t fptr;
    char *cache;
    size_t cache_size;
};

#endif