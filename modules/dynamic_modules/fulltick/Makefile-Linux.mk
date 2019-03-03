#Build archiver dynamic module for LINUX
#
#There is no tool or dependency needed on a typical linux
#installation. To build the fulltick.so change your
#directory to the modules/dynamic_modules/fulltick/ directory 
#
#user $ cd modules/dynamic_modules/archiver/
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#simple/modules/dynamic_modules/fultick $ make -f Makefile-Linux.mk

# Flags
CFLAGS= -c -fpic -g -w
FLTKFlAGS=
LDFLAGS= -lpthread -ldl -lm -lX11 -lXfixes -lXinerama -lfontconfig -lXft -lXcursor
LDFLAGS:= $(LDFLAGS) "-Wl,-rpath,./ ../../bin/ $(DESTDIR)$(PREFIX)/lib/ ~/lib/,--no-as-needed"

# Macros
CND_PLATFORM=
CND_DLIB_EXT=so
CND_BUILDDIR=build
CND_DISTDIR =../dist
FULLTICK_FILES='./fulltick.cpp' 
	
# Link Libraries and Options
LDLIBSOPTIONS=-Lsimple.so

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

clean: 
	g++ -shared -fpermissive -w -fPIC $(ARC_FLAG) -I$(DESTDIR)$(PREFIX)/include -I$(DESTDIR)$(PREFIX)/include/FL/images ${FLTKFLAGS}  -fvisibility-inlines-hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT -o '$(CND_DISTDIR)/$(CND_PLATFORM)/libfulltick.$(CND_DLIB_EXT)' $(FULLTICK_FILES)  -l:libfltk.a $(LDFLAGS) $(LDLIBSOPTIONS)
	cp -R ${CND_DISTDIR}/${CND_PLATFORM}/libfulltick.${CND_DLIB_EXT} ./dist/libfulltick$(ARC).${CND_DLIB_EXT}

distclean: clean

#This Makefile-Windows.mk was written in adaptation to the standard
#method of writing makefiles
#
#If this make file does not work on your LINUX PC feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/simple . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Linux-{distro}.mk
#
#e.g Makefile-Linux-mint-cinnamon.mk
#
#looking forward to your contribution
#Thank You
