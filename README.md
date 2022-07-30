## FontDump

A dumper for Xenoblade 2/DE FNTC files, which writes all glyphs out to a single png file.

Based on [tipdump](https://github.com/modeco80/tipdump).

## Usage

```
Usage: fontdump [Path to font file]
```

## Building

### Requirements

 - A C++20 compiler
 - CMake

To build:

```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
...
Profit?
```
