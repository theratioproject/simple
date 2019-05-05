## simple-lang roadmap

The to dos are executed without order, mostly the most needed or simplest issue is taken up first. 
For any type of addition or subtraction to the simple-lang the **request for comment (rfc)** should be use, you can check 
out how to make  a **rfc** in the [rfc](https://github.com/simple-lang/rfcs) repository by reading the 
[readme file](https://github.com/simple-lang/rfcs/blob/master/README.md)

The roadmap is divided into sections
- [General](#general)
- [Modules](#modules)
- [Extended Modules](#extended-modules)
- [Environments](#environments)

### General

These are features which apply to the general construction of the core of the language which includes the compiler, interpreter
build, installation, features e.t.c 

- [x] create the simple-lang interpreter 
- [x] create a working installer script to enable installation with curl and bash or shell script [working issue](https://github.com/simple-lang/simple/issues/24)
- [ ] build a compiler to allow faster program execution - simplify
- [x] make scanner search for **call** files and **dynamic modules** in these folders and order. 
	- [x] use the list to itterate the search path
	- [x] 1 absolute to path
	- [x] 1 relative to modules folder in working directory
	- [x] 2 in relative to environment SIMPLE_PATH
	- [x] 1 in relative to installation folder per os 
	- [x] search in assets folder in android. ~BINGED all sources in assets are copied to external app dir on android~  
	- [x] search in **/storage/emulated/0/Android/data/<package>/files** as it where the assets are stored
	- [x] search in **sdcard/simple/sSIMPLE_VERSION/modules/** on android 
	- [x] search in **sdcard/simple/modules/** on android in assumption developer copy the module manually
	- [x] create built-in block in core_dynamic_module to add path to the modules path 
- [x] write build script for building simple-lang core, environment and modules for windows os
- [x] write build script for building simple-lang core, environment and modules for linux os
- [x] write build script for building simple-lang core, environment and modules for mac os
- [ ] write build script for building simple-lang core, environment and modules for haiku os
- [x] make linux build script generate .deb and .zip package
- [ ] presence of simple-lang codes and snippets on rosetta codes [working issue](https://github.com/simple-lang/simple/issues/20)
- [x] IRC or gitter channel for simple-lang [working issue](https://github.com/simple-lang/simple/issues/25)
- [ ] write documentation to get started with developing with simple lang
- [ ] build the language website
- [ ] write a comprehensive book on developing with simple-lang
- [ ] re write the simple-lang interpreter with lot of optimization and split into in dependable parts
- [x] load shared library in linux [working issue](https://github.com/simple-lang/simple/issues/8)
- [x] load shared library on MAC
- [x] load shared library on windows
- [ ] load shared library on haiku os
- [x] writing a vscode extension [working issue](https://github.com/simple-lang/simple/issues/13)
- [ ] add the simple-lang to the github language repository - linguistic 
- [ ] create simple-lang tag in stack overflow and simlar forums
- [ ] a suitable, befitting and upto date README on github repository
- [x] build script should build .lib for windows os
- [x] build script should create a .a archive for statically linking simple-lang runtime on windows os
- [x] build script should create a .a archive for statically linking simple-lang runtime on linux os
- [x] build script should create a .a archive for statically linking simple-lang runtime on mac os
- [ ] build script should create a .a archive for statically linking simple-lang runtime on haiku os
- [x] add a new flexible keyword **final** to lock a variable to a particular to prevent re initializing [PR](https://github.com/simple-lang/simple/pull/38)
- [ ] allow strong and weak typing to prevent inconsistent and conflicting initialization
- [ ] add directive for compiler notation in [] format
- [ ] VM should treat really really large number ad big as 10e+50
- [x] allow calling file with explicit module name translating to literal e.g `call simple.core.String` = `call "simple\core\String.sim" ? simple.core` [PR](https://github.com/simple-lang/simple/pull/34)
- [ ] Add strict equality `==` and `!=` and weak equality `===` and `!==` 
- [ ] Add the `**` operator
- [ ] allow creating multi block i.e blocks with the same name but different parameter length
- [ ] use the Karatsuba Algorithm for pure multiplication of large numbers
- [ ] reformat the way the error are thrown in the console and web 
- [ ] allow '*' to call all the file in a folder e.g simple.core.*
- [ ] update windows build file Windows-Build.bat to use main build C/C++ toolchain to build environment apps
- [ ] make simple-lang multi-threaded
- [ ] add lambda support to fetch consistent block in a class per parent classes
- [ ] make the simple.core module holds true data type e.g num = new UInteger, num = uint
- [ ] add tenary operator addition to the main syntax 
- [ ] prevent Global Interpreter Lock (GIL) (VM lock) for Better threads and concurrency for a faster execution
- [x] add support for `getter` and `setter` methods in the classes
- [x] allow changing the behaviour of operators in classes 
- [x] use of braces `{}` to access and modify fields and other in class delcaration e.g `class = new Class { }`
- [x] call the block **open** if present in class when a class is declared using brace on opening brace
- [x] call the block **close** if present in class when a class is declared using brace on closing brace
- [x] change the **catch** behaviour by allowing to call an error method in a class instead of just the error
- [ ] a more elegant stack trace and error logging in console  
- [x] resolve clashing error in using 0 base index on list items [0][0][0]
- [x] enable variadic parameter in block to allow block overloading and dynamic block. Using ellipsis = **...** after parameter
- [ ] fix `final` keyword not effective on incremental and decremental command ++ -- (move to issue)
- [ ] enable `final keyword before `class` keyword to prevent inheriting it
- [ ] enable `final` keyword before `block` keyword to prevent overriding the block in sub classes
- [ ] support using braces to call/import multiple files at once e.g `call { module1 module2 }` 
- [ ] make break from multiple loop start from index 0 instead of one `break 0` instead of `break 1`
- [ ] allow inline return of new object instance even if constructor return self
- [ ] import a module as soon as it is declared
- [ ] `private` variable outside a class should limit the variable to the file scope
- [ ] allow an overided method to be called using super as the overrided method name e.g `super(param)`
- [ ] prevent a class initialization without constructor if it has a constructor. enforce constructor if present
- [ ] by strong typing, notify class of assignment for a more native data type creation
- [x] add `import` keyword to import module in a source file, with comma seperated for importing multiple modules
- [ ] if supporting strong typing, probably allow a variable with more than one datatype e.g string|number val = 0 and val can also be val = "zero" only 
- [ ] enable the camparison between any data type and **null**
- [x] allow iterating over an object using **lengthOf** operator in place of **iterator** operator
- [ ] both false/0 and null variable should be false in a conditional statement e.g `v = null if v display "never it false it null" end`
- [ ] revisit the data types operator rules e.g list + object = list[object] should be list += object = list[object]
- [ ] completely remove the '@' operator to print expression and replace with display + newLine
- [ ] get ride of the global variable `cmdparams` which hold the command line parameters for optional arguments in `main()` block
- [ ] add option for configure to install an old version of gcc for building compatible binaries in *nux-Build scripts. **preferable gcc-6 g++-6**
- [ ] add option to use a version of gcc/g++ compiler for build, *nix.
- [ ] replace the Makefiles in dynamic modules to use a simple conf file
- [ ] enforce variables to be created using keyword or the Type **?**
- [ ] natively attend to escape characters
- [ ] use the operator method for assignment also, putting the shallow or deep copy option in developer control
- [x] change 'call' keyword to 'from' for loading module
- [x] change 'invoke' keyword to 'call' for calling lambda block
- [ ] change the method **execCode** to **eval**
- [x] use the Error method in classes to attend to error that occur when class access is in braces

### simplify
- [ ] create and optimize simple source before compiling into bytecode (.complex)
- [ ] does not compile the following, removing in the order below
	- [ ] variable
	- [ ] block and method
	- [ ] class 
	- [ ] module
- [ ] hint user as a type of level error when a similar variable that has not been declared is used 
- [ ] ~add support for directive '##' for compile time cutomization~
- [ ] display verbose warning and errors when using the compiler 
- [ ] add and use the keyword `var` to allow variable declaration
- [ ] directive : allow the use of strict declaration to render undefine variable error `see perl 'use strict;'`
- [-] ~allow the `&` operator to pass a parameter by reference~
- [ ] compiles to .complex file
- [ ] compiles simple bytecodes into Web Assembly Text File (WAT) 
- [ ] option to encrypt string in bytecode, if available the VM take option to determine if string is encrypted
- [ ] inline variables and function calls e.g final CONST = __CONST() becomes __CONST() in the bytecode

### Modules

To dos and features relative to the simple-lang standard modules which includes new modules addition, module modification or any other
issue related to the module

- [ ] change all existing module methods and function identifier to starts with Capital letter instead of small letter
- [ ] make the conf.sim file in dynamic module folder for compiling dynamic module instead of makefiles 
- [ ] Makefiles for various platform can be generated from the options in dynamic module conf.sim
- [ ] generate static dynamic modules for static building for bake, making DynamicLoader.sim aware of statically link dynamic module
- [ ] add makefile for building fulltick on windows
- [x] create the input output (io) module which include
	- [x] File
	- [x] Path
	- [x] Directory
	- [ ] FileReader
	- [x] FileWriter
- [ ] create all high level data types [working issue](https://github.com/simple-lang/simple/issues/15)
- [x] init functional console module to simplify working with command line and terminal 
- [x] resolve the string lib to accurately unescape characters
- [x] building a better debugging module [working issue](https://github.com/simple-lang/simple/issues/17)
- [ ] develop the complete functional GUI module (fulltick) using the fltk c++ library
	- [ ] call and execute events natively
	- [x] cutomize widget to look native 
	- [ ] remove validatePointer() block after contructor has been enforced in VM
	- [ ] add custom event listener to FMenuItem such as Inactive, Removal, Add e.t.c 
	- [ ] export Fl_Menu_Item.H struct 
	- [ ] css to set the style
- [ ] port qt library to simple-lang for a higher GUI module 
- [ ] create database module for simple-lang which includes mysql, sqlite, odbc and access
	- [ ] build the mysql database module
	- [ ] build the sqlite database module
	- [ ] build the odbc database module
	- [ ] build the access database module
	- [ ] build the postgresql database module
- [ ] build the net module using curl as the back bone
	- [x] make curl request and accept both http and https protocols
- [ ] build a web module for cgi and template base development
- [x] Math module to treat any form of basic math operation
	- [ ] add various multiplication method in the math module including Karatsuba algorithm
	- [ ] include a block that fetch the number of factors a number have and another that return a list of a number factors
- [-] date and time module 
- [ ] conversion module to convert between objects and types 
- [ ] system, simplex and runtime module
- [x] create the hash module 
- [x] a basic encrypt and decrypt module that uses keys and IV
- [ ] port murmur hash C library to simple-lang
- [ ] implement ncurses for use in simple-lang
- [ ] use a light and simple alternate ANSI C internet library for networking
- [ ] parser.json module to parse and create json string
	- [x] load json from string and create json from class, list and manually
	- [ ] a json module that load the json file and store as class attributes and fields and allow writing back to file
	- [ ] use reflection to serialize and deserialize object into json
- [x] reStructuredText parser module to read rst file into usable tokens
- [x] create a built in block to get hex as number using `H("0x00")
- [ ] build a comprehensive color module in simple.system
- [ ] create a look ahead class for pure string and file stream for parser implementation
	- [x] LookAhead class for pure string. `simple.utilities.LookAhead`
	- [ ] for file stream or file reader. `simple.io.LookAheadReader`
- [ ] create block to locate resources in possible locations with file name and program name e.g `locateResource(string programName, string name)`
- [ ] create proper encodings module
- [ ] implement a matrix module with base type of list in simple.core
- [ ] stop moving libsimple_fulltick dynamic module after SIDE has been created
- [ ] write better and more robust strSplit function
- [ ] re implement the String class completely in simple-lang without depending on libstring_savant
- [ ] implement foreach method in any class that operate on array, accepting anonymous block as parameter with the anonymous block parameter corresponding to the element structure

### Extended Modules

Modules which are not part of the standard module that comes distributed with simple-lang. These modules are only avilable for use by downloading the release versions or using the simple-lang module manager **modular** to install them. These sources are hosted in a seperate repository but in the same organization. [source here.](https://github.com/simple-lang/extended-modules/)

- [ ] create material and native os extended module for fulltick GUI module
- [ ] a module that convert fultick Widget to HTML element
- [ ] write a C/C++ parser module to scan C/C++ sources into resuable token groups 
- [ ] move the libstring_savant dynamic module to extended modules

### Environments

- [ ] modular
	- [ ] build package installer - modular [working issue](https://github.com/simple-lang/simple/issues/18)
	- [ ] modular install and upgrade new module, doc and dynamic module added to the package index
	- [ ] modular clone and install module from github repository
	- [ ] upgrade simple-lang distro on the system from either dev or stable version
	- [ ] test full operation on windows os
	- [ ] test full operation on linux os
	- [ ] test full operation on mac os
	- [ ] test full operation on haiku os
	
- [x] simplerepl 
	- [x] execute multi-line code
	- [x] read input from terminal
	- [ ] extend simple-repl functionalities (Case Study : elixr iex)
	
- [x] ~minifier~
	- [x] ~reduces module size by compressing code upon installation. (if skip compilation)~

- [ ] bake
	- [ ] read simple bytecodes (.complex) and write to C/C++ for speed and more C optimization
	- [ ] use a small compiler to generate executable
	- [x] package simple compiled file (.complex) to system executable
	- [x] package simple compiled file (.complex) to system library or simple-lang specific library
	- [x] create directory for generated output
	- [ ] allow static linking of simple-lang runtime
	- [x] allow dynamic linking of simple-lang runtime
	- [ ] minify and build a distributable modules and dynamic modules for distribution
	- [ ] test full operation on windows os
	- [ ] test full operation on linux os
	- [ ] test full operation on mac os
	- [ ] test full operation on haiku os
	
- [ ] build the documentation environment to read comment from source into reStructuredText
	- [ ] generate conf.py for sphinx
	- [ ] generatemake.bat and Makefile for sphinx build
	- [ ] auto create index pages for each folder
	- [ ] allow linking to raw source code
	
- [ ] simplem 
	- [ ] enable executing the **simple.sim** script in module folder i`simplem archive.zip -l [zipfile]`
	- [ ] check for the module first in relative to the current directory
	- [ ] check for the module in the standard modules location

- [ ] smoothc
	- [ ] auto create simple dynamic module from a C/C++ Header file
	- [ ] dispose unassigned pointer in function
	- [ ] struct is a small class with all the variables working
	- [ ] callback functions in C/C++ can be replaced by native simple function
	- [ ] option to change exported struct to conform with Naming Style in simple
	- [ ] export struct pointer with create and destroy function
	- [ ] enable overloaded function export from C/C++
	- [ ] resolve addressOf and & operator while creating funtions
	
- [ ] side
	- [working issue](https://github.com/simple-lang/simple/issues/18)
	- [ ] able to debug and manipulate complex files
	- [ ] break point enable in the program but hidden in editor and build
	- [ ] can preview and parse Mark Down



