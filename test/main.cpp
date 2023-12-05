#include <iostream>
#include "cio_reader.h"
#include "cio_writer.h"

#define BUF_SIZE 500

int main(int argc, char*argv[])
{
    if(argc != 2)
        std::cerr << "Usage: " << argv[0] << " <file>\n";
    else
    {
        CIOWriter cw;
        char buf[] = "\tgaozhihui\n";
        
        cw.open(argv[1], O_WRONLY);
        cw.write(buf, sizeof(buf) - 1);
        cw.close();
    }
}
