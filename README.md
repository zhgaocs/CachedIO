# CachedIO

CachedIO encapsulates Linux APIs such as `open`, `close`, `read`, and `write`.

## Project Structure

```
.
├── CMakeLists.txt
├── README.md
├── include
│   ├── cio_base.h
│   ├── cio_reader.h
│   └── cio_writer.h
├── src
│   ├── cio_base.cpp
│   ├── cio_reader.cpp
│   └── cio_writer.cpp
└── test
    └── main.cpp
```

## Building and Testing

1. Clone the repository

```bash
git clone https://github.com/zhgaocs/CachedIO.git
```

2. Navigate to the project directory

```bash
cd CachedIO
```

3. Create a build directory

```bash
mkdir build && cd build
```

4. Configure and build

```bash
cmake ..
make
```

5. Run the test

```bash
./cio-test <file>
```
