[![Simple License](https://img.shields.io/github/license/simple-lang/simple.svg)](https://github.com/simple-lang/simple/blob/master/LICENSE)
[![Popular Language](https://img.shields.io/github/languages/top/simple-lang/simple.svg)](https://github.com/simple-lang/simple/search?l=c)
[![Boot App Build](https://img.shields.io/badge/bootapp--build-passed-brightgreen.svg)](https://github.com/simple-lang/simple/tree/master/bootsrc/) 
[![Simple Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/) 
[![Simple release](https://img.shields.io/github/release/simple-lang/simple/all.svg)](https://github.com/simple-lang/simple/releases/)
[![Last Commit](https://img.shields.io/github/last-commit/simple-lang/simple.svg)](https://github.com/simple-lang/simple/commits/master)
[![Pull Request](https://img.shields.io/github/issues-pr-closed/simple-lang/simple.svg)](https://github.com/simple-lang/simple/issues?q=is%3Apr+is%3Aclosed)
# Simple

The Simple Intelligent and Modular Programming Language and Environment</br>
Current Version : 0.3.213
![simple-repl](https://i.imgur.com/qx5bbc3.png)

### About Simple
SIMPLE is a plain and innovative programming with multi-paradigm. It can be embedded in C/C++ projects. The language is portable to various OS including windows, macOS, any linux and unix distros and other OS. The language is small and fast.

### Features
Simple has features every programming language will have such as variable declarations, functional programming, Object oriented programming etc and more to come. It houses all these features as it parent architecture comes from **C**. Simple is weakly typed, no explicit end of line required and can be embedded in C and C++ projects. Portability with javascript is a major goal we're trying and going to achieve.

### Downloading & Installing SIMPLE.
Simple has compilers that can be installed in our Windows/Linux/Mac systems. Simple can either be cloned, downloaded as zip or gotten from [here](https://simple-lang.sourceforge.io/)
Below are the procedures for installing on each system respectively.

#### Installing on Windows.
This is quite the easiest installation. Download the windows type file from [here](https://simple-lang.sourceforge.io/) and run.

#### Installing on Linux 
After downloading simple from either methods listed above, unzip/move into the SIMPLE folder from your console and follow the instructions below.
```sh
# Copy make file from bootsrc/makefiles/inux to sources
$ cp bootsrc/makefiles/linux/Makefile bootsrc/sources
# install simple with the "make" command.
$ make
```
Wait for a few moments, probably a minute. The make file installs simple in a folder *dist* located in the **bootsrc** folder. start the SIMPLE compiler with the command 
```sh
./simple
```
##### Got an error ?
Was there an error stating **simple.so** couldn't be found ?. Use this command every time once you're in the folder via the console.
```sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./
```
##### Unable to add to global path.
Sadly, we're working on that issue and a fix will be issued in the next release.

#### Installing on Mac
To install on Mac, the same procedures are followed but some small differences. Steps to install..
After downloading the Mac package, navigate to the home folder of SIMPLE and run commands.
```sh
# Copy make file from bootsrc/makefiles/inux to sources
$ cp bootsrc/makefiles/mac/Makefile bootsrc/sources
# install simple with the "make" command.
$ make
```
Boom, we have simple installed.

### Getting started.
You can check the unofficial documentation / guide to simple as the official documentation comes up. Get acquainted with SIMPLE's syntax [**HERE**](https://github.com/simple-lang/simple/blob/master/doc/Simple-Mini-Tutorial-v1.0)
### Contributors.
We love contributors. This is an open source project and needs the supports of the community extensively. Check out the [contributing guide](/CONTRIBUTORS.MD)
### License
MIT License 

Copyright (c) 2018 simple

 Built with :heart: in Nigeria
