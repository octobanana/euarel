# Euarel
A CLI tool for URL percent-encoding and percent-decoding text.

Euarel is a command line tool for URL percent-encoding and percent-decoding UTF-8 encoded text.
It is unicode aware, so characters like `♥ = %E2%99%A5` or `π = %CF%80` are properly handled.
Working with the media type `application/x-www-form-urlencoded` is possible by passing the `--form` flag.

Examples:
```
euarel --encode 'text to encode'
euarel --decode 'text to decode'
euarel -ef 'encode form data'
printf 'redirect text to encode' | euarel -e
euarel --help
euarel --version
```

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
