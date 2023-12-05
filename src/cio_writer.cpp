#include "cio_writer.h"

CIOWriter::CIOWriter(const char *filename, int oflag)
    : CIOWriter()
{
    if (oflag & O_CREAT)
        throw std::invalid_argument("Create mode missing");

    if ((oflag & O_RDONLY) || (oflag & O_RDWR))
        throw std::invalid_argument("Contains read open");

    fd = ::open(filename, oflag);
    if (fd != -1)
    {
        try
        {
            cache = new char[CACHE_CAPACITY];
        }
        catch (const std::bad_alloc &e)
        {
            close();
            throw;
        }

        if (oflag & O_APPEND)
            fptr = -1;
    }
    else
        throw std::runtime_error(strerror(errno));
}

CIOWriter::CIOWriter(const char *filename, int oflag, mode_t mode)
    : CIOWriter()
{
    if (!(oflag & O_CREAT))
        throw std::invalid_argument("Missing O_CREAT flag");

    if ((oflag & O_RDONLY) || (oflag & O_RDWR))
        throw std::invalid_argument("Contains read open");

    fd = ::open(filename, oflag, mode);
    if (fd != -1)
    {
        try
        {
            cache = new char[CACHE_CAPACITY];
        }
        catch (const std::bad_alloc &e)
        {
            close();
            throw;
        }

        if (oflag & O_APPEND)
            fptr = -1;
    }
    else
        throw std::runtime_error(strerror(errno));
}

CIOWriter::~CIOWriter()
{
    try
    {
        flush();
    }
    catch (const std::runtime_error &e)
    {
    }
}

void CIOWriter::open(const char *filename, int oflag)
{
    if (oflag & O_CREAT)
        throw std::invalid_argument("Create mode missing");

    if ((oflag & O_RDONLY) || (oflag & O_RDWR))
        throw std::invalid_argument("Contains read open");

    bool ever_opened = (fd != -1) ? true : false;

    if (ever_opened)
        close();

    fd = ::open(filename, oflag);
    if (fd != -1)
    {
        fptr = 0;
        cache_size = 0;
        if (!ever_opened)
        {
            try
            {
                cache = new char[CACHE_CAPACITY];
            }
            catch (const std::bad_alloc &e)
            {
                close();
                throw;
            }
        }

        if (oflag & O_APPEND)
            fptr = -1;
    }
    else
        throw std::runtime_error(strerror(errno));
}

void CIOWriter::open(const char *filename, int oflag, mode_t mode)
{
    if (!(oflag & O_CREAT))
        throw std::invalid_argument("Missing O_CREAT flag");

    if ((oflag & O_RDONLY) || (oflag & O_RDWR))
        throw std::invalid_argument("Contains read open");

    bool ever_opened = (fd != -1) ? true : false;

    if (ever_opened)
        close();

    fd = ::open(filename, oflag, mode);
    if (fd != -1)
    {
        fptr = 0;
        cache_size = 0;
        if (!ever_opened)
        {
            try
            {
                cache = new char[CACHE_CAPACITY];
            }
            catch (const std::bad_alloc &e)
            {
                close();
                throw;
            }
        }

        if (oflag & O_APPEND)
            fptr = -1;
    }
    else
        throw std::runtime_error(strerror(errno));
}

size_t CIOWriter::write(const char *buf, size_t nbytes)
{
    if (fd != -1)
    {
        size_t remaining = nbytes, have_written = 0;

        while (remaining)
        {
            if (CACHE_CAPACITY == cache_size) // full
                flush();
            if (cache_size + remaining <= CACHE_CAPACITY)
            {
                memmove(cache + cache_size, buf + have_written, sizeof(char) * remaining);
                if (fptr != -1)
                    fptr += remaining;
                cache_size += remaining;
                have_written += remaining;
                remaining = 0; // break
            }
            else
            {
                size_t cache_rest_size = CACHE_CAPACITY - cache_size;
                memmove(cache + cache_size, buf + have_written, sizeof(char) * cache_rest_size);
                if (fptr != -1)
                    fptr += cache_rest_size;
                cache_size = CACHE_CAPACITY;
                have_written += cache_rest_size;
                remaining -= cache_rest_size;
            }
        }
        flush();
        return have_written;
    }
    else
        return 0;
}

void CIOWriter::flush()
{
    if (fd != -1)
    {
        ssize_t ret = ::write(fd, cache, cache_size);

        if (ret != cache_size)
            throw std::runtime_error(strerror(errno));
        else
        {
            if (fptr != -1)
                fptr += cache_size;
            cache_size = 0;
        }
    }
}
