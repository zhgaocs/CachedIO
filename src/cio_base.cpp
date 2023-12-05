#include "cio_base.h"

CIOBase::CIOBase()
    : fd(-1), fptr(0), cache(nullptr), cache_size(0)
{
}

CIOBase::~CIOBase()
{
    if (cache)
        delete[] cache;
    try
    {
        close();
    }
    catch (const std::runtime_error &e)
    {
    }
}

bool CIOBase::is_open() const noexcept
{
    return (fd != -1);
}

void CIOBase::seek(off_t offset, int whence) noexcept
{
    if (fd != -1)
    {
        off_t len = ::lseek(fd, 0, SEEK_END);

        switch (whence)
        {
        case SEEK_SET:
        {
            if (offset >= len)
                fptr = -1;
            else if (offset < 0)
                fptr = 0;
            else
                fptr = ::lseek(fd, offset, SEEK_SET);
            break;
        }
        case SEEK_CUR:
        {
            fptr = ::lseek(fd, fptr + offset, SEEK_SET);

            if (fptr >= len)
                fptr = -1;
            else if (fptr < 0)
                fptr = 0;
            else
                ;
            break;
        }
        case SEEK_END:
        {
            if (offset >= 0)
                fptr = -1;
            else if (len + offset < 0)
                fptr = 0;
            else
                fptr = ::lseek(fd, offset, SEEK_END);
            break;
        }
        default:
            break;
        }
    }
}

off_t CIOBase::tell() const noexcept
{
    return fptr;
}

bool CIOBase::eof() const noexcept
{
    return (-1 == fptr);
}

void CIOBase::close()
{
    if (fd != -1)
    {
        if (::close(fd) != 0)
            throw std::runtime_error(strerror(errno));
        else
            fd = -1;
    }
}
