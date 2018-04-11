#Build simple for LINUX
#
#There is no tool or dependency needed on a typical linux
#installation. To build the simple.so and simple change your
#directory to the simple/src/makefiles/ folder 
#
#user $ cd simple/src/makefiles/  
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#simple/src/makefiles/ $ make -f Makefile-Linux.mk

# Flags
CFLAGS= -c -fpic -g
LFlAGS= -lm -ldl
LDFLAGS= "-Wl,-rpath,../dist/"

# Macros
CND_PLATFORM=
CND_DLIB_EXT=so
CND_BUILDDIR=build
CND_DISTDIR =../dist
CLEAN_DEBUGDIR=../../../s0.3.302-debug
BINARYDIR=bin
SOURCE_DIR=../sources

# Object Directory
OBJECTDIR=$(CND_DISTDIR)/$(CND_BUILDDIR)/$(CND_PLATFORM)

# Object Files
OBJECTFILES= \
	$(OBJECTDIR)/simple_api.o \
	$(OBJECTDIR)/simple_codegen.o \
	$(OBJECTDIR)/simple_expr.o \
	${OBJECTDIR}/simple_hashtable.o \
	${OBJECTDIR}/simple_item.o \
	${OBJECTDIR}/simple_list.o \
	${OBJECTDIR}/simple_misc.o \
	${OBJECTDIR}/simple_parser.o \
	${OBJECTDIR}/simple_scanner.o \
	${OBJECTDIR}/simple_state.o \
	${OBJECTDIR}/simple_stmt.o \
	${OBJECTDIR}/simple_string.o \
	${OBJECTDIR}/simple_vm.o \
	${OBJECTDIR}/simple_vmblock.o \
	${OBJECTDIR}/simple_vmdll.o \
	${OBJECTDIR}/simple_vmexpr.o \
	${OBJECTDIR}/simple_vmgc.o \
	${OBJECTDIR}/simple_vmlists.o \
	${OBJECTDIR}/simple_vmoop.o \
	${OBJECTDIR}/simple_vmperformance.o \
	${OBJECTDIR}/simple_vmstackvars.o \
	${OBJECTDIR}/simple_vmstate.o \
	${OBJECTDIR}/simple_vmstrindex.o \
	${OBJECTDIR}/simple_vmvars.o
	
# Simple Object File
SIMPLE_OBJECTFILES= \
	${OBJECTDIR}/simple.o

$(CND_DISTDIR)/$(CND_PLATFORM)/simple: $(OBJECTFILES)
	$(CC) -shared -o $(CND_DISTDIR)/simple.$(CND_DLIB_EXT) $(OBJECTFILES)
	$(CC) $(LFlAGS) $(LDFLAGS) -o $(CND_DISTDIR)/simple ../simple.c $(CND_DISTDIR)/simple.$(CND_DLIB_EXT)

$(OBJECTDIR)/simple_api.o: $(SOURCE_DIR)/simple_api.c
	mkdir -p ../dist/build
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_api.c
	mv simple_api.o $(OBJECTDIR)

$(OBJECTDIR)/simple_codegen.o: $(SOURCE_DIR)/simple_codegen.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_codegen.c
	mv simple_codegen.o $(OBJECTDIR)

$(OBJECTDIR)/simple_expr.o: $(SOURCE_DIR)/simple_expr.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_expr.c
	mv simple_expr.o $(OBJECTDIR)

$(OBJECTDIR)/simple_hashtable.o: $(SOURCE_DIR)/simple_hashtable.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_hashtable.c
	mv simple_hashtable.o $(OBJECTDIR)

$(OBJECTDIR)/simple_item.o: $(SOURCE_DIR)/simple_item.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_item.c
	mv simple_item.o $(OBJECTDIR)

$(OBJECTDIR)/simple_list.o: $(SOURCE_DIR)/simple_list.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_list.c
	mv simple_list.o $(OBJECTDIR)

$(OBJECTDIR)/simple_misc.o: $(SOURCE_DIR)/simple_misc.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_misc.c
	mv simple_misc.o $(OBJECTDIR)

$(OBJECTDIR)/simple_parser.o: $(SOURCE_DIR)/simple_parser.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_parser.c
	mv simple_parser.o $(OBJECTDIR)

$(OBJECTDIR)/simple_scanner.o: $(SOURCE_DIR)/simple_scanner.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_scanner.c
	mv simple_scanner.o $(OBJECTDIR)

$(OBJECTDIR)/simple_state.o: $(SOURCE_DIR)/simple_state.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_state.c
	mv simple_state.o $(OBJECTDIR)

$(OBJECTDIR)/simple_stmt.o: $(SOURCE_DIR)/simple_stmt.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_stmt.c
	mv simple_stmt.o $(OBJECTDIR)

$(OBJECTDIR)/simple_string.o: $(SOURCE_DIR)/simple_string.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_string.c
	mv simple_string.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vm.o: $(SOURCE_DIR)/simple_vm.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vm.c
	mv simple_vm.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmblock.o: $(SOURCE_DIR)/simple_vmblock.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmblock.c
	mv simple_vmblock.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmdll.o: $(SOURCE_DIR)/simple_vmdll.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmdll.c
	mv simple_vmdll.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmexpr.o: $(SOURCE_DIR)/simple_vmexpr.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmexpr.c
	mv simple_vmexpr.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmgc.o: $(SOURCE_DIR)/simple_vmgc.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmgc.c
	mv simple_vmgc.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmlists.o: $(SOURCE_DIR)/simple_vmlists.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmlists.c
	mv simple_vmlists.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmoop.o: $(SOURCE_DIR)/simple_vmoop.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmoop.c
	mv simple_vmoop.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmperformance.o: $(SOURCE_DIR)/simple_vmperformance.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmperformance.c
	mv simple_vmperformance.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmstackvars.o: $(SOURCE_DIR)/simple_vmstackvars.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmstackvars.c
	mv simple_vmstackvars.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmstate.o: $(SOURCE_DIR)/simple_vmstate.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmstate.c
	mv simple_vmstate.o $(OBJECTDIR)

$(OBJECTDIR)/simple_vmstrindex.o: $(SOURCE_DIR)/simple_vmstrindex.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmstrindex.c
	mv simple_vmstrindex.o $(OBJECTDIR)

$(OBJECTDIR)/simple.o: $(SOURCE_DIR)/simple.c
	$(CC) $(CFLAGS) ../simple.c
	mv simple.o $(OBJECTDIR)
	
$(OBJECTDIR)/simple_vmvars.o: $(SOURCE_DIR)/simple_vmvars.c
	$(CC) $(CFLAGS) $(SOURCE_DIR)/simple_vmvars.c
	mv simple_vmvars.o $(OBJECTDIR)

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
