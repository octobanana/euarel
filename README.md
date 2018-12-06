# Euarel
A CLI tool for URL percent-encoding and percent-decoding text.

## Build
Environment:
* Tested on Linux
* C++17 compiler
* CMake >= 3.8

Libraries:
* my [parg](https://github.com/octobanana/parg) library, for parsing cli args, included as `./src/parg.hh`

The following shell command will build the project in release mode:
```sh
./build.sh -r
```
To build in debug mode, run the script with the `-d` flag.

## Install
The following shell command will install the project in release mode:
```sh
./install.sh -r
```
To install in debug mode, run the script with the `-d` flag.
