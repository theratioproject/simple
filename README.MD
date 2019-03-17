
# <p style="text-align: center;" align="center">Simple</p>

<p style="text-align: center;" align="center">The Simple Intelligent and Modular Programming Language and Environment</p>

___

| Platform / Architecture  | Build Status |
|--------------------------|--------------|
| Windows (7, 8, 10, ...)  | [![Simple Windows Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/)   |
| Linux (2.6.18 or later)  | [![Simple Linux Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/)   |
| OSX (10.7 Lion or later) | [![Simple OSX Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/)   |
| Android (SDK 16 or later) | [![Simple Android Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/)   |
| Android Termux | [![Simple Android Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/simple-lang/simple/)   |
| IOS | [![Simple IOS Build](https://img.shields.io/badge/build-pending-yellow.svg)](https://github.com/simple-lang/simple/)   |

___

[![Download simple-lang](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/simple-lang/files/s0.4.0/) 

## Building from source

simple provide self sufficent platform scripts for some of the platform below for building simple successfully with less or no effort at all. 
The scripts are [here](./build/). Each script has the following options to customize your build or avoid building a failing section.
```bash
[FLAGS] :
        -c --configure  configure your system for simple-lang successful build
        -i --install    install simple-lang on your system
        -b --build-dir  manually enter folder to install simple-lang
        -u --uninstall  uninstall simple-lang from your system
        -d --debug      create a distributable version in ..\..\ source directory
        x86 --32-bit    build 32 bit version of simple-lang
        x64 --64-bit    build 64 bit version of simple-lang
        -t --temp       keep the */dist/ folder(s) in source tree
        -h --help       print this help message
        -min --minify   minify all modules sources (Not Recommended for Debug Purpose)

[STANDALONE BUILD FLAGS]
        -so --simple-only       build only simple.exe, simplew.exe and libsimple.dll
        -do --dep-only          build only the dependencies
        -io --include-only      copy only the simple include files
        -mo --modules-only      copy only the standard modules
        -yo --dymodules-only    build only the dynamic modules
        -eo --environment-only  build only the environment programs
```
If you just clone this repository you should first configure your system for a successful building by using the **-c** flag, this 
process requires internet connection because all dependencies will be downloaded with an execption to Windows which has no particular libraries location.

Download this repository and extract to a working folder or clone this repository into a working folder using git
```bash
 $ git clone https://github.com/simple-lang/simple.git
```
After downloading simple source from either methods listed above, continue with the instruction for your platform below.

- [Building on Linux](#building-on-linux)
- [Building on OSX](#building-on-osx)
- [Building on Windows](#building-on-windows)
- [Building on Android](#building-on-android)
- [Building on Android Termux](#building-on-android-termux)

### Building on Linux

##### Configure
For the first time using the script configure your building enviroment
```bash
 $ cd build
 $ sudo bash ./Linux-Build.sh -c
```

##### Installing
Proceed to install simple-lang on your system and start using from any directory. After it complete you can execute sim scripts from any folder
```bash
 $ sudo bash ./Linux-Build.sh x64 -i
```

##### Debugging
If you wish to debug simple build or try it before installing in your system executable space use the **-d** flag. 
Note : this will allow more debugging flag in simple such that you can debug upto the VM Stack level
```bash
 $ sudo bash ./Linux-Build.sh x64 -d
```
After running the command above simple will be installed in the same directory you clone simple source into in the following format `s$Version-debug`
+ simple
	+ build
+ s$Version-debug
	+ bin

### Building on OSX

##### Configure
For the first time using the script configure your building enviroment
```bash
 $ cd build
 $ sudo bash ./Mac-Build.sh -c
```

##### Installing
Proceed to install simple-lang on your system and start using from any directory. After it complete you can execute sim scripts from any folder
```bash
 $ sudo bash ./Mac-Build.sh x64 -i
```

##### Debugging
If you wish to debug simple build or try it before installing in your system executable space use the **-d** flag. 
Note : this will allow more debugging flag in simple such that you can debug upto the VM Stack level
```bash
 $ sudo bash ./Mac-Build.sh.sh x64 -d
```

### Building on Windows

It obvious windows does not have a central base for dependencies like the *nix oses, all the dependencies such as [curl](https://curl.haxx.se/libcurl/), 
[openssl](https://www.openssl.org/), [fltk](https://www.fltk.org/), will have to be manually download and added to a global directory where windows 
could find them at compile time, this dependencies are only for the dynamic modules and does not affect the main simple executable and shared library also 
other dynamic modules does not need these dependencies and can be built independently.

##### Build Toolchain

simple currently uses the MinGW toolchain that can be downloaded [here](http://www.mingw.org/), add the directory where gcc and make is to your environment
 path. 
 
##### Installing
Proceed to install simple-lang on your system and start using from any directory. After it complete you can execute sim scripts from any folder
```bash
 $ ./Windows-Build.bat x64 -i -so
```

##### Debugging
If you wish to debug simple build or try it before installing in your system executable space use the **-d** flag. 
Note : this will allow more debugging flag in simple such that you can debug upto the VM Stack level
```bash
 $ ./Windows-Build.bat x64 -d -so
```
After running the command above simple will be installed in the same directory you clone simple source into in the following format `s$Version-debug`
+ simple
	+ build
+ s$Version-debug
	+ bin

### Building on Android

This require the following dependencies <br />
ANDROID SDK [https://developer.android.com/studio/](https://developer.android.com/studio/) <br />
ANDROID NDK [https://developer.android.com/ndk/](https://developer.android.com/ndk/) <br />
FLTK [https://www.fltk.org/](https://www.fltk.org/) <br />
Read full instruction on building your first android app with simple-lang [here](https://simple-lang.sourceforge.io/blog/android-build)

### Building on Android Termux

[Termux](https://termux.com/) is a free and open code app that simulates the command shell used in Linux. By doing so, you can introduce all the usual commands and work comfortably from your Android device.

All simple section compiles fine on the termux app and you can test all the source file scripts in the [examples](./examples/) folder with exception for 
the **[fulltick](https://github.com/simple-lang/simple/tree/master/modules/fulltick)** module with build is still under way.

##### Configure
For the first time using the script configure your building enviroment
```bash
 $ cd build
 $ bash ./Android-Termux-Build.sh -c
```

##### Installing
Proceed to install simple-lang on your system and start using from any directory. After it complete you can execute sim scripts from any folder
```bash
 $ bash ./Android-Termux-Build.sh x64 -i
```

##### Debugging
If you wish to debug simple build or try it before installing in your system executable space use the **-d** flag. 
Note : this will allow more debugging flag in simple such that you can debug upto the VM Stack level
```bash
 $ sudo bash ./Android-Termux-Build.sh x64 -d
```
After running the command above simple will be installed in working home directory in termux `~/`
```
 $ cd ~/
 $ cd s$Version-debug/bin/
```

### Note

This project is still so much in it infancy, unexpected failure, seg-faults, errors should be expected therefore it not advisable to build seroius project in it. But if you build something cool with it or a usefull module you can share with the community on Twitter [@thesimplelang](https://twitter.com/thesimplelang) or write to **whatisthis914@gmail.com**. And also we love issues if it make the project better [here](https://github.com/simple-lang/simple/issues).

### Contributors

We love contributors. This is an open source project and needs the supports of the community extensively. Check out the [contributing guide](./CONTRIBUTORS.MD)

### License

MIT License Copyright (c) 2018 simple Built with :heart: in Nigeria
