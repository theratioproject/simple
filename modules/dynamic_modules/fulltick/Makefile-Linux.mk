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
CFLAGS= -c -fpic -g
LFlAGS= -fvisibility-inlines-hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT 
LDFLAGS= -lpthread -ldl -lm -lX11

# Macros
CND_PLATFORM=
CND_DLIB_EXT=so
CND_BUILDDIR=build
CND_DISTDIR =../dist

# Object Directory
OBJECTDIR=$(CND_DISTDIR)/$(CND_BUILDDIR)/$(CND_PLATFORM)

# Object Files
OBJECTFILES= \
	$(OBJECTDIR)/fulltick.o \
	$(OBJECTDIR)/fulltick_delegate.o
	
# Link Libraries and Options
LDLIBSOPTIONS=../../../simple/dist/simple.so

${CND_DISTDIR}/${CND_PLATFORM}/fulltick.${CND_DLIB_EXT}: $(OBJECTFILES) 
	g++ -shared -I/usr/local/include -I/usr/local/include/FL/images $(LFLAGS) -o '$(CND_DISTDIR)/$(CND_PLATFORM)/fulltick.$(CND_DLIB_EXT)' $(OBJECTFILES)  /usr/local/lib/libfltk.a $(LDFLAGS) $(LDLIBSOPTIONS)

$(OBJECTDIR)/fulltick.o: fulltick.cpp
	mkdir -p $(OBJECTDIR)
	g++ $(CFLAGS) fulltick.cpp
	mv fulltick.o $(OBJECTDIR)

$(OBJECTDIR)/fulltick_delegate.o: fulltick_delegate.cpp
	mkdir -p $(OBJECTDIR)
	g++ $(CFLAGS) fulltick_delegate.cpp
	mv fulltick_delegate.o $(OBJECTDIR)

clean:
	@- $(RM) $(OBJECTDIR)/*.o
	@- $(RM) $(program_OBJS)

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
