#include "cio_reader.h"

CIOReader::CIOReader(const char *filename)
    : CIOReader()
{
    fd = ::open(filename, O_RDONLY);
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
    }
    else
        throw std::runtime_error(strerror(errno));
}

void CIOReader::open(const char *filename)
{
    bool ever_opened = (fd != -1) ? true : false;

    if (ever_opened)
        close();

    fd = ::open(filename, O_RDONLY);
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
    }
    else
        throw std::runtime_error(strerror(errno));
}

size_t CIOReader::read(char *buf, size_t bufsize)
{
    if (fd != -1)
    {
        size_t remaining = bufsize, have_read = 0;

        while (remaining)
        {
            if (0 == cache_size)
            {
                ssize_t ret = ::read(fd, cache, CACHE_CAPACITY);

                if (ret < 0)
                    throw std::runtime_error(strerror(errno));
                else
                {
                    cache_size = ret;

                    if (0 == ret) // end of file
                        fptr = -1;
                    else
                        fptr += ret;
                }
            }

            if (cache_size >= remaining)
            {
                memmove(buf + have_read, cache, sizeof(char) * remaining);
                memmove(cache, cache + remaining, sizeof(char) * (cache_size - remaining));
                fptr += remaining;
                cache_size -= remaining;
                have_read += remaining;
                remaining = 0; // break
            }
            else
            {
                if (fptr != -1)
                {
                    memmove(buf + have_read, cache, sizeof(char) * cache_size);
                    fptr += cache_size;
                    have_read += cache_size;
                    remaining -= cache_size;
                    cache_size = 0;
                }
                else               // end of file
                    remaining = 0; // break
            }
        }

        return have_read;
    }
    else
        return 0;
}