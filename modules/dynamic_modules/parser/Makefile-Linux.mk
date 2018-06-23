#Build PARSER dynamic module for LINUX
#
#There is no tool or dependency needed on a typical linux
#installation. To build the simple.so and simple change your
#directory to the modules/dynamic_modules/consoler/ folder 
#
#user $ cd modules/dynamic_modules/parser/
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#simple/src/makefiles/parser/ $ make -f Makefile-Linux.mk

# Flags
CFLAGS= -c -fpic -g -w
LFlAGS= -lm -ldl
LDFLAGS= "-Wl,--no-as-needed"

# Macros
CND_PLATFORM=
CND_DLIB_EXT=so
CND_BUILDDIR=build
CND_DISTDIR =../dist

# Object Directory
OBJECTDIR=$(CND_DISTDIR)/$(CND_BUILDDIR)/$(CND_PLATFORM)

# Simple Object Directory
SIMPLE_OBJECTDIR=../../../simple/dist/$(CND_BUILDDIR)/$(CND_PLATFORM)

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/arraylist.o \
	${OBJECTDIR}/debug.o \
	${OBJECTDIR}/json_object.o \
	${OBJECTDIR}/json_tokener.o \
	${OBJECTDIR}/json_util.o \
	${OBJECTDIR}/linkhash.o \
	${OBJECTDIR}/printbuf.o \
	${OBJECTDIR}/parser.o

# Simple Object Files
SIMPLE_OBJECTFILES = \
	$(SIMPLE_OBJECTDIR)/simple_api.o 
	
# Link Libraries and Options
LDLIBSOPTIONS= -Lsimple.so

${CND_DISTDIR}/${CND_PLATFORM}/parser.${CND_DLIB_EXT}: $(OBJECTFILES)
	$(CC) -shared -o $(CND_DISTDIR)/$(CND_PLATFORM)/parser.$(CND_DLIB_EXT) $(SIMPLE_OBJECTFILES) $(OBJECTFILES)
	
$(OBJECTDIR)/arraylist.o: includes/arraylist.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/arraylist.c
	mv arraylist.o $(OBJECTDIR)
	
$(OBJECTDIR)/debug.o: includes/debug.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/debug.c
	mv debug.o $(OBJECTDIR)
	
$(OBJECTDIR)/json_object.o: includes/json_object.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/json_object.c
	mv json_object.o $(OBJECTDIR)
	
$(OBJECTDIR)/json_tokener.o: includes/json_tokener.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/json_tokener.c
	mv json_tokener.o $(OBJECTDIR)
	
$(OBJECTDIR)/json_util.o: includes/json_util.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/json_util.c
	mv json_util.o $(OBJECTDIR)
	
$(OBJECTDIR)/linkhash.o: includes/linkhash.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/linkhash.c
	mv linkhash.o $(OBJECTDIR)
	
$(OBJECTDIR)/printbuf.o: includes/printbuf.c
	mkdir -p $(OBJECTDIR)
	$(CC) $(CFLAGS) includes/printbuf.c
	mv printbuf.o $(OBJECTDIR)

$(OBJECTDIR)/parser.o: parser.c
	$(CC) $(CFLAGS) parser.c
	mv parser.o $(OBJECTDIR)

clean:
	@- $(RM) $(OBJECTDIR)/*.o
	@- $(RM) $(program_OBJS)

distclean: clean

#This Makefile-Windows.mk was written in adaptation to the standard
#method of writing makefiles
#
#If this make file does not work on your LINUX PC feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/modules . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Linux-{distro}.mk
#
#e.g Makefile-Linux-mint-cinnamon.mk
#
#looking forward to your contribution
#Thank You
